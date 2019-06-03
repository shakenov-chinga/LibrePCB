#ifndef LIBREPCB_X_VERSION_XB_VIA_H
#define LIBREPCB_X_VERSION_XB_VIA_H

#include "xb_baseitem.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace librepcb {

namespace x_version {

class XB_Via : public XB_BaseItem {
Q_OBJECT

enum class XB_ViaShape{
  Square, Round, Octagon
};

public:
  XB_Via()                    = delete;
  XB_Via(const XB_Via& other) = delete;
  XB_Via(Point& position, Length& drill, Length& size, XB_ViaShape shape,
         QObject* parent = nullptr);
  ~XB_Via() noexcept;

  XB_ItemType getType() const noexcept override {
    return XB_BaseItem::XB_ItemType::Via;
  }

  const Point& getPosition() const noexcept { return mPosition; }
  const Length& getDrill() const noexcept { return mDrill; }
  const Length& getSize() const noexcept { return mSize; }
  XB_ViaShape getShape() const noexcept { return mShape; }

private:
  Point mPosition;
  Length mDrill;
  Length mSize;
  XB_ViaShape mShape;
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XB_VIA_H
