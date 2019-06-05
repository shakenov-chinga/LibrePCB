#ifndef LIBREPCB_X_VERSION_XB_FOOTPRINT_H
#define LIBREPCB_X_VERSION_XB_FOOTPRINT_H

#include "xb_baseitem.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace librepcb {

namespace  x_version {

class XB_Footprint : public XB_BaseItem {

Q_OBJECT
public:
  XB_Footprint(QObject* parent = nullptr);
  XB_Footprint(const XB_Footprint* other) = delete;
  ~XB_Footprint() noexcept;

  XB_ItemType getType() const noexcept override {
    return XB_BaseItem::XB_ItemType::Footprint;
  }
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XB_FOOTPRINT_H
