#ifndef LIBREPCB_X_VERSION_XB_PADPTH_H
#define LIBREPCB_X_VERSION_XB_PADPTH_H

#include "xb_baseitem.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace librepcb {

namespace x_version {

class XB_PadPth : public XB_BaseItem {
Q_OBJECT

enum class XB_PthShape {
  Square, Round, Octagon//, Long
};

public:
  XB_PadPth()                       = delete;
  XB_PadPth(const XB_PadPth& other) = delete;
  XB_PadPth(Point& position, Length& drill, Length& size, XB_PthShape shape,
            QObject* parent = nullptr);
  ~XB_PadPth() noexcept;

  XB_ItemType getType() const noexcept override {
    return XB_BaseItem::XB_ItemType::PadPTH;
  }

  const Point& getPosition() const noexcept { return mPosition; }
  const Length& getDrill() const noexcept { return mDrill; }
  const Length& getSize() const noexcept { return mSize; }
  XB_PthShape getShape() const noexcept { return mShape; }

private:
  Point mPosition;
  Length mDrill;
  Length mSize;
  XB_PthShape mShape;
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XB_PADPTH_H
