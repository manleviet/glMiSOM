//
//
// featureschosenlist.cpp
//
// LE Viet Man
// 28/07/2011
//
//

#include "featureschosenlist.h"

FeaturesChosenList::FeaturesChosenList()
{
    size = 0;
}

FeaturesChosenList::~FeaturesChosenList()
{
    indexes.clear();
    weights.clear();
}

void FeaturesChosenList::addFeature(int index, double weight)
{
    ++size;
    indexes << index;
    weights << weight;
}

int FeaturesChosenList::getSize()
{
    return size;
}

int FeaturesChosenList::getIndex(int index)
{
    if ((index < 0) || (index >= size))
        return -1;
    return indexes[index];
}

double FeaturesChosenList::getWeight(int index)
{
    if ((index < 0) || (index >= size))
        return DBL_MAX;
    return weights[index];
}
