#-------------------------------------------------
#
# Project created by QtCreator 2015-01-29T15:57:01
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH +=/usr/include/opencv2\
                /usr/include/opencv\
                /usr/include/opencv2/core

LIBS += `pkg-config opencv --libs`

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ImageProject
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    renderarea.cpp \
    labelimage.cpp \
    updater.cpp \
    calcwidget.cpp \
    qcustomplot.cpp \
    plotingwidget.cpp \
    strategie.cpp \
    derivedalgo.cpp \
    tfd.cpp \
    optionwidget.cpp \
    modifierwidget.cpp \
    analyzewidget.cpp \
    camerawidget.cpp \
    camerathread.cpp

HEADERS  += window.h \
    renderarea.h \
    labelimage.h \
    updater.h \
    spc.h \
    calcwidget.h \
    qcustomplot.h \
    plotingwidget.h \
    strategie.h \
    derivedealgo.h \
    Vector.h \
    tfd.h \
    optionwidget.h \
    modifierwidget.h \
    analyzewidget.h \
    camerawidget.h \
    camerathread.h

FORMS    +=
