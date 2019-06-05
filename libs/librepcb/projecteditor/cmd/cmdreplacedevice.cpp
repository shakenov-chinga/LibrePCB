/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * https://librepcb.org/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************************
 *  Includes
 ******************************************************************************/
#include "cmdreplacedevice.h"

#include "cmdadddevicetoboard.h"

#include <librepcb/common/scopeguard.h>
#include <librepcb/project/boards/board.h>
#include <librepcb/project/boards/cmd/cmdboardnetpointedit.h>
#include <librepcb/project/boards/cmd/cmdboardnetsegmentadd.h>
#include <librepcb/project/boards/cmd/cmdboardnetsegmentremove.h>
#include <librepcb/project/boards/cmd/cmddeviceinstanceremove.h>
#include <librepcb/project/boards/items/bi_device.h>
#include <librepcb/project/boards/items/bi_footprint.h>
#include <librepcb/project/boards/items/bi_footprintpad.h>
#include <librepcb/project/boards/items/bi_netline.h>
#include <librepcb/project/boards/items/bi_netpoint.h>
#include <librepcb/project/project.h>

#include <QtCore>

/*******************************************************************************
 *  Namespace
 ******************************************************************************/
namespace librepcb {
namespace project {
namespace editor {

/*******************************************************************************
 *  Constructors / Destructor
 ******************************************************************************/

CmdReplaceDevice::CmdReplaceDevice(
    workspace::Workspace& workspace, X_Board& board, BI_Device& device,
    const Uuid&               newDeviceUuid,
    const tl::optional<Uuid>& newFootprintUuid) noexcept
  : UndoCommandGroup(tr("Change Device")),
    mWorkspace(workspace),
    mBoard(board),
    mDeviceInstance(device),
    mNewDeviceUuid(newDeviceUuid),
    mNewFootprintUuid(newFootprintUuid) {
}

CmdReplaceDevice::~CmdReplaceDevice() noexcept {
}

/*******************************************************************************
 *  Inherited from UndoCommand
 ******************************************************************************/

bool CmdReplaceDevice::performExecute() {
  // if an error occurs, undo all already executed child commands
  auto undoScopeGuard = scopeGuard([&]() { performUndo(); });

  // remove all connected netlines
  foreach (BI_FootprintPad* pad, mDeviceInstance.getFootprint().getPads()) {
    BI_NetSegment* netsegment = pad->getNetSegmentOfLines();
    if (netsegment) {
      execNewChildCmd(new CmdBoardNetSegmentRemove(*netsegment));  // can throw
    }
  }

  // replace the device instance
  execNewChildCmd(new CmdDeviceInstanceRemove(mDeviceInstance));  // can throw
  CmdAddDeviceToBoard* cmd = new CmdAddDeviceToBoard(
      mWorkspace, mBoard, mDeviceInstance.getComponentInstance(),
      mNewDeviceUuid, mNewFootprintUuid, mDeviceInstance.getPosition(),
      mDeviceInstance.getRotation(), mDeviceInstance.getIsMirrored());
  execNewChildCmd(cmd);  // can throw
  BI_Device* newDevice = cmd->getDeviceInstance();
  Q_ASSERT(newDevice);

  // TODO: reconnect all netpoints/netlines

  undoScopeGuard.dismiss();  // no undo required
  return (getChildCount() > 0);
}

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace editor
}  // namespace project
}  // namespace librepcb
