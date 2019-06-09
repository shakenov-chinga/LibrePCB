#include "x_board.h"

#include "xb_baseitem.h"
#include "xb_circle.h"
#include "xb_device.h"
#include "xb_footprint.h"
#include "xb_hole.h"
#include "xb_line.h"
#include "xb_padpth.h"
#include "xb_padsmd.h"
#include "xb_path.h"
#include "xb_polygon.h"
#include "xb_text.h"
#include "xb_via.h"

#include <librepcb/project/circuit/circuit.h>
#include <librepcb/project/circuit/componentinstance.h>
#include <librepcb/project/circuit/netsignal.h>
#include <librepcb/project/erc/ercmsg.h>
#include <librepcb/project/project.h>
#include <librepcb/project/boards/boardairwiresbuilder.h>
#include <librepcb/project/boards/boardfabricationoutputsettings.h>
#include <librepcb/project/boards/boardlayerstack.h>
#include <librepcb/project/boards/boardselectionquery.h>
#include <librepcb/project/boards/boardusersettings.h>

#include <librepcb/common/application.h>
#include <librepcb/common/boarddesignrules.h>
#include <librepcb/common/fileio/sexpression.h>
#include <librepcb/common/geometry/polygon.h>
#include <librepcb/common/graphics/graphicsscene.h>
#include <librepcb/common/graphics/graphicsview.h>
#include <librepcb/common/gridproperties.h>
#include <librepcb/common/scopeguardlist.h>
#include <librepcb/library/cmp/component.h>
#include <librepcb/library/pkg/footprint.h>

#include <QtCore>

namespace librepcb {

using namespace project;

namespace x_version {

/*******************************************************************************
 *  Constructors / Destructor
 ******************************************************************************/

X_Board::X_Board(const X_Board&                          other,
                 std::unique_ptr<TransactionalDirectory> directory,
                 const ElementName&                      name)
  : QObject(&other.getProject()),
    mProject(other.getProject()),
    mDirectory(std::move(directory)),
    mIsAddedToProject(false),
    mUuid(Uuid::createRandom()),
    mName(name),
    mDefaultFontFileName(other.mDefaultFontFileName) {
  try {
    // copy layer stack
    mLayerStack.reset(new BoardLayerStack(*this, *other.mLayerStack));

    // copy grid properties
    mGridProperties.reset(new GridProperties(*other.mGridProperties));

    // copy design rules
    mDesignRules.reset(new BoardDesignRules(*other.mDesignRules));

    // copy fabrication output settings
    mFabricationOutputSettings.reset(
        new BoardFabricationOutputSettings(*other.mFabricationOutputSettings));

    // copy user settings
    mUserSettings.reset(new BoardUserSettings(*this, *other.mUserSettings));

    // copy device instances
    QHash<const XB_Device*, XB_Device*> copiedDeviceInstances;
    foreach (const XB_Device* device, other.mDeviceInstances) {
      XB_Device* copy = new XB_Device(*this, *device);
      Q_ASSERT(
          !getDeviceInstanceByComponentUuid(copy->getComponentInstanceUuid()));
      mDeviceInstances.insert(copy->getComponentInstanceUuid(), copy);
      copiedDeviceInstances.insert(device, copy);
    }

    // copy netsegments
    foreach (const XB_Path* path, other.mPaths) {
      XB_Path* copy =
          new XB_Path(*this, *path, copiedDeviceInstances);
      Q_ASSERT(!getPathByUuid(copy->getUuid()));
      mPaths.append(copy);
    }

    // copy polygons
    foreach (const XB_Polygon* polygon, other.mPolygons) {
      XB_Polygon* copy = new XB_Polygon(*this, *polygon);
      mPolygons.append(copy);
    }

    // copy stroke texts
    foreach (const XB_Text* text, other.mTexts) {
      XB_Text* copy = new XB_Text(*this, *text);
      mTexts.append(copy);
    }

    // copy holes
    foreach (const XB_Hole* hole, other.mHoles) {
      XB_Hole* copy = new XB_Hole(*this, *hole);
      mHoles.append(copy);
    }

    // rebuildAllPlanes(); --> fragments are copied too, so no need to rebuild
    // them
    updateErcMessages();
    updateIcon();

    // emit the "attributesChanged" signal when the project has emited it
    connect(&mProject, &Project::attributesChanged, this,
            &X_Board::attributesChanged);

    connect(&mProject.getCircuit(), &Circuit::componentAdded, this,
            &X_Board::updateErcMessages);
    connect(&mProject.getCircuit(), &Circuit::componentRemoved, this,
            &X_Board::updateErcMessages);
  } catch (...) {
    // free the allocated memory in the reverse order of their allocation...
    qDeleteAll(mErcMsgListUnplacedComponentInstances);
    mErcMsgListUnplacedComponentInstances.clear();
    qDeleteAll(mHoles);
    mHoles.clear();
    qDeleteAll(mTexts);
    mTexts.clear();
    qDeleteAll(mPolygons);
    mPolygons.clear();
    qDeleteAll(mPaths);
    mPaths.clear();
    qDeleteAll(mDeviceInstances);
    mDeviceInstances.clear();
    mUserSettings.reset();
    mFabricationOutputSettings.reset();
    mDesignRules.reset();
    mGridProperties.reset();
    mLayerStack.reset();
    throw;  // ...and rethrow the exception
  }
}

X_Board::X_Board(Project&                                project,
             std::unique_ptr<TransactionalDirectory> directory, bool create,
             const QString& newName)
  : QObject(&project),
    mProject(project),
    mDirectory(std::move(directory)),
    mIsAddedToProject(false),
    mUuid(Uuid::createRandom()),
    mName("New X_Board") {
  try {

    // try to open/create the board file
    if (create) {
      // set attributes
      mName                = newName;
      mDefaultFontFileName = qApp->getDefaultStrokeFontName();

      // load default layer stack
      mLayerStack.reset(new BoardLayerStack(*this));

      // load default grid properties (smaller grid than in schematics to avoid
      // grid snap issues)
      mGridProperties.reset(new GridProperties(GridProperties::Type_t::Lines,
                                               PositiveLength(635000),
                                               LengthUnit::millimeters()));

      // load default design rules
      mDesignRules.reset(new BoardDesignRules());

      // load default fabrication output settings
      mFabricationOutputSettings.reset(new BoardFabricationOutputSettings());

      // load default user settings
      mUserSettings.reset(new BoardUserSettings(*this));

      // add 100x80mm board outline (1/2 Eurocard size)
      Polygon polygon(Uuid::createRandom(),
                      GraphicsLayerName(GraphicsLayer::sBoardOutlines),
                      UnsignedLength(0), false, false,
                      Path::rect(Point(0, 0), Point(100000000, 80000000)));
      mPolygons.append(new XB_Polygon(*this, polygon));
    } else {
      SExpression root = SExpression::parse(
          mDirectory->read(getFilePath().getFilename()), getFilePath());

      // the board seems to be ready to open, so we will create all needed
      // objects

      mUuid = root.getChildByIndex(0).getValue<Uuid>();
      mName = root.getValueByPath<ElementName>("name");
      if (const SExpression* child = root.tryGetChildByPath("default_font")) {
        mDefaultFontFileName = child->getValueOfFirstChild<QString>(true);
      } else {
        mDefaultFontFileName = qApp->getDefaultStrokeFontName();
      }

      // Load grid properties
      mGridProperties.reset(new GridProperties(root.getChildByPath("grid")));

      // Load layer stack
      mLayerStack.reset(
          new BoardLayerStack(*this, root.getChildByPath("layers")));

      // load design rules
      mDesignRules.reset(
          new BoardDesignRules(root.getChildByPath("design_rules")));

      // load fabrication output settings
      mFabricationOutputSettings.reset(new BoardFabricationOutputSettings(
          root.getChildByPath("fabrication_output_settings")));

      // load user settings
      try {
        QString     userSettingsFp = "settings.user.lp";
        SExpression userSettingsRoot =
            SExpression::parse(mDirectory->read(userSettingsFp),
                               mDirectory->getAbsPath(userSettingsFp));
        mUserSettings.reset(new BoardUserSettings(*this, userSettingsRoot));
      } catch (const Exception&) {
        // Project user settings are normally not put under version control and
        // thus the likelyhood of parse errors is higher (e.g. when switching to
        // an older, now incompatible revision). To avoid frustration, we just
        // ignore these errors and load the default settings instead...
        qCritical() << "Could not open board user settings, defaults will be "
                       "used instead!";
        mUserSettings.reset(new BoardUserSettings(*this));
      }

      // Load all device instances
      foreach (const SExpression& node, root.getChildren("device")) {
        XB_Device* device = new XB_Device(*this, node);
        if (getDeviceInstanceByComponentUuid(
                device->getComponentInstanceUuid())) {
          throw RuntimeError(
              __FILE__, __LINE__,
              QString(tr("There is already a device of the component instance "
                         "\"%1\"!"))
                  .arg(device->getComponentInstanceUuid().toStr()));
        }
        mDeviceInstances.insert(device->getComponentInstanceUuid(), device);
      }

      // Load all netsegments
      foreach (const SExpression& node, root.getChildren("path")) {
        XB_Path* path = new XB_Path(*this, node);
        if (getPathByUuid(path->getUuid())) {
          throw RuntimeError(
              __FILE__, __LINE__,
              QString(tr("There is already a path with the UUID \"%1\"!"))
                  .arg(path->getUuid().toStr()));
        }
        mPaths.append(path);
      }

      // Load all planes
      foreach (const SExpression& node, root.getChildren("plane")) {
        BI_Plane* plane = new BI_Plane(*this, node);
        mPlanes.append(plane);
      }

      // Load all polygons
      foreach (const SExpression& node, root.getChildren("polygon")) {
        XB_Polygon* polygon = new XB_Polygon(*this, node);
        mPolygons.append(polygon);
      }

      // Load all stroke texts
      foreach (const SExpression& node, root.getChildren("stroke_text")) {
        XB_Text* text = new XB_Text(*this, node);
        mTexts.append(text);
      }

      // Load all holes
      foreach (const SExpression& node, root.getChildren("hole")) {
        XB_Hole* hole = new XB_Hole(*this, node);
        mHoles.append(hole);
      }
    }

    rebuildAllPlanes();
    updateErcMessages();
    updateIcon();

    // emit the "attributesChanged" signal when the project has emited it
    connect(&mProject, &Project::attributesChanged, this,
            &X_Board::attributesChanged);

    connect(&mProject.getCircuit(), &Circuit::componentAdded, this,
            &X_Board::updateErcMessages);
    connect(&mProject.getCircuit(), &Circuit::componentRemoved, this,
            &X_Board::updateErcMessages);
  } catch (...) {
    // free the allocated memory in the reverse order of their allocation...
    qDeleteAll(mErcMsgListUnplacedComponentInstances);
    mErcMsgListUnplacedComponentInstances.clear();
    qDeleteAll(mHoles);
    mHoles.clear();
    qDeleteAll(mTexts);
    mTexts.clear();
    qDeleteAll(mPolygons);
    mPolygons.clear();
    qDeleteAll(mPaths);
    mPaths.clear();
    qDeleteAll(mDeviceInstances);
    mDeviceInstances.clear();
    mUserSettings.reset();
    mFabricationOutputSettings.reset();
    mDesignRules.reset();
    mGridProperties.reset();
    mLayerStack.reset();
    throw;  // ...and rethrow the exception
  }
}

X_Board::~X_Board() noexcept {
  Q_ASSERT(!mIsAddedToProject);

  qDeleteAll(mErcMsgListUnplacedComponentInstances);
  mErcMsgListUnplacedComponentInstances.clear();

  // delete all items
  qDeleteAll(mHoles);
  mHoles.clear();
  qDeleteAll(mTexts);
  mTexts.clear();
  qDeleteAll(mPolygons);
  mPolygons.clear();
  qDeleteAll(mPaths);
  mPaths.clear();
  qDeleteAll(mDeviceInstances);
  mDeviceInstances.clear();

  mUserSettings.reset();
  mFabricationOutputSettings.reset();
  mDesignRules.reset();
  mGridProperties.reset();
  mLayerStack.reset();
}

/*******************************************************************************
 *  Getters: General
 ******************************************************************************/

FilePath X_Board::getFilePath() const noexcept {
  return mDirectory->getAbsPath("board.lp");
}

bool X_Board::isEmpty() const noexcept {
  return (mDeviceInstances.isEmpty() && mPaths.isEmpty() && mPolygons.isEmpty()
          && mTexts.isEmpty() && mHoles.isEmpty());
}

QList<XB_BaseItem*> X_Board::getAllItems() const noexcept {
  QList<XB_BaseItem*> items;
  foreach (XB_Device* device, mDeviceInstances)
    items.append(device);
  foreach (XB_Path* path, mPaths)
    items.append(path);
  foreach (XB_Polygon* polygon, mPolygons)
    items.append(polygon);
  foreach (XB_Text* text, mTexts)
    items.append(text);
  foreach (XB_Hole* hole, mHoles)
    items.append(hole);
  return items;
}

/*******************************************************************************
 *  Setters: General
 ******************************************************************************/

void X_Board::setGridProperties(const GridProperties& grid) noexcept {
  *mGridProperties = grid;
}

/*******************************************************************************
 *  DeviceInstance Methods
 ******************************************************************************/

XB_Device* X_Board::getDeviceInstanceByComponentUuid(const Uuid& uuid) const
    noexcept {
  return mDeviceInstances.value(uuid, nullptr);
}

void X_Board::addDeviceInstance(XB_Device& instance) {
  if ((!mIsAddedToProject) || (&instance.getBoard() != this)) {
    throw LogicError(__FILE__, __LINE__);
  }
  // check if there is no device with the same component instance in the list
  if (getDeviceInstanceByComponentUuid(
          instance.getComponentInstance().getUuid())) {
    throw RuntimeError(
        __FILE__, __LINE__,
        QString(
            tr("There is already a device with the component instance \"%1\"!"))
            .arg(instance.getComponentInstance().getUuid().toStr()));
  }
  // add to board
  instance.addToBoard();  // can throw
  mDeviceInstances.insert(instance.getComponentInstanceUuid(), &instance);
  updateErcMessages();
  emit deviceAdded(instance);
}

void X_Board::removeDeviceInstance(XB_Device& instance) {
  if ((!mIsAddedToProject) ||
      (!mDeviceInstances.contains(instance.getComponentInstanceUuid()))) {
    throw LogicError(__FILE__, __LINE__);
  }
  // remove from board
  instance.removeFromBoard();  // can throw
  mDeviceInstances.remove(instance.getComponentInstanceUuid());
  updateErcMessages();
  emit deviceRemoved(instance);
}

/*******************************************************************************
 *  NetSegment Methods
 ******************************************************************************/

XB_Path* X_Board::getPathByUuid(const Uuid& uuid) const noexcept {
  foreach (XB_Path* path, mPaths) {
    if (path->getUuid() == uuid) return path;
  }
  return nullptr;
}

void X_Board::addPath(XB_Path& path) {
  if ((!mIsAddedToProject) || (mPaths.contains(&path)) ||
      (&path.getBoard() != this)) {
    throw LogicError(__FILE__, __LINE__);
  }
  // check if there is no path with the same uuid in the list
  if (getPathByUuid(path.getUuid())) {
    throw RuntimeError(
        __FILE__, __LINE__,
        QString(tr("There is already a path with the UUID \"%1\"!"))
            .arg(path.getUuid().toStr()));
  }
  // add to board
  path.addToBoard();  // can throw
  mPaths.append(&path);
}

void X_Board::removePath(XB_Path& path) {
  if ((!mIsAddedToProject) || (!mPaths.contains(&path))) {
    throw LogicError(__FILE__, __LINE__);
  }
  // remove from board
  path.removeFromBoard();  // can throw
  mPaths.removeOne(&path);
}

/*******************************************************************************
 *  Polygon Methods
 ******************************************************************************/

void X_Board::addPolygon(XB_Polygon& polygon) {
  if ((!mIsAddedToProject) || (mPolygons.contains(&polygon)) ||
      (&polygon.getBoard() != this)) {
    throw LogicError(__FILE__, __LINE__);
  }
  polygon.addToBoard();  // can throw
  mPolygons.append(&polygon);
}

void X_Board::removePolygon(XB_Polygon& polygon) {
  if ((!mIsAddedToProject) || (!mPolygons.contains(&polygon))) {
    throw LogicError(__FILE__, __LINE__);
  }
  polygon.removeFromBoard();  // can throw
  mPolygons.removeOne(&polygon);
}

/*******************************************************************************
 *  StrokeText Methods
 ******************************************************************************/

void X_Board::addStrokeText(XB_Text& text) {
  if ((!mIsAddedToProject) || (mTexts.contains(&text)) ||
      (&text.getBoard() != this)) {
    throw LogicError(__FILE__, __LINE__);
  }
  text.addToBoard();  // can throw
  mTexts.append(&text);
}

void X_Board::removeStrokeText(XB_Text& text) {
  if ((!mIsAddedToProject) || (!mTexts.contains(&text))) {
    throw LogicError(__FILE__, __LINE__);
  }
  text.removeFromBoard();  // can throw
  mTexts.removeOne(&text);
}

/*******************************************************************************
 *  Hole Methods
 ******************************************************************************/

void X_Board::addHole(XB_Hole& hole) {
  if ((!mIsAddedToProject) || (mHoles.contains(&hole)) ||
      (&hole.getBoard() != this)) {
    throw LogicError(__FILE__, __LINE__);
  }
  hole.addToBoard();  // can throw
  mHoles.append(&hole);
}

void X_Board::removeHole(XB_Hole& hole) {
  if ((!mIsAddedToProject) || (!mHoles.contains(&hole))) {
    throw LogicError(__FILE__, __LINE__);
  }
  hole.removeFromBoard();  // can throw
  mHoles.removeOne(&hole);
}

/*******************************************************************************
 *  General Methods
 ******************************************************************************/

void X_Board::addToProject() {
//  if (mIsAddedToProject) {
//    throw LogicError(__FILE__, __LINE__);
//  }
//  QList<XB_BaseItem*> items = getAllItems();
//  ScopeGuardList  sgl(items.count());
//  for (int i = 0; i < items.count(); ++i) {
//    XB_BaseItem* item = items.at(i);
//    item->addToBoard();  // can throw
//    sgl.add([item]() { item->removeFromBoard(); });
//  }
//  mIsAddedToProject = true;
//  updateErcMessages();
//  sgl.dismiss();
}

void X_Board::removeFromProject() {
//  if (!mIsAddedToProject) {
//    throw LogicError(__FILE__, __LINE__);
//  }
//  QList<XB_BaseItem*> items = getAllItems();
//  ScopeGuardList  sgl(items.count());
//  for (int i = items.count() - 1; i >= 0; --i) {
//    XB_BaseItem* item = items.at(i);
//    item->removeFromBoard();  // can throw
//    sgl.add([item]() { item->addToBoard(); });
//  }
//  mIsAddedToProject = false;
//  updateErcMessages();
//  sgl.dismiss();
}

void X_Board::save() {
  if (mIsAddedToProject) {
    // save board file
    SExpression brdDoc(serializeToDomElement("librepcb_board"));  // can throw
    mDirectory->write(getFilePath().getFilename(),
                      brdDoc.toByteArray());  // can throw

    // save user settings
    SExpression usrDoc(mUserSettings->serializeToDomElement(
        "librepcb_board_user_settings"));                         // can throw
    mDirectory->write("settings.user.lp", usrDoc.toByteArray());  // can throw
  } else {
    mDirectory->removeDirRecursively();  // can throw
  }
}

/*******************************************************************************
 *  Inherited from AttributeProvider
 ******************************************************************************/

QString X_Board::getBuiltInAttributeValue(const QString& key) const noexcept {
  if (key == QLatin1String("BOARD")) {
    return *mName;
  } else {
    return QString();
  }
}

QVector<const AttributeProvider*> X_Board::getAttributeProviderParents() const
    noexcept {
  return QVector<const AttributeProvider*>{&mProject};
}

/*******************************************************************************
 *  Private Methods
 ******************************************************************************/

void X_Board::serialize(SExpression& root) const {
  root.appendChild(mUuid);
  root.appendChild("name", mName, true);
  root.appendChild("default_font", mDefaultFontFileName, true);
  root.appendChild(mGridProperties->serializeToDomElement("grid"), true);
  root.appendChild(mLayerStack->serializeToDomElement("layers"), true);
  root.appendChild(mDesignRules->serializeToDomElement("design_rules"), true);
  root.appendChild(mFabricationOutputSettings->serializeToDomElement(
                       "fabrication_output_settings"),
                   true);
  root.appendLineBreak();
  serializePointerContainer(root, mDeviceInstances, "device");
  root.appendLineBreak();
  serializePointerContainerUuidSorted(root, mPaths, "path");
  root.appendLineBreak();
  serializePointerContainerUuidSorted(root, mPolygons, "polygon");
  root.appendLineBreak();
  serializePointerContainerUuidSorted(root, mTexts, "text");
  root.appendLineBreak();
  serializePointerContainerUuidSorted(root, mHoles, "hole");
  root.appendLineBreak();
}

void X_Board::updateErcMessages() noexcept {
  // type: UnplacedComponent (ComponentInstances without DeviceInstance)
  if (mIsAddedToProject) {
    const QMap<Uuid, ComponentInstance*>& componentInstances =
        mProject.getCircuit().getComponentInstances();
    foreach (const ComponentInstance* component, componentInstances) {
      if (component->getLibComponent().isSchematicOnly()) continue;
      XB_Device* device = mDeviceInstances.value(component->getUuid());
      ErcMsg*    ercMsg =
          mErcMsgListUnplacedComponentInstances.value(component->getUuid());
      if ((!device) && (!ercMsg)) {
        ErcMsg* ercMsg = new ErcMsg(
            mProject, *this,
            QString("%1/%2").arg(mUuid.toStr(), component->getUuid().toStr()),
            "UnplacedComponent", ErcMsg::ErcMsgType_t::BoardError,
            QString("Unplaced Component: %1 (X_Board: %2)")
                .arg(*component->getName(), *mName));
        ercMsg->setVisible(true);
        mErcMsgListUnplacedComponentInstances.insert(component->getUuid(),
                                                     ercMsg);
      } else if ((device) && (ercMsg)) {
        delete mErcMsgListUnplacedComponentInstances.take(component->getUuid());
      }
    }
    foreach (const Uuid& uuid, mErcMsgListUnplacedComponentInstances.keys()) {
      if (!componentInstances.contains(uuid))
        delete mErcMsgListUnplacedComponentInstances.take(uuid);
    }
  } else {
    qDeleteAll(mErcMsgListUnplacedComponentInstances);
    mErcMsgListUnplacedComponentInstances.clear();
  }
}

/*******************************************************************************
 *  Static Methods
 ******************************************************************************/

X_Board* X_Board::create(Project&                                project,
                     std::unique_ptr<TransactionalDirectory> directory,
                     const ElementName&                      name) {
  return new X_Board(project, std::move(directory), true, *name);
}

/*******************************************************************************
 *  End of File
 ******************************************************************************/

} // namespace x_version
} // namespace librepcb
