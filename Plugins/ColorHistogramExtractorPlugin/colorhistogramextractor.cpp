//
//
// colorhistogramextractor.cpp
//
// Implementation de la classe colorhistogramextractor.h
//
// LE Viet Man
// 12/06/2011
//
//

#include "colorhistogramextractor.h"

ColorHistogramExtractor::ColorHistogramExtractor()
    : ExtractorInterface()
{
    name = QString("COLORHISTOGRAM");
    fullname = QString("Color Histogram");
    ui = 0;
}

QString ColorHistogramExtractor::about()
{
    return QString("<p><b>Plugin ColorHistogramExtractor version 1.1</b></p>"
                   "<p>Static plugin"
                   "<br>Build date: %1"
                   "<br>This plugins uses Qt 4.7, OpenCV 2.1"
                   "<br>Author: LE Viet Man"
                   "<br>Email: <a href=\"mailto:manleviet@gmail.com>\">manleviet@gmail.com</a>"
                   "<br>09/2011"
                   "</p>").arg(__TIMESTAMP__);
}

QString ColorHistogramExtractor::getPluginName()
{
    return QString("libcolorhistogramextractor.a");
}

ExtractorWidgetInterface *ColorHistogramExtractor::createUi(QWidget *parent)
{
    ColorHistogramWidget *widget = new ColorHistogramWidget(parent);
    ui = widget;
    return widget;
}

Feature *ColorHistogramExtractor::extract(Image *image, QString params)
{
    // parser des parametres
    bool local;
    int numBins;
    parseParams(params, local, numBins);

    IplImage *img = cvLoadImage(image->getPath().toStdString().c_str());

    if (!img)
    {
        throw std::bad_exception();
        return NULL;
    }

    QList<CvRect> parts;
    // a partir de la valeur local pour prendre des partis de l'image
    Util::splitImageToParts(local, img, parts);

    int numFeaturesOfAPart = computeSizeTextureOfAPart(numBins);
    int numFeatures = computeSizeTexture(local, numBins);
    double *histograms = (double*)malloc(sizeof(double) * numFeatures);
    memset(histograms, 0, sizeof(double) * numFeatures);
    CvRect part;
    for (int i = 0; i < parts.size(); i++)
    {
        part = parts[i];

        cvSetImageROI(img, part);

        calculFeature(img, i, histograms, numBins, numFeaturesOfAPart);
    }
    cvReleaseImage(&img);

    // creer un Feature
    Feature *feature = new Feature(getCodedDescriptor(local, numBins), numFeatures, histograms);

    free(histograms);
    return feature;
}

bool ColorHistogramExtractor::isMyDescriptor(QString codedDes)
{
    QStringList fields = codedDes.split(",");
    if (fields[0] == name)
        return true;
    return false;
}

bool ColorHistogramExtractor::isLocal(QString params)
{
    // parser des parametres
    bool local;
    int numBins;
    parseParams(params, local, numBins);

    return local;
}

QString ColorHistogramExtractor::getCodedDescriptor(QString params)
{
    // parser des parametres
    bool local;
    int numBins;
    parseParams(params, local, numBins);

    return getCodedDescriptor(local, numBins);
}

QString ColorHistogramExtractor::getFullDescriptor(QString codedDes)
{
    QStringList fields = codedDes.split(",");

    QString des = fullname;

    if (fields[1].toInt() == 1)
    {
        des += QString(" - Local - ");
    }
    else
    {
        des += QString(" - Global - ");
    }

    des += QString("Bin number : %1").arg(fields[2].toInt());

    return des;
}

double ColorHistogramExtractor::calDistanceEuc(Feature *fea1, Feature *fea2)
{
    double diff, difference;
    difference = 0;

    int size = fea1->getSize();
    for (int i = 0; i < size; i++)
    {
        diff = fea1->getValue(i) - fea2->getValue(i);
        difference += diff * diff;
    }
    difference /= size;

    return difference;
}

int ColorHistogramExtractor::computeSizeTexture(QString codedDes)
{
    if (!isMyDescriptor(codedDes)) return -1;

    QString name;
    int numBins;
    bool local;
    parseParams(codedDes, name, local, numBins);

    return computeSizeTexture(local, numBins);
}

void ColorHistogramExtractor::adapt(Feature *fea, Feature *imgFea, double alpha)
{
    double value;
    for (int i = 0; i < fea->getSize(); i++)
    {
        value = fea->getValue(i);
        value += alpha * (imgFea->getValue(i) - value);
        fea->setValue(i, value);
    }
}

// PRIVATE
QString ColorHistogramExtractor::getCodedDescriptor(bool local, int numBins)
{
    QString coded = QString("%1,%2,%3").arg(name).arg(local?1:0).arg(numBins);

    return coded;
}

int ColorHistogramExtractor::computeSizeTextureOfAPart(int numBins)
{
    return numBins * 3; // trois couleurs RGB
}

int ColorHistogramExtractor::computeSizeTexture(bool local, int numBins)
{
    int numFeaturesOfAPart = computeSizeTextureOfAPart(numBins);

    if (local) return numFeaturesOfAPart * 5;
    return numFeaturesOfAPart;
}

//
// Calculer l'histogramme
// @param :
//      IplImage *img : une image
//      int numBins : niveau de gris
//
void ColorHistogramExtractor::calculFeature(IplImage *img,
                                            int indexPart,
                                            double *histograms,
                                            int numBins,
                                            int numFeatureOfAPart)
{
    if ((histograms == NULL) || (img == NULL))
    {
        throw std::bad_exception();
    }

    IplImage *part = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
    cvCopy(img, part);

    int index = indexPart * numFeatureOfAPart;
    int divise = 256 / numBins;
    int b, g, r;
    CvScalar s;
    double totalPixels = 0;
    for (int i = 0; i < part->height; i++)
    {
        for (int j = 0; j < part->width; j++)
        {
            s = cvGet2D(part, i, j);
            totalPixels++;
            // reduire le niveau de gris
            b = (int)s.val[0] / divise;
            g = ((int)s.val[1] / divise) + numBins;
            r = ((int)s.val[2] / divise) + (2 * numBins);

            if (b == numBins) b--;
            if (g == (2 * numBins)) g--;
            if (r == (3 * numBins)) r--;

            b += index;
            g += index;
            r += index;

            histograms[b] += 1;
            histograms[g] += 1;
            histograms[r] += 1;
        }
    }
    cvReleaseImage(&part);

    // normaliser
    for (int i = 0; i < numFeatureOfAPart; i++)
    {
        histograms[i + index] /= totalPixels;
    }
}

void ColorHistogramExtractor::parseParams(QString params, bool &local, int &numBins)
{
    QStringList fields = params.split(",");

    local = (fields[0].toInt() == 1)?true:false;
    numBins = fields[1].toInt();
}

void ColorHistogramExtractor::parseParams(QString codedDes, QString &name, bool &local, int &numBins)
{
    QStringList fields = codedDes.split(",");

    name = fields[0];
    local = (fields[1].toInt() == 1)?true:false;
    numBins = fields[2].toInt();
}

Q_EXPORT_PLUGIN2(colorhistogramextractor, ColorHistogramExtractor)
