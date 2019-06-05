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

namespace x_version {

class X_Board final : public QObject {
Q_OBJECT

public:
  X_Board()                     = delete;
  X_Board(const X_Board& other) = delete;
  DECLARE_ERC_MSG_CLASS_NAME(Board)

public:
  // Constructors / Destructor
  X_Board()                   = delete;
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
  const QMap<Uuid, BI_Device*>& getDeviceInstances() const noexcept {
    return mDeviceInstances;
  }
  BI_Device* getDeviceInstanceByComponentUuid(const Uuid& uuid) const noexcept;
  void       addDeviceInstance(BI_Device& instance);
  void       removeDeviceInstance(BI_Device& instance);

  // NetSegment Methods
  const QList<BI_NetSegment*>& getNetSegments() const noexcept {
    return mNetSegments;
  }
  BI_NetSegment* getNetSegmentByUuid(const Uuid& uuid) const noexcept;
  void           addNetSegment(BI_NetSegment& netsegment);
  void           removeNetSegment(BI_NetSegment& netsegment);

  // Plane Methods
  const QList<BI_Plane*>& getPlanes() const noexcept { return mPlanes; }
  void                    addPlane(BI_Plane& plane);
  void                    removePlane(BI_Plane& plane);
  void                    rebuildAllPlanes() noexcept;

  // Polygon Methods
  const QList<BI_Polygon*>& getPolygons() const noexcept { return mPolygons; }
  void                      addPolygon(BI_Polygon& polygon);
  void                      removePolygon(BI_Polygon& polygon);

  // StrokeText Methods
  const QList<BI_StrokeText*>& getStrokeTexts() const noexcept {
    return mStrokeTexts;
  }
  void addStrokeText(BI_StrokeText& text);
  void removeStrokeText(BI_StrokeText& text);

  // Hole Methods
  const QList<BI_Hole*>& getHoles() const noexcept { return mHoles; }
  void                   addHole(BI_Hole& hole);
  void                   removeHole(BI_Hole& hole);

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

  void deviceAdded(BI_Device& comp);
  void deviceRemoved(BI_Device& comp);

private:
  X_Board(Project& project, std::unique_ptr<TransactionalDirectory> directory,
        bool create, const QString& newName);
  void updateIcon() noexcept;
  void updateErcMessages() noexcept;

  /// @copydoc librepcb::SerializableObject::serialize()
  // void serialize(SExpression& root) const override;

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
  QMap<Uuid, BI_Device*>              mDeviceInstances;
  QList<BI_NetSegment*>               mNetSegments;
  QList<BI_Plane*>                    mPlanes;
  QList<BI_Polygon*>                  mPolygons;
  QList<BI_StrokeText*>               mStrokeTexts;
  QList<BI_Hole*>                     mHoles;
  QMultiHash<NetSignal*, BI_AirWire*> mAirWires;

  // ERC messages
  QHash<Uuid, ErcMsg*> mErcMsgListUnplacedComponentInstances;
};

}  // namespace x_version
}  // namespace librepcb

#endif // LIBREPCB_X_VERSION_X_BOARD_H
