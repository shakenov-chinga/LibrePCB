#include "xb_padsmd.h"

namespace  librepcb {

namespace x_version {

XB_PadSmd::XB_PadSmd(Point& position, Length& width, Length& height,
                     Angle& angle, Length& roundness, QObject* parent)
  : XB_BaseItem(parent),
    mPosition(position),
    mWidth(width),
    mHeight(height),
    mAngle(angle),
    mRoundness(roundness) {
}

XB_PadSmd::~XB_PadSmd() {
}

} // namespace x_verion
} // namespace librepcb
