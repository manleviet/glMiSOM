//
//
// matrixcooccurrence2extractor.h
//
// Un extracteur utilisant la methode Matrix Cooccurrence 2
//
// LE Viet Man
// 12/09/2011
//
//

#ifndef MATRIXCOOCCURRENCE2EXTRACTOR_H
#define MATRIXCOOCCURRENCE2EXTRACTOR_H

#include <QtPlugin>
#include "Extractor/extractorinterface.h"
#include "Extractor/extractorwidgetinterface.h"
#include "Core/image.h"
#include "Core/feature.h"
#include "glcm.h"
#include "matrixcooccurrence2widget.h"
#include "cv.h"
#include "highgui.h"
#include "util.h"

class Image;
class Feature;
class MatrixCooccurrence2Widget;

using namespace cv;

class MatrixCooccurrence2Extractor : public QObject, public ExtractorInterface
{
    Q_OBJECT
    Q_INTERFACES(ExtractorInterface)

public:
    MatrixCooccurrence2Extractor();
    ~MatrixCooccurrence2Extractor() {}

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

    int computeSizeTexture(bool local, QList<bool> descriptors);

    void adapt(Feature *fea, Feature *imgFea, double alpha);

private:
    QString name;
    QString fullname;
    MatrixCooccurrence2Widget *ui;

    QString getCodedDescriptor(bool local, QList<bool> distances, int numGreyLevel, QList<bool> descriptors);

    double calDistance(Feature *fea1, Feature *fea2, int posBegin1, int posBegin2, int size);

    int computeSizeTextureOfAPart(QList<bool> descriptors);

    int computeNumMatrixOfAPart(QList<bool> distances);

    void calculFeature(IplImage *img,
                       int indexPart,
                       double *textures,
                       int numGreyLevel,
                       QList<bool> distances,
                       QList<bool> descriptors,
                       int numFeatureOfAPart);
    static IplImage *convertToGrey(IplImage *img);

    void parseParams(QString params, bool &local, QList<bool> &distances, int &numGreyLevel, QList<bool> &descriptors);
    void parseParams(QString codedDes, QString &name, bool &local, QList<bool> &distances, int &numGreyLevel, QList<bool> &descriptors);

    QList<bool> convertStrListToBList(QString string, int max);
};

#endif // MATRIXCOOCCURRENCE2EXTRACTOR_H
