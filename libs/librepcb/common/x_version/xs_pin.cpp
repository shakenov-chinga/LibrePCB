#include "xs_pin.h"

#include <QObject>

namespace  librepcb {

namespace x_version {

XS_Pin::XS_Pin(QString& name, Point& position, Length& length, QObject* parent)
  : XS_BaseItem(parent),
    mName(name),
    mPosition(position),
    mLength(length) {
}

XS_Pin::~XS_Pin() {
}

} // namespace x_version
} // namespace librepcb
