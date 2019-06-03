#include "xb_line.h"

namespace librepcb {

namespace x_version {

XB_Line::XB_Line(Point& startPoint, Point& endPoint, QObject* parent)
  : XB_BaseItem(parent),
    mStartPoint(new Point(startPoint)),
    mEndPoint(new Point(endPoint)) {
}

XB_Line::~XB_Line() {
}

} // namespace x_version
} // namespace librepcb
