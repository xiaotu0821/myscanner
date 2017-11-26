#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T15:54:29
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
LIBS += libws32.a
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += \
    mainwindow.hpp

FORMS    += mainwindow.ui
