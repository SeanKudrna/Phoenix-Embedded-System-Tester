#-------------------------------------------------
#
# Project created by QtCreator 2020-12-15T08:28:57
#
#-------------------------------------------------

QT       += core gui
QT +=serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pp
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

CONFIG += c++11

SOURCES += \
        main.cpp \
    equipment/bk.cpp \
    equipment/bk2831e.cpp \
    equipment/bk9200.cpp \
    equipment/GSerial.cpp \
    equipment/SerialDevice.cpp \
    equipment/serialrxthread.cpp \
    Pi2c-master/mcp2317.cpp \
    Pi2c-master/pi2c.cpp \
    vars.cpp \
    relay.cpp \
    capitalequipment.cpp \
    can.cpp \
    lib.c \
    mainwindow.cpp \
    testmenu.cpp \
    dactest.cpp \
    dac.cpp \
    relaydriver.cpp \
    powersupply2.cpp

HEADERS += \
        mainwindow.h \
    equipment/bk.h \
    equipment/bk2831e.h \
    equipment/bk9200.h \
    equipment/GSerial.h \
    equipment/SerialDevice.h \
    equipment/serialrxthread.h \
    equipment/types.h \
    Pi2c-master/mcp2317.h \
    Pi2c-master/pi2c.h \
    vars.h \
    relay.h \
    capitalequipment.h \
    can.h \
    lib.h \
    j1939.h \
    testmenu.h \
    dactest.h \
    dac.h \
    relaydriver.h \
    powersupply2.h

FORMS += \
        mainwindow.ui \
    powersupply2.ui \
    testmenu.ui \
    dactest.ui \
    relaydriver.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
