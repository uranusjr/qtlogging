QT       += testlib

QT       -= gui

TARGET    = qtloggingtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE  = app

include(../qtlogging.pri)

DEFINES += SRCDIR=\\\"$$PWD/../src\\\"

INCLUDEPATH += $$PWD/../src

SOURCES += \
    qtloggingtest.cpp \
    test_main.cpp

HEADERS += \
    qtloggingtest.h
