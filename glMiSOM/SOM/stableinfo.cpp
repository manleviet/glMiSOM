//
//
// stableinfo.cpp
//
// LE Viet Man
// 28/07/2011
//
//

#include "stableinfo.h"

StableInfo::StableInfo(int i, int j, CellSOM *c, EntrySOM *e)
{
    this->i = i;
    this->j = j;
    cell = c;
    entry = e;
}

StableInfo::~StableInfo()
{
    cell = 0;
    entry = 0;
}
