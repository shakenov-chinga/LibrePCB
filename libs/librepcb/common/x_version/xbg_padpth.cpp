#include "xbg_padpth.h"

namespace librepcb {

namespace x_version {

XBG_PadPth::XBG_PadPth(GraphicsScene* parent)
  : XBG_BaseItem(parent) {
}

XBG_PadPth::~XBG_PadPth() {
}

void XBG_PadPth::moveTo(Point& position) const noexcept {
  Q_UNUSED(position);
}

void XBG_PadPth::rotateTo(Angle& angle, Point& pivot) const noexcept {
  Q_UNUSED(angle);
  Q_UNUSED(pivot);
}

void XBG_PadPth::mirror(Point& pivot) const noexcept {
  Q_UNUSED(pivot);
}

void XBG_PadPth::duplicate() const noexcept {
}

void XBG_PadPth::apply() const noexcept {
}

// Inherited from QGraphicsItem
void XBG_PadPth::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget = 0){
  Q_UNUSED(option);
  Q_UNUSED(widget);

  Q_UNUSED(painter);
}

} // namespace x_version
} // namespace librepcb
