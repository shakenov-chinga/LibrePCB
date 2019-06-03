#include "xs_line.h"

namespace librepcb{

namespace x_version {

XS_Line::XS_Line(Point* startPoint, Point* endPoint, Length& width,
                 QObject* parent)
  : XS_BaseItem(parent),
    mStartPoint(startPoint),
    mEndPoint(endPoint),
    mWidth(width) {
}

XS_Line::~XS_Line() {
}

} // namespace x_version
} // namespace librepcb
