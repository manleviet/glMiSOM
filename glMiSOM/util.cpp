//
//
// util.cpp
//
// LE Viet Man
// 28/05/2011
//
//

#include "util.h"

Util::Util()
{
}

QString Util::getDirName(const QString &path) // ex : "/home/manleviet/Stage/DB/BW/Wang-ppm"
{
    return QDir(path).dirName(); // Wang-ppm
}

QString Util::getMetadataPath(const QString &path) // ex : "/home/manleviet/Stage/DB/BW/Wang-ppm"
{
    return path + QDir::separator() + QObject::tr("metadata"); // "/home/manleviet/Stage/DB/BW/Wang-ppm/metadata"
}

QString Util::getMetadataPathOfImage(const QString &pathMetadata, const QString &filename)
{
    return pathMetadata + QDir::separator() + filename;
}

QString Util::getFilenameMetadata(const QString &basename)
{
    return basename + QObject::tr(".meta");
}

QString Util::getDBMetadata(const QString &path)
{
    return path + QDir::separator() + "database.meta";
}

QString Util::getFeaturesMetadata(const QString &path)
{
    return path + QDir::separator() + "features.meta";
}

QString Util::getNoImage()
{
    return QDir::homePath() + QDir::separator() + QObject::tr("p0.jpg");
}

QStringList Util::getNameFilters()
{
    QStringList filters;
    for (int i = 0; i < NUM_EXTEN_SUPP; i++)
    {
        filters << extensions[i];
    }

    return filters;
}

void Util::splitImageToParts(bool local, IplImage *img, QList<CvRect> &parts)
{
    if (!local)
    {
        CvRect part = cvRect(0, 0, img->width, img->height);

        parts << part;
    }
    else
    {
        int width = img->width / 2;
        int height = img->height / 2;

        int y = height - (height / 2);
        int x = width - (width / 2);

        CvRect part0 = cvRect(x, y, width, height);
        CvRect part1 = cvRect(0, 0, width, height);
        CvRect part2 = cvRect(0, height, width, height);
        CvRect part3 = cvRect(width, 0, width, height);
        CvRect part4 = cvRect(width, height, width, height);

        parts << part0 << part1 << part2 << part3 << part4;
    }
}

int Util::computeNumberNeurons(int size)
{
    int numNeurons = qRound(qSqrt(size));
    if (size > (numNeurons * numNeurons))
    {
        numNeurons++;
    }

    return numNeurons;
}

int Util::computeNumberNeuronsAdapt(int size)
{
    int numNeurons = computeNumberNeurons(size);

    while ((numNeurons * numNeurons - size / (numNeurons * numNeurons)) < 0.25)
    {
        numNeurons++;
    }

    return numNeurons;
}

//
// Prendre le chemin du repertoire "images"
// @result : le chemin du repertoire "images"
//
QString Util::getPathImageId(int id)
{
    QString path = QDir::currentPath() + QDir::separator()
            + PATH_DIR_IMAGES + QDir::separator()
            + QString("%1.png").arg(id);
    return path;
}

//
// Prendre le chemin de l'image transparent.png
//
QString Util::getPathImageTransparent()
{
    QString path = QDir::currentPath() + QDir::separator() + PATH_IMAGE_TRANSPARENT;
    return path;
}

QString Util::getPathFileSOM()
{
    QString path = QDir::currentPath() + QDir::separator() + QString("som.txt");
    return path;
}

QString Util::getFileImageUntitle()
{
    QString file = QDir::currentPath() + QDir::separator() + QString("untitle.png");
    return file;
}

QString Util::getFileWeightUntitle()
{
    QString file = QDir::currentPath() + QDir::separator() + QString("untitle.wht");
    return file;
}

QString Util::getFileMapUntitle()
{
    QString file = QDir::currentPath() + QDir::separator() + QString("untitle.map");
    return file;
}

bool Util::isDynamicLibrary(QString pluginName)
{
    QStringList fields = pluginName.split(".");
    if (fields[1] == "so")
    {
        return true;
    }
    return false;
}

QString Util::getPathFilePlugin(QString pluginName)
{
    return QApplication::applicationDirPath() + QDir::separator()
            + QString("plugins") + QDir::separator() + pluginName;
}

QString Util::getFileMapMeta(const QString &path)
{
    return path + QDir::separator() + "map.meta";
}
