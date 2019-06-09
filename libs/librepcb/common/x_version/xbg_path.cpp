#include "xbg_path.h"

namespace librepcb {

namespace x_version {

XBG_Path::XBG_Path(GraphicsScene* parent)
  : XG_IF_BaseItem(parent) {
}

XBG_Path::~XBG_Path() {
}

void XBG_Path::moveTo(Point& position) const noexcept {
  Q_UNUSED(position);
}

void XBG_Path::rotateTo(Angle& angle, Point& pivot) const noexcept {
  Q_UNUSED(angle);
  Q_UNUSED(pivot);
}

void XBG_Path::mirror(Point& pivot) const noexcept {
  Q_UNUSED(pivot);
}

void XBG_Path::duplicate() const noexcept {
}

void XBG_Path::apply() const noexcept {
}

// Inherited from QGraphicsItem
void XBG_Path::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget = 0){
  Q_UNUSED(option);
  Q_UNUSED(widget);

  Q_UNUSED(painter);
}

} // namespace x_version
} // namespace librepcb
