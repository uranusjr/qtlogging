QT      += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    CONFIG += c++11
}

TARGET   = qtlogging
TEMPLATE = lib

include(../qtlogging.pri)

DEFINES += QTLOGGING_LIBRARY

unix {
    target.path = /usr/lib
    INSTALLS += target
}
