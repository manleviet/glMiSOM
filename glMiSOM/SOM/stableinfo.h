//
//
// stableinfo.h
//
// LE Viet Man
// 28/07/2011
//
//

#ifndef STABLEINFO_H
#define STABLEINFO_H

#include "Core/cellsom.h"
#include "entrysom.h"

class StableInfo
{
public:
    StableInfo(int i, int j, CellSOM *c, EntrySOM *e);
    ~StableInfo();

    CellSOM *getCell() { return cell; }
    EntrySOM *getEntry() { return entry; }
    int getX() { return i; }
    int getY() { return j; }

private:
    int i;
    int j;
    CellSOM *cell;
    EntrySOM *entry;
};

#endif // STABLEINFO_H
