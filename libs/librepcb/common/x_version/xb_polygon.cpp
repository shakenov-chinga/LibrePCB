#include "xb_polygon.h"

namespace  librepcb {

namespace x_version {

XB_Polygon::XB_Polygon(Length& width, bool filled, QObject* parent)
  : XB_BaseItem(parent),
    mWidth(width),
    mFilled(filled) {
}

XB_Polygon::~XB_Polygon() {
}

} // namespace x_version
} // namespace librepcb
