#-------------------------------------------------
#
# Project created by QtCreator 2015-01-29T15:57:01
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ImageProject
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    renderarea.cpp \
    labelimage.cpp \
    updater.cpp \
    calcwidget.cpp \
    qcustomplot.cpp

HEADERS  += window.h \
    renderarea.h \
    labelimage.h \
    updater.h \
    spc.h \
    calcwidget.h \
    qcustomplot.h

FORMS    +=
