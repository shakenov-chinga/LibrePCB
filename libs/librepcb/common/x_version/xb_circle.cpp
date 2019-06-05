#include "xb_circle.h"

namespace  librepcb {

namespace x_version {

XB_Circle::XB_Circle(Point& center, Length& radius, Length& width, bool filled,
                     QObject* parent)
  : XB_BaseItem(parent),
    mCenter(center),
    mRadius(radius),
    mWidth(width),
    mFilled(filled) {
}

XB_Circle::~XB_Circle() {
}

} // namespace x_version
} // namespace librepcb
