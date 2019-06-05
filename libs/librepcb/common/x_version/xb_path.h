#ifndef LIBREPCB_X_VERSION_XB_PATH_H
#define LIBREPCB_X_VERSION_XB_PATH_H

#include "xb_baseitem.h"
#include "xb_line.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace librepcb {

namespace x_version {

class XB_Path : public XB_BaseItem {
Q_OBJECT

public:
  XB_Path(QObject* parent = nullptr);
  XB_Path(const XB_Path& other) = delete;
  ~XB_Path() noexcept;

  XB_ItemType getType() const noexcept override {
    return XB_BaseItem::XB_ItemType::Path;
  }

  void addLine(XB_Line* line) const noexcept;

private:
  QList<Point*> mCorners;
  QList<XB_Line*> mLines;
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XB_PATH_H
