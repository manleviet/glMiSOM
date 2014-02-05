//
//
// feature.cpp
//
// Implementation de la classe feature.h
//
// LE Viet Man
// 28/05/2011
//
//

#include "feature.h"

//
// Constructeur
// @param :
//      const QString &descriptor : un descripteur
//      int size : la taille du descripteur
//
Feature::Feature(const QString &descriptor, int size)
{
    this->descriptor = descriptor;
    this->size = size;

    // initialisation
    vecteur = (double*)malloc(sizeof(double) * size);
    memset(vecteur, 0, sizeof(double) * size);
}

//
// Constructeur
// @param :
//      const QString &descriptor : un descripteur
//      int size : la taille du descripteur
//      double *feature : un array des valeurs de descripteur
//
Feature::Feature(const QString &descriptor, int size, double *feature)
{
    this->descriptor = descriptor;
    this->size = size;

    vecteur = (double*)malloc(sizeof(double) * size);
    memcpy(this->vecteur, feature, sizeof(double) * size);
}

//
// Constructeur
// Analyser une ligne de texte lit a partir du fichier meta
// @param :
//      const QString &dataFromFile : une chaine de descripteur
//
Feature::Feature(const QString &dataFromFile)
{
    // ColorHistogram,0,5 0.320862 0.394236 0.207041 0.0660807 0.0117798 0.225494
    // 0.355062 0.300517 0.0915324 0.0273946 0.122955 0.369039 0.274434 0.153819 0.0797526

    QStringList fields = dataFromFile.split(" ");
    this->descriptor = fields.at(0);
    this->size = fields.size() - 1;

    vecteur = (double*)malloc(sizeof(double) * size);
    memset(vecteur, 0, sizeof(double) * size);
    for (int i = 1; i < fields.size(); i++)
    {
        vecteur[i - 1] = fields.at(i).toDouble();
    }
}

Feature::~Feature()
{
    if (vecteur != NULL)
    {
        free(vecteur);
        vecteur = NULL;
    }
}

QString Feature::getDescriptor()
{
    return descriptor;
}

//
// Prendre le descripteur sous forme de texte
// @return :
//      un descripteur comme suivant :
//      ColorHistogram,0,5 0.320862 0.394236 0.207041 0.0660807 0.0117798 0.225494
//      0.355062 0.300517 0.0915324 0.0273946 0.122955 0.369039 0.274434 0.153819 0.0797526
//
QString Feature::getFeature()
{
    QString feature;// = descriptor;

    for (int i = 0; i < size; i++)
    {
        feature += QObject::tr("%1 ").arg(vecteur[i]);
    }
    feature.remove(feature.size() - 1, 1);

    return feature;
}

int Feature::getSize()
{
    return size;
}

double Feature::getValue(int index)
{
    if ((index < 0) || (index >= size))
        return DBL_MAX;
    return vecteur[index];
}

//
// Mettre la nouvelle valeur du descripteur a l'indice
// @param :
//      int index : l'indice
//      double value : la nouvelle valeur
//
void Feature::setValue(int index, double value)
{
    if ((index >= 0) && (index < size))
    {
        vecteur[index] = value;
    }
}
