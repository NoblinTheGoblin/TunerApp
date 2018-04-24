#-------------------------------------------------
#
# Project created by QtCreator 2018-03-09T12:27:28
#
#-------------------------------------------------

QT       += core gui widgets multimedia opengl printsupport

TARGET = Tuner
TEMPLATE = app

unix:macx{
    INCLUDEPATH += /usr/local/include
    DEPENDPATH  += /usr/local/include
    LIBS        += -L/usr/local/lib -lfftw3
}

unix:!macx{
    INCLUDEPATH += "/home/noblinthegoblin/fftw3/fftw-3.3.7"
    LIBS     += -lfftw3
}

SOURCES  += main.cpp\
            tunergui.cpp \
            qcustomplot.cpp \
            lauaudioobject.cpp \
    laufftobject.cpp

HEADERS  += tunergui.h \
            qcustomplot.h \
            lauaudioobject.h \
    laufftobject.h

FORMS    += tunergui.ui

LIBS     += -lfftw3
