#-------------------------------------------------
#
# Project created by QtCreator 2013-03-15T16:13:42
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++0x #For GCC-4.7

QMAKE_CXXFLAGS += -DDEBUG

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui