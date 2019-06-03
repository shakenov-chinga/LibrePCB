#include "xs_circle.h"

namespace  librepcb {

namespace x_version {

XS_Circle::XS_Circle(Point& center, Length& radius, QObject* parent)
  : XS_BaseItem(parent),
    mCenter(center),
    mRadius(radius) {
}

XS_Circle::~XS_Circle() {
}

}  // namespace x_version
}  // namespace librepcb
