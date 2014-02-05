TEMPLATE      = lib
TARGET        = colorhistogramextractor
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
                colorhistogramextractor.h \
                colorhistogramwidget.h
SOURCES       = ../../glMiSOM/Core/image.cpp \
                ../../glMiSOM/Core/feature.cpp \
                ../../glMiSOM/util.cpp \
                colorhistogramextractor.cpp \
                colorhistogramwidget.cpp
TARGET        = $$qtLibraryTarget(colorhistogramextractor)
DESTDIR       = ../../glMiSOM-build-desktop/plugins

target.path  += ../../glMiSOM-build-desktop/plugins
INSTALLS     += target
