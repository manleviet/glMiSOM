//
//
// cellsom.cpp
//
// Implementation de la classe cellsom.h
//
// LE Viet Man
// 20/07/2011
//
//

#include "cellsom.h"

//
// Constructeur
//
CellSOM::CellSOM()
{
    color = Qt::white;
}

CellSOM::~CellSOM()
{
    while (!imgs.isEmpty())
    {
        imgs.takeFirst();
    }
    diffs.clear();
    textures.clear();
    rects.clear();
}

//
// Ajouter une nouvelle image a la casse
// @param :
//      Image *img : un object de la classe Image
//      double diff : la valeur de quantization erreur
//      QColor color : la couleur du fond de la casse
//
void CellSOM::addImage(Image *img, double diff, QColor color)
{
    imgs << img;
    diffs << diff;
    this->color = color;
}

//
// Prendre l'image la plus proche du centroide
// @return : l'image la plus proche du centroide
//
Image* CellSOM::getImage()
{
    double min = DBL_MAX;
    int index = -1;
    for (int i = 0; i < imgs.size(); i++)
    {
        if (diffs[i] < min)
        {
            min = diffs[i];
            index = i;
        }
    }

    if (index == -1) return NULL;
    return imgs[index];
}

//
// Prendre la valeur de quantisation erreur de l'image la plus proche du centroide
// @return : la valeur de quantisation erreur
//
double CellSOM::getDiff()
{
    double min = DBL_MAX;
    for (int i = 0; i < imgs.size(); i++)
    {
        if (diffs[i] < min)
        {
            min = diffs[i];
        }
    }

    return min;
}

QList<Image*> CellSOM::getAllImage() const
{
    return imgs;
}

QList<double> CellSOM::getAllDiff() const
{
    return diffs;
}

int CellSOM::getQuantityOfImages() const
{
    return imgs.size();
}

void CellSOM::setColor(QColor c)
{
    color = c;
}

void CellSOM::removeAllExceptWinner(WinnerInfo *winner)
{
    Image *img = winner->getImage();
    double diff = winner->getDiff();

    QList<Image*> tImgs;
    QList<double> tDiffs;

    tImgs << img;
    tDiffs << diff;

    imgs = tImgs;
    diffs = tDiffs;
}

//
// Effacer une image dans la casse
// @param :
//      Image *img : un object de la classe Image
//
void CellSOM::removeImage(Image *img)
{
    // chercher l'indice de img
    int i;
    for (i = 0; i < imgs.size(); i++)
    {
        if (imgs[i]->isEqual(img))
            break;
    }

    if (i < imgs.size())
    {
        QList<Image*>::iterator itImg;

        itImg = imgs.begin() + i;
        *itImg = 0;

        imgs.removeAt(i);
        diffs.removeAt(i);
        textures.removeAt(i);
        rects.removeAt(i);
    }
}

//
// Vouloir savoir si cette casse contient une image
// @param :
//      Image *img : un object de la classe Image
// @return : true, false
//
bool CellSOM::contains(Image *img)
{
    int i;
    for (i = 0; i < imgs.size(); i++)
    {
        if (imgs[i]->isEqual(img))
            break;
    }

    if (i < imgs.size())
        return true;
    return false;
}

//
// Ajouter un nouveau texture de OpenGL
// @param :
//      GLuint texture : un nouveau texture
//      QRectF rect : la region pour dessiner le texture
//
void CellSOM::addTexture(GLuint texture, QRectF rect)
{
    textures << texture;
    rects << rect;
}

GLuint CellSOM::getTexture(int index)
{
    if ((index < 0) || (index >= textures.size()))
        return -1;
    return textures[index];
}

QRectF CellSOM::getRectF(int index)
{
    if ((index < 0) || (index >= textures.size()))
        return QRectF(0, 0, 0, 0);
    return rects[index];
}

QString CellSOM::getClass()
{
    return imgs[0]->getClass();
}

bool CellSOM::containsImageOfClass(QString classname)
{
    foreach (Image* img, imgs)
    {
        if (img->getClass() == classname)
            return true;
    }
    return false;
}
