//
//
// util.h
//
// LE Viet Man
// 28/05/2011
//
//

#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QDir>
#include <QApplication>
#include <qmath.h>
#include "cv.h"

//#define NUM_PART_LOCAL 5

const int NUM_EXTEN_SUPP = 8;
const QString extensions[NUM_EXTEN_SUPP] = {"*.jpg", "*.jpeg", "*.png", "*.bmp",
                                            "tiff",  "ico",    "*.ppm", "*.pgm"};

const QString PATH_DIR_IMAGES = "images";
const QString PATH_IMAGE_TRANSPARENT = "images/transparent.png";

class Util
{
public:
    Util();

    static QString getDirName(const QString &path);
    static QString getMetadataPath(const QString &path);
    static QString getMetadataPathOfImage(const QString &pathMetadata, const QString &filename);
    static QString getFilenameMetadata(const QString &basename);
    static QString getDBMetadata(const QString &path);
    static QString getFeaturesMetadata(const QString &path);

    static QString getNoImage();

    static QStringList getNameFilters();

    static void splitImageToParts(bool local, IplImage *img, QList<CvRect> &parts);

    static int computeNumberNeurons(int size);
    static int computeNumberNeuronsAdapt(int size);

    static QString getPathImageId(int id);
    static QString getPathImageTransparent();

    static QString getPathFileSOM();

    static QString getFileImageUntitle();
    static QString getFileWeightUntitle();
    static QString getFileMapUntitle();

    static bool isDynamicLibrary(QString pluginName);

    static QString getPathFilePlugin(QString pluginName);

    static QString getFileMapMeta(const QString &path);
};

#endif // UTIL_H
