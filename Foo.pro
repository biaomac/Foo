#-------------------------------------------------
#
# Project created by QtCreator 2013-03-17T14:42:09
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Foo
TEMPLATE = app

CONFIG -= app_bundle


SOURCES += main.cpp\
        Widget.cpp \
    ColorWheel.cpp \
    ColorPicker.cpp

HEADERS  += Widget.hpp \
    ColorWheel.hpp \
    ColorPicker.hpp

FORMS    += Widget.ui

RESOURCES +=
