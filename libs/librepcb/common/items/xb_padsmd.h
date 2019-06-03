#ifndef LIBREPCB_X_VERSION_XB_PADSMD_H
#define LIBREPCB_X_VERSION_XB_PADSMD_H

#include "xb_baseitem.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace librepcb {

namespace x_version {

class XB_PadSmd : public XB_BaseItem {
Q_OBJECT

public:
  XB_PadSmd()                       = delete;
  XB_PadSmd(const XB_PadSmd& other) = delete;
  XB_PadSmd(Point& position, Length& width, Length& height, Angle& angle,
            Length& roundness, QObject* parent = nullptr);
  ~XB_PadSmd() noexcept;

  XB_ItemType getType() const noexcept override {
    return XB_BaseItem::XB_ItemType::PadSMD;
  }

  const Point& getPosition() const noexcept { return mPosition; }
  const Length& getWidth() const noexcept { return mWidth; }
  const Length& getHeight() const noexcept { return mHeight; }
  const Angle& getAngle() const noexcept { return mAngle; }
  const Length& getRoundness() const noexcept { return mRoundness; }

private:
  Point mPosition;
  Length mWidth;
  Length mHeight;
  Angle mAngle;
  Length mRoundness;
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XB_PADSMD_H
