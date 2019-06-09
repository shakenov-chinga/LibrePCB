#include "xbg_footprint.h"

namespace librepcb {

namespace x_version {

XBG_Footprint::XBG_Footprint(GraphicsScene* parent)
  : XG_IF_BaseItem(parent) {
}

XBG_Footprint::~XBG_Footprint() {
}

void XBG_Footprint::moveTo(Point& position) const noexcept {
  Q_UNUSED(position);
}

void XBG_Footprint::rotateTo(Angle& angle, Point& pivot) const noexcept {
  Q_UNUSED(angle);
  Q_UNUSED(pivot);
}

void XBG_Footprint::mirror(Point& pivot) const noexcept {
  Q_UNUSED(pivot);
}

void XBG_Footprint::duplicate() const noexcept {
}

void XBG_Footprint::apply() const noexcept {
}

// Inherited from QGraphicsItem
void XBG_Footprint::paint(QPainter* painter,
                          const QStyleOptionGraphicsItem* option,
                          QWidget* widget = 0){
  Q_UNUSED(option);
  Q_UNUSED(widget);

  Q_UNUSED(painter);
}

} // namespace x_version
} // namespace librepcb
