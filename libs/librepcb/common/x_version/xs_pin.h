#ifndef LIBREPCB_X_VERSION_XS_PIN_H
#define LIBREPCB_X_VERSION_XS_PIN_H

#include "xs_baseitem.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace  librepcb {

namespace x_version {

class XS_Pin : public XS_BaseItem {
Q_OBJECT

public:
  XS_Pin()                    = delete;
  XS_Pin(const XS_Pin& other) = delete;
  XS_Pin(QString& name, Point& position, Length& length,
         QObject* parent = nullptr);
  ~XS_Pin() noexcept;

  XS_ItemType getType() const noexcept override {
    return XS_BaseItem::XS_ItemType::Pin;
  }

  const QString& getName() const noexcept { return mName; }
  const Point& getPosition() const noexcept { return mPosition; }
  const Length& getLength() const noexcept { return mLength; }

private:
  QString mName;
  Point mPosition;
  Length mLength;
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XS_PIN_H
