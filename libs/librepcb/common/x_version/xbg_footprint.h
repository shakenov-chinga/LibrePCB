#ifndef LIBREPCB_X_VERSION_XBG_FOOTPRINT_H
#define LIBREPCB_X_VERSION_XBG_FOOTPRINT_H

#include <librepcb/common/units/all_length_units.h>

#include "xg_if_baseitem.h"
#include "xb_footprint.h"

#include <QtCore>
#include <QtWidgets>

namespace librepcb {

namespace x_version {

class XBG_Footprint : public XG_IF_BaseItem {
public:
  XBG_Footprint()                           = delete;
  XBG_Footprint(const XBG_Footprint& other) = delete;
  XBG_Footprint(GraphicsScene* parent);
  ~XBG_Footprint();

  void moveTo(Point& position) const noexcept override;
  void rotateTo(Angle& angle, Point& pivot) const noexcept override;
  void mirror(Point& pivot) const noexcept override;
  void duplicate() const noexcept override;
  void apply() const noexcept override;

private:
  XB_Footprint*  mFootprint;
  QPainterPath   mShape;
  QRectF         mBoundingRect;

};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XBG_FOOTPRINT_H
