#-------------------------------------------------
#
# Project created by QtCreator 2014-03-23T22:18:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = diff
TEMPLATE = app


SOURCES += ../../src/qt/main.cpp \
    ../../src/qt/mainwindow.cpp \
    ../../src/qt/codeeditor.cpp

HEADERS  += ../../src/qt/mainwindow.h \
    ../../src/qt/codeeditor.h

FORMS    += mainwindow.ui
