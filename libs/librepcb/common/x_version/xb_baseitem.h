#ifndef LIBREPCB_X_VERSION_XB_BASEITEM_H
#define LIBREPCB_X_VERSION_XB_BASEITEM_H

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace  librepcb {

namespace x_version {

class XB_BaseItem : public QObject {
Q_OBJECT

public:
  enum class XB_ItemType{
    Circle, Device, Footprint, Hole, Line, PadPTH, PadSMD, Path, Polygon, Text,
    Via
  };

  XB_BaseItem(); //                     = delete;
  XB_BaseItem(const XB_BaseItem& other) = delete;
  XB_BaseItem(QObject* parent = nullptr);
//  XB_BaseItem(X_Board& board) noexcept;
  virtual ~XB_BaseItem() noexcept;

  virtual XB_ItemType getType() const noexcept = 0;

signals:

public slots:
};

} // namespace librepcb
} // namespace x_version

#endif // LIBREPCB_X_VERSION_XB_BASEITEM_H
