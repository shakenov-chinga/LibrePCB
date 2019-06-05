#include "xs_polygon.h"

namespace  librepcb {

namespace x_version {

XS_Polygon::XS_Polygon(Length& width, bool filled, QObject* parent)
  : XS_BaseItem(parent),
    mWidth(width),
    mFilled(filled) {
}

//XS_Polygon::XS_Polygon(const SExpression& node){
//Q_UNUSED(node)
//}

XS_Polygon::~XS_Polygon() noexcept {
}

void XS_Polygon::addCorner(const Point& point) const noexcept {
  Q_UNUSED(point);
}

const Point* XS_Polygon::getCornerAt(int index) noexcept {
  Q_UNUSED(index);
  return nullptr;
}

} // namespace x_version
} // namespace librepcb
