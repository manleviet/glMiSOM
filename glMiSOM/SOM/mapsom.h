//
//
// mapsom.h
//
// LE Viet Man
// 28/07/2011
//
//

#ifndef MAPSOM_H
#define MAPSOM_H

#include <QTime>
#include <QProgressDialog>
#include "time.h"
#include "Core/baseimage.h"
#include "Core/image.h"
#include "Core/feature.h"
#include "Core/gridsom.h"
#include "entrysom.h"
#include "featureschosenlist.h"
#include "winnerinfo.h"
#include "stableinfo.h"
#include "Extractor/extractorinterface.h"
#include "Exception/incorrespondentexception.h"

#define RND_MAX 32767L

class GridSOM;

class MapSOM
{
public:
    enum NEIGH_TYPE { NEIGH_BUBBLE, NEIGH_GAUSSIAN }; // neighborhood types
    enum ALPHA_TYPE { ALPHA_LINEAR, ALPHA_INVERSE_T }; // alpha fnction types
    enum TRAINING_TYPE { ORDERING, CONVERGENCE };

    MapSOM(BaseImage *base);
    ~MapSOM();

    void addExtractors(QList<ExtractorInterface *> extractors);

    void init(QProgressDialog &progress,
              int &count,
              FeaturesChosenList *chosenList,
              int xdim, int ydim,
              NEIGH_TYPE typeNeigh = NEIGH_GAUSSIAN,
              ALPHA_TYPE typeAlpha = ALPHA_LINEAR,
              int randomize = 0);
    void training(QProgressDialog &progress, int &count, TRAINING_TYPE typeTraining, long length, double radius = 1, double alpha = 1);
    GridSOM *visual(QProgressDialog &progress, int &count);
    GridSOM *rearrange(QProgressDialog &progress, int &count, long length, GridSOM *grid);

    void setBaseImage(BaseImage *base);
    BaseImage *getBaseImage() { return base; }

    EntrySOM *getCode(int index);
    int getXdim() { return xdim; }
    int getYdim() { return ydim; }
    NEIGH_TYPE getTypeNeigh() { return type_neigh; }
    ALPHA_TYPE getTypeAlpha() { return type_alpha; }
    double getRadiusOrdering() { return radiusOrdering; }
    double getRadiusConver() { return radiusConver; }
    double getAlphaOrdering() { return alphaOrdering; }
    double getAlphaConver() { return alphaConver; }
    long getLengthOrdering() { return lengthOrdering; }
    long getLengthConver() { return lengthConver; }
    long getRadomize() { return next; }
    int getNumFeaChoosen() { return feaChosenList->getSize(); }
    long getLengthRearrange() { return lengthRearrange; }
    FeaturesChosenList *getChoosenFeatures() { return feaChosenList; }

    bool isChoosenFeatures() { return feaChosenList != 0; }
    bool isInitCodes() { return !codes.isEmpty(); }

    void save();
    void saveWeight(QString filename);

    void load();
    void load(QString filename);
    void loadWeight(QString filename, FeaturesChosenList *list);

    void resetToDefaultValues();

    bool isHaveGridSOM() { return (gridSOM != 0); }
    bool isHaveGridRearrange() { return (gridRearr != 0); }

    GridSOM *getGridSOM() { return gridSOM; }
    GridSOM *getGridRearrange() { return gridRearr; }

    QPoint search(Image *img);
    QList<QPoint> classify(GridSOM *grid, QPoint point, double aqe);

private:
    int dim; // dimension of features
    int xdim, ydim;
    int numCodes;
    NEIGH_TYPE type_neigh;
    ALPHA_TYPE type_alpha;
    double radiusOrdering;
    double radiusConver;
    double alphaOrdering;
    double alphaConver;
    long lengthOrdering;
    long lengthConver;
    FeaturesChosenList *feaChosenList;

    long lengthRearrange;

    QTime qtime;

    BaseImage *base; // comme data in SOMPak
    QList<EntrySOM*> codes; // comme code in SOMPak

    QList<ExtractorInterface*> extractors;

    GridSOM *gridSOM;
    GridSOM *gridRearr;

    unsigned long next;

    void init_random(int seed);
    void osrand(int i);
    int orand();

    EntrySOM *createEntrySOM(double value);

    WinnerInfo *findWinnerEuc(Image *img);
    double distanceEuc(Feature *fea1, Feature *fea2);
    double distanceEuc(Image *img1, Image *img2);
    double distanceEuc(Image *img, EntrySOM* entry);
    double distanceEuc(EntrySOM *entry1, EntrySOM *entry2);

    // fonctions pour l'apprentissage
    double getAlphaLinear(long iter, long length, double alpha);
    double getAlphaInverseT(long iter, long length, double alpha);

    void bubble_adapt(Image *img, int bx, int by, double radius, double alpha);
    void gaussian_adapt(Image *img, int bx, int by, double radius, double alpha);

    double rect_dis(int bx, int by, int tx, int ty);
    void adapt_vector(EntrySOM *entry, Image *img, double alpha);

    // fonctions pour le re-arrangement
    bool** createStableTable();
    void resetStableTable(bool** S);
    void deleteStableTable(bool** s);
    bool* createPrioriteTable();
    //void resetPrioriteTable(bool* p);
    void deletePrioriteTable(bool* p);

    StableInfo* findCasesStable(GridSOM *grid, bool** s);
    void getImagePriorite(QList<Image*> imgs, bool* p, QList<Image*> &P, QList<Image*> &R);

    WinnerInfo *findWinnerEuc(EntrySOM *entry, QList<Image*> imgs);
    void addRemainInPToR(WinnerInfo *winner, QList<Image*> P, QList<Image*> &R);
    void removeWinnerOutR(WinnerInfo *winner, QList<Image*> &R);

    QList<EntrySOM*> getNeighbours(int x, int y, bool** s);

    WinnerInfo *findWinnerEuc(Image *img, QList<EntrySOM*> entries);

    // for test
    void printEntrySOM(EntrySOM *entry);
    void printGridSOM(GridSOM *grid);
    void printGridSOMtoFile(GridSOM *grid);

    // for save
    void saveHeader(QTextStream &out);
    void saveCodes(QTextStream &out);
    void saveGrid(QTextStream &out, GridSOM *grid);

    // for load
    void loadHeader(QTextStream &in);
    FeaturesChosenList *readFeaturesChoosenList(QTextStream &in);
    void readParams(QTextStream &in);
    bool isMyMapMeta(QString nameDB, int sizeDB);
    QString readParam(QTextStream &in);
    bool isEqual(FeaturesChosenList *list1, FeaturesChosenList *list2);
    void loadCodes(QTextStream &in);
    double* convertFromStringToDoubleArr(QString string);
    GridSOM *loadGrid(QTextStream &in);
    void readLineOfGrid(QTextStream &in, QPoint &coord, int &id, double &weight, QColor &color);
};

#endif // MAPSOM_H
