//
//
// humomentsextractor.cpp
//
// Implementation de la classe humomentsextractor.h
//
// LE Viet Man
// 12/06/2011
//
//

#include "humomentsextractor.h"

HuMomentsExtractor::HuMomentsExtractor() : ExtractorInterface()
{
    name = "HUMOMENTS";
    fullname = "Hu Moments";
    ui = 0;
}

QString HuMomentsExtractor::about()
{
    return QString("<p><b>Plugin HuMomentsExtractor version 1.1</b></p>"
                   "<p>Static plugin"
                   "<br>Build date: %1"
                   "<br>This plugins uses Qt 4.7, OpenCV 2.1"
                   "<br>Author: LE Viet Man"
                   "<br>Email: <a href=\"mailto:manleviet@gmail.com>\">manleviet@gmail.com</a>"
                   "<br>09/2011"
                   "</p>").arg(__TIMESTAMP__);
}

QString HuMomentsExtractor::getPluginName()
{
    return QString("libhumomentsextractor.a");
}

ExtractorWidgetInterface *HuMomentsExtractor::createUi(QWidget *parent)
{
    HuMomentsWidget *widget = new HuMomentsWidget(parent);
    ui = widget;
    return widget;
}

Feature *HuMomentsExtractor::extract(Image *image, QString params)
{
    // parser des parametres
    bool local;
    int numBins;
    parseParams(params, local, numBins);

    IplImage *img = cvLoadImage(image->getPath().toStdString().c_str());

    if (!img)
    {
        // il n'existe pas de cette image
        throw std::bad_exception();
        return NULL;
    }

    QList<CvRect> parts;
    // a partir de la valeur local, on prend des partis
    Util::splitImageToParts(local, img, parts);

    int numFeatures = computeSizeTexture(local, numBins);
    double *humoments = (double*)malloc(sizeof(double) * numFeatures);
    memset(humoments, 0, sizeof(double) * numFeatures);

    CvRect part;
    for (int i = 0; i < parts.size(); i++)
    {
        part = parts[i];

        cvSetImageROI(img, part);

        calculHuMoments(img, i, humoments, numBins, MAX_HUMOMENTS);
    }
    cvReleaseImage(&img);

    // creer un Feature
    Feature *feature = new Feature(getCodedDescriptor(local, numBins), numFeatures, humoments);

    free(humoments);
    return feature;
}

bool HuMomentsExtractor::isMyDescriptor(QString codedDes)
{
    QStringList fields = codedDes.split(",");
    if (fields[0] == name)
        return true;
    return false;
}

bool HuMomentsExtractor::isLocal(QString params)
{
    // parser des parametres
    bool local;
    int numBins;
    parseParams(params, local, numBins);

    return local;
}

QString HuMomentsExtractor::getCodedDescriptor(QString params)
{
    // parser des parametres
    bool local;
    int numBins;
    parseParams(params, local, numBins);

    return getCodedDescriptor(local, numBins);
}

QString HuMomentsExtractor::getFullDescriptor(QString codedDes)
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

    des += QString("Grey Level : %1").arg(fields[2].toInt());

    return des;
}

double HuMomentsExtractor::calDistanceEuc(Feature *fea1, Feature *fea2)
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

int HuMomentsExtractor::computeSizeTexture(QString codedDes)
{
    if (!isMyDescriptor(codedDes)) return -1;

    QString name;
    int numBins;
    bool local;
    parseParams(codedDes, name, local, numBins);

    return computeSizeTexture(local, numBins);
}

void HuMomentsExtractor::adapt(Feature *fea, Feature *imgFea, double alpha)
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
QString HuMomentsExtractor::getCodedDescriptor(bool local, int numBins)
{
    QString coded = QString("%1,%2,%3").arg(name).arg(local?1:0).arg(numBins);

    return coded;
}

int HuMomentsExtractor::computeSizeTexture(bool local, int numBins)
{
    Q_UNUSED(numBins);
    int numFeaturesOfAPart = MAX_HUMOMENTS;

    if (local)
        return numFeaturesOfAPart * 5;
    return numFeaturesOfAPart;
}

void HuMomentsExtractor::calculHuMoments(IplImage *img,
                                         int indexPart,
                                         double *humoments,
                                         int numBins,
                                         int numFeatureOfAPart)
{
    if ((humoments == NULL) || (img == NULL))
    {
        throw std::bad_exception();
        return;
    }

    int index = indexPart * numFeatureOfAPart;

    IplImage *part = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
    cvCopy(img, part);

    // convertir en gris
    part = convertToGrey(part);

    // reduire le niveau de gris
    reduceGreyLevels(part, numBins);

    int lowerThreshold = 80;// lower canny edge threshold initial setting
    int upperThreshold = 160; // upper canny edge threshold initial setting
    int matrixSize = 3; // la taille de matrix Canny

    cvCanny(part, part, lowerThreshold, upperThreshold, matrixSize);
    cvThreshold(part, part, 100, 255, CV_THRESH_BINARY_INV);

    // CALCUL HU MOMENTS
    Moments momentsImageRequete = moments(part, false);
    cvReleaseImage(&part);

    double *huMomentRequete = (double*) malloc(sizeof (double) * MAX_HUMOMENTS);
    memset(huMomentRequete, 0, sizeof(double) * MAX_HUMOMENTS);

    HuMoments(momentsImageRequete, huMomentRequete);

    for (int i = 0; i < MAX_HUMOMENTS; i++)
    {
        humoments[i + index] = huMomentRequete[i];
    }

    free(huMomentRequete);
}

//
// Reduire le nombre de niveau de gris
// @param :
//      IplImage *img : l'image originale
//      int numLevels : nombre de niveau de gris desire
//
void HuMomentsExtractor::reduceGreyLevels(IplImage *img, int numLevels)
{
    int divise = 256 / numLevels;

    CvScalar s;
    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            s = cvGet2D(img, i, j);

            s.val[0] = (int)s.val[0] / divise;
            if (s.val[0] == numLevels) s.val[0]--;

            cvSet2D(img, i, j, s);
        }
    }
}

//
// Convertir en gris
// @param :
//      IplImage *img : une image
//
IplImage *HuMomentsExtractor::convertToGrey(IplImage *img)
{
    IplImage *imgGrey = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);
    cvZero(imgGrey);

    CvScalar s;
    CvScalar grey;
    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            s = cvGet2D(img, i, j);

            grey.val[0] = (s.val[0] + s.val[1] + s.val[2]) / 3;

            cvSet2D(imgGrey, i, j, grey);
        }
    }

    return imgGrey;
}

void HuMomentsExtractor::parseParams(QString params, bool &local, int &numBins)
{
    QStringList fields = params.split(",");

    local = (fields[0].toInt() == 1)?true:false;
    numBins = fields[1].toInt();
}

void HuMomentsExtractor::parseParams(QString codedDes, QString &name, bool &local, int &numBins)
{
    QStringList fields = codedDes.split(",");

    name = fields[0];
    local = (fields[1].toInt() == 1)?true:false;
    numBins = fields[2].toInt();
}

Q_EXPORT_PLUGIN2(humomentsextractor, HuMomentsExtractor)
