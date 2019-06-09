#ifndef LIBREPCB_X_VERSION_XBG_PADSMD_H
#define LIBREPCB_X_VERSION_XBG_PADSMD_H

#include <librepcb/common/units/all_length_units.h>

#include "xg_if_baseitem.h"
#include "xb_padsmd.h"

#include <QtCore>
#include <QtWidgets>

namespace librepcb {

namespace x_version {

class XBG_PadSmd : public QGraphicsItem, XG_IF_BaseItem {
public:
  XBG_PadSmd()                        = delete;
  XBG_PadSmd(const XBG_PadSmd& other) = delete;
  XBG_PadSmd(GraphicsScene* parent);
  ~XBG_PadSmd();

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
  XB_PadSmd*   mPadSmd;
  QPainterPath mShape;
  QRectF       mBoundingRect;

};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XBG_PADSMD_H
