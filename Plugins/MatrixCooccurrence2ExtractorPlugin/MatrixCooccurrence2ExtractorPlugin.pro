TEMPLATE      = lib
TARGET        = matrixcooccurrence2extractor
CONFIG       += plugin static

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
                matrixcooccurrence2extractor.h \
                matrixcooccurrence2widget.h \
                glcm.h
SOURCES       = ../../glMiSOM/Core/image.cpp \
                ../../glMiSOM/Core/feature.cpp \
                ../../glMiSOM/util.cpp \
                matrixcooccurrence2extractor.cpp \
                matrixcooccurrence2widget.cpp \
                glcm.cpp
TARGET        = $$qtLibraryTarget(matrixcooccurrence2extractor)
DESTDIR       = ../../glMiSOM-build-desktop/plugins

target.path  += ../../glMiSOM-build-desktop/plugins
INSTALLS     += target
