#ifndef LIBREPCB_X_VERSION_XS_TEXT_H
#define LIBREPCB_X_VERSION_XS_TEXT_H

#include "xs_baseitem.h"
#include "x_textalign.h"
#include "xs_symbol.h"

#include <librepcb/common/units/all_length_units.h>
#include <librepcb/common/fileio/serializableobject.h>

#include <QtCore>

namespace  librepcb {

namespace x_version {

class XS_Text : public XS_BaseItem {
Q_OBJECT

public:
  XS_Text()                     = delete;
  XS_Text(const XS_Text& other) = delete;
//  XS_Text(const SExpression& node);
  XS_Text(QString& text, Point& position, X_TextAlign textAlign,
          QObject* parent = nullptr);
  ~XS_Text() noexcept;

  XS_ItemType getType() const noexcept override {
    return XS_BaseItem::XS_ItemType::Text;
  }

  const QString& getText() const noexcept { return mText; }
  const Point& getPosition() const noexcept { return mPosition; }
  X_TextAlign getTextAlign() const noexcept { return mTextAlign; }

private:
//  Uuid mUuid;
  QString mText;
  Point mPosition;
  X_TextAlign mTextAlign;

};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_XS_TEXT_H
