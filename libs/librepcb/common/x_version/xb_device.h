#ifndef LIBREPCB_X_VERSION_XB_DEVICE_H
#define LIBREPCB_X_VERSION_XB_DEVICE_H

#include "xb_baseitem.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace librepcb {

namespace x_version {

class XB_Device : public XB_BaseItem {
Q_OBJECT

public:
  XB_Device(QObject* parent = nullptr);
  XB_Device(const XB_Device& other) = delete;
  ~XB_Device() noexcept;

  XB_ItemType getType() const noexcept override {
    return XB_BaseItem::XB_ItemType::Device;
  }
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XB_DEVICE_H
