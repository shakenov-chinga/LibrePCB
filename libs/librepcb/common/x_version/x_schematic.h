#ifndef LIBREPCB_X_VERSION_X_SCHEMATIC_H
#define LIBREPCB_X_VERSION_X_SCHEMATIC_H

#include <librepcb/common/attributes/attributeprovider.h>
#include <librepcb/common/elementname.h>
#include <librepcb/common/exceptions.h>
#include <librepcb/common/fileio/filepath.h>
#include <librepcb/common/fileio/serializableobject.h>
#include <librepcb/common/fileio/transactionaldirectory.h>
#include <librepcb/common/units/all_length_units.h>
#include <librepcb/common/uuid.h>

#include <QtCore>

namespace librepcb {

namespace project{
class Project;
class GridProperties;
}
using namespace project;

namespace x_version {
class XS_Symbol;
class XS_Path;

class X_Schematic : public QObject,
                    public AttributeProvider,
                    public SerializableObject  {
Q_OBJECT

public:
  X_Schematic()                         = delete;
  X_Schematic(const X_Schematic& other) = delete;
  X_Schematic(Project& project,
              std::unique_ptr<TransactionalDirectory> directory)
    : X_Schematic(project, std::move(directory), false, QString()) {}
  X_Schematic(QObject* parent = nullptr);
  ~X_Schematic() noexcept;

  // Getters: General
  Project&              getProject() const noexcept { return mProject; }
  FilePath              getFilePath() const noexcept;
  const GridProperties& getGridProperties() const noexcept {
    return *mGridProperties;
  }
  bool            isEmpty() const noexcept;

  // Setters: General
  void setGridProperties(const GridProperties& grid) noexcept;

  // Getters: Attributes
  const Uuid&        getUuid() const noexcept { return mUuid; }
  const ElementName& getName() const noexcept { return mName; }

  // Symbol Methods
  QList<XS_Symbol*> getSymbols() const noexcept { return mSymbols; }
  XS_Symbol*        getSymbolByUuid(const Uuid& uuid) const noexcept;
  void              addSymbol(XS_Symbol& symbol);
  void              removeSymbol(XS_Symbol& symbol);

  // NetSegment Methods
  XS_Path* getNetSegmentByUuid(const Uuid& uuid) const noexcept;
  void           addNetSegment(XS_Path& netsegment);
  void           removeNetSegment(XS_Path& netsegment);

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
  X_Schematic& operator=(const X_Schematic& rhs) = delete;
  bool operator==(const X_Schematic& rhs) noexcept { return (this == &rhs); }
  bool operator!=(const X_Schematic& rhs) noexcept { return (this != &rhs); }

  // Static Methods
  static X_Schematic* create(Project&                                project,
                           std::unique_ptr<TransactionalDirectory> directory,
                           const ElementName&                      name);

signals:

  /// @copydoc AttributeProvider::attributesChanged()
  void attributesChanged() override;

private:
  X_Schematic(Project& project, std::unique_ptr<TransactionalDirectory> directory,
            bool create, const QString& newName);

  /// @copydoc librepcb::SerializableObject::serialize()
  // void serialize(SExpression& root) const override;

  // General
  Project& mProject;  ///< A reference to the Project object (from the ctor)
  std::unique_ptr<TransactionalDirectory> mDirectory;
  bool                                    mIsAddedToProject;

  QScopedPointer<GridProperties> mGridProperties;

  // Attributes
  Uuid        mUuid;
  ElementName mName;

  QList<XS_Symbol*>     mSymbols;
  QList<XS_Path*> mNetSegments;

};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_X_SCHEMATIC_H
