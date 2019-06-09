#ifndef LIBREPCB_X_VERSION_XBG_VIA_H
#define LIBREPCB_X_VERSION_XBG_VIA_H

#include <librepcb/common/units/all_length_units.h>

#include "xg_if_baseitem.h"
#include "xb_via.h"

#include <QtCore>
#include <QtWidgets>

namespace librepcb {

namespace x_version {

class XBG_Via : public QGraphicsItem, XG_IF_BaseItem {
public:
  XBG_Via()                     = delete;
  XBG_Via(const XBG_Via& other) = delete;
  XBG_Via(GraphicsScene* parent);
  ~XBG_Via();

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
  XB_Via*      mVia;
  QPainterPath mShape;
  QRectF       mBoundingRect;

};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XBG_VIA_H
