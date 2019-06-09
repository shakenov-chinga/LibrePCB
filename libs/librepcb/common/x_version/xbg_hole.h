#ifndef LIBREPCB_X_VERSION_XBG_HOLE_H
#define LIBREPCB_X_VERSION_XBG_HOLE_H

#include <librepcb/common/units/all_length_units.h>

#include "xg_if_baseitem.h"
#include "xb_hole.h"

#include <QtCore>
#include <QtWidgets>

namespace librepcb {

namespace x_version {

class XBG_Hole : public QGraphicsItem, XG_IF_BaseItem {
public:
  XBG_Hole()                      = delete;
  XBG_Hole(const XBG_Hole& other) = delete;
  XBG_Hole(GraphicsScene* parent);
  ~XBG_Hole();

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
  XB_Hole*     mHole;
  QPainterPath mShape;
  QRectF       mBoundingRect;

};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XBG_HOLE_H
