#include "xs_path.h"

namespace  librepcb {

namespace x_version {

XS_Path::XS_Path(QObject* parent)
  : XS_BaseItem(parent) {
}

XS_Path::~XS_Path() {
}

void XS_Path::addLine(XS_Line *line) const noexcept {
  Q_UNUSED(line);
}

} // namespace x_version
} // namespace librepcb
