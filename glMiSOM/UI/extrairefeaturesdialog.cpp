//
//
// extrairefeaturesdialog.h
//
// LE Viet Man
// 01/07/2011
//
//

#include "extrairefeaturesdialog.h"
#include "ui_extrairefeaturesdialog.h"

ExtraireFeaturesDialog::ExtraireFeaturesDialog(QMainWindow *mainWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExtraireFeaturesDialog)
{
    ui->setupUi(this);

    // CO THE KHONG CAN DUNG THANG NAY
    this->mainWindow = mainWindow;
}

ExtraireFeaturesDialog::~ExtraireFeaturesDialog()
{
    delete ui;
    base = 0;
    mainWindow = 0;
}

void ExtraireFeaturesDialog::closeEvent(QCloseEvent *e)
{
    Q_UNUSED(e);

    emit close(geometry());
}

void ExtraireFeaturesDialog::addBaseImage(BaseImage *base)
{
    this->base = base;

    addItemsToListDescriptors();

    on_cmdDefault_clicked();
}

void ExtraireFeaturesDialog::addExtractors(QList<ExtractorInterface *> extractors)
{
    this->extractors = extractors;

    ExtractorWidgetInterface *groupBox;
    foreach (ExtractorInterface *ext, extractors)
    {
        if (!isAddedToUI(ext->getName()))
        {
            groupBox = ext->createUi(ui->scrollAreaWidgetContents);
            ui->verticalLayout_5->addWidget(groupBox);
            nameExtractors << ext->getName();
        }
    }
}

void ExtraireFeaturesDialog::on_cmdCancel_clicked()
{
    on_cmdDefault_clicked();

    hide();
}

void ExtraireFeaturesDialog::on_cmdDefault_clicked()
{
    foreach (ExtractorInterface *ext, extractors)
    {
        ((ExtractorWidgetInterface*)ext->getUi())->resetDefault();
    }
}

void ExtraireFeaturesDialog::on_cmdExtract_clicked()
{
    if (isHaveError()) return;

    setEnabled(false);

    int count = 0;

    QProgressDialog progress("Extract features...", "Cancel", 0, computeMaxOfProgress() + 6, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    ExtractorWidgetInterface *widget;
    Image *image;
    Feature *feature;
    QStringList params;
    QString coded, fea, nameExt, local;
    foreach (ExtractorInterface *ext, extractors)
    {
        widget = ext->getUi();
        nameExt = ext->getFullName();

        if (widget->isChecked())
        {
            progress.setLabelText( QString("Extract features using %1...").arg(ext->getFullName()) );
            progress.setValue(++count);
            progress.show();

            try
            {
                params = widget->getParams();
                foreach (QString param, params)
                {
                    coded = ext->getCodedDescriptor(param);

                    if (base->isAddable(coded))
                    {
                        fea = ext->getFullDescriptor(coded);
                        base->addFeature(fea, coded);
                        local = ext->isLocal(param) ? QString("Local") : QString("Global");

                        for (int i = 0; i < base->getSizeOfDB(); i++)
                        {
                            image = base->getImage(i);

                            progress.setLabelText( QString("Extract features using %1 - %2 - file %3...").arg(nameExt).arg(local).arg(image->getName()) );
                            progress.show();

                            feature = ext->extract(image, param);

                            image->addFeature(feature);

                            progress.setValue(++count);
                        }
                    }
                    else
                    {
                        count += base->getSizeOfDB();
                        progress.setValue(count);
                    }
                }
            }
            catch (std::exception &ex)
            {
                QMessageBox::information(this, "Error",
                                         QString::fromStdString(ex.what()),
                                         QMessageBox::Ok);
            }
        }

        if (progress.wasCanceled()) return;
    }
    widget = 0;
    image = 0;
    feature = 0;

    progress.setLabelText( QString("Save features...") );
    progress.setValue(++count);
    progress.show();
    // enregistrer des features
    try
    {
        base->saveMetaOfFeature();
    }
    catch (std::exception &ex)
    {
        QMessageBox::information(this, "Error",
                                 QString::fromStdString(ex.what()),
                                 QMessageBox::Ok);
    }

    progress.setLabelText( QString("Done.") );
    progress.setValue(++count);
    progress.show();

    progress.setValue(++count);

    setEnabled(true);

    addItemsToListDescriptors();
}

int ExtraireFeaturesDialog::computeMaxOfProgress()
{
    int total = base->getSizeOfDB();
    int count = 0;

    ExtractorWidgetInterface *widget;
    foreach (ExtractorInterface *ext, extractors)
    {
        widget = ext->getUi();
        if (widget->isChecked())
        {
            if (widget->isGlobalChecked()) count++;
            if (widget->isLocalChecked()) count++;
        }
    }
    widget = 0;

    return total * count;
}

bool ExtraireFeaturesDialog::isHaveError()
{
    foreach (ExtractorInterface *ext, extractors)
    {
        if (ext->getUi()->isHaveError())
            return true;
    }
    return false;
}

void ExtraireFeaturesDialog::addItemsToListDescriptors()
{
    ui->lstDescriptors->clear();
    QStringList feature = base->getFeatureList();

    foreach (QString fea, feature)
    {
        ui->lstDescriptors->addItem(fea);
    }

    ui->lblTotal->setText( QString("List of descriptors (%1) :").arg(feature.size()) );
}

bool ExtraireFeaturesDialog::isAddedToUI(QString nameExtractor)
{
    foreach (QString str, nameExtractors)
    {
        if (str == nameExtractor)
            return true;
    }
    return false;
}
