#include "xb_hole.h"

namespace  librepcb {

namespace x_version {

XB_Hole::XB_Hole(Point& center, Length& radius, QObject* parent)
  : XB_BaseItem(parent),
    mCenter(center),
    mRadius(radius) {
}

XB_Hole::~XB_Hole() {
}

} // namespace x_verion
} // namespace librepcb
