#-------------------------------------------------
#
# Project created by QtCreator 2011-10-01T15:41:10
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = thumpeg4
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH  += ../../glMiSOM/ \
                "/usr/include/opencv" \
                /home/manleviet/MPEG7FexLib/include
LIBS         += -L/usr/lib \
                -lcv \
                -lhighgui \
                -L/home/manleviet/MPEG7FexLib/include/libMPEG7Fex.a

HEADERS +=
