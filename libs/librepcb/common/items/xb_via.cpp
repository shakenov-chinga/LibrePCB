#include "xb_via.h"

namespace  librepcb {

namespace x_version {

XB_Via::XB_Via(Point& position, Length& drill, Length& size, XB_ViaShape shape,
               QObject* parent)
 : XB_BaseItem(parent),
   mPosition(position),
   mDrill(drill),
   mSize(size),
   mShape(shape) {
}

XB_Via::~XB_Via() {
}

} // namespace x_verion
} // namespace librepcb
