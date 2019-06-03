#ifndef LIBREPCB_X_VERSION_X_SCHEMATIC_H
#define LIBREPCB_X_VERSION_X_SCHEMATIC_H

#include <QtCore>

namespace librepcb {

namespace x_version {

class X_Schematic : public QObject {
Q_OBJECT

public:
  X_Schematic()                         = delete;
  X_Schematic(const X_Schematic& other) = delete;
  X_Schematic(QObject* parent = nullptr);
  ~X_Schematic() noexcept;
};

} // namespace x_version
} // namespace librepcb

#endif // LIBREPCB_X_VERSION_X_SCHEMATIC_H
