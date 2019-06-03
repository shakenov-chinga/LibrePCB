#ifndef LIBREPCB_X_VERSION_XS_LINE_H
#define LIBREPCB_X_VERSION_XS_LINE_H

#include "xs_baseitem.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace librepcb{

namespace x_version {

class XS_Line : public XS_BaseItem {
Q_OBJECT

public:
  XS_Line()                     = delete;
  XS_Line(const XS_Line& other) = delete;
  XS_Line(Point* startPoint, Point* endPoint, Length& width,
          QObject* parent = nullptr);
  ~XS_Line() noexcept;

  XS_ItemType getType() const noexcept override {
    return XS_BaseItem::XS_ItemType::Line;
  }

  const Point* getStartPoint() const noexcept { return mStartPoint; }
  const Point* getEndPoint() const noexcept { return mEndPoint; }
  const Length& getWidth() const noexcept { return mWidth; }

private:
  Point* mStartPoint;
  Point* mEndPoint;
  Length mWidth;
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XS_LINE_H
