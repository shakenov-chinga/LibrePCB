#include "xb_path.h"

namespace  librepcb {

namespace x_version {

XB_Path::XB_Path(QObject* parent)
  : XB_BaseItem(parent) {
}

XB_Path::~XB_Path() {
}

void XB_Path::addLine(XB_Line *line) const noexcept {
  Q_UNUSED(line);
}

} // namespace x_version
} // namespace librepcb
