#ifndef LIBREPCB_X_VERSION_XS_BASEITEM_H
#define LIBREPCB_X_VERSION_XS_BASEITEM_H

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace  librepcb {

namespace project {
class Project;
class Circuit;
}

namespace x_version {

using namespace project;

class X_Schematic;

class XS_BaseItem : public QObject {
Q_OBJECT

public:
  enum class XS_ItemType{
    Circle, Line, Path, Pin, Polygon, Symbol, Text
  };

  XS_BaseItem();  //                    = delete;
  XS_BaseItem(const XS_BaseItem& other) = delete;
  XS_BaseItem(QObject* parent = nullptr);
//  XS_BaseItem(X_Schematic& schematic) noexcept;
  virtual ~XS_BaseItem() noexcept;

//  Project&            getProject() const noexcept;
//  Circuit&            getCircuit() const noexcept;
//  X_Schematic&        getSchematic() const noexcept { return mSchematic; }
  virtual XS_ItemType getType() const noexcept = 0;

protected:
//  X_Schematic& mSchematic;

};

}  // namespace x_version
}  // namespace librepcb

#endif // LIBREPCB_X_VERSION_XS_BASEITEM_H

/****
project
+-----------------------------+
circuit                       board
+-device                       +-footprint
 +--circle                      +--circle
 +--path(doc only)              +--hole
 +--pin                         +--pad-pth
 +--polygon                     +--pad-smd
 +--text                        +--path
+-circle                        +--polygon
+-path(net or doc)              +--text
+-polygon(doc only)            +-circle
+-text                         +-hole
                               +-path
                               +-polygon
                               +-text
                               +-via
****/
