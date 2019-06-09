#include "xbg_hole.h"

namespace librepcb {

namespace x_version {

XBG_Hole::XBG_Hole(GraphicsScene* parent)
  : XG_IF_BaseItem(parent) {
}

XBG_Hole::~XBG_Hole() {
}

void XBG_Hole::moveTo(Point& position) const noexcept {
  Q_UNUSED(position);
}

void XBG_Hole::rotateTo(Angle& angle, Point& pivot) const noexcept {
  Q_UNUSED(angle);
  Q_UNUSED(pivot);
}

void XBG_Hole::mirror(Point& pivot) const noexcept {
  Q_UNUSED(pivot);
}

void XBG_Hole::duplicate() const noexcept {
}

void XBG_Hole::apply() const noexcept {
}

// Inherited from QGraphicsItem
void XBG_Hole::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget = 0){
  Q_UNUSED(option);
  Q_UNUSED(widget);

  Q_UNUSED(painter);
}

} // namespace x_version
} // namespace librepcb
