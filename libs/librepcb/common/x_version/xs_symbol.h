#ifndef LIBREPCB_X_VERSION_XS_SYMBOL_H
#define LIBREPCB_X_VERSION_XS_SYMBOL_H

#include <QtCore>

#include "xs_baseitem.h"

#include <librepcb/common/units/all_length_units.h>

namespace  librepcb {

namespace x_version {

class XS_Symbol : public XS_BaseItem {
Q_OBJECT

public:
  XS_Symbol(QObject* parent = nullptr);
  XS_Symbol(const XS_Symbol& other) = delete;
  ~XS_Symbol() noexcept;

  XS_ItemType getType() const noexcept override {
    return XS_BaseItem::XS_ItemType::Symbol;
  }
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XS_SYMBOL_H
