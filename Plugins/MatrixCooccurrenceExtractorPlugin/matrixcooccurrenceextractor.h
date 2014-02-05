//
//
// matrixcooccurrenceextractor.h
//
// Un extracteur utilisant la methode Matrix Cooccurrence
//
// LE Viet Man
// 12/06/2011
//
//

#ifndef MATRIXCOOCCURRENCEEXTRACTOR_H
#define MATRIXCOOCCURRENCEEXTRACTOR_H

#include <QtPlugin>
#include "Extractor/extractorinterface.h"
#include "Extractor/extractorwidgetinterface.h"
#include "Core/image.h"
#include "Core/feature.h"
#include "glcm.h"
#include "matrixcooccurrencewidget.h"
#include "cv.h"
#include "highgui.h"
#include "util.h"

class Image;
class Feature;
class MatrixCooccurrenceWidget;

using namespace cv;

class MatrixCooccurrenceExtractor : public QObject, public ExtractorInterface
{
    Q_OBJECT
    Q_INTERFACES(ExtractorInterface)

public:
    MatrixCooccurrenceExtractor();
    ~MatrixCooccurrenceExtractor() {}

    QString about();
    QString getPluginName();

    QString getName() { return name; }
    QString getFullName() { return fullname; }
    ExtractorWidgetInterface *getUi() { return (ExtractorWidgetInterface*)ui; }

    ExtractorWidgetInterface *createUi(QWidget *parent);

    Feature *extract(Image *image, QString params);
    bool isMyDescriptor(QString codedDes);
    bool isLocal(QString params);

    QString getCodedDescriptor(QString params);
    QString getFullDescriptor(QString codedDes);

    double calDistanceEuc(Feature *fea1, Feature *fea2);
    int computeSizeTexture(QString codedDes);

    void adapt(Feature *fea, Feature *imgFea, double alpha);

    int getNumMatrix(QString codedDes);
    int getNumDescriptors(QString codedDes);

    int computeSizeTexture(bool local, QList<bool> distances, QList<bool> descriptors);

    double calDistance(Feature *fea1, Feature *fea2, int posBegin1, int posBegin2, int size);

private:
    QString name;
    QString fullname;
    MatrixCooccurrenceWidget *ui;

    QString getCodedDescriptor(bool local,
                          QList<bool> distances,
                          int numGreyLevel,
                          QList<bool> descriptors);

    int computeSizeTextureOfAPart(QList<bool> distances, QList<bool> descriptors);

    int computeNumMatrixOfAPart(QList<bool> distances);
    int computeNumMatrix(bool local, QList<bool> distances);

    void calculFeature(IplImage *img,
                       int indexPart,
                       double *textures,
                       int numGreyLevel,
                       QList<bool> distances,
                       QList<bool> descriptors,
                       int numFeatureOfAPart);
    IplImage *convertToGrey(IplImage *img);

    void parseParams(QString params, bool &local, QList<bool> &distances, int &numGreyLevel, QList<bool> &descriptors);
    void parseParams(QString codedDes, QString &name, bool &local, QList<bool> &distances, int &numGreyLevel, QList<bool> &descriptors);

    static QList<bool> convertStrListToBList(QString string, int max);
};

#endif // MATRIXCOOCCURRENCEEXTRACTOR_H
