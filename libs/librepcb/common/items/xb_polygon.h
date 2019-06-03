#ifndef LIBREPCB_X_VERSION_XB_POLYGON_H
#define LIBREPCB_X_VERSION_XB_POLYGON_H

#include "xb_baseitem.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace librepcb {

namespace x_version {

class XB_Polygon : public XB_BaseItem {
Q_OBJECT

public:
  XB_Polygon()                        = delete;
  XB_Polygon(const XB_Polygon& other) = delete;
  XB_Polygon(Length& width, bool filled, QObject* parent = nullptr);
  ~XB_Polygon() noexcept;

  XB_ItemType getType() const noexcept override {
    return XB_BaseItem::XB_ItemType::Polygon;
  }

  const Length& getWidth() const noexcept { return mWidth; }
  bool isFIlled() const noexcept { return mFilled; }

private:
  QList<Point*> mCorners;
  Length mWidth;
  bool mFilled;
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XB_POLYGON_H
