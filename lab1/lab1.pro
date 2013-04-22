#-------------------------------------------------
#
# Project created by QtCreator 2013-03-15T16:13:42
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -Wall -Wextra -pedantic -lpoppler-qt4

LIBS += -L/usr/local/lib -lpoppler -lpoppler-qt4

QMAKE_CXXFLAGS += -std=c++0x #For GCC-4.6

QMAKE_CXXFLAGS += -DDEBUG

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gronsfeld.cpp \
    xorcypher.cpp \
    elgamal.cpp \
    rsaencrypt.cpp \
    rsadecrypt.cpp \
    rsagenerate.cpp \
    rsa.cpp \
    utils.cpp

HEADERS  += mainwindow.h \
    gronsfeld.h \
    xorcypher.hpp \
    elgamal.hpp \
    rsaencrypt.h \
    rsadecrypt.h \
    rsagenerate.h \
    rsa.h \
    utils.h

FORMS    += mainwindow.ui
