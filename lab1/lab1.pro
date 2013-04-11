#-------------------------------------------------
#
# Project created by QtCreator 2013-03-15T16:13:42
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -O2 -Wall -Wextra -pedantic

QMAKE_CXXFLAGS += -std=c++0x #For GCC-4.7

QMAKE_CXXFLAGS += -DDEBUG

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gronsfeld.cpp \
    xorcypher.cpp \
    elgamal.cpp

HEADERS  += mainwindow.h \
    gronsfeld.h \
    xorcypher.hpp \
    elgamal.hpp

FORMS    += mainwindow.ui
