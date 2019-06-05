#include "xbg_text.h"

namespace librepcb {

namespace x_version {

XBG_Text::XBG_Text(GraphicsScene* parent)
  : XBG_BaseItem(parent) {
}

XBG_Text::~XBG_Text() {
}

void XBG_Text::moveTo(Point& position) const noexcept {
  Q_UNUSED(position);
}

void XBG_Text::rotateTo(Angle& angle, Point& pivot) const noexcept {
  Q_UNUSED(angle);
  Q_UNUSED(pivot);
}

void XBG_Text::mirror(Point& pivot) const noexcept {
  Q_UNUSED(pivot);
}

void XBG_Text::duplicate() const noexcept {
}

void XBG_Text::apply() const noexcept {
}

// Inherited from QGraphicsItem
void XBG_Text::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget = 0){
  Q_UNUSED(option);
  Q_UNUSED(widget);

  Q_UNUSED(painter);
}

} // namespace x_version
} // namespace librepcb
