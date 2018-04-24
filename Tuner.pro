#-------------------------------------------------
#
# Project created by QtCreator 2018-03-09T12:27:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += multimedia widgets printsupport

TARGET = Tuner
TEMPLATE = app

INCLUDEPATH += "/home/noblinthegoblin/fftw3/fftw-3.3.7"

SOURCES += main.cpp\
        tunergui.cpp \
    qcustomplot.cpp \
    ../../../Lau/RuffnerAudioFilter/LAUAudioFilter/lauaudioobject.cpp

HEADERS  += tunergui.h \
    qcustomplot.h \
    ../../../Lau/RuffnerAudioFilter/LAUAudioFilter/lauaudioobject.h

FORMS    += tunergui.ui

LIBS     += -lfftw3
