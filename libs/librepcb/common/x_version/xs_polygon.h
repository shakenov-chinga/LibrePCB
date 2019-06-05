#ifndef LIBREPCB_X_VERSION_XS_POLYGON_H
#define LIBREPCB_X_VERSION_XS_POLYGON_H

#include "xs_baseitem.h"

#include <librepcb/common/units/all_length_units.h>
#include <librepcb/common/fileio/serializableobject.h>

#include <QtCore>

namespace  librepcb {

namespace x_version {

class XS_Polygon : public XS_BaseItem {
Q_OBJECT

public:
  XS_Polygon()                        = delete;
  XS_Polygon(const XS_Polygon& other) = delete;
  XS_Polygon(Length& width, bool filled, QObject* parent = nullptr);
//  XS_Polygon(const SExpression& node);
  ~XS_Polygon() noexcept;

public:
  void addCorner(const Point& point) const noexcept;
  const Point* getCornerAt(int index) noexcept;

  XS_ItemType getType() const noexcept override {
    return XS_BaseItem::XS_ItemType::Polygon;
  }

  const Length& getWidth() const noexcept { return mWidth; }
  bool isFilled() const noexcept { return mFilled; }

private:
  QList<Point*> mCorners;
  Length mWidth;
  bool mFilled;
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XS_POLYGON_H
