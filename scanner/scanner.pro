#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T10:43:20
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
LIBS += -lws2_32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scanner
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += \
    mainwindow.hpp

FORMS    += mainwindow.ui

RESOURCES += \
    ../ziyuanfile.qrc
