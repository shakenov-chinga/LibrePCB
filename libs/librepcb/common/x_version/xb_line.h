#ifndef LIBREPCB_X_VERSION_XB_LINE_H
#define LIBREPCB_X_VERSION_XB_LINE_H

#include "xb_baseitem.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace librepcb {

namespace x_version {

class XB_Line : public XB_BaseItem {
Q_OBJECT

public:
  XB_Line()                     = delete;
  XB_Line(const XB_Line& other) = delete;
  XB_Line(Point& startPoint, Point& endPoint, QObject* parent = nullptr);
  ~XB_Line() noexcept;

  XB_ItemType getType() const noexcept override {
    return XB_BaseItem::XB_ItemType::Line;
  }

  const Point* getStartPoint() const noexcept { return mStartPoint; }
  const Point* getEndPoint() const noexcept { return mEndPoint; }

private:
  Point* mStartPoint;
  Point* mEndPoint;
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XB_LINE_H
