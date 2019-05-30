#-------------------------------------------------
#
# Project created by QtCreator 2019-05-14T22:35:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        acerca/acercade.cpp \
        error/error.cpp \
        game/clases/alfil.cpp \
        game/clases/caballo.cpp \
        game/clases/cuadroselect.cpp \
        game/clases/peon.cpp \
        game/clases/piezabase.cpp \
        game/clases/reina.cpp \
        game/clases/rey.cpp \
        game/clases/torre.cpp \
        game/coronacionpeon.cpp \
        game/tablero.cpp \
        main.cpp \
        menu.cpp

HEADERS += \
        acerca/acercade.h \
        error/error.h \
        game/clases/alfil.h \
        game/clases/caballo.h \
        game/clases/cuadroselect.h \
        game/clases/peon.h \
        game/clases/piezabase.h \
        game/clases/reina.h \
        game/clases/rey.h \
        game/clases/torre.h \
        game/coronacionpeon.h \
        game/global.hpp \
        game/tablero.h \
        menu.hpp

FORMS += \
        acerca/acercade.ui \
        error/error.ui \
        game/coronacionpeon.ui \
        game/tablero.ui \
        menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
