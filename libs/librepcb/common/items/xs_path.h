#ifndef LIBREPCB_X_VERSION_XS_PATH_H
#define LIBREPCB_X_VERSION_XS_PATH_H

#include "xs_baseitem.h"
#include "xs_line.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace  librepcb {

namespace x_version {

class XS_Path : public XS_BaseItem {
Q_OBJECT

public:
  XS_Path(QObject* parent = nullptr);
  XS_Path(const XS_Path& other) = delete;
  ~XS_Path() noexcept;

  XS_ItemType getType() const noexcept override {
    return XS_BaseItem::XS_ItemType::Polygon;
  }

  void addLine(XS_Line* line) const noexcept;

private:
  QList<Point*> mPoints;
  QList<XS_Line*> mLines;
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XS_PATH_H
