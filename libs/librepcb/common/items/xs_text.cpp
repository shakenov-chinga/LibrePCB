#include "xs_text.h"

namespace  librepcb {

namespace x_version {

//XS_Text::XS_Text(const SExpression& node) {
//}

XS_Text::XS_Text(QString& text, Point& position, X_TextAlign textAlign,
                 QObject* parent)
  : XS_BaseItem(parent),
    mText(text),
    mPosition(position),
    mTextAlign(textAlign) {
}

XS_Text::~XS_Text() noexcept {
}

} // namespace x_version
} // namespace librepcb
