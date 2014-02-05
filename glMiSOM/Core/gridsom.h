//
//
// gridsom.h
//
// Une classe demonstrate une carte de Kohonen
//
// LE Viet Man
// 20/07/2011
//
//

#ifndef GRIDSOM_H
#define GRIDSOM_H

#include <QList>
#include <qmath.h>
#include "Core/rowsom.h"
#include "Core/cellsom.h"
#include "Core/baseimage.h"
#include "SOM/stableinfo.h"
#include "SOM/mapsom.h"

class MapSOM;

class GridSOM
{
public:
    GridSOM(int xdim, int ydim);
    GridSOM(BaseImage *base);
    ~GridSOM();

    int getXDim() { return xdim; }
    int getYDim() { return ydim; }

    int getMaxNumImages(bool **s);

    void addImage(int i, int j, Image *img, double diff, QColor color = Qt::white);
    CellSOM* getCell(int i, int j);

    void copy(GridSOM *grid);

    QList<StableInfo*> getStableCell(int max, bool **s, MapSOM *map);

    double getAQE();
    QList<QPoint> getImagesSameClass(QPoint pos);

private:
    int xdim;
    int ydim;

    QList<RowSOM*> grid;
};

#endif // GRIDSOM_H
