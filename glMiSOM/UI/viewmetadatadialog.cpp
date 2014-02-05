//
//
// viewmetadatadialog.h
//
// LE Viet Man
// 07/07/2011
//
//

#include "viewmetadatadialog.h"
#include "ui_viewmetadatadialog.h"

ViewMetadataDialog::ViewMetadataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewMetadataDialog)
{
    ui->setupUi(this);
    base = 0;
}

ViewMetadataDialog::~ViewMetadataDialog()
{
    delete ui;
    base = 0;
}

void ViewMetadataDialog::setMetadata(QList<Image *> imgs, QList<double> diffs, BaseImage *b)
{
    this->imgs = imgs;
    this->diffs = diffs;
    base = b;

    setWindowTitle(QString("View Metadata - %1 images").arg(imgs.size()));

    currentRow = 0;
    curr = 0;
    addItemsToListDescriptors();
    changeContent();
}

void ViewMetadataDialog::closeEvent(QCloseEvent *e)
{
    Q_UNUSED(e);

    emit close(geometry());
}

void ViewMetadataDialog::on_lstDescriptors_currentRowChanged(int currentRow)
{
    if (currentRow == -1) return;

    this->currentRow = currentRow;
    changeContent();
}

void ViewMetadataDialog::changeContent()
{
    QStringList featuresCoded = base->getFeatureCodedList();
    QString coded = featuresCoded[currentRow];

    Image *img = imgs[curr];
    Feature *feature;
    for (int i = 0; i < img->getSizeFeatures(); i++)
    {
        feature = img->getFeature(i);

        if (feature->getDescriptor() == coded)
        {
            ui->txtMetadata->setText(feature->getFeature());
            break;
        }
    }
    feature = 0;
}

void ViewMetadataDialog::addItemsToListDescriptors()
{
    ui->lstDescriptors->clear();

    QStringList features = base->getFeatureList();
    int size = features.size();
    foreach (QString feature, features)
    {
        ui->lstDescriptors->addItem(feature);
    }

    ui->lblDescriptor->setText( QString("List of descriptors (%1) :").arg(size) );

    ui->cmbImage->clear();
    QString image;
    Image *img;
    double d;
    for (int i = 0; i < imgs.size(); i++)
    {
        img = imgs[i];
        d = diffs[i];
        image = QString("%1 - %2").arg(img->getName()).arg(d);

        ui->cmbImage->addItem(image);
    }
}

void ViewMetadataDialog::on_cmbImage_currentIndexChanged(int index)
{
    if (index == -1) return;

    curr = index;
    changeContent();
}
