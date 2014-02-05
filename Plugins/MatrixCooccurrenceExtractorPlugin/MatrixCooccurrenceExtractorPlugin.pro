TEMPLATE      = lib
TARGET        = matrixcooccurrenceextractor
CONFIG       += plugin

INCLUDEPATH  += ../../glMiSOM/ \
                "/usr/include/opencv"
LIBS         += -L/usr/lib \
                -lcv \
                -lhighgui
HEADERS      += ../../glMiSOM/Extractor/extractorinterface.h \
                ../../glMiSOM/Extractor/extractorwidgetinterface.h \
                ../../glMiSOM/Core/image.h \
                ../../glMiSOM/Core/feature.h \
                ../../glMiSOM/util.h \
                glcm.h \
                matrixcooccurrenceextractor.h \
                matrixcooccurrencewidget.h
SOURCES       = ../../glMiSOM/Core/image.cpp \
                ../../glMiSOM/Core/feature.cpp \
                ../../glMiSOM/util.cpp \
                glcm.cpp \
                matrixcooccurrenceextractor.cpp \
                matrixcooccurrencewidget.cpp
TARGET        = $$qtLibraryTarget(matrixcooccurrenceextractor)
DESTDIR       = ../../glMiSOM-build-desktop/plugins

target.path  += ../../glMiSOM-build-desktop/plugins
INSTALLS     += target
