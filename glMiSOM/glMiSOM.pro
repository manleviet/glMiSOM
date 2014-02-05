#-------------------------------------------------
#
# Project created by QtCreator 2011-09-01T12:41:28
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = glMiSOM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Core/image.cpp \
    Core/feature.cpp \
    Core/baseimage.cpp \
    util.cpp \
    Scene/glsomscene.cpp \
    Scene/glimage.cpp \
    Core/gridsom.cpp \
    Core/rowsom.cpp \
    Core/cellsom.cpp \
    Scene/animator.cpp \
    UI/extrairefeaturesdialog.cpp \
    UI/viewmetadatadialog.cpp \
    UI/viewimagedialog.cpp \
    UI/indexationdialog.cpp \
    SOM/mapsom.cpp \
    SOM/entrysom.cpp \
    SOM/winnerinfo.cpp \
    SOM/featureschosenlist.cpp \
    SOM/stableinfo.cpp \
    UI/chosendescriptors.cpp \
    UI/weightdelegate.cpp \
    UI/capturescreendialog.cpp \
    UI/pluginsdialog.cpp \
    UI/viewcodesdialog.cpp \
    UI/codedialog.cpp \
    Exception/incorrespondentexception.cpp

HEADERS  += mainwindow.h \
    Core/image.h \
    Core/feature.h \
    Core/baseimage.h \
    util.h \
    Scene/glsomscene.h \
    Scene/glimage.h \
    Core/gridsom.h \
    Core/rowsom.h \
    Core/cellsom.h \
    Scene/animator.h \
    UI/extrairefeaturesdialog.h \
    UI/viewmetadatadialog.h \
    UI/viewimagedialog.h \
    UI/indexationdialog.h \
    SOM/mapsom.h \
    SOM/entrysom.h \
    SOM/winnerinfo.h \
    SOM/featureschosenlist.h \
    SOM/stableinfo.h \
    UI/chosendescriptors.h \
    UI/weightdelegate.h \
    Extractor/extractorinterface.h \
    Extractor/extractorwidgetinterface.h \
    UI/capturescreendialog.h \
    UI/pluginsdialog.h \
    UI/viewcodesdialog.h \
    UI/codedialog.h \
    Exception/incorrespondentexception.h

FORMS    += mainwindow.ui \
    UI/extrairefeaturesdialog.ui \
    UI/viewmetadatadialog.ui \
    UI/viewimagedialog.ui \
    UI/indexationdialog.ui \
    UI/capturescreendialog.ui \
    UI/pluginsdialog.ui \
    UI/viewcodesdialog.ui \
    UI/codedialog.ui

INCLUDEPATH += "/usr/include/opencv"
LIBS += -L/usr/lib \
    -lcv \
    -lhighgui \
    -L./plugins -lcolorhistogramextractor \
    -L./plugins -lhumomentsextractor \
    -L./plugins -lmatrixcooccurrence2extractor

OTHER_FILES += \
    Readme.txt
