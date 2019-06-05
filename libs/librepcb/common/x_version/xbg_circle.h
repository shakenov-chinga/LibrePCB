#ifndef LIBREPCB_X_VERSION_XBG_CIRCLE_H
#define LIBREPCB_X_VERSION_XBG_CIRCLE_H

#include <librepcb/common/units/all_length_units.h>

#include "xbg_baseitem.h"
#include "xb_circle.h"

#include <QtCore>
#include <QtWidgets>

namespace librepcb {

namespace x_version {

class XBG_Circle : public XBG_BaseItem, QGraphicsItem {
public:
  XBG_Circle()                        = delete;
  XBG_Circle(const XBG_Circle& other) = delete;
  XBG_Circle(GraphicsScene* parent);
  ~XBG_Circle();

  void moveTo(Point& position) const noexcept override;
  void rotateTo(Angle& angle, Point& pivot) const noexcept override;
  void mirror(Point& pivot) const noexcept override;
  void duplicate() const noexcept override;
  void apply() const noexcept override;

  // Inherited from QGraphicsItem
  QRectF       boundingRect() const noexcept { return mBoundingRect; }
  QPainterPath shape() const noexcept { return mShape; }
  void         paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                     QWidget* widget = 0);

private:
  XB_Circle*     mCircle;
  QPainterPath   mShape;
  QRectF         mBoundingRect;

};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XBG_CIRCLE_H
