//
//
// humomentsextractor.h
//
// Un extracteur utilisant la methode Hu Moments
//
// LE Viet Man
// 12/06/2011
//
//

#ifndef HUMOMENTSEXTRACTOR_H
#define HUMOMENTSEXTRACTOR_H

#include <QtPlugin>
#include "Extractor/extractorinterface.h"
#include "Extractor/extractorwidgetinterface.h"
#include "Core/image.h"
#include "Core/feature.h"
#include "humomentswidget.h"
#include "cv.h"
#include "highgui.h"
#include "util.h"

#define MAX_HUMOMENTS 7

class Image;
class Feature;

using namespace cv;

class HuMomentsExtractor : public QObject, public ExtractorInterface
{
    Q_OBJECT
    Q_INTERFACES(ExtractorInterface)

public:
    HuMomentsExtractor();
    ~HuMomentsExtractor() {}

    QString about();
    QString getPluginName();

    QString getName() { return name; }
    QString getFullName() { return fullname; }
    ExtractorWidgetInterface *getUi() { return ui; }

    ExtractorWidgetInterface *createUi(QWidget *parent);

    Feature *extract(Image *image, QString params);
    bool isMyDescriptor(QString codedDes);
    bool isLocal(QString params);

    QString getCodedDescriptor(QString params);
    QString getFullDescriptor(QString codedDes);

    double calDistanceEuc(Feature *fea1, Feature *fea2);
    int computeSizeTexture(QString codedDes);

    void adapt(Feature *fea, Feature *imgFea, double alpha);

private:
    QString name;
    QString fullname;
    HuMomentsWidget *ui;

    QString getCodedDescriptor(bool local, int numBins);

    int computeSizeTexture(bool local, int numBins);

    void calculHuMoments(IplImage *img, int indexPart, double *humoments, int numBins, int numFeatureOfAPart);
    void reduceGreyLevels(IplImage *img, int numLevels);
    IplImage *convertToGrey(IplImage *img);

    void parseParams(QString params, bool &local, int &numBins);
    void parseParams(QString codedDes, QString &name, bool &local, int &numBins);
};

#endif // HUMOMENTSEXTRACTOR_H
