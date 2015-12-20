#-------------------------------------------------
#
# Project created by QtCreator 2015-05-31T12:53:17
#
#-------------------------------------------------

TEMPLATE = lib
TARGET = librepcblibrary

# Set the path for the generated binary
GENERATED_DIR = ../../generated

# Use common project definitions
include(../../common.pri)

QT += core widgets xml sql printsupport

CONFIG += staticlib

INCLUDEPATH += \
    ../

HEADERS += \
    cat/componentcategory.h \
    cat/packagecategory.h \
    pkg/footprint.h \
    pkg/package.h \
    spcmdl/spicemodel.h \
    sym/symbol.h \
    sym/symbolellipse.h \
    sym/symbolpin.h \
    sym/symbolpinpreviewgraphicsitem.h \
    sym/symbolpolygon.h \
    sym/symbolpreviewgraphicsitem.h \
    sym/symboltext.h \
    library.h \
    librarybaseelement.h \
    libraryelement.h \
    libraryelementattribute.h \
    pkg/footprintpolygon.h \
    pkg/footprintellipse.h \
    pkg/footprinttext.h \
    pkg/footprintpad.h \
    cat/librarycategory.h \
    cat/categorytreemodel.h \
    cat/categorytreeitem.h \
    elements.h \
    dev/device.h \
    cmp/component.h \
    cmp/componentsignal.h \
    cmp/componentsymbolvariant.h \
    cmp/componentsymbolvariantitem.h \
    pkg/packagepad.h

SOURCES += \
    cat/componentcategory.cpp \
    cat/packagecategory.cpp \
    pkg/footprint.cpp \
    pkg/package.cpp \
    spcmdl/spicemodel.cpp \
    sym/symbol.cpp \
    sym/symbolellipse.cpp \
    sym/symbolpin.cpp \
    sym/symbolpinpreviewgraphicsitem.cpp \
    sym/symbolpolygon.cpp \
    sym/symbolpreviewgraphicsitem.cpp \
    sym/symboltext.cpp \
    library.cpp \
    librarybaseelement.cpp \
    libraryelement.cpp \
    libraryelementattribute.cpp \
    pkg/footprintpolygon.cpp \
    pkg/footprintellipse.cpp \
    pkg/footprinttext.cpp \
    pkg/footprintpad.cpp \
    cat/librarycategory.cpp \
    cat/categorytreemodel.cpp \
    cat/categorytreeitem.cpp \
    dev/device.cpp \
    cmp/componentsignal.cpp \
    cmp/componentsymbolvariant.cpp \
    cmp/componentsymbolvariantitem.cpp \
    cmp/component.cpp \
    pkg/packagepad.cpp

