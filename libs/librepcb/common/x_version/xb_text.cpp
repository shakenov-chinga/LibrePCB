#include "xb_text.h"

namespace  librepcb {

namespace x_version {

XB_Text::XB_Text(QString& text, Point& position, X_TextAlign textAlign,
                 QObject* parent)
  : XB_BaseItem(parent),
    mText(text),
    mPosition(position),
    mTextAlign(textAlign) {
}

XB_Text::~XB_Text() {
}

} // namespace x_version
} // namespace librepcb
