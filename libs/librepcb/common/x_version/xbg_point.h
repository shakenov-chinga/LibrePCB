#ifndef LIBREPCB_X_VERSION_XBG_POINT_H
#define LIBREPCB_X_VERSION_XBG_POINT_H

#include <librepcb/common/units/all_length_units.h>

#include "xg_if_baseitem.h"

#include <QtCore>
#include <QtWidgets>

namespace librepcb {

namespace x_version {

class XBG_Point : public XG_IF_BaseItem{
public:
  XBG_Point()                       = delete;
  XBG_Point(const XBG_Point& other) = delete;
  XBG_Point(GraphicsScene* parent);
  ~XBG_Point();

  void moveTo(Point& position) const noexcept override;
  void rotateTo(Angle& angle, Point& pivot) const noexcept override;
  void mirror(Point& pivot) const noexcept override;
  void duplicate() const noexcept override;
  void apply() const noexcept override;

private:
  QPainterPath mShape;
  QRectF       mBoundingRect;

};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XBG_Point_H
