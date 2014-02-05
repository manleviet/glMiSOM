//
//
// feature.h
//
// Une classe sert a stocker des descripteurs extraites de l'image
//
// LE Viet Man
// 28/05/2011
//
//

#ifndef FEATURE_H
#define FEATURE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include "stdlib.h"
#include "float.h"

class Feature
{
public:
    Feature(const QString &descriptor, int size);
    Feature(const QString &descriptor, int size, double *feature);
    Feature(const QString &dataFromFile);
    ~Feature();

    QString getDescriptor();
    QString getFeature();
    int getSize();
    double getValue(int index);
    void setValue(int index, double value);

private:
    QString descriptor;
    int size;
    double *vecteur;
};

#endif // FEATURE_H
