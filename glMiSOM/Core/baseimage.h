//
//
// baseimage.h
//
// Une classe sert a gerer tous les images d'une base de donnees d'images
//
// LE Viet Man
// 28/05/2011
//
//

#ifndef BASEIMAGE_H
#define BASEIMAGE_H

#include <exception>
#include "Core/image.h"
#include "Extractor/extractorinterface.h"
#include "util.h"

class BaseImage
{
public:
    BaseImage(const QString &pathDB);
    ~BaseImage();

    void loadDB();
    void saveMetaOfDatabase();
    void saveMetaOfFeature();
    void saveMetaOfImages();

    QString getPathOfDB();
    QString getPathMetadata();
    QString getNameOfDB();

    int getSizeOfDB();
    Image *getImage(const int index);
    void addImage(Image *img);
    void removeImage(Image *img);

    bool isAddable(QString featureCoded);
    void addFeature(QString feature, QString featureCoded);
    QStringList getFeatureList() const { return features; }
    QStringList getFeatureCodedList() const { return featuresCoded; }

    bool isImportable(QList<ExtractorInterface*> extractors);

private:
    QString name;
    QString path;
    QString pathMetadata;

    QList<Image *> images;
    QList<bool> savedImages;

    QStringList featuresCoded;
    QStringList features;
    QList<bool> featureSaved;

    // load
    void loadWithoutMetadata();
    void loadImages();
    void loadFeatures();
    void loadFeaturesOfImages();

    bool isHaveSameExtractedFeatures(Image *img);
};

#endif // BASEIMAGE_H
