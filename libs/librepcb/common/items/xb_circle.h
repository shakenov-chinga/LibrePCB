#ifndef LIBREPCB_X_VERSION_XB_CIRCLE_H
#define LIBREPCB_X_VERSION_XB_CIRCLE_H

#include "xb_baseitem.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace librepcb {

namespace x_version {

class XB_Circle : public XB_BaseItem {
Q_OBJECT

public:
  XB_Circle()                       = delete;
  XB_Circle(const XB_Circle& other) = delete;
  XB_Circle(Point& center, Length& radius, Length& width, bool filled,
            QObject* parent = nullptr);
  ~XB_Circle() noexcept;

  XB_ItemType getType() const noexcept override {
    return XB_BaseItem::XB_ItemType::Circle;
  }

  const Point& getCenter() const noexcept { return mCenter; }
  const Length& getRadius() const noexcept { return mRadius; }
  const Length& getWidth() const noexcept { return mWidth; }
  bool isFilled() const noexcept { return mFilled; }

private:
  Point mCenter;
  Length mRadius;
  Length mWidth;
  bool mFilled;
};

} // namespace librepcb
} // namespace x_version

#endif // LIBREPCB_X_VERSION_XB_CIRCLE_H
