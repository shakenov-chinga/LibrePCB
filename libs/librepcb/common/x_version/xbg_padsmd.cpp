#include "xbg_padsmd.h"

namespace librepcb {

namespace x_version {

XBG_PadSmd::XBG_PadSmd(GraphicsScene* parent)
  : XBG_BaseItem(parent) {
}

XBG_PadSmd::~XBG_PadSmd() {
}

void XBG_PadSmd::moveTo(Point& position) const noexcept {
  Q_UNUSED(position);
}

void XBG_PadSmd::rotateTo(Angle& angle, Point& pivot) const noexcept {
  Q_UNUSED(angle);
  Q_UNUSED(pivot);
}

void XBG_PadSmd::mirror(Point& pivot) const noexcept {
  Q_UNUSED(pivot);
}

void XBG_PadSmd::duplicate() const noexcept {
}

void XBG_PadSmd::apply() const noexcept {
}

// Inherited from QGraphicsItem
void XBG_PadSmd::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget = 0){
  Q_UNUSED(option);
  Q_UNUSED(widget);

  Q_UNUSED(painter);
}

} // namespace x_version
} // namespace librepcb
