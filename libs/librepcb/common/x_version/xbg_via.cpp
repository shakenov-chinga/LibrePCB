#include "xbg_via.h"

namespace librepcb {

namespace x_version {

XBG_Via::XBG_Via(GraphicsScene* parent)
  : XBG_BaseItem(parent) {
}

XBG_Via::~XBG_Via() {
}

void XBG_Via::moveTo(Point& position) const noexcept {
  Q_UNUSED(position);
}

void XBG_Via::rotateTo(Angle& angle, Point& pivot) const noexcept {
  Q_UNUSED(angle);
  Q_UNUSED(pivot);
}

void XBG_Via::mirror(Point& pivot) const noexcept {
  Q_UNUSED(pivot);
}

void XBG_Via::duplicate() const noexcept {
}

void XBG_Via::apply() const noexcept {
}

// Inherited from QGraphicsItem
void XBG_Via::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget = 0){
  Q_UNUSED(option);
  Q_UNUSED(widget);

  Q_UNUSED(painter);
}

} // namespace x_version
} // namespace librepcb
