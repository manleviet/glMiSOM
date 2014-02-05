//
//
// entrysom.cpp
//
// LE Viet Man
// 28/07/2011
//
//

#include "entrysom.h"

EntrySOM::EntrySOM(int id, int dimension)
{
    this->id = id;
    dim = dimension;
    numFeatures = 0;
}

void EntrySOM::addFeature(int index, Feature *fea, double weight)
{
    ++numFeatures;
    indexes << index;
    features << fea;
    weights << weight;
}

Feature* EntrySOM::getFeature(int index)
{
    if ((index < 0) || (index >= numFeatures))
        return NULL;
    return features[index];
}
