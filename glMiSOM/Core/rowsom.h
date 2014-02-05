//
//
// rowsom.h
//
// Une classe demonstrate une ligne dans la carte de Kohonen
//
// LE Viet Man
// 20/07/2011
//
//

#ifndef ROWSOM_H
#define ROWSOM_H

#include <QList>
#include "Core/cellsom.h"

class RowSOM
{
public:
    RowSOM();
    ~RowSOM();

    void addCell(CellSOM *cell);
    CellSOM* getCell(int j);

    void addImage(int j, Image *img, double diff, QColor color = Qt::white);

private:
    QList<CellSOM*> row;
};

#endif // ROWSOM_H
