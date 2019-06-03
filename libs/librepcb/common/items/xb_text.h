#ifndef LIBREPCB_X_VERSION_XB_TEXT_H
#define LIBREPCB_X_VERSION_XB_TEXT_H

#include "xb_baseitem.h"
#include "x_textalign.h"

#include <librepcb/common/units/all_length_units.h>

#include <QtCore>

namespace librepcb {

namespace x_version {

class XB_Text : public XB_BaseItem {
Q_OBJECT

public:
  XB_Text()                     = delete;
  XB_Text(const XB_Text& other) = delete;
  XB_Text(QString& text, Point& position, X_TextAlign textAlign,
          QObject* parent = nullptr);
  ~XB_Text() noexcept;

  XB_ItemType getType() const noexcept override {
    return XB_BaseItem::XB_ItemType::Text;
  }

  const QString& getText() const noexcept { return mText; }
  const Point& getPosition() const noexcept { return mPosition; }
  X_TextAlign getTextAlign() const noexcept { return mTextAlign; }

private:
  QString mText;
  Point mPosition;
  X_TextAlign mTextAlign;
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XB_TEXT_H
