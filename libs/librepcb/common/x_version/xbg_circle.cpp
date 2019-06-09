#include "xbg_circle.h"

namespace librepcb {

namespace x_version {

XBG_Circle::XBG_Circle(GraphicsScene* parent)
  : XG_IF_BaseItem(parent) {
}

XBG_Circle::~XBG_Circle() {
}

void XBG_Circle::moveTo(Point& position) const noexcept {
  Q_UNUSED(position);
}

void XBG_Circle::rotateTo(Angle& angle, Point& pivot) const noexcept {
  Q_UNUSED(angle);
  Q_UNUSED(pivot);
}

void XBG_Circle::mirror(Point& pivot) const noexcept {
  Q_UNUSED(pivot);
}

void XBG_Circle::duplicate() const noexcept {
}

void XBG_Circle::apply() const noexcept {
}

// Inherited from QGraphicsItem
void XBG_Circle::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget = 0){
  Q_UNUSED(option);
  Q_UNUSED(widget);

  Q_UNUSED(painter);
}

} // namespace x_version
} // namespace librepcb
