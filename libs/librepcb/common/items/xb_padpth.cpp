#include "xb_padpth.h"

namespace  librepcb {

namespace x_version {

XB_PadPth::XB_PadPth(Point& position, Length& drill, Length& size,
                     XB_PthShape shape, QObject* parent)
  : XB_BaseItem(parent),
    mPosition(position),
    mDrill(drill),
    mSize(size),
    mShape(shape) {
}

XB_PadPth::~XB_PadPth() {
}

} // namespace x_verion
} // namespace librepcb
