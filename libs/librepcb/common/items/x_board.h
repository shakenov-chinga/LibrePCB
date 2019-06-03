#ifndef LIBREPCB_X_VERSION_X_BOARD_H
#define LIBREPCB_X_VERSION_X_BOARD_H
/*******************************************************************************
 *  Includes
 ******************************************************************************/
#include "../../project/erc/if_ercmsgprovider.h"

#include <librepcb/common/attributes/attributeprovider.h>
#include <librepcb/common/elementname.h>
#include <librepcb/common/exceptions.h>
#include <librepcb/common/fileio/filepath.h>
#include <librepcb/common/fileio/serializableobject.h>
#include <librepcb/common/fileio/transactionaldirectory.h>
#include <librepcb/common/units/all_length_units.h>
#include <librepcb/common/uuid.h>

#include <QtCore>
#include <QtWidgets>

#include <memory>

/*******************************************************************************
 *  Namespace / Forward Declarations
 ******************************************************************************/

namespace librepcb {

namespace x_version{

class X_Board final : public QObject {
Q_OBJECT

public:
  X_Board()                     = delete;
  X_Board(const X_Board& other) = delete;
  X_Board(QObject* parent = nullptr);
  ~X_Board() noexcept;

};

}  // namespace x_version
}  // namespace librepcb

#endif // LIBREPCB_X_VERSION_X_BOARD_H
