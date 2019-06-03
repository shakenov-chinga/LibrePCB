#ifndef LIBREPCB_X_VERSION_XB_HOLE_H
#define LIBREPCB_X_VERSION_XB_HOLE_H

#include "xb_baseitem.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace librepcb {

namespace x_version {

class XB_Hole : public XB_BaseItem {
Q_OBJECT

public:
  XB_Hole()                     = delete;
  XB_Hole(const XB_Hole* other) = delete;
  XB_Hole(Point& center, Length& radius, QObject* parent = nullptr);
  ~XB_Hole() noexcept;

  XB_ItemType getType() const noexcept override {
    return XB_BaseItem::XB_ItemType::Hole;
  }

  const Point& getCenter() const noexcept { return mCenter; }
  const Length& getRadius() const noexcept { return mRadius; }

private:
  Point mCenter;
  Length mRadius;
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XB_HOLE_H
