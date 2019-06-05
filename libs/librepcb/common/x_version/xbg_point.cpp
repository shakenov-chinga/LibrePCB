#include "xbg_point.h"

namespace librepcb {

namespace x_version {

XBG_Point::XBG_Point(GraphicsScene* parent)
  : XBG_BaseItem(parent) {
}

XBG_Point::~XBG_Point() {
}

void XBG_Point::moveTo(Point& position) const noexcept {
  Q_UNUSED(position);
}

void XBG_Point::rotateTo(Angle& angle, Point& pivot) const noexcept {
  Q_UNUSED(angle);
  Q_UNUSED(pivot);
}

void XBG_Point::mirror(Point& pivot) const noexcept {
  Q_UNUSED(pivot);
}

void XBG_Point::duplicate() const noexcept {
}

void XBG_Point::apply() const noexcept {
}

} // namespace x_version
} // namespace librepcb
