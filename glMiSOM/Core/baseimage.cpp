//
//
// baseimage.cpp
//
// Implementation de la classe baseimage.h
//
// LE Viet Man
// 28/05/2011
//
//

#include "baseimage.h"

//
// La construction
// @param :
//      const QString &pahtDB : le chemin de la base de donnees
//
BaseImage::BaseImage(const QString &pathDB)
{
    // ex : "/home/manleviet/Stage/DB/BW/Wang-ppm"
    this->name = Util::getDirName(pathDB);
    this->path = pathDB;
    this->pathMetadata = Util::getMetadataPath(pathDB);
}

//
// Destruction
//
BaseImage::~BaseImage()
{
    while (!images.isEmpty())
    {
        delete images.takeFirst();
    }
    savedImages.clear();
    featuresCoded.clear();
    features.clear();
    featureSaved.clear();
}

//
// Chargement de la base de donnees
//
void BaseImage::loadDB()
{
    QDir dir(pathMetadata);
    if (!dir.exists())
    {
        // il n'existe pas
        // charger toutes les images dans le dossier de la base de donnees
        loadWithoutMetadata();

        // creer le dossier metadata
        // et creer le fichier database.meta
        saveMetaOfDatabase();
    }
    else
    {
        // charger les images
        loadImages();

        //il existe features.meta ?
        if (QFile::exists(Util::getFeaturesMetadata(pathMetadata)))
        {
            // charger les features
            loadFeatures();
            // charger les descripteurs des images
            loadFeaturesOfImages();
        }
    }
}

//
// Enregistrer le metadata de la base de donnees sur le fichier database.meta
//
void BaseImage::saveMetaOfDatabase()
{
    QDir dir(pathMetadata);
    if (!dir.exists()) // il existe le dossier metadata ?
    {
        // non -> creer le dossier metadata
        dir.setPath(this->path);
        dir.mkdir("metadata");
    }

    // enregistrer
    QString filename = Util::getDBMetadata(pathMetadata);

    QFile file(filename);
    bool append = false;
    if (file.exists())
    {
        append = true;
        if (!file.open(QFile::Append | QFile::Text))
            throw std::bad_exception();
    }
    else
    {
        if (!file.open(QFile::WriteOnly | QFile::Text))
            throw std::bad_exception();
    }

    // ecrire les informations sur le fichier
    QTextStream out(&file);

    QList<bool>::iterator it;
    int index;
    for (index = 0, it = savedImages.begin(); it != savedImages.end(); ++it, ++index)
    {
        if (*it == false)
        {
            if (append) out << "\n";

            out << images.at(index)->getPath();

            if ((!append) && (index < (savedImages.size() - 1)))
                out << "\n";

            *it = true;
        }
    }
    file.close();
}

//
// Enregistrer les features extraits sur le fichier features.meta
//
void BaseImage::saveMetaOfFeature()
{
    QFile file(Util::getFeaturesMetadata(pathMetadata));
    bool append = false;
    if (file.exists())
    {
        append = true;
        if (!file.open(QFile::Append | QFile::Text))
            throw std::bad_exception();
    }
    else
    {
        if (!file.open(QFile::WriteOnly | QFile::Text))
            throw std::bad_exception();
    }

    // ecrire les informations sur le fichier
    QTextStream out(&file);

    QList<bool>::iterator it;
    int index;
    for  (index = 0, it = featureSaved.begin(); it != featureSaved.end(); ++it, ++index)
    {
        if (*it == false)
        {
            // enregistrer
            if (append) out << "\n";

            out << featuresCoded[index] << " " << features[index];

            if ((!append) && (index < (featureSaved.size() - 1)))
                out << "\n";

            *it = true;
        }
    }
    file.close();

    saveMetaOfImages();
}

//
// Enregistrer les descripteurs des images sur les fichiers meta
//
void BaseImage::saveMetaOfImages()
{
    // luu metadata cua cac image
    Image *image = NULL;
    for (int i = 0; i < images.size(); i++)
    {
        image = images[i];

        image->saveMetadata();
    }
    image = NULL;
}

QString BaseImage::getPathOfDB()
{
    return path;
}

QString BaseImage::getPathMetadata()
{
    return pathMetadata;
}

QString BaseImage::getNameOfDB()
{
    return name;
}

int BaseImage::getSizeOfDB()
{
    return images.length();
}

Image* BaseImage::getImage(const int index)
{
    if ((index < 0) || (index > images.length()))
    {
        return NULL;
    }
    return images[index];
}

//
// Ajouter une nouvelle image
// @param :
//      Image *img : un object de la classe Image
//
void BaseImage::addImage(Image *img)
{
    // kiem tra xem img nay co phu hop voi
    if (!isHaveSameExtractedFeatures(img))
        throw std::bad_exception();

    images << img;
    savedImages << false;
}

//
// Effacer une image de la base de donnees
// @param :
//      Image *img : un object de la classe Image
//
void BaseImage::removeImage(Image *img)
{
    // effacer le fichier metadata de l'image
    img->remove();

    int index = img->getId();

    // effacer l'image
    images.removeAt(index);
    savedImages.removeAt(index);

    QList<bool>::iterator it;
    for (it = savedImages.begin(); it != savedImages.end(); ++it)
    {
        *it = false;
    }

    QFile::remove(Util::getDBMetadata(pathMetadata));
    // enregistrer le nouveau fichier database.meta sans img
    saveMetaOfDatabase();
}

//
// Tester un nouveau descripteur qui a ete extraite
// @param :
//      QString featureCoded : un descripteur code
// @return :
//      true : pouvoir extraire
//      false : deja extraite
//
bool BaseImage::isAddable(QString featureCoded)
{
    foreach (QString fea, featuresCoded)
    {
        if (fea == featureCoded)
        {
            return false;
        }
    }

    return true;
}

//
// Ajouter un nouveau descripteur
// @param :
//      QString feature : un descripteur
//      QString featureCoded : un descripteur code
//
void BaseImage::addFeature(QString feature, QString featureCoded)
{
    features << feature;
    featuresCoded << featureCoded;
    featureSaved << false;
}

//
// Tester la posibilite de l'importation des nouvelles images
// @param :
//      QList<ExtractorInterface*> extractors : une liste des extracteurs
// @return :
//      true : pouvoir importer
//      false : non
//
bool BaseImage::isImportable(QList<ExtractorInterface *> extractors)
{
    bool check;
    foreach (QString coded, featuresCoded)
    {
        check = false;
        foreach (ExtractorInterface *ext, extractors)
        {
            if (ext->isMyDescriptor(coded))
            {
                check = true;
                break;
            }
        }

        if (!check) return false;
    }

    return true;
}

//////////////// PRIVATE ////////////////////////

//
// Charger toutes les images dans le dossier de la base de donnees
//
void BaseImage::loadWithoutMetadata()
{
    QDir dir(path);
    // charger seulement des fichiers
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    // mettre les extensions
    dir.setNameFilters(Util::getNameFilters());

    QFileInfoList list = dir.entryInfoList();

    Image *image = 0;
    QString pathMD; // pathMetadata of image
    QString filename;
    for (int i = 0; i < list.size(); i++)
    {
        filename = Util::getFilenameMetadata(list[i].baseName());
        pathMD = Util::getMetadataPathOfImage(pathMetadata, filename);
        image = new Image(i, list[i].fileName(), list[i].filePath(), pathMD);

        images << image;
        savedImages << false;
    }
    image = 0;
}

//
// Charger les images grace a les chemins dans le fichier database.meta
//
void BaseImage::loadImages()
{
    // ouvrier le fichier database.meta pour prendre les chemins
    QString filename = Util::getDBMetadata(pathMetadata);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        throw std::bad_exception();
    }

    QTextStream in(&file);

    // lire
    QString path;
    Image *image = NULL;
    QFileInfo fileInfo;
    QString pathMD;
    QString basename;
    int id = -1;
    while (!in.atEnd())
    {
        // lire une ligne
        path = in.readLine();

        id++;
        fileInfo.setFile(path);
        basename = Util::getFilenameMetadata(fileInfo.baseName());
        pathMD = Util::getMetadataPathOfImage(pathMetadata, basename);
        image = new Image(id, fileInfo.fileName(), fileInfo.filePath(), pathMD);

        images << image; // mettre une image a la liste des images
        savedImages << true;
    }
    image = 0;
    file.close();
}

//
// Charger les features dans le fichier features.meta
//
void BaseImage::loadFeatures()
{
    QFile file(Util::getFeaturesMetadata(pathMetadata));
    if (!file.open(QIODevice::ReadOnly))
    {
        throw std::bad_exception();
    }

    QTextStream in(&file);

    // lire
    QString line;
    QStringList fields;
    QString feature;
    while (!in.atEnd())
    {
        // lire une ligne
        line = in.readLine();

        fields = line.split(" ");

        feature = "";
        for (int i = 1; i < fields.size(); i++)
        {
            feature += fields[i] + " ";
        }

        featuresCoded << fields[0];
        features << feature;
        featureSaved << true;
    }
    file.close();
}

//
// Charger les descripteurs dans les fichier meta des images
//
void BaseImage::loadFeaturesOfImages()
{
    foreach (Image *img, images)
    {
        img->loadMetadata();
    }
}

//
// Tester la correspondente de la nouvelle image qui ont des meme features extraits
// avec les features extraits de la base d'images
// @param :
//      Image *img : un object de la classe Image
// @return :
//      true : si l'on ont des meme features extraits
//      false : si non
//
bool BaseImage::isHaveSameExtractedFeatures(Image *img)
{
    if (featuresCoded.size() != img->getSizeFeatures()) return false;

    Feature *fea;
    for (int i = 0; i < featuresCoded.size(); i++)
    {
        fea = img->getFeature(i);

        // avoir meme descripteur
        if (featuresCoded[i] != fea->getDescriptor())
            return false;
    }
    fea = 0;

    return true;
}
