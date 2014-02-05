//
//
// image.h
//
// Une classe sert a stocker une image et les descripteurs de cette image
//
// LE Viet Man
// 28/05/2011
//
//

#ifndef IMAGE_H
#define IMAGE_H

#include <QList>
#include <QFile>
#include <QTextStream>
#include "Core/feature.h"

class Feature;

class Image
{
public:
    Image(int id, const QString &name, const QString &path, const QString &pathMetadata);
    ~Image();

    int getId();
    QString getName();
    QString getPath();
    QString getPathMetadata();

    int getSizeFeatures();
    void addFeature(Feature *feature);
    Feature *getFeature(int index);

    void loadMetadata();
    void saveMetadata();

    bool isEqual(Image *img);

    void remove();

    QString getClass();

private:
    int id;
    QString name;
    QString path;
    QString pathMetadata;

    QList<Feature *> features;
    QList<bool> savedFeatures;
};

#endif // IMAGE_H
