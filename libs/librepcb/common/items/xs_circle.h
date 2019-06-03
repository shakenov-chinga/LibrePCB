#ifndef LIBREPCB_X_VERSION_XS_CIRCLE_H
#define LIBREPCB_X_VERSION_XS_CIRCLE_H

#include "xs_baseitem.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace  librepcb {

namespace x_version {

class XS_Circle : public XS_BaseItem {
Q_OBJECT

public:
  XS_Circle()                       = delete;
  XS_Circle(const XS_Circle* other) = delete;
  XS_Circle(Point& center, Length& radius, QObject* parent = nullptr);
  ~XS_Circle() noexcept;

  XS_ItemType getType() const noexcept override {
    return XS_BaseItem::XS_ItemType::Circle;
  }

  const Point& getCenter() const noexcept { return mCenter; }
  const Length& getRadius() const noexcept { return mRadius; }

private:
  Point mCenter;
  Length mRadius;
};

}  // namespace x_version
}  // namespace librepcb

#endif // LIBREPCB_X_VERSION_XS_CIRCLE_H
