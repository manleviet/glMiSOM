//
//
// image.cpp
//
// Implementation de la classe image.h
//
// LE Viet Man
// 28/05/2011
//
//

#include "image.h"

Image::Image(int id, const QString &name, const QString &path, const QString &pathMetadata)
{
    this->id = id;
    this->name = name;
    this->path = path;
    this->pathMetadata = pathMetadata;
}

Image::~Image()
{
    while (!features.isEmpty())
    {
         delete features.takeFirst();
    }
    savedFeatures.clear();
}

int Image::getId()
{
    return this->id;
}

QString Image::getName()
{
    return this->name;
}

QString Image::getPath()
{
    return this->path;
}

QString Image::getPathMetadata()
{
    return this->pathMetadata;
}

int Image::getSizeFeatures()
{
    return features.size();
}

//
// Ajouter un nouveau feature
// @param :
//      Feature *feature : un object de la classe Feature
//
void Image::addFeature(Feature *feature)
{
    this->features << feature;
    this->savedFeatures << false;
}

Feature *Image::getFeature(int index)
{
    if ((index < 0) || (index > features.size()))
    {
        return NULL;
    }

    return features[index];
}

//
// Charger le meta de l'image (ce sont des descripteurs)
//
void Image::loadMetadata()
{
    QFile file(pathMetadata);
    if (!file.open(QIODevice::ReadOnly))
    {
        throw std::bad_exception();
    }

    QTextStream in(&file);

    QString line;
    Feature *feature;
    while (!in.atEnd())
    {
        // lire une ligne
        line = in.readLine();

        feature = new Feature(line);

        features << feature;
        savedFeatures << true;
    }
    file.close();
}

//
// Enregistrer le meta de l'image sur le fichier meta
//
void Image::saveMetadata()
{
    if (pathMetadata.isEmpty())
    {
        throw std::bad_exception();
    }

    QFile file(pathMetadata);
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
    Feature *feature = NULL;
    QString des;
    for  (index = 0, it = savedFeatures.begin(); it != savedFeatures.end(); ++it, ++index)
    {
        if (*it == false)
        {
            // enregistrer
            feature = getFeature(index);
            if (append) out << "\n";

            des = QString("%1 %2").arg(feature->getDescriptor()).arg(feature->getFeature());
            out << des;

            if ((!append) && (index < (savedFeatures.size() - 1)))
                out << "\n";

            *it = true;
        }
    }
    file.close();
}

//
// Verifier le ressemblance de deux Image
//
bool Image::isEqual(Image *img)
{
    // meme indice et meme nom
    if ((id == img->id) && (name == img->name))
        return true;
    return false;
}

//
// Effacer l'image et le fichier metadata de cette image
//
void Image::remove()
{
    // effacer l'image
    QFile::remove(path);
    // effacer le fichier meta
    QFile::remove(pathMetadata);
}

QString Image::getClass()
{
    if (name.contains("_"))
    {
        QStringList fields = name.split("_");

        return fields[0];
    }
    else
        return name.left(1);
}
