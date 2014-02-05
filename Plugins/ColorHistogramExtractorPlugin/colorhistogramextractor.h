//
//
// colorhistogramextractor.h
//
// Un extracteur utilisant la methode Color Histogram
//
// LE Viet Man
// 12/06/2011
//
//

#ifndef COLORHISTOGRAMEXTRACTOR_H
#define COLORHISTOGRAMEXTRACTOR_H

#include <QtPlugin>
#include "Extractor/extractorinterface.h"
#include "Extractor/extractorwidgetinterface.h"
#include "Core/image.h"
#include "Core/feature.h"
#include "colorhistogramwidget.h"
#include "cv.h"
#include "highgui.h"
#include "util.h"

class Image;
class Feature;

using namespace cv;

class ColorHistogramExtractor : public QObject, public ExtractorInterface
{
    Q_OBJECT
    Q_INTERFACES(ExtractorInterface)

public:
    ColorHistogramExtractor();
    ~ColorHistogramExtractor() {}

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
    ColorHistogramWidget *ui;

    QString getCodedDescriptor(bool local, int numBins);

    int computeSizeTextureOfAPart(int numBins);
    int computeSizeTexture(bool local, int numBins);

    void calculFeature(IplImage *img, int indexPart, double *histograms, int numBins, int numFeatureOfAPart);

    void parseParams(QString params, bool &local, int &numBins);
    void parseParams(QString codedDes, QString &name, bool &local, int &numBins);
};

#endif // COLORHISTOGRAMEXTRACTOR_H
