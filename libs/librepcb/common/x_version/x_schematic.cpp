#include "x_schematic.h"

#include <librepcb/project/project.h>
#include <librepcb/project/schematics/schematicselectionquery.h>

#include <librepcb/common/application.h>
#include <librepcb/common/fileio/sexpression.h>
#include <librepcb/common/graphics/graphicsscene.h>
#include <librepcb/common/graphics/graphicsview.h>
#include <librepcb/common/gridproperties.h>
#include <librepcb/common/scopeguardlist.h>
#include <librepcb/library/sym/symbolpin.h>

/*******************************************************************************
 *  Namespace
 ******************************************************************************/
namespace librepcb {

namespace x_version {

/*******************************************************************************
 *  Constructors / Destructor
 ******************************************************************************/

X_Schematic::X_Schematic(Project&                                project,
                     std::unique_ptr<TransactionalDirectory> directory,
                     bool create, const QString& newName)
  : QObject(&project),
    AttributeProvider(),
    mProject(project),
    mDirectory(std::move(directory)),
    mIsAddedToProject(false),
    mUuid(Uuid::createRandom()),
    mName("New Page") {
  try {
    // try to open/create the schematic file
    if (create) {
      // set attributes
      mName = newName;

      // load default grid properties
      mGridProperties.reset(new GridProperties());
    } else {
      SExpression root = SExpression::parse(
          mDirectory->read(getFilePath().getFilename()), getFilePath());

      // the schematic seems to be ready to open, so we will create all needed
      // objects

      mUuid = root.getChildByIndex(0).getValue<Uuid>();
      mName = root.getValueByPath<ElementName>("name");

      // Load grid properties
      mGridProperties.reset(new GridProperties(root.getChildByPath("grid")));

      // Load all symbols
      foreach (const SExpression& node, root.getChildren("symbol")) {
        SI_Symbol* symbol = new SI_Symbol(*this, node);
        if (getSymbolByUuid(symbol->getUuid())) {
          throw RuntimeError(
              __FILE__, __LINE__,
              QString(tr("There is already a symbol with the UUID \"%1\"!"))
                  .arg(symbol->getUuid().toStr()));
        }
        mSymbols.append(symbol);
      }

      // Load all netsegments
      foreach (const SExpression& node, root.getChildren("netsegment")) {
        SI_NetSegment* netsegment = new SI_NetSegment(*this, node);
        if (getNetSegmentByUuid(netsegment->getUuid())) {
          throw RuntimeError(
              __FILE__, __LINE__,
              QString(tr("There is already a netsegment with the UUID \"%1\"!"))
                  .arg(netsegment->getUuid().toStr()));
        }
        mNetSegments.append(netsegment);
      }
    }

    // emit the "attributesChanged" signal when the project has emited it
    connect(&mProject, &Project::attributesChanged, this,
            &X_Schematic::attributesChanged);
  } catch (...) {
    // free the allocated memory in the reverse order of their allocation...
    qDeleteAll(mNetSegments);
    mNetSegments.clear();
    qDeleteAll(mSymbols);
    mSymbols.clear();
    mGridProperties.reset();
    mGraphicsScene.reset();
    throw;  // ...and rethrow the exception
  }
}

X_Schematic::~X_Schematic() noexcept {
  Q_ASSERT(!mIsAddedToProject);

  // delete all items
  qDeleteAll(mNetSegments);
  mNetSegments.clear();
  qDeleteAll(mSymbols);
  mSymbols.clear();

  mGridProperties.reset();
  mGraphicsScene.reset();
}

/*******************************************************************************
 *  Getters: General
 ******************************************************************************/

FilePath X_Schematic::getFilePath() const noexcept {
  return mDirectory->getAbsPath("schematic.lp");
}

bool X_Schematic::isEmpty() const noexcept {
  return (mSymbols.isEmpty() && mNetSegments.isEmpty());
}

/*******************************************************************************
 *  Setters: General
 ******************************************************************************/

void X_Schematic::setGridProperties(const GridProperties& grid) noexcept {
  *mGridProperties = grid;
}

/*******************************************************************************
 *  Symbol Methods
 ******************************************************************************/

SI_Symbol* X_Schematic::getSymbolByUuid(const Uuid& uuid) const noexcept {
  foreach (SI_Symbol* symbol, mSymbols) {
    if (symbol->getUuid() == uuid) return symbol;
  }
  return nullptr;
}

void X_Schematic::addSymbol(SI_Symbol& symbol) {
  if ((!mIsAddedToProject) || (mSymbols.contains(&symbol)) ||
      (&symbol.getSchematic() != this)) {
    throw LogicError(__FILE__, __LINE__);
  }
  // check if there is no symbol with the same uuid in the list
  if (getSymbolByUuid(symbol.getUuid())) {
    throw RuntimeError(
        __FILE__, __LINE__,
        QString(tr("There is already a symbol with the UUID \"%1\"!"))
            .arg(symbol.getUuid().toStr()));
  }
  // add to schematic
  symbol.addToSchematic();  // can throw
  mSymbols.append(&symbol);
}

void X_Schematic::removeSymbol(SI_Symbol& symbol) {
  if ((!mIsAddedToProject) || (!mSymbols.contains(&symbol))) {
    throw LogicError(__FILE__, __LINE__);
  }
  // remove from schematic
  symbol.removeFromSchematic();  // can throw
  mSymbols.removeOne(&symbol);
}

/*******************************************************************************
 *  NetSegment Methods
 ******************************************************************************/

SI_NetSegment* X_Schematic::getNetSegmentByUuid(const Uuid& uuid) const noexcept {
  foreach (SI_NetSegment* netsegment, mNetSegments) {
    if (netsegment->getUuid() == uuid) return netsegment;
  }
  return nullptr;
}

void X_Schematic::addNetSegment(SI_NetSegment& netsegment) {
  if ((!mIsAddedToProject) || (mNetSegments.contains(&netsegment)) ||
      (&netsegment.getSchematic() != this)) {
    throw LogicError(__FILE__, __LINE__);
  }
  // check if there is no netsegment with the same uuid in the list
  if (getNetSegmentByUuid(netsegment.getUuid())) {
    throw RuntimeError(
        __FILE__, __LINE__,
        QString(tr("There is already a netsegment with the UUID \"%1\"!"))
            .arg(netsegment.getUuid().toStr()));
  }
  // add to schematic
  netsegment.addToSchematic();  // can throw
  mNetSegments.append(&netsegment);
}

void X_Schematic::removeNetSegment(SI_NetSegment& netsegment) {
  if ((!mIsAddedToProject) || (!mNetSegments.contains(&netsegment))) {
    throw LogicError(__FILE__, __LINE__);
  }
  // remove from schematic
  netsegment.removeFromSchematic();  // can throw
  mNetSegments.removeOne(&netsegment);
}

/*******************************************************************************
 *  General Methods
 ******************************************************************************/

void X_Schematic::addToProject() {
  if (mIsAddedToProject) {
    throw LogicError(__FILE__, __LINE__);
  }

  ScopeGuardList sgl(mSymbols.count() + mNetSegments.count());
  foreach (SI_Symbol* symbol, mSymbols) {
    symbol->addToSchematic();  // can throw
    sgl.add([symbol]() { symbol->removeFromSchematic(); });
  }
  foreach (SI_NetSegment* segment, mNaetSegments) {
    segment->addToSchematic();  // can throw
    sgl.add([segment]() { segment->removeFromSchematic(); });
  }

  mIsAddedToProject = true;
  updateIcon();
  sgl.dismiss();
}

void X_Schematic::removeFromProject() {
  if (!mIsAddedToProject) {
    throw LogicError(__FILE__, __LINE__);
  }

  ScopeGuardList sgl(mSymbols.count() + mNetSegments.count());
  foreach (SI_NetSegment* segment, mNetSegments) {
    segment->removeFromSchematic();  // can throw
    sgl.add([segment]() { segment->addToSchematic(); });
  }
  foreach (SI_Symbol* symbol, mSymbols) {
    symbol->removeFromSchematic();  // can throw
    sgl.add([symbol]() { symbol->addToSchematic(); });
  }

  mIsAddedToProject = false;
  sgl.dismiss();
}

void X_Schematic::save() {
  if (mIsAddedToProject) {
    // save schematic file
    SExpression doc(serializeToDomElement("librepcb_schematic"));  // can throw
    mDirectory->write(getFilePath().getFilename(),
                      doc.toByteArray());  // can throw
  } else {
    mDirectory->removeDirRecursively();  // can throw
  }
}

/*******************************************************************************
 *  Inherited from AttributeProvider
 ******************************************************************************/

QString X_Schematic::getBuiltInAttributeValue(const QString& key) const noexcept {
  if (key == QLatin1String("SHEET")) {
    return *mName;
  } else if (key == QLatin1String("PAGE")) {
    return QString::number(mProject.getSchematicIndex(*this) + 1);
  } else {
    return QString();
  }
}

QVector<const AttributeProvider*> X_Schematic::getAttributeProviderParents() const
    noexcept {
  return QVector<const AttributeProvider*>{&mProject};
}

/*******************************************************************************
 *  Private Methods
 ******************************************************************************/
/*
void X_Schematic::serialize(SExpression& root) const {
  root.appendChild(mUuid);
  root.appendChild("name", mName, true);
  root.appendChild(mGridProperties->serializeToDomElement("grid"), true);
  root.appendLineBreak();
  serializePointerContainerUuidSorted(root, mSymbols, "symbol");
  root.appendLineBreak();
  serializePointerContainerUuidSorted(root, mNetSegments, "netsegment");
  root.appendLineBreak();
}
*/
/*******************************************************************************
 *  Static Methods
 ******************************************************************************/

X_Schematic* X_Schematic::create(Project&                                project,
                             std::unique_ptr<TransactionalDirectory> directory,
                             const ElementName&                      name) {
  return new X_Schematic(project, std::move(directory), true, *name);
}

/*******************************************************************************
 *  End of File
 ******************************************************************************/

} // namespace x_version
} // namespace librepcb
