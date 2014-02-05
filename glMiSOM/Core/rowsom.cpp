//
//
// rowsom.cpp
//
// Implementation de la classe rowsom.h
//
// LE Viet Man
// 20/07/2011
//
//

#include "rowsom.h"

RowSOM::RowSOM()
{
}

RowSOM::~RowSOM()
{
    while (!row.isEmpty())
    {
        delete row.takeFirst();
    }
}

void RowSOM::addCell(CellSOM *cell)
{
    row << cell;
}

CellSOM* RowSOM::getCell(int j)
{
    if ((j < 0) || (j >= row.size()))
        return NULL;
    return row[j];
}

void RowSOM::addImage(int j, Image *img, double diff, QColor color)
{
    if ((j < 0) || (j >= row.size()))
        return;
    row[j]->addImage(img, diff, color);
}
