//
//
// matrixcooccurrenceextractor.cpp
//
// Implementation de la classe matrixcooccurrenceextractor.h
//
// LE Viet Man
// 12/06/2011
//
//

#include "matrixcooccurrenceextractor.h"

MatrixCooccurrenceExtractor::MatrixCooccurrenceExtractor() : ExtractorInterface()
{
    name = "MATRIXCOOCCURRENCE";
    fullname = "Matrix Co-occurrences";
    ui = 0;
}

QString MatrixCooccurrenceExtractor::about()
{
    return QString("<p><b>Plugin MatrixCooccurrenceExtractor version 1.1</b></p>"
                   "<p>Using the methode Bipartite matching for calculate the distance"
                   "<br>Build date: %1"
                   "<br>This plugins uses Qt 4.7, OpenCV 2.1"
                   "<br>Author: LE Viet Man"
                   "<br>Email: <a href=\"mailto:manleviet@gmail.com>\">manleviet@gmail.com</a>"
                   "<br>09/2011"
                   "</p>").arg(__TIMESTAMP__);
}

QString MatrixCooccurrenceExtractor::getPluginName()
{
    return QString("libmatrixcooccurrenceextractor.so");
}

ExtractorWidgetInterface *MatrixCooccurrenceExtractor::createUi(QWidget *parent)
{
    MatrixCooccurrenceWidget *widget = new MatrixCooccurrenceWidget(parent);
    ui = widget;
    return widget;
}

Feature *MatrixCooccurrenceExtractor::extract(Image *image, QString params)
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
    // a partir de la valeur local, on prend des partis
    Util::splitImageToParts(local, img, parts);

    int numFeaturesOfAPart = computeSizeTextureOfAPart(distances, descriptors);
    int numFeatures = computeSizeTexture(local, distances, descriptors);
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

    // creer un Feature
    Feature *feature = new Feature(getCodedDescriptor(local, distances, numGreyLevel, descriptors),
                                   numFeatures,
                                   textures);

    free(textures);
    return feature;
}

bool MatrixCooccurrenceExtractor::isMyDescriptor(QString codedDes)
{
    QStringList fields = codedDes.split(",");
    if (fields[0] == name)
        return true;
    return false;
}

bool MatrixCooccurrenceExtractor::isLocal(QString params)
{
    // parser des parametres
    bool local;
    QList<bool> distances, descriptors;
    int numGreyLevel;
    parseParams(params, local, distances, numGreyLevel, descriptors);

    return local;
}

QString MatrixCooccurrenceExtractor::getCodedDescriptor(QString params)
{
    // parser des parametres
    bool local;
    QList<bool> distances, descriptors;
    int numGreyLevel;
    parseParams(params, local, distances, numGreyLevel, descriptors);

    return getCodedDescriptor(local, distances, numGreyLevel, descriptors);
}

QString MatrixCooccurrenceExtractor::getFullDescriptor(QString codedDes)
{
    QStringList fields = codedDes.split(",");

    QString des = QString("Matrix Cooccurrences");

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

double MatrixCooccurrenceExtractor::calDistanceEuc(Feature *fea1, Feature *fea2)
{
    // calculer le nombre des matrices
    int numMatrix, numDes;
    QString des = fea1->getDescriptor();

    numMatrix = getNumMatrix(des);
    numDes = getNumDescriptors(des);

    double distance = 0;
    double minDistance;
    bool* flag;
    double* d;
    int mem;
    int posBegin1, posBegin2;

    flag = (bool*)malloc(sizeof(bool) * numMatrix);
    memset(flag, 0, sizeof(bool) * numMatrix);

    d = (double*)malloc(sizeof(double) * numMatrix);

    for (int i = 0; i < numMatrix; i++)
    {
        // chaque matrice de co-occurence
        // calculer la distance avec les autres matrices
        memset(d, (int)DBL_MAX, sizeof(double) * numMatrix);

        posBegin1 = i * numDes;

        for (int j = 0; j < numMatrix; j++)
        {
            if (!flag[j])
            {
                posBegin2 = j * numDes;

                d[j] = calDistance(fea1, fea2, posBegin1, posBegin2, numDes);
            }
        }

        // trouver la plus basse valeur
        minDistance = DBL_MAX;
        mem = numMatrix;
        for (int j = 0; j < numMatrix; j++)
        {
            if (d[j] < minDistance)
            {
                minDistance = d[j];
                mem = j;
            }
        }

        flag[mem] = true;
        distance += minDistance;
    }

    free(flag);
    free(d);
    flag = 0;
    d = 0;

    return distance;
}

int MatrixCooccurrenceExtractor::computeSizeTexture(QString codedDes)
{
    if (!isMyDescriptor(codedDes)) return -1;

    QString name;
    bool local;
    int numGreyLevel;
    QList<bool> distances, descriptors;
    parseParams(codedDes, name, local, distances, numGreyLevel, descriptors);

    return computeSizeTexture(local, distances, descriptors);
}

void MatrixCooccurrenceExtractor::adapt(Feature *fea, Feature *imgFea, double alpha)
{
    QString des = fea->getDescriptor();
    if (!isMyDescriptor(des)) return;

    int numMatrix, numDes;
    // calculer le nombre des matrices
    numMatrix = getNumMatrix(des);
    // calculer le nombre des descripteurs
    numDes = getNumDescriptors(des);

    double minDistance;
    bool *flag;
    double *d;
    double value;
    int mem;
    int posBegin1, posBegin2;

    flag = (bool*)malloc(sizeof(bool) * numMatrix);
    memset(flag, 0, sizeof(bool) * numMatrix);

    d = (double*)malloc(sizeof(double) * numMatrix);

    for (int i = 0; i < numMatrix; i++)
    {
        // chaque matrice de co-occurence
        // calculer la distance avec les autres matrices
        memset(d, (int)DBL_MAX, sizeof(double) * numMatrix);

        posBegin1 = i * numDes;

        for (int j = 0; j < numMatrix; j++)
        {
            if (!flag[j])
            {
                posBegin2 = j * numDes;

                d[j] = calDistance(fea, imgFea, posBegin1, posBegin2, numDes);
            }
        }

        // trouver la plus basse valeur
        minDistance = DBL_MAX;
        mem = numMatrix;
        for (int j = 0; j < numMatrix; j++)
        {
            if (d[j] < minDistance)
            {
                minDistance = d[j];
                mem = j;
            }
        }

        flag[mem] = true;
        // faire l'adaption
        posBegin2 = mem * numDes;
        for (int i = 0; i < numDes; i++)
        {
            value = fea->getValue(posBegin1 + i);
            value += alpha * (imgFea->getValue(posBegin2 + i) - value);
            fea->setValue(posBegin1 + i, value);
        }
    }
    free(flag);
    free(d);
    flag = 0;
    d = 0;
}

int MatrixCooccurrenceExtractor::getNumMatrix(QString codedDes)
{
    if (!isMyDescriptor(codedDes)) return -1;
    // calculer le nombre des matrices
    QString name;
    bool local;
    int numGreyLevel;
    QList<bool> distances, descriptors;
    parseParams(codedDes, name, local, distances, numGreyLevel, descriptors);

    return computeNumMatrix(local, distances);
}

int MatrixCooccurrenceExtractor::getNumDescriptors(QString codedDes)
{
    if (!isMyDescriptor(codedDes)) return -1;

    QStringList fields = codedDes.split(",");
    fields = fields[4].split("-");

    return fields.size();
}

double MatrixCooccurrenceExtractor::calDistance(Feature *fea1, Feature *fea2, int posBegin1, int posBegin2, int size)
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

// PRIVATE
QString MatrixCooccurrenceExtractor::getCodedDescriptor(bool local, QList<bool> distances, int numGreyLevel, QList<bool> descriptors)
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

int MatrixCooccurrenceExtractor::computeSizeTextureOfAPart(QList<bool> distances, QList<bool> descriptors)
{
    int size = computeNumMatrixOfAPart(distances);
    int count = 0;
    for (int i = 0; i < descriptors.size(); i++)
    {
        if (descriptors[i]) count++;
    }
    size *= count;
    return size;
}

int MatrixCooccurrenceExtractor::computeSizeTexture(bool local, QList<bool> distances, QList<bool> descriptors)
{
    int numFeaturesOfAPart = computeSizeTextureOfAPart(distances, descriptors);

    if (local)
        return numFeaturesOfAPart * 5;
    return numFeaturesOfAPart;
}

int MatrixCooccurrenceExtractor::computeNumMatrixOfAPart(QList<bool> distances)
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

int MatrixCooccurrenceExtractor::computeNumMatrix(bool local, QList<bool> distances)
{
    int numMatrixOfAPart = computeNumMatrixOfAPart(distances);

    if (local)
        return numMatrixOfAPart * 5;
    return numMatrixOfAPart;
}

void MatrixCooccurrenceExtractor::calculFeature(IplImage *img,
                                                int indexPart,
                                                double *textures,
                                                int numGreyLevel,
                                                QList<bool> distances,
                                                QList<bool> descriptors,
                                                int numFeatureOfAPart)
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
    int pos = index - 1;
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
                for (int n = 0; n < numDescriptors; n++)
                {
                    if (descriptors.at(n))
                    {
                        pos++;
                        textures[pos] = glcm->getDescriptor(m, n);
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
IplImage *MatrixCooccurrenceExtractor::convertToGrey(IplImage *img)
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

void MatrixCooccurrenceExtractor::parseParams(QString params, bool &local, QList<bool> &distances, int &numGreyLevel, QList<bool> &descriptors)
{
    QStringList fields = params.split(",");

    local = (fields[0].toInt() == 1)?true:false;
    distances = convertStrListToBList(fields[1], MAX_DISTANCES);
    numGreyLevel = fields[2].toInt();
    descriptors = convertStrListToBList(fields[3], MAX_DESCRIPTORS);
}

void MatrixCooccurrenceExtractor::parseParams(QString codedDes, QString &name, bool &local, QList<bool> &distances, int &numGreyLevel, QList<bool> &descriptors)
{
    QStringList fields = codedDes.split(",");

    name = fields[0];
    local = (fields[1].toInt() == 1)?true:false;
    distances = convertStrListToBList(fields[2], MAX_DISTANCES);
    numGreyLevel = fields[3].toInt();
    descriptors = convertStrListToBList(fields[4], MAX_DESCRIPTORS);
}

QList<bool> MatrixCooccurrenceExtractor::convertStrListToBList(QString string, int max)
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

Q_EXPORT_PLUGIN2(matrixcooccurrenceextractor, MatrixCooccurrenceExtractor)
