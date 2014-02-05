//
//
// gridsom.cpp
//
// Implementation de la classe gridsom.h
//
// LE Viet Man
// 20/07/2011
//
//

#include "gridsom.h"

//
// Constructeur
// @param :
//      int xdim : le nombre des lignes
//      int ydim : le nombre des colonnes
//
GridSOM::GridSOM(int xdim, int ydim)
{
    this->xdim = xdim;
    this->ydim = ydim;

    RowSOM *row;
    CellSOM *cell;
    // initier la carte
    for (int i = 0; i < xdim; i++)
    {
        row = new RowSOM();
        for (int j = 0; j < ydim; j++)
        {
            cell = new CellSOM();

            row->addCell(cell);
        }
        grid << row;
    }
    cell = 0;
    row = 0;
}

//
// Constructeur
// @param :
//      BaseImage *base : un object de la classe BaseImage
//
GridSOM::GridSOM(BaseImage *base)
{
    // calculer le nombre de neurons de chaque dimension
    xdim = ydim = Util::computeNumberNeurons(base->getSizeOfDB());

    RowSOM *row;
    CellSOM *cell;
    int index;
    // initier la carte ou chaque casse stocke une image
    for (int i = 0; i < xdim; i++)
    {
        row = new RowSOM();
        for (int j = 0; j < ydim; j++)
        {
            index = i * ydim + j;
            cell = new CellSOM();

            if (index < base->getSizeOfDB())
                cell->addImage(base->getImage(index), 0);

            row->addCell(cell);
        }

        grid << row;
    }
    cell = 0;
    row = 0;
}

GridSOM::~GridSOM()
{
    while (!grid.isEmpty())
    {
        delete grid.takeFirst();
    }
}

//
// Prendre la maximum valeur de nombre d'images dans une telle casse dans la carte
// @param :
//      bool **s : une matrice de stablables casses
// @return :
//      la maximum valeur de nombre d'images
//
int GridSOM::getMaxNumImages(bool **s)
{
    int q, max = 0;
    CellSOM *cell;
    for (int i = 0; i < xdim; i++)
    {
        for (int j = 0; j < ydim; j++)
        {
            cell = getCell(i, j);
            q = cell->getQuantityOfImages();

            if ((!s[i][j]) && (max < q))
            {
                max = q;
            }
        }
    }
    return max;
}

//
// Ajouter une nouvelle image a la casse (i,j)
// @param :
//      int i : l'indice de ligne
//      int j : l'indice de colonne
//      Image *img : un object de Image
//      double diff : la valeur de quantisation erreur
//      QColor color : la couleur du fond de la casse
//
void GridSOM::addImage(int i, int j, Image *img, double diff, QColor color)
{
    if (((i < 0) || (i >= xdim))
        && ((j < 0) || (j >= ydim)))
        return;
    grid[i]->addImage(j, img, diff, color);
}

CellSOM* GridSOM::getCell(int i, int j)
{
    if (((i < 0) || (i >= xdim))
        && ((j < 0) || (j >= ydim)))
        return NULL;
    return grid[i]->getCell(j);
}

//
// Copier
//
void GridSOM::copy(GridSOM *grid)
{
    if ((xdim != grid->getXDim()) || (ydim != grid->getYDim())) return;

    CellSOM *cell;
    QList<Image*> imgs;
    QList<double> diffs;
    for (int i = 0; i < xdim; i++)
    {
        for (int j = 0; j < ydim; j++)
        {
            cell = grid->getCell(i, j);

            imgs = cell->getAllImage();
            diffs = cell->getAllDiff();

            for (int k = 0; k < imgs.size(); k++)
            {
                addImage(i, j, imgs[k], diffs[k]);
            }
        }
    }
    cell = 0;
}

//
// Prendre les casses dont le nombre d'images est egal max
// @param :
//      int max : le nombre d'images desire
//      bool **s : la matrice des stablables casses
//      MapSOM *map : un object de MapSOM
// @return : une liste des stablables casses
//
QList<StableInfo*> GridSOM::getStableCell(int max, bool **s, MapSOM *map)
{
    QList<StableInfo*> list;

    StableInfo *stable;
    EntrySOM *entry;
    CellSOM *cell;
    int q;
    for (int i = 0; i < xdim; i++)
    {
        for (int j = 0; j < ydim; j++)
        {
            cell = getCell(i, j);
            q = cell->getQuantityOfImages();

            if ((!s[i][j]) && (q == max))
            {
                entry = map->getCode(i * ydim + j);
                stable = new StableInfo(i, j, cell, entry);

                list << stable;
            }
        }
    }
    stable = 0;
    entry = 0;
    cell = 0;

    return list;
}

//
// Calculer la valeur de l'average quantisation erreur
//
double GridSOM::getAQE()
{
    CellSOM *cell;
    QList<double> diffs;
    double aqe = 0;
    int total = 0;
    for (int i = 0; i < xdim; i++)
    {
        for (int j = 0; j < ydim; j++)
        {
            cell = getCell(i, j);
            diffs = cell->getAllDiff();
            total += diffs.size();

            foreach (double diff, diffs)
            {
                aqe += diff;
            }
        }
    }
    cell = 0;
    aqe /= total;
    return aqe;
}

QList<QPoint> GridSOM::getImagesSameClass(QPoint pos)
{
    QList<QPoint> listPos;

    CellSOM *cell = getCell(pos.x(), pos.y());

    QString className = cell->getClass();

    for (int i = 0; i < xdim; i++)
    {
        for (int j = 0; j < ydim; j++)
        {
            cell = getCell(i, j);

            if (cell->containsImageOfClass(className))
            {
                QPoint pos = QPoint(i, j);

                listPos << pos;
            }
        }
    }
    cell = 0;

    return listPos;
}
