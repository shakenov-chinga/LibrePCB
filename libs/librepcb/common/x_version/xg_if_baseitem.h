#ifndef LIBREPCB_X_VERSION_XBG_BASEITEM_H
#define LIBREPCB_X_VERSION_XBG_BASEITEM_H

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>
#include <QtWidgets>

namespace librepcb {
class GraphicsScene;

namespace x_version {

class XG_IF_BaseItem {
public:
  virtual ~XG_IF_BaseItem();

  virtual void moveTo(Point& position) const noexcept = 0;
  virtual void rotateTo(Angle& angle, Point& pivot) const noexcept = 0;
  virtual void mirror(Point& pivot) const noexcept = 0;
  virtual void duplicate() const noexcept = 0;
  virtual void apply() const noexcept = 0;

};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XBG_BASEITEM_H
