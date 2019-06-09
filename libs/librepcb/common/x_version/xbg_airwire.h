#ifndef LIBREPCB_X_VERSION_XBG_AIRWIRE_H
#define LIBREPCB_X_VERSION_XBG_AIRWIRE_H

#include <QtCore>
#include <QtWidgets>

namespace librepcb {
class GraphicsScene;

namespace x_version {

class XBG_Airwire : public QGraphicsItem {
public:
  XBG_Airwire()                         = delete;
  XBG_Airwire(const XBG_Airwire* other) = delete;
  XBG_Airwire(GraphicsScene* parent);
  ~XBG_Airwire();
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XBG_AIRWIRE_H
