#include "xb_baseitem.h"

#include <librepcb/common/uuid.h>

namespace  librepcb {

namespace x_version {

XB_BaseItem::XB_BaseItem(QObject* parent)
  : QObject(parent) {
}

XB_BaseItem::~XB_BaseItem() noexcept {
}

} // namespace x_version
} // namespace librepcb