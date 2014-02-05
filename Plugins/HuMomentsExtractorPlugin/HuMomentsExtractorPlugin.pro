TEMPLATE      = lib
TARGET        = humomentsextractor
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
    humomentsextractor.h \
    humomentswidget.h
SOURCES       = ../../glMiSOM/Core/image.cpp \
                ../../glMiSOM/Core/feature.cpp \
                ../../glMiSOM/util.cpp \
    humomentsextractor.cpp \
    humomentswidget.cpp
TARGET        = $$qtLibraryTarget(humomentsextractor)
DESTDIR       = ../../glMiSOM-build-desktop/plugins

target.path  += ../../glMiSOM-build-desktop/plugins
INSTALLS     += target
