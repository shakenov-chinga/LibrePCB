#ifndef LIBREPCB_X_VERSION_XB_DEVICE_H
#define LIBREPCB_X_VERSION_XB_DEVICE_H

#include "xb_baseitem.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace librepcb {

namespace project {
class ComponentInstance;
}
using namespace project;

namespace library{
class Device;
class Package;
class Footprint;
}
using namespace library;

namespace x_version {
class XB_Footprint;

class XB_Device : public XB_BaseItem {
Q_OBJECT

public:
  XB_Device(QObject* parent = nullptr);
  XB_Device(const XB_Device& other) = delete;
  ~XB_Device() noexcept;

  XB_ItemType getType() const noexcept override {
    return XB_BaseItem::XB_ItemType::Device;
  }

private:
  // General
  ComponentInstance*           mCompInstance;
  const Device*       mLibDevice;
  const Package*      mLibPackage;
  const Footprint*    mLibFootprint;
  QScopedPointer<XB_Footprint> mFootprint;
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XB_DEVICE_H
