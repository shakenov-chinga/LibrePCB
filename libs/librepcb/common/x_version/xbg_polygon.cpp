#include "xbg_polygon.h"

namespace librepcb {

namespace x_version {

XBG_Polygon::XBG_Polygon(GraphicsScene* parent)
  : XG_IF_BaseItem(parent) {
}

XBG_Polygon::~XBG_Polygon() {
}

void XBG_Polygon::moveTo(Point& position) const noexcept {
  Q_UNUSED(position);
}

void XBG_Polygon::rotateTo(Angle& angle, Point& pivot) const noexcept {
  Q_UNUSED(angle);
  Q_UNUSED(pivot);
}

void XBG_Polygon::mirror(Point& pivot) const noexcept {
  Q_UNUSED(pivot);
}

void XBG_Polygon::duplicate() const noexcept {
}

void XBG_Polygon::apply() const noexcept {
}

// Inherited from QGraphicsItem
void XBG_Polygon::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget = 0){
  Q_UNUSED(option);
  Q_UNUSED(widget);

  Q_UNUSED(painter);
}

} // namespace x_version
} // namespace librepcb
