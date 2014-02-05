//
//
// indexationdialog.h
//
// LE Viet Man
// 27/08/2011
//
//

#include "indexationdialog.h"
#include "ui_indexationdialog.h"

IndexationDialog::IndexationDialog(QMainWindow *main, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndexationDialog)
{
    ui->setupUi(this);
    som = 0;
    base = 0;
    gridSOM = 0;
    gridRearrange = 0;

    // CO THE KHONG DUNG DEN THANG NAY
    this->mainWindow = main;

    ui->tabChosenDescriptors->setAcceptDrops(true);
    ui->tabChosenDescriptors->setItemDelegate(new WeightDelegate(COL_WEIGHT));
    connect(ui->tabChosenDescriptors, SIGNAL(chooseFeature()), this, SLOT(chooseFeature()));
    ui->lstDescriptors->setDragEnabled(true);

    dialogViewCodes = new ViewCodesDialog(this);
    connect(ui->btnViewCodes, SIGNAL(clicked()), this, SLOT(viewCodes()));

    connect(ui->btnInit, SIGNAL(clicked()), this, SLOT(init()));
    connect(ui->btnOrdering, SIGNAL(clicked()), this, SLOT(ordering()));
    connect(ui->btnConverge, SIGNAL(clicked()), this, SLOT(converge()));
    connect(ui->btnVisual, SIGNAL(clicked()), this, SLOT(visual()));
    connect(ui->btnRearrange, SIGNAL(clicked()), this, SLOT(rearrange()));
    connect(ui->btnSaveWeight, SIGNAL(clicked()), this, SLOT(saveWeight()));
    connect(ui->btnLoadWeight, SIGNAL(clicked()), this, SLOT(loadWeight()));
}

IndexationDialog::~IndexationDialog()
{
    delete ui;
    mainWindow = 0;
    som = 0;
    base = 0;
    gridSOM = 0;
    gridRearrange = 0;
    delete dialogViewCodes;
}

void IndexationDialog::addExtractors(QList<ExtractorInterface *> exts)
{
    ui->tabChosenDescriptors->addExtractors(exts);
}

void IndexationDialog::setMapSOM(MapSOM *mapSOM)
{
    som = mapSOM;
    base = som->getBaseImage();
    ui->tabChosenDescriptors->setFeatures(base->getFeatureList(), base->getFeatureCodedList());

    addItemsToListDescriptors();

    // mettre des parametres
    setValuesFromSOM();

    updateStatusOfGroups();
}

void IndexationDialog::closeEvent(QCloseEvent *e)
{
    Q_UNUSED(e);

    dialogViewCodes->hide();

    emit close(geometry());
}

void IndexationDialog::on_btnDefault_clicked()
{
    som->resetToDefaultValues();
    setValuesFromSOM();
    updateStatusOfGroups();
}

void IndexationDialog::on_btnCancel_clicked()
{
    hide();
}

void IndexationDialog::viewCodes()
{
    dialogViewCodes->addCodes(som);
    dialogViewCodes->show();
}

void IndexationDialog::chooseFeature()
{
    updateStatusOfGroups();
}

void IndexationDialog::init()
{
    if (isHaveError()) return;

    // prendre des parametres
    FeaturesChosenList *list = createFeaturesChosenList();
    int xdim = ui->spiXdim->value();
    int ydim = ui->spiYdim->value();
    int randomize = ui->spbRandomize->value();
    MapSOM::NEIGH_TYPE typeNeight;
    if (ui->cmbNeighType->currentIndex() == 0)
    {
        typeNeight = MapSOM::NEIGH_BUBBLE;
    }
    else
    {
        typeNeight = MapSOM::NEIGH_GAUSSIAN;
    }
    MapSOM::ALPHA_TYPE typeAlpha;
    if (ui->cmbAlphaType->currentIndex() == 0)
    {
        typeAlpha = MapSOM::ALPHA_LINEAR;
    }
    else
    {
        typeAlpha = MapSOM::ALPHA_INVERSE_T;
    }

    QString content;
    QTime time;

    int count = 0;

    QProgressDialog progress("Init...", "Cancel", 0, 8, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    // 1. INIT
    progress.setLabelText( QString("Init map...") );
    progress.setValue(++count);
    progress.show();

    time.start();
    try
    {
        som->init(progress, count, list, xdim, ydim, typeNeight, typeAlpha, randomize);
    }
    catch (std::exception &ex)
    {
        QMessageBox::information(this, "Error",
                                 QString::fromStdString(ex.what()),
                                 QMessageBox::Ok);
    }
    list = 0;
    int t = time.elapsed();
    content = QString("Init time : %1 ms").arg(t);
    ui->lblInitTime->setText(content);
    ui->lblInitTime->adjustSize();

    // SAVE MAP
    progress.setLabelText( QString("Save map...") );
    progress.setValue(++count);
    progress.show();

    try
    {
        som->save();
    }
    catch (std::exception &ex)
    {
        QMessageBox::information(this, "Error",
                                 QString::fromStdString(ex.what()),
                                 QMessageBox::Ok);
    }
    emit saveMap(true);

    progress.setLabelText( QString("Done.") );
    progress.setValue(++count);
    progress.show();

    progress.setValue(++count);

    updateStatusOfGroups();
}

void IndexationDialog::saveWeight()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Choose a filename for save the codes"),
                                                Util::getFileWeightUntitle(),
                                                tr("Weight File (*.wht)"));
    if (!fileName.isEmpty())
    {
        int count = 0;

        QProgressDialog progress("Save weight...", "Cancel", 0, 3, mainWindow);
        progress.setWindowModality(Qt::WindowModal);
        progress.show();

        progress.setLabelText( QString("Write header...") );
        progress.setValue(++count);
        progress.show();

        try
        {
            progress.setLabelText( QString("Write codes...") );
            progress.setValue(++count);
            progress.show();

            som->saveWeight(fileName);
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
    }
}

void IndexationDialog::loadWeight()
{
    int ret = QMessageBox::warning(this, "Warning",
                                   QString("When load a weight file, the calculated codes will be lost."
                                           "You should save before loading."
                                           "Do you still want to load ?"),
                                   QMessageBox::Yes | QMessageBox::No,
                                   QMessageBox::Yes);

    if (ret == QMessageBox::No) return;

    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Choose a weights file"),
                                                    QDir::homePath(),
                                                    tr("Weight file (*.wht)"));

    if (!filename.isEmpty())
    {
        try
        {
            FeaturesChosenList *list = createFeaturesChosenList();

            som->loadWeight(filename, list);
        }
        catch (std::exception &ex)
        {
            QMessageBox::information(this, "Error",
                                     QString::fromStdString(ex.what()),
                                     QMessageBox::Ok);
        }

        ui->spiXdim->setValue(som->getXdim());
        ui->spiYdim->setValue(som->getYdim());
        ui->spbRandomize->setValue(som->getRadomize());
        ui->cmbNeighType->setCurrentIndex(som->getTypeNeigh());
        ui->cmbAlphaType->setCurrentIndex(som->getTypeAlpha());
        ui->spbLengthOrdering->setValue(som->getLengthOrdering());
        ui->spbLengthConvergence->setValue(som->getLengthConver());
        ui->spbRadius_Ordering->setValue(som->getRadiusOrdering());
        ui->spbRadius_Conver->setValue(som->getRadiusConver());
        ui->spbAlpha_Ordering->setValue(som->getAlphaOrdering());
        ui->spbAlpha_Conver->setValue(som->getAlphaConver());
        ui->spiStepRearr->setValue(som->getLengthRearrange());

        updateStatusOfGroups();
    }
}

void IndexationDialog::ordering()
{
    if (!som->isInitCodes()) return;

    // prendre des parametres
    long lengthOrdering = ui->spbLengthOrdering->value();
    double radiusOrdering = ui->spbRadius_Ordering->value();
    double alphaOrdering = ui->spbAlpha_Ordering->value();

    QString content;
    QTime time;

    int count = 0;

    QProgressDialog progress("Training...", "Cancel", 0, ui->spbLengthOrdering->value() + 4, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    // 2. TRAINING
    progress.setLabelText( QString("Ordering phase...") );
    progress.setValue(++count);
    progress.show();

    time.start();
    try
    {
        som->training(progress, count, MapSOM::ORDERING, lengthOrdering, radiusOrdering, alphaOrdering);
    }
    catch (std::exception &ex)
    {
        QMessageBox::information(this, "Error",
                                 QString::fromStdString(ex.what()),
                                 QMessageBox::Ok);
    }
    int t = time.elapsed();
    content += QString("Ordering time : %1 ms").arg(t);
    ui->lblOrderingTime->setText(content);
    ui->lblOrderingTime->adjustSize();

    // 5. SAVE MAP
    progress.setLabelText( QString("Save map...") );
    progress.setValue(++count);
    progress.show();

    try
    {
        som->save();
    }
    catch (std::exception &ex)
    {
        QMessageBox::information(this, "Error",
                                 QString::fromStdString(ex.what()),
                                 QMessageBox::Ok);
    }
    emit saveMap(true);

    progress.setLabelText( QString("Done.") );
    progress.setValue(++count);
    progress.show();

    progress.setValue(++count);
}

void IndexationDialog::converge()
{
    if (!som->isInitCodes()) return;

    // prendre des parametres
    long lengthConver = ui->spbLengthConvergence->value();
    double radiusConver = ui->spbRadius_Conver->value();
    double alphaConver = ui->spbAlpha_Conver->value();

    QString content;
    QTime time;

    int count = 0;

    QProgressDialog progress("Training...", "Cancel", 0, ui->spbLengthConvergence->value() + 4, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    // 2. TRAINING
    progress.setLabelText( QString("Convergence phase...") );
    progress.setValue(++count);
    progress.show();

    time.start();
    try
    {
        som->training(progress, count, MapSOM::CONVERGENCE, lengthConver, radiusConver, alphaConver);
    }
    catch (std::exception &ex)
    {
        QMessageBox::information(this, "Error",
                                 QString::fromStdString(ex.what()),
                                 QMessageBox::Ok);
    }
    int t = time.elapsed();
    content += QString("Convergence time : %1 ms").arg(t);
    ui->lblConvergeTime->setText(content);
    ui->lblConvergeTime->adjustSize();

    // 5. SAVE MAP
    progress.setLabelText( QString("Save map...") );
    progress.setValue(++count);
    progress.show();

    try
    {
        som->save();
    }
    catch (std::exception &ex)
    {
        QMessageBox::information(this, "Error",
                                 QString::fromStdString(ex.what()),
                                 QMessageBox::Ok);
    }
    emit saveMap(true);

    progress.setLabelText( QString("Done.") );
    progress.setValue(++count);
    progress.show();

    progress.setValue(++count);
}

void IndexationDialog::visual()
{
    if (!som->isInitCodes()) return;

    int count = 0;

    QProgressDialog progress("Visual...", "Cancel", 0, base->getSizeOfDB() + 4, mainWindow);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    // 3. VISUAL
    progress.setLabelText( QString("Visual...") );
    progress.setValue(++count);
    progress.show();

    try
    {
        gridSOM = som->visual(progress, count);
    }
    catch (std::exception &ex)
    {
        QMessageBox::information(this, "Error",
                                 QString::fromStdString(ex.what()),
                                 QMessageBox::Ok);
    }
    emit finishVisual(gridSOM);

    // 5. SAVE MAP
    progress.setLabelText( QString("Save map...") );
    progress.setValue(++count);
    progress.show();

    try
    {
        som->save();
    }
    catch (std::exception &ex)
    {
        QMessageBox::information(this, "Error",
                                 QString::fromStdString(ex.what()),
                                 QMessageBox::Ok);
    }
    emit saveMap(true);

    progress.setLabelText( QString("Done.") );
    progress.setValue(++count);
    progress.show();

    progress.setValue(++count);

    updateStatusOfGroups();
}

void IndexationDialog::rearrange()
{
    if (gridSOM == 0) return;

    int count = 0;

    QProgressDialog progress("Re-arrangement...", "Cancel", 0, ui->spiStepRearr->value() + 4, mainWindow);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    // 4. REARRANGEMENT
    progress.setLabelText( QString("Re-arrangement...") );
    progress.setValue(++count);
    progress.show();

    try
    {
        gridRearrange = som->rearrange(progress, count, ui->spiStepRearr->value(), gridSOM);
    }
    catch (std::exception &ex)
    {
        QMessageBox::information(this, "Error",
                                 QString::fromStdString(ex.what()),
                                 QMessageBox::Ok);
    }
    emit finishRearrange(gridRearrange);

    // 5. SAVE MAP
    progress.setLabelText( QString("Save map...") );
    progress.setValue(++count);
    progress.show();

    try
    {
        som->save();
    }
    catch (std::exception &ex)
    {
        QMessageBox::information(this, "Error",
                                 QString::fromStdString(ex.what()),
                                 QMessageBox::Ok);
    }
    emit saveMap(true);

    progress.setLabelText( QString("Done.") );
    progress.setValue(++count);
    progress.show();

    progress.setValue(++count);
}

// PRIVATE

FeaturesChosenList *IndexationDialog::createFeaturesChosenList()
{
    FeaturesChosenList *list = new FeaturesChosenList();

    QString fea;
    double weight;
    QStringList features = base->getFeatureList();
    for (int i = 0; i < ui->tabChosenDescriptors->rowCount(); i++)
    {
        fea = ui->tabChosenDescriptors->item(i, COL_FEATURE)->text();
        weight = ui->tabChosenDescriptors->item(i, COL_WEIGHT)->text().toDouble() / 100;

        for (int j = 0; j < features.size(); j++)
        {
            if (fea == features[j])
            {
                list->addFeature(j, weight);
                break;
            }
        }
    }

    return list;
}

void IndexationDialog::setValuesFromSOM()
{
    ui->spiXdim->setValue(som->getXdim());
    ui->spiYdim->setValue(som->getYdim());
    ui->spbRandomize->setValue(som->getRadomize());
    ui->cmbNeighType->setCurrentIndex(som->getTypeNeigh());
    ui->cmbAlphaType->setCurrentIndex(som->getTypeAlpha());
    ui->spbLengthOrdering->setValue(som->getLengthOrdering());
    ui->spbLengthConvergence->setValue(som->getLengthConver());
    ui->spbRadius_Ordering->setValue(som->getRadiusOrdering());
    ui->spbRadius_Conver->setValue(som->getRadiusConver());
    ui->spbAlpha_Ordering->setValue(som->getAlphaOrdering());
    ui->spbAlpha_Conver->setValue(som->getAlphaConver());
    ui->spiStepRearr->setValue(som->getLengthRearrange());

    ui->tabChosenDescriptors->removeAllItems();
    if (som->isChoosenFeatures())
    {
        ui->tabChosenDescriptors->addItems(som->getChoosenFeatures());
    }

    if (som->isHaveGridSOM())
        gridSOM = som->getGridSOM();
    if (som->isHaveGridRearrange())
        gridRearrange = som->getGridRearrange();
}

void IndexationDialog::updateStatusOfGroups()
{
    bool bFeaChoosen = ui->tabChosenDescriptors->isChoosenFeatures();
    bool bCodesInited = som->isInitCodes();

    ui->grpInit->setEnabled(bFeaChoosen);
    ui->btnSaveWeight->setEnabled(bCodesInited);
    ui->grpTraining->setEnabled(bCodesInited);
    ui->grpVisual->setEnabled(bCodesInited);
    ui->btnRearrange->setEnabled( (gridSOM == 0) ? false : true );
}

void IndexationDialog::addItemsToListDescriptors()
{
    ui->lstDescriptors->clear();
    QStringList feature = base->getFeatureList();

    foreach (QString fea, feature)
    {
        ui->lstDescriptors->addItem(fea);
    }

    ui->lblTotal->setText( QString("List of descriptors (%1) :").arg(feature.size()) );
}

bool IndexationDialog::isHaveError()
{
    if (calTotalOfWeights() != 100)
    {
        QMessageBox::information(this, tr("Error"), tr("Total of weights have to equal 100%."));

        return true;
    }

    if ((ui->spiXdim->value() * ui->spiYdim->value()) < base->getSizeOfDB())
    {
        QMessageBox::information(this, tr("Error"), tr("Size of map have to larger number of images."));

        return true;
    }

    return false;
}

int IndexationDialog::calTotalOfWeights()
{
    float total = 0;
    for (int i = 0; i < ui->tabChosenDescriptors->rowCount(); i++)
    {
        total += ui->tabChosenDescriptors->item(i, COL_WEIGHT)->text().toFloat();
    }
    return (int)total;
}

#include <iostream>
using namespace std;

void IndexationDialog::printGridSOM(GridSOM *grid)
{
    CellSOM *cell;
    QList<Image*> imgs;
    Image *img;
    for (int i = 0; i < grid->getXDim(); i++)
    {
        for (int j = 0; j < grid->getYDim(); j++)
        {
            cell = grid->getCell(i, j);
            imgs = cell->getAllImage();

            cout << "<" << i << "," << j << "> ";

            for (int k = 0; k < imgs.size(); k++)
            {
                img = imgs[k];
                cout << img->getName().toStdString() << " ";
            }
            cout << endl;
        }
    }
    cell = 0;
    img = 0;
}

void IndexationDialog::printGridSOMtoFile(GridSOM *grid)
{
    QFile file(Util::getPathFileSOM());
    bool append = false;
    if (file.exists())
    {
        append = true;
        if (!file.open(QFile::Append | QFile::Text))
            throw std::bad_exception();
    }
    else
    {
        if (!file.open(QFile::WriteOnly | QFile::Text))
            throw std::bad_exception();
    }

    QTextStream out(&file);

    CellSOM *cell;
    QList<Image*> imgs;
    Image *img;
    for (int i = 0; i < grid->getXDim(); i++)
    {
        for (int j = 0; j < grid->getYDim(); j++)
        {
            cell = grid->getCell(i, j);
            imgs = cell->getAllImage();

            out << "<" << i << "," << j << "> ";

            for (int k = 0; k < imgs.size(); k++)
            {
                img = imgs[k];
                out << img->getName() << " ";
            }
            out << endl;
        }
        flush(out);
    }
    cell = 0;
    img = 0;
}
