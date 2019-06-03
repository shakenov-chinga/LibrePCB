#-------------------------------------------------
#
# Project created by QtCreator 2015-05-31T12:55:49
#
#-------------------------------------------------

TEMPLATE = lib
TARGET = librepcbcommon

# Use common project definitions
include(../../../common.pri)

# Set preprocessor defines
DEFINES += BUILD_OUTPUT_DIRECTORY="\\\"$${OUTPUT_DIR_ABS}\\\""
DEFINES += SHARE_DIRECTORY_SOURCE="\\\"$${SHARE_DIR_ABS}\\\""
DEFINES += GIT_COMMIT_SHA="\\\"$(shell git -C \""$$_PRO_FILE_PWD_"\" rev-parse --verify HEAD)\\\""

QT += core widgets xml opengl network sql

CONFIG += staticlib

INCLUDEPATH += \
    ../../ \
    ../../fontobene \
    ../../quazip \
    ../../sexpresso \
    ../../type_safe/include \
    ../../type_safe/external/debug_assert \

SOURCES += \
    alignment.cpp \
    application.cpp \
    attributes/attribute.cpp \
    attributes/attributeprovider.cpp \
    attributes/attributesubstitutor.cpp \
    attributes/attributetype.cpp \
    attributes/attributeunit.cpp \
    attributes/attrtypecapacitance.cpp \
    attributes/attrtypecurrent.cpp \
    attributes/attrtypefrequency.cpp \
    attributes/attrtypeinductance.cpp \
    attributes/attrtypepower.cpp \
    attributes/attrtyperesistance.cpp \
    attributes/attrtypestring.cpp \
    attributes/attrtypevoltage.cpp \
    boarddesignrules.cpp \
    cam/excellongenerator.cpp \
    cam/gerberaperturelist.cpp \
    cam/gerbergenerator.cpp \
    debug.cpp \
    dialogs/aboutdialog.cpp \
    dialogs/boarddesignrulesdialog.cpp \
    dialogs/circlepropertiesdialog.cpp \
    dialogs/filedialog.cpp \
    dialogs/gridsettingsdialog.cpp \
    dialogs/holepropertiesdialog.cpp \
    dialogs/polygonpropertiesdialog.cpp \
    dialogs/stroketextpropertiesdialog.cpp \
    dialogs/textpropertiesdialog.cpp \
    exceptions.cpp \
    fileio/directorylock.cpp \
    fileio/filepath.cpp \
    fileio/fileutils.cpp \
    fileio/sexpression.cpp \
    fileio/transactionaldirectory.cpp \
    fileio/transactionalfilesystem.cpp \
    fileio/versionfile.cpp \
    font/strokefont.cpp \
    font/strokefontpool.cpp \
    geometry/circle.cpp \
    geometry/cmd/cmdcircleedit.cpp \
    geometry/cmd/cmdholeedit.cpp \
    geometry/cmd/cmdpolygonedit.cpp \
    geometry/cmd/cmdstroketextedit.cpp \
    geometry/cmd/cmdtextedit.cpp \
    geometry/hole.cpp \
    geometry/path.cpp \
    geometry/polygon.cpp \
    geometry/stroketext.cpp \
    geometry/text.cpp \
    geometry/vertex.cpp \
    graphics/circlegraphicsitem.cpp \
    graphics/defaultgraphicslayerprovider.cpp \
    graphics/graphicslayer.cpp \
    graphics/graphicsscene.cpp \
    graphics/graphicsview.cpp \
    graphics/holegraphicsitem.cpp \
    graphics/linegraphicsitem.cpp \
    graphics/origincrossgraphicsitem.cpp \
    graphics/polygongraphicsitem.cpp \
    graphics/primitivecirclegraphicsitem.cpp \
    graphics/primitivepathgraphicsitem.cpp \
    graphics/primitivetextgraphicsitem.cpp \
    graphics/stroketextgraphicsitem.cpp \
    graphics/textgraphicsitem.cpp \
    gridproperties.cpp \
    network/filedownload.cpp \
    network/networkaccessmanager.cpp \
    network/networkrequest.cpp \
    network/networkrequestbase.cpp \
    network/repository.cpp \
    signalrole.cpp \
    sqlitedatabase.cpp \
    systeminfo.cpp \
    toolbox.cpp \
    undocommand.cpp \
    undocommandgroup.cpp \
    undostack.cpp \
    units/angle.cpp \
    units/length.cpp \
    units/lengthunit.cpp \
    units/point.cpp \
    units/ratio.cpp \
    utils/clipperhelpers.cpp \
    utils/exclusiveactiongroup.cpp \
    utils/graphicslayerstackappearancesettings.cpp \
    utils/toolbarproxy.cpp \
    utils/undostackactiongroup.cpp \
    uuid.cpp \
    version.cpp \
    widgets/alignmentselector.cpp \
    widgets/attributelisteditorwidget.cpp \
    widgets/attributetypecombobox.cpp \
    widgets/attributeunitcombobox.cpp \
    widgets/centeredcheckbox.cpp \
    widgets/graphicslayercombobox.cpp \
    widgets/patheditorwidget.cpp \
    widgets/plaintextedit.cpp \
    widgets/signalrolecombobox.cpp \
    widgets/statusbar.cpp \
    widgets/tabwidget.cpp \
    items/xs_baseitem.cpp \
    items/xs_circle.cpp \
    items/x_board.cpp \
    items/x_schematic.cpp \
    items/xb_baseitem.cpp \
    items/xb_device.cpp \
    items/xb_circle.cpp \
    items/xb_footprint.cpp \
    items/xb_hole.cpp \
    items/xb_padpth.cpp \
    items/xb_padsmd.cpp \
    items/xb_path.cpp \
    items/xb_polygon.cpp \
    items/xb_text.cpp \
    items/xb_via.cpp \
    items/xs_path.cpp \
    items/xs_pin.cpp \
    items/xs_polygon.cpp \
    items/xs_text.cpp \
    items/xs_symbol.cpp \
    items/xs_line.cpp \
    items/xb_line.cpp

HEADERS += \
    alignment.h \
    application.h \
    attributes/attribute.h \
    attributes/attributekey.h \
    attributes/attributeprovider.h \
    attributes/attributesubstitutor.h \
    attributes/attributetype.h \
    attributes/attributeunit.h \
    attributes/attrtypecapacitance.h \
    attributes/attrtypecurrent.h \
    attributes/attrtypefrequency.h \
    attributes/attrtypeinductance.h \
    attributes/attrtypepower.h \
    attributes/attrtyperesistance.h \
    attributes/attrtypestring.h \
    attributes/attrtypevoltage.h \
    boarddesignrules.h \
    cam/excellongenerator.h \
    cam/gerberaperturelist.h \
    cam/gerbergenerator.h \
    circuitidentifier.h \
    debug.h \
    dialogs/aboutdialog.h \
    dialogs/boarddesignrulesdialog.h \
    dialogs/circlepropertiesdialog.h \
    dialogs/filedialog.h \
    dialogs/gridsettingsdialog.h \
    dialogs/holepropertiesdialog.h \
    dialogs/polygonpropertiesdialog.h \
    dialogs/stroketextpropertiesdialog.h \
    dialogs/textpropertiesdialog.h \
    elementname.h \
    exceptions.h \
    fileio/cmd/cmdlistelementinsert.h \
    fileio/cmd/cmdlistelementremove.h \
    fileio/cmd/cmdlistelementsswap.h \
    fileio/directorylock.h \
    fileio/filepath.h \
    fileio/filesystem.h \
    fileio/fileutils.h \
    fileio/serializablekeyvaluemap.h \
    fileio/serializableobject.h \
    fileio/serializableobjectlist.h \
    fileio/sexpression.h \
    fileio/transactionaldirectory.h \
    fileio/transactionalfilesystem.h \
    fileio/versionfile.h \
    font/strokefont.h \
    font/strokefontpool.h \
    geometry/circle.h \
    geometry/cmd/cmdcircleedit.h \
    geometry/cmd/cmdholeedit.h \
    geometry/cmd/cmdpolygonedit.h \
    geometry/cmd/cmdstroketextedit.h \
    geometry/cmd/cmdtextedit.h \
    geometry/hole.h \
    geometry/path.h \
    geometry/polygon.h \
    geometry/stroketext.h \
    geometry/text.h \
    geometry/vertex.h \
    graphics/circlegraphicsitem.h \
    graphics/defaultgraphicslayerprovider.h \
    graphics/graphicslayer.h \
    graphics/graphicslayername.h \
    graphics/graphicsscene.h \
    graphics/graphicsview.h \
    graphics/holegraphicsitem.h \
    graphics/if_graphicsvieweventhandler.h \
    graphics/linegraphicsitem.h \
    graphics/origincrossgraphicsitem.h \
    graphics/polygongraphicsitem.h \
    graphics/primitivecirclegraphicsitem.h \
    graphics/primitivepathgraphicsitem.h \
    graphics/primitivetextgraphicsitem.h \
    graphics/stroketextgraphicsitem.h \
    graphics/textgraphicsitem.h \
    gridproperties.h \
    network/filedownload.h \
    network/networkaccessmanager.h \
    network/networkrequest.h \
    network/networkrequestbase.h \
    network/repository.h \
    norms.h \
    scopeguard.h \
    scopeguardlist.h \
    signalrole.h \
    signalslot.h \
    sqlitedatabase.h \
    systeminfo.h \
    toolbox.h \
    undocommand.h \
    undocommandgroup.h \
    undostack.h \
    units/all_length_units.h \
    units/angle.h \
    units/length.h \
    units/lengthunit.h \
    units/point.h \
    units/ratio.h \
    utils/clipperhelpers.h \
    utils/exclusiveactiongroup.h \
    utils/graphicslayerstackappearancesettings.h \
    utils/toolbarproxy.h \
    utils/undostackactiongroup.h \
    uuid.h \
    version.h \
    widgets/alignmentselector.h \
    widgets/attributelisteditorwidget.h \
    widgets/attributetypecombobox.h \
    widgets/attributeunitcombobox.h \
    widgets/centeredcheckbox.h \
    widgets/graphicslayercombobox.h \
    widgets/patheditorwidget.h \
    widgets/plaintextedit.h \
    widgets/signalrolecombobox.h \
    widgets/statusbar.h \
    widgets/tabwidget.h \
    items/xs_baseitem.h \
    items/xs_circle.h \
    items/x_board.h \
    items/x_schematic.h \
    items/xb_baseitem.h \
    items/xb_device.h \
    items/xb_circle.h \
    items/xb_footprint.h \
    items/xb_hole.h \
    items/xb_padpth.h \
    items/xb_padsmd.h \
    items/xb_path.h \
    items/xb_polygon.h \
    items/xb_text.h \
    items/xb_via.h \
    items/xs_path.h \
    items/xs_pin.h \
    items/xs_polygon.h \
    items/xs_text.h \
    items/xs_symbol.h \
    items/x_textalign.h \
    items/xs_line.h \
    items/xb_line.h

FORMS += \
    dialogs/aboutdialog.ui \
    dialogs/boarddesignrulesdialog.ui \
    dialogs/circlepropertiesdialog.ui \
    dialogs/gridsettingsdialog.ui \
    dialogs/holepropertiesdialog.ui \
    dialogs/polygonpropertiesdialog.ui \
    dialogs/stroketextpropertiesdialog.ui \
    dialogs/textpropertiesdialog.ui \
    widgets/alignmentselector.ui \

