//
//
// entrysom.h
//
// LE Viet Man
// 28/07/2011
//
//

#ifndef ENTRYSOM_H
#define ENTRYSOM_H

#include "Core/feature.h"

class EntrySOM
{
public:
    EntrySOM(int id, int dimension);

    int getId() { return id; }

    void addFeature(int index, Feature *fea, double weight = 1);

    Feature *getFeature(int index);

private:
    int id;
    int dim;
    int numFeatures;

    QList<int> indexes;
    QList<Feature*> features;
    QList<double> weights;
};

#endif // ENTRYSOM_H
