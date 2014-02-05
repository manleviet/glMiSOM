//
//
// featureschosenlist.h
//
// LE Viet Man
// 28/07/2011
//
//

#ifndef FEATURESCHOSENLIST_H
#define FEATURESCHOSENLIST_H

#include "QList"
#include "float.h"

class FeaturesChosenList
{
public:
    FeaturesChosenList();
    ~FeaturesChosenList();

    void addFeature(int index, double weight);

    int getSize();
    int getIndex(int index);
    double getWeight(int index);

private:
    int size;
    QList<int> indexes;
    QList<double> weights;
};

#endif // FEATURESCHOSENLIST_H
