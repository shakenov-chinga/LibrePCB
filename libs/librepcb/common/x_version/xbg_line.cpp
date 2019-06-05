#include "xbg_line.h"

namespace librepcb {

namespace x_version {

XBG_Line::XBG_Line(GraphicsScene* parent)
  : XBG_BaseItem(parent) {
}

XBG_Line::~XBG_Line() {
}

void XBG_Line::moveTo(Point& position) const noexcept {
  Q_UNUSED(position);
}

void XBG_Line::rotateTo(Angle& angle, Point& pivot) const noexcept {
  Q_UNUSED(angle);
  Q_UNUSED(pivot);
}

void XBG_Line::mirror(Point& pivot) const noexcept {
  Q_UNUSED(pivot);
}

void XBG_Line::duplicate() const noexcept {
}

void XBG_Line::apply() const noexcept {
}

// Inherited from QGraphicsItem
void XBG_Line::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget = 0){
  Q_UNUSED(option);
  Q_UNUSED(widget);

  Q_UNUSED(painter);
}

} // namespace x_version
} // namespace librepcb
