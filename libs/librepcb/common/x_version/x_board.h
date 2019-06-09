#ifndef LIBREPCB_X_VERSION_X_BOARD_H
#define LIBREPCB_X_VERSION_X_BOARD_H
/*******************************************************************************
 *  Includes
 ******************************************************************************/
#include "../../project/erc/if_ercmsgprovider.h"

#include <librepcb/common/attributes/attributeprovider.h>
#include <librepcb/common/elementname.h>
#include <librepcb/common/exceptions.h>
#include <librepcb/common/fileio/filepath.h>
#include <librepcb/common/fileio/serializableobject.h>
#include <librepcb/common/fileio/transactionaldirectory.h>
#include <librepcb/common/units/all_length_units.h>
#include <librepcb/common/uuid.h>

#include <QtCore>
#include <QtWidgets>

#include <memory>

/*******************************************************************************
 *  Namespace / Forward Declarations
 ******************************************************************************/

namespace librepcb {

class GridProperties;
class BoardDesignRules;

namespace project{
class Project;
class NetSignal;
class BoardLayerStack;
class BoardFabricationOutputSettings;
class BoardUserSettings;
}
using namespace project;

namespace x_version {
class XB_BaseItem;
class XB_Device;
class XB_Path;
class XB_Polygon;
class XB_Text;
class XB_Hole;

class X_Board final : public QObject,
                      public AttributeProvider,
                      public IF_ErcMsgProvider,
                      public SerializableObject {
  Q_OBJECT
  DECLARE_ERC_MSG_CLASS_NAME(X_Board)

public:
  // Constructors / Destructor
  X_Board()                     = delete;
  X_Board(const X_Board& other) = delete;
  X_Board(const X_Board& other,
          std::unique_ptr<TransactionalDirectory> directory,
          const ElementName& name);
  X_Board(Project& project, std::unique_ptr<TransactionalDirectory> directory)
    : X_Board(project, std::move(directory), false, QString()) {}
  ~X_Board() noexcept;

  // Getters: General
  Project&              getProject() const noexcept { return mProject; }
  FilePath              getFilePath() const noexcept;
  const GridProperties& getGridProperties() const noexcept {
    return *mGridProperties;
  }
  BoardLayerStack& getLayerStack() noexcept { return *mLayerStack; }
  const BoardLayerStack& getLayerStack() const noexcept { return *mLayerStack; }
  BoardDesignRules&      getDesignRules() noexcept { return *mDesignRules; }
  const BoardDesignRules& getDesignRules() const noexcept {
    return *mDesignRules;
  }
  BoardFabricationOutputSettings& getFabricationOutputSettings() noexcept {
    return *mFabricationOutputSettings;
  }
  const BoardFabricationOutputSettings& getFabricationOutputSettings() const
      noexcept {
    return *mFabricationOutputSettings;
  }

  QList<XB_BaseItem*> getAllItems() const noexcept;
  bool                isEmpty() const noexcept;

  // Setters: General
  void setGridProperties(const GridProperties& grid) noexcept;

  // Getters: Attributes
  const Uuid&        getUuid() const noexcept { return mUuid; }
  const ElementName& getName() const noexcept { return mName; }
  const QString&     getDefaultFontName() const noexcept {
    return mDefaultFontFileName;
  }

  // DeviceInstance Methods
  const QMap<Uuid, XB_Device*>& getDeviceInstances() const noexcept {
    return mDeviceInstances;
  }
  XB_Device* getDeviceInstanceByComponentUuid(const Uuid& uuid) const noexcept;
  void       addDeviceInstance(XB_Device& instance);
  void       removeDeviceInstance(XB_Device& instance);

  // NetSegment Methods
  const QList<XB_Path*>& getPaths() const noexcept {
    return mPaths;
  }
  XB_Path* getPathByUuid(const Uuid& uuid) const noexcept;
  void     addPath(XB_Path& path);
  void     removePath(XB_Path& path);

  // Polygon Methods
  const QList<XB_Polygon*>& getPolygons() const noexcept {
    return mPolygons;
  }
  void                      addPolygon(XB_Polygon& polygon);
  void                      removePolygon(XB_Polygon& polygon);
  void                      rebuildAllPolygon() noexcept;

  // StrokeText Methods
  const QList<XB_Text*>& getTexts() const noexcept {
    return mTexts;
  }
  void addText(XB_Text& text);
  void removeText(XB_Text& text);

  // Hole Methods
  const QList<XB_Hole*>& getHoles() const noexcept { return mHoles; }
  void                   addHole(XB_Hole& hole);
  void                   removeHole(XB_Hole& hole);

  // General Methods
  void addToProject();
  void removeFromProject();
  void save();

  // Inherited from AttributeProvider
  /// @copydoc librepcb::AttributeProvider::getBuiltInAttributeValue()
  QString getBuiltInAttributeValue(const QString& key) const noexcept override;
  /// @copydoc librepcb::AttributeProvider::getAttributeProviderParents()
  QVector<const AttributeProvider*> getAttributeProviderParents() const
      noexcept override;

  // Operator Overloadings
  X_Board& operator=(const X_Board& rhs) = delete;
  bool   operator==(const X_Board& rhs) noexcept { return (this == &rhs); }
  bool   operator!=(const X_Board& rhs) noexcept { return (this != &rhs); }

  // Static Methods
  static X_Board* create(Project&                                project,
                       std::unique_ptr<TransactionalDirectory> directory,
                       const ElementName&                      name);

signals:

  /// @copydoc AttributeProvider::attributesChanged()
  void attributesChanged() override;

  void deviceAdded(XB_Device& comp);
  void deviceRemoved(XB_Device& comp);

private:
  X_Board(Project& project, std::unique_ptr<TransactionalDirectory> directory,
        bool create, const QString& newName);
  void updateIcon() noexcept;
  void updateErcMessages() noexcept;

  /// @copydoc librepcb::SerializableObject::serialize()
   void serialize(SExpression& root) const override;

  // General
  Project& mProject;  ///< A reference to the Project object (from the ctor)
  std::unique_ptr<TransactionalDirectory> mDirectory;
  bool                                    mIsAddedToProject;

  QScopedPointer<BoardLayerStack>                mLayerStack;
  QScopedPointer<GridProperties>                 mGridProperties;
  QScopedPointer<BoardDesignRules>               mDesignRules;
  QScopedPointer<BoardFabricationOutputSettings> mFabricationOutputSettings;
  QScopedPointer<BoardUserSettings>              mUserSettings;
  QRectF                                         mViewRect;
  QSet<NetSignal*> mScheduledNetSignalsForAirWireRebuild;

  // Attributes
  Uuid        mUuid;
  ElementName mName;
  QString     mDefaultFontFileName;

  // items
  QMap<Uuid, XB_Device*> mDeviceInstances;
  QList<XB_Path*>        mPaths;
  QList<XB_Polygon*>     mPolygons;
  QList<XB_Text*>        mTexts;
  QList<XB_Hole*>        mHoles;

  // ERC messages
  QHash<Uuid, ErcMsg*> mErcMsgListUnplacedComponentInstances;
};

}  // namespace x_version
}  // namespace librepcb

#endif // LIBREPCB_X_VERSION_X_BOARD_H
