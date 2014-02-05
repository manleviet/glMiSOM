//
//
// matrixcooccurren2widget.cpp
//
// Implementation de la classe matrixcooccurren2widget.h
//
// LE Viet Man
// 12/09/2011
//
//

#include "matrixcooccurrence2widget.h"

MatrixCooccurrence2Widget::MatrixCooccurrence2Widget(QWidget *parent)
{
    Q_UNUSED(parent)

    setTitle(QString("Matrix Coocurrences 2 - Average of descriptors"));
    setCheckable(true);
    setChecked(false);

    createUI();

    computeQuantity();
}

MatrixCooccurrence2Widget::~MatrixCooccurrence2Widget()
{
    delete chkGlobal;
    delete chkLocal;
    delete lblGreyLevel;
    delete lblQuantity;
    delete cmbGreyLevel;
    delete chk1;
    delete chk2;
    delete chk3;
    delete chk4;
    delete chkContrast;
    delete chkEntropy;
    delete chkDissimilarity;
    delete chkMean;
    delete chkHomogeneity;
    delete chkVariance;
    delete chkASM;
    delete chkStd;
    delete chkMaxProbabilite;
    delete chkCorrelation;
    delete chkEnergy;
}

void MatrixCooccurrence2Widget::resetDefault()
{
    setChecked(false);
    chkGlobal->setChecked(false);
    chkLocal->setChecked(true);
    cmbGreyLevel->setCurrentIndex(0);
    chk1->setChecked(true);
    chk2->setChecked(true);
    chk3->setChecked(false);
    chk4->setChecked(false);
    chkContrast->setChecked(true);
    chkDissimilarity->setChecked(false);
    chkHomogeneity->setChecked(true);
    chkASM->setChecked(false);
    chkEnergy->setChecked(true);
    chkMaxProbabilite->setChecked(false);
    chkEntropy->setChecked(true);
    chkMean->setChecked(false);
    chkVariance->setChecked(false);
    chkStd->setChecked(false);
    chkCorrelation->setChecked(false);

    computeQuantity();
}

QStringList MatrixCooccurrence2Widget::getParams()
{
    QList<bool> distances = getValuesDistances();
    QList<bool> descirptors = getValuesDescriptors();
    int numBins = cmbGreyLevel->currentText().toInt();
    QStringList list;
    if (chkGlobal->isChecked())
    {
        list << getParam(!chkGlobal->isChecked(), distances, numBins, descirptors);
    }
    if (chkLocal->isChecked())
    {
        list << getParam(chkLocal->isChecked(), distances, numBins, descirptors);
    }
    return list;
}

bool MatrixCooccurrence2Widget::isHaveError()
{
    if ((isChecked()) && (!chkGlobal->isChecked()) && (!chkLocal->isChecked()))
    {
        QMessageBox::information(this, tr("Error"), tr("You should choose local or global in Matrix Cooccurrences."));

        return true;
    }

    if ((isChecked())
            && (!chk1->isChecked())
            && (!chk2->isChecked())
            && (!chk3->isChecked())
            && (!chk4->isChecked()))
    {
        QMessageBox::information(this, tr("Error"), tr("You should choose at least a distance in Matrix Cooccurrences."));

        return true;
    }

    if ((isChecked())
            && (!chkContrast->isChecked())
            && (!chkASM->isChecked())
            && (!chkCorrelation->isChecked())
            && (!chkDissimilarity->isChecked())
            && (!chkEnergy->isChecked())
            && (!chkEntropy->isChecked())
            && (!chkHomogeneity->isChecked())
            && (!chkMaxProbabilite->isChecked())
            && (!chkMean->isChecked())
            && (!chkStd->isChecked())
            && (!chkVariance->isChecked()))
    {
        QMessageBox::information(this, tr("Error"), tr("You should choose at least a descriptor in Matrix Cooccurrences."));

        return true;
    }

    return false;
}

bool MatrixCooccurrence2Widget::isGlobalChecked()
{
    return chkGlobal->isChecked();
}

bool MatrixCooccurrence2Widget::isLocalChecked()
{
    return chkLocal->isChecked();
}

void MatrixCooccurrence2Widget::computeQuantity()
{
    QList<bool> descriptors = getValuesDescriptors();

    QString quantity = tr("Quantity of features : ");
    MatrixCooccurrence2Extractor *ext = new MatrixCooccurrence2Extractor();

    int local, global;

    if (chkGlobal->isChecked())
    {
        global = ext->computeSizeTexture(false, descriptors);
        quantity += tr("Global - %1     ").arg(global);
    }
    if (chkLocal->isChecked())
    {
        local = ext->computeSizeTexture(true, descriptors);
        quantity += tr("Local - %1").arg(local);
    }

    lblQuantity->setText(quantity);
}

void MatrixCooccurrence2Widget::createUI()
{
    QGridLayout *gridLayout = new QGridLayout(this);

    lblQuantity = new QLabel(this);
    lblQuantity->setText(QString("Quantity of features :"));
    QFont font;
    font.setItalic(true);
    lblQuantity->setFont(font);

    gridLayout->addWidget(lblQuantity, 0, 0, 1, 1);

    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QHBoxLayout *horizontalLayout_3 = new QHBoxLayout();
    QVBoxLayout *verticalLayout1 = new QVBoxLayout();
    // horizontal 1
    QHBoxLayout *horizontalLayout = new QHBoxLayout();

    chkGlobal = new QCheckBox(this);
    chkGlobal->setText(QString("Global"));
    connect(chkGlobal, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    horizontalLayout->addWidget(chkGlobal);

    chkLocal = new QCheckBox(this);
    chkLocal->setChecked(true);
    chkLocal->setText(QString("Local"));
    connect(chkLocal, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    horizontalLayout->addWidget(chkLocal);

    QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    verticalLayout1->addLayout(horizontalLayout);

    // horizontal 2
    QHBoxLayout *horizontalLayout_2 = new QHBoxLayout();

    lblGreyLevel = new QLabel(this);
    lblGreyLevel->setText(QString("Grey Level :"));

    horizontalLayout_2->addWidget(lblGreyLevel);

    cmbGreyLevel = new QComboBox(this);
    QStringList items;
    items << "4" << "8" << "16" << "32";
    cmbGreyLevel->addItems(items);

    horizontalLayout_2->addWidget(cmbGreyLevel);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer);

    verticalLayout1->addLayout(horizontalLayout_2);
    // end vertical 1
    horizontalLayout_3->addLayout(verticalLayout1);

    // grpDistance
    QGroupBox *grpDistance = new QGroupBox(this);
    grpDistance->setTitle(QString("Distances"));

    QGridLayout *gridLayout_2 = new QGridLayout(grpDistance);

    chk1 = new QCheckBox(grpDistance);
    chk1->setChecked(true);
    chk1->setText(QString("1"));
    connect(chk1, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_2->addWidget(chk1, 0, 0, 1, 1);

    chk2 = new QCheckBox(grpDistance);
    chk2->setChecked(true);
    chk2->setText(QString("2"));
    connect(chk2, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_2->addWidget(chk2, 0, 1, 1, 1);

    chk3 = new QCheckBox(grpDistance);
    chk3->setText(QString("3"));
    connect(chk3, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_2->addWidget(chk3, 1, 0, 1, 1);

    chk4 = new QCheckBox(grpDistance);
    chk4->setText(QString("4"));
    connect(chk4, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_2->addWidget(chk4, 1, 1, 1, 1);

    horizontalLayout_3->addWidget(grpDistance);

    verticalLayout->addLayout(horizontalLayout_3);

    QGroupBox *grpDescriptors = new QGroupBox(this);
    grpDescriptors->setTitle(QString("Descriptors"));
    QGridLayout *gridLayout_3 = new QGridLayout(grpDescriptors);

    chkContrast = new QCheckBox(grpDescriptors);
    chkContrast->setChecked(true);
    chkContrast->setText(QString("Contrast"));
    connect(chkContrast, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_3->addWidget(chkContrast, 0, 0, 1, 1);

    chkEntropy = new QCheckBox(grpDescriptors);
    chkEntropy->setChecked(true);
    chkEntropy->setText(QString("Entropy"));
    connect(chkEntropy, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_3->addWidget(chkEntropy, 0, 1, 1, 1);

    chkDissimilarity = new QCheckBox(grpDescriptors);
    chkDissimilarity->setText(QString("Dissimilarity"));
    connect(chkDissimilarity, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_3->addWidget(chkDissimilarity, 1, 0, 1, 1);

    chkMean = new QCheckBox(grpDescriptors);
    chkMean->setText(QString("Mean"));
    connect(chkMean, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_3->addWidget(chkMean, 1, 1, 1, 1);

    chkHomogeneity = new QCheckBox(grpDescriptors);
    chkHomogeneity->setChecked(true);
    chkHomogeneity->setText(QString("Homogeneity"));
    connect(chkHomogeneity, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_3->addWidget(chkHomogeneity, 2, 0, 1, 1);

    chkVariance = new QCheckBox(grpDescriptors);
    chkVariance->setText(QString("Variance"));
    connect(chkVariance, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_3->addWidget(chkVariance, 2, 1, 1, 1);

    chkASM = new QCheckBox(grpDescriptors);
    chkASM->setText(QString("ASM"));
    connect(chkASM, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_3->addWidget(chkASM, 3, 0, 1, 1);

    chkStd = new QCheckBox(grpDescriptors);
    chkStd->setText(QString("Standard Deviation"));
    connect(chkStd, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_3->addWidget(chkStd, 3, 1, 1, 1);

    chkMaxProbabilite = new QCheckBox(grpDescriptors);
    chkMaxProbabilite->setText(QString("Max Probabilite"));
    connect(chkMaxProbabilite, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_3->addWidget(chkMaxProbabilite, 6, 0, 1, 1);

    chkCorrelation = new QCheckBox(grpDescriptors);
    chkCorrelation->setText(QString("Correlation"));
    connect(chkCorrelation, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_3->addWidget(chkCorrelation, 4, 1, 1, 1);

    chkEnergy = new QCheckBox(grpDescriptors);
    chkEnergy->setText(QString("Energy"));
    chkEnergy->setChecked(true);
    connect(chkEnergy, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    gridLayout_3->addWidget(chkEnergy, 4, 0, 1, 1);

    verticalLayout->addWidget(grpDescriptors);

    gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);
}

QList<bool> MatrixCooccurrence2Widget::getValuesDistances()
{
    QList<bool> distances;

    distances << chk1->isChecked()
              << chk2->isChecked()
              << chk3->isChecked()
              << chk4->isChecked();

    return distances;

}

QList<bool> MatrixCooccurrence2Widget::getValuesDescriptors()
{
    QList<bool> descriptors;

    descriptors << chkContrast->isChecked()
                << chkDissimilarity->isChecked()
                << chkHomogeneity->isChecked()
                << chkASM->isChecked()
                << chkEnergy->isChecked()
                << chkMaxProbabilite->isChecked()
                << chkEntropy->isChecked()
                << chkMean->isChecked()
                << chkMean->isChecked()
                << chkVariance->isChecked()
                << chkVariance->isChecked()
                << chkStd->isChecked()
                << chkStd->isChecked()
                << chkCorrelation->isChecked()
                << chkCorrelation->isChecked();

    return descriptors;
}

QString MatrixCooccurrence2Widget::convertToStrDes(QList<bool> list)
{
    QString str = "";
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i])
        {
            str += QString("%1-").arg(i + 1);
        }
    }
    str.remove(str.size() - 1, 1);
    return str;
}

QString MatrixCooccurrence2Widget::getParam(bool local, QList<bool> distances, int greyLevel, QList<bool> descriptors)
{
    QString param = QString("%1,%2,%3,%4")
                            .arg(local?1:0)
                            .arg(convertToStrDes(distances))
                            .arg(greyLevel)
                            .arg(convertToStrDes(descriptors));
    return param;
}
