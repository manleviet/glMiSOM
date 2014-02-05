//
//
// matrixcooccurrence2extractor.cpp
//
// Implementation de la classe matrixcooccurrence2extractor.h
//
// LE Viet Man
// 12/09/2011
//
//

#include "matrixcooccurrence2extractor.h"

MatrixCooccurrence2Extractor::MatrixCooccurrence2Extractor() : ExtractorInterface()
{
    name = "MATRIXCOOCCURRENCE2";
    fullname = "Matrix Co-occurrences 2";
    ui = 0;
}

QString MatrixCooccurrence2Extractor::about()
{
    return QString("<p><b>Plugin MatrixCooccurrence2Extractor version 1.1</b></p>"
                   "<p>Averaging for every descriptor"
                   "<br>Static plugin"
                   "<br>Build date: %1"
                   "<br>This plugins uses Qt 4.7, OpenCV 2.1"
                   "<br>Author: LE Viet Man"
                   "<br>Email: <a href=\"mailto:manleviet@gmail.com>\">manleviet@gmail.com</a>"
                   "<br>09/2011"
                   "</p>").arg(__TIMESTAMP__);
}

QString MatrixCooccurrence2Extractor::getPluginName()
{
    return QString("libmatrixcooccurrence2extractor.a");
}

ExtractorWidgetInterface *MatrixCooccurrence2Extractor::createUi(QWidget *parent)
{
    MatrixCooccurrence2Widget *widget = new MatrixCooccurrence2Widget(parent);
    ui = widget;
    return widget;
}

Feature *MatrixCooccurrence2Extractor::extract(Image *image, QString params)
{
    // parser des parametres
    bool local;
    int numGreyLevel;
    QList<bool> distances, descriptors;
    parseParams(params, local, distances, numGreyLevel, descriptors);

    IplImage *img = cvLoadImage(image->getPath().toStdString().c_str());

    if (!img)
    {
        // il n'existe pas de cette image
        throw std::bad_exception();
        return NULL;
    }

    QList<CvRect> parts;
    // a partir de la valeur local, on prend des partis de l'image
    Util::splitImageToParts(local, img, parts);

    int numFeaturesOfAPart = computeSizeTextureOfAPart(descriptors);
    int numFeatures = computeSizeTexture(local, descriptors);
    double *textures = (double*)malloc(sizeof(double) * numFeatures);
    memset(textures, 0, sizeof(double) * numFeatures);

    CvRect part;
    for (int i = 0; i < parts.size(); i++)
    {
        part = parts[i];

        cvSetImageROI(img, part);

        calculFeature(img,
                       i,
                       textures,
                       numGreyLevel,
                       distances,
                       descriptors,
                       numFeaturesOfAPart);
    }

    cvReleaseImage(&img);

    // normalisation
    int numMatrix = computeNumMatrixOfAPart(distances);
    for (int i = 0; i < numFeatures; i++)
    {
        textures[i] /= numMatrix;
    }

    // creer un Feature
    Feature *feature = new Feature(getCodedDescriptor(local, distances, numGreyLevel, descriptors),
                                   numFeatures,
                                   textures);

    free(textures);
    return feature;
}

bool MatrixCooccurrence2Extractor::isMyDescriptor(QString codedDes)
{
    QStringList fields = codedDes.split(",");
    if (fields[0] == name)
        return true;
    return false;
}

bool MatrixCooccurrence2Extractor::isLocal(QString params)
{
    // parser des parametres
    bool local;
    QList<bool> distances, descriptors;
    int numGreyLevel;
    parseParams(params, local, distances, numGreyLevel, descriptors);

    return local;
}

QString MatrixCooccurrence2Extractor::getCodedDescriptor(QString params)
{
    // parser des parametres
    bool local;
    QList<bool> distances, descriptors;
    int numGreyLevel;
    parseParams(params, local, distances, numGreyLevel, descriptors);

    return getCodedDescriptor(local, distances, numGreyLevel, descriptors);
}

QString MatrixCooccurrence2Extractor::getFullDescriptor(QString codedDes)
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

    des += QString("Grey Level : %1 - ").arg(fields[3]);

    des += QString("Distances : %1 - ").arg(fields[2]);

    des += QString("Descriptors :");

    QStringList feaList = fields[4].split("-");

    foreach (QString fea, feaList)
    {
        int tmp = fea.toInt();

        switch (tmp)
        {
        case 1:
            des += QString(" Contrast,");
            break;
        case 2:
            des += QString(" Dissimilarity,");
            break;
        case 3:
            des += QString(" Homogeneity,");
            break;
        case 4:
            des += QString(" ASM,");
            break;
        case 5:
            des += QString(" Energy,");
            break;
        case 6:
            des += QString(" Max Probabilite,");
            break;
        case 7:
            des += QString(" Entropy,");
            break;
        case 8:
        case 9:
            des += QString(" Mean,");
            break;
        case 10:
        case 11:
            des += QString(" Variance,");
            break;
        case 12:
        case 13:
            des += QString(" Standard Deviation,");
            break;
        case 14:
        case 15:
            des += QString(" Correlation,");
            break;
        }
    }
    des.remove(des.size() - 1, 1);

    return des;
}

double MatrixCooccurrence2Extractor::calDistanceEuc(Feature *fea1, Feature *fea2)
{
    double difference = 0;

    int size = fea1->getSize();
    difference = calDistance(fea1, fea2, 0, 0, size);

    return difference / size;
}

int MatrixCooccurrence2Extractor::computeSizeTexture(QString codedDes)
{
    if (!isMyDescriptor(codedDes)) return -1;

    QString name;
    bool local;
    int numGreyLevel;
    QList<bool> distances, descriptors;
    parseParams(codedDes, name, local, distances, numGreyLevel, descriptors);

    return computeSizeTexture(local, descriptors);
}

void MatrixCooccurrence2Extractor::adapt(Feature *fea, Feature *imgFea, double alpha)
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
QString MatrixCooccurrence2Extractor::getCodedDescriptor(bool local, QList<bool> distances, int numGreyLevel, QList<bool> descriptors)
{
    QString string = QString("%1,%2,").arg(name).arg(local?1:0);
    for (int i = 0; i < distances.size(); i++)
    {
        if (distances[i])
        {
            string += QString("%1-").arg(i + 1);
        }
    }
    string.remove(string.size() - 1, 1);
    string += QString(",%1,").arg(numGreyLevel);
    for (int i = 0; i < descriptors.size(); i++)
    {
        if (descriptors[i])
        {
            string += QString("%1-").arg(i + 1);
        }
    }
    string.remove(string.size() - 1, 1);
    return string;
}

double MatrixCooccurrence2Extractor::calDistance(Feature *fea1, Feature *fea2, int posBegin1, int posBegin2, int size)
{
    double diff, difference;
    difference = 0;

    for (int i = 0; i < size; i++)
    {
        diff = fea1->getValue(posBegin1 + i) - fea2->getValue(posBegin2 + i);
        difference += diff * diff;
    }
    difference /= size;

    return difference;
}

int MatrixCooccurrence2Extractor::computeSizeTextureOfAPart(QList<bool> descriptors)
{
    int count = 0;
    for (int i = 0; i < descriptors.size(); i++)
    {
        if (descriptors[i]) count++;
    }
    return count;
}

int MatrixCooccurrence2Extractor::computeSizeTexture(bool local, QList<bool> descriptors)
{
    int numFeaturesOfAPart = computeSizeTextureOfAPart(descriptors);

    if (local)
        return numFeaturesOfAPart * 5;
    return numFeaturesOfAPart;
}

int MatrixCooccurrence2Extractor::computeNumMatrixOfAPart(QList<bool> distances)
{
    int count = 0;
    for (int i = 0; i < distances.size(); i++)
    {
        if (distances[i])
        {
            switch (i)
            {
            case 0:
                count += 4;
                break;
            case 1:
                count += 8;
                break;
            case 2:
                count += 12;
                break;
            case 3:
                count += 16;
                break;
            }
        }
    }
    return count;
}

void MatrixCooccurrence2Extractor::calculFeature(IplImage *img, int indexPart, double *textures, int numGreyLevel, QList<bool> distances, QList<bool> descriptors, int numFeatureOfAPart)
{
    if ((textures == NULL) || (img == NULL))
    {
        throw std::bad_exception();
        return;
    }

    int index = indexPart * numFeatureOfAPart;

    IplImage *part = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
    cvCopy(img, part);
    // convertir en gris
    part = convertToGrey(part);

    // CALCUL TEXTURE
    // pour chaque distance
    GLCM *glcm = NULL;
    int pos;
    int numDirections;
    int numDescriptors = descriptors.size();

    for (int k = 0; k < distances.size(); k++)
    {
        if (distances[k])
        {
            numDirections = (k + 1) * 4;
            // creer la matrice co-occurrence
            glcm = new GLCM(numGreyLevel, part, k + 1, numDirections);

            // prendre des parametres
            for (int m = 0; m < numDirections; m++)
            {
                pos = -1;
                for (int n = 0; n < numDescriptors; n++)
                {
                    if (descriptors.at(n))
                    {
                        pos++;
                        textures[index + pos] = glcm->getDescriptor(m, n);
                    }
                }
            }
            delete glcm;
        }
    }
    cvReleaseImage(&part);
}

//
// Convertir en gris
// @param :
//      IplImage *img : une image
//
IplImage *MatrixCooccurrence2Extractor::convertToGrey(IplImage *img)
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

void MatrixCooccurrence2Extractor::parseParams(QString params, bool &local, QList<bool> &distances, int &numGreyLevel, QList<bool> &descriptors)
{
    QStringList fields = params.split(",");

    local = (fields[0].toInt() == 1)?true:false;
    distances = convertStrListToBList(fields[1], MAX_DISTANCES);
    numGreyLevel = fields[2].toInt();
    descriptors = convertStrListToBList(fields[3], MAX_DESCRIPTORS);
}

void MatrixCooccurrence2Extractor::parseParams(QString codedDes, QString &name, bool &local, QList<bool> &distances, int &numGreyLevel, QList<bool> &descriptors)
{
    QStringList fields = codedDes.split(",");

    name = fields[0];
    local = (fields[1].toInt() == 1)?true:false;
    distances = convertStrListToBList(fields[2], MAX_DISTANCES);
    numGreyLevel = fields[3].toInt();
    descriptors = convertStrListToBList(fields[4], MAX_DESCRIPTORS);
}

QList<bool> MatrixCooccurrence2Extractor::convertStrListToBList(QString string, int max)
{
    int t;
    QList<bool> tmp;
    for (int i = 0; i < max; i++)
    {
        tmp << false;
    }

    QStringList fields = string.split("-");

    foreach (QString f, fields)
    {
        t = f.toInt();
        tmp[t - 1] = true;
    }
    return tmp;
}

Q_EXPORT_PLUGIN2(matrixcooccurrence2extractor, MatrixCooccurrence2Extractor)
