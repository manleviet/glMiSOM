//
//
// extractorinterface.h
//
// Un interface pour tous les extracteurs des descripteurs
//
// LE Viet Man
// 02/09/2011
//
//

#ifndef EXTRACTORINTERFACE_H
#define EXTRACTORINTERFACE_H

#include <QtPlugin>
#include "Core/image.h"
#include "Core/feature.h"
#include "extractorwidgetinterface.h"

class ExtractorInterface
{
public:
    virtual ~ExtractorInterface() {}

    virtual QString about() = 0;
    virtual QString getPluginName() = 0;

    virtual QString getName() = 0;
    virtual QString getFullName() = 0;
    virtual ExtractorWidgetInterface *getUi() = 0;

    virtual ExtractorWidgetInterface *createUi(QWidget *parent = 0) = 0;

    virtual Feature *extract(Image *image, QString params) = 0;
    virtual bool isMyDescriptor(QString codedDescriptor) = 0;
    virtual bool isLocal(QString params) = 0;

    virtual QString getCodedDescriptor(QString params) = 0;
    virtual QString getFullDescriptor(QString codedDes) = 0;

    virtual double calDistanceEuc(Feature *fea1, Feature *fea2) = 0;
    virtual int computeSizeTexture(QString codedDes) = 0;

    virtual void adapt(Feature *fea, Feature *imgFea, double alpha) = 0;
};

Q_DECLARE_INTERFACE(ExtractorInterface,
                    "com.manleviet.glMiSOM.ExtractorInterface/1.1")

#endif // EXTRACTORINTERFACE_H
