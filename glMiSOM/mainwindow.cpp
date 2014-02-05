//
//
// mainwindow.cpp
//
// LE Viet Man
// 28/05/2011
//
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <iostream>
//using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("glMiSOM");

    this->base = 0;
    this->glNormalScene = 0;
    this->glSOMScene = 0;
    this->glRearrangeScene = 0;
    this->gridSOM = 0;
    this->gridNormal = 0;
    this->gridRearrange = 0;
    this->som = 0;

    workspace = new QWorkspace();
    connect(workspace, SIGNAL(windowActivated(QWidget*)), this, SLOT(updateMenus()));
    setCentralWidget(workspace);

    loadPlugins();
    createMenu();
    createDialogs();

    ui->statusBar->showMessage("Ready");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete workspace;
    delete glSOMScene;
    delete glNormalScene;
    delete glRearrangeScene;
    delete gridNormal;
    delete gridSOM;
    delete gridRearrange;
    delete som;
    delete base;
    delete dialogExtractFeature;
    delete dialogViewMetadata;
    delete dialogViewImage;
    delete dialogIndexing;
    delete dialogCaptureScreen;
    delete dialogPlugins;

    while (!extractors.isEmpty())
    {
        delete extractors.takeFirst();
    }
}

QSize MainWindow::minimumSizeHint() const
{
    return QSize(200,200);
}

QSize MainWindow::sizeHint() const
{
    return QSize(850, 600);
}

void MainWindow::addWindowToWorkspace(GLSOMScene *scene)
{
    workspace->addWindow(scene);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!activeSOMScene()) return;
    switch (event->key())
    {
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Up:
        case Qt::Key_Down:
            emit keyPress(activeSOMScene(), event);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    workspace->closeAllWindows();
    if (activeSOMScene())
        event->ignore();

    closeAllDialogs();

    event->accept();
}

void MainWindow::openDatabase()
{
    closeAllDialogs();

    // ouvrir la dialog pour choisir un fichier
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this,
                                                          tr("Open database of images"),
                                                          QDir::homePath(),
                                                          options);

    if (!directory.isEmpty())
    {
        QDir dir(directory);
        if (!dir.exists())
        {
            QErrorMessage errorMessageDialog(this);

            errorMessageDialog.showMessage(
                        QObject::tr("This database of images is not exist."
                                    "The path given is maybe not right."));

            return;
        }

        try
        {
            if (base != 0) delete base;

            // creer un nouveau BaseImage
            base = new BaseImage(directory);

            ui->statusBar->showMessage(QObject::tr("Load database %1...").arg(base->getNameOfDB()));

            // load
            base->loadDB();

            // creer un gridSOM de type Normal
            gridNormal = new GridSOM(base);

            if (glNormalScene != 0)
            {
                glNormalScene->hide();
                delete glNormalScene;
            }
            glNormalScene = 0;
            viewNormalScene();
            if (glSOMScene != 0)
            {
                glSOMScene->hide();
                delete glSOMScene;
            }
            glSOMScene = 0;
            if (glRearrangeScene != 0)
            {
                glRearrangeScene->hide();
                delete glRearrangeScene;
            }
            glRearrangeScene = 0;
            ui->actionNormal->setEnabled(true);

            // SOM
            if (som != 0)
                delete som;

            som = new MapSOM(base);
            som->addExtractors(extractors);
            som->load();

            // mettre a jour des fenetres
            updateGridSOMAndRearrange();
        }
        catch (std::exception &ex)
        {
            QMessageBox::information(this, "Error",
                                     QString::fromStdString(ex.what()),
                                     QMessageBox::Ok);
        }
        // enabled actions
        enableActions();

        ui->actionAnimation->setChecked(false);
        ui->actionOriginal_Position->setEnabled(false);
        ui->actionLoad_map->setEnabled(true);

        this->setWindowTitle(QString("glMiSOM - %1").arg(base->getNameOfDB()));

        ui->statusBar->showMessage("Load done");
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About glMiSOM"),
            tr("<p><b>glMiSOM version 1.5</b></p>"
               "<p>Build date: %1"
               "<br>This program uses Qt 4.7, OpenCV 2.1"
               "<br>Author: LE Viet Man"
               "<br>Email: <a href=\"mailto:manleviet@gmail.com>\">manleviet@gmail.com</a>"
               "<br>09/2011"
               "</p>").arg(__TIMESTAMP__));
}

void MainWindow::information()
{
    QString content, descriptors, cFeatures;

    QStringList features = base->getFeatureList();

    foreach (QString fea, features)
    {
        descriptors += tr("<br> + %1").arg(fea);
    }

    content = tr("<p><b>Database %1</b></p>"
                 "<p><b>Path</b> : %2"
                 "<br><b>Quantity of images</b> : %3"
                 "<br><b>List of descriptors (%4)</b> :"
                 "%5</p>")
            .arg(base->getNameOfDB())
            .arg(base->getPathOfDB())
            .arg(base->getSizeOfDB())
            .arg(features.size())
            .arg(descriptors);

    if (som->isChoosenFeatures())
    {
        FeaturesChosenList *list = som->getChoosenFeatures();

        for (int i = 0; i < list->getSize(); i++)
        {
            cFeatures += tr("<br> + %1").arg(features[list->getIndex(i)]);
        }

        content += tr("<p><br><b>List of choosen descriptors for SOM </b>:"
                      "%6</p>").arg(cFeatures);
    }

    QMessageBox::about(this, tr("Information of database"), content);
}

void MainWindow::viewNormal()
{
    viewNormalScene();
}

void MainWindow::viewSOM()
{
    viewSOMScene();
}

void MainWindow::viewRearrange()
{
    viewRearrangeScene();
}

void MainWindow::viewOriginPosition()
{
    if (activeSOMScene())
    {
        activeSOMScene()->viewOriginPosition();
        ui->actionOriginal_Position->setEnabled(false);
    }
}

void MainWindow::onAnimation(bool enabled)
{
    if (activeSOMScene())
        activeSOMScene()->setAnimatable(enabled);
}

void MainWindow::showSOMSceneOnFullScreen()
{
    GLSOMScene *scene = activeSOMScene();
    if (scene)
    {
        scene->saveGeometryBeforeFullscreen();
        scene->setParent(0);
        this->hide();
        this->setParent(scene);
        scene->showFullScreen();
    }
}

void MainWindow::showFeaturesExtractDialog()
{
    dialogExtractFeature->addBaseImage(base);
    dialogExtractFeature->addExtractors(extractors);

    if (dialogExtractFeature->isHidden() && (geoExtractFeature != QRect(0, 0, 0, 0)))
        dialogExtractFeature->setGeometry(geoExtractFeature);

    dialogExtractFeature->show();
}

void MainWindow::showIndexingDialog()
{
    dialogIndexing->setMapSOM(som);
    dialogIndexing->addExtractors(extractors);

    if (dialogIndexing->isHidden() && (geoIndexing != QRect(0, 0, 0, 0)))
        dialogIndexing->setGeometry(geoIndexing);

    dialogIndexing->show();
}

void MainWindow::showMetadataDialog(QList<Image *> imgs, QList<double> diffs)
{
    dialogViewMetadata->setMetadata(imgs, diffs, base);

    if (dialogViewMetadata->isHidden() && (geoViewMetadata != QRect(0, 0, 0, 0)))
        dialogViewMetadata->setGeometry(geoViewMetadata);

    dialogViewMetadata->show();
}

void MainWindow::viewImage(QList<Image *> imgs, QList<double> diffs)
{
    if (dialogViewImage->isHidden() && (geoViewImage != QRect(0, 0, 0, 0)))
        dialogViewImage->setGeometry(geoViewImage);

    dialogViewImage->setImages(imgs, diffs);

    dialogViewImage->show();
}

void MainWindow::captureScreen()
{
    if (activeSOMScene())
    {
        dialogCaptureScreen->addScreen(activeSOMScene());
        dialogCaptureScreen->show();
    }
}

void MainWindow::showPluginsDialog()
{
    dialogPlugins->addExtractors(extractors);
    dialogPlugins->show();
}

void MainWindow::import()
{
    if (som->isInitCodes())
    {
        int ret = QMessageBox::warning(this, "Warning",
                                       QString("When you add photos to the database, the database will no longer consistent with"
                                               "the saved file map and weight."
                                               "Do you want to import ?"),
                                       QMessageBox::Yes | QMessageBox::No,
                                       QMessageBox::Yes);

        if (ret == QMessageBox::No) return;
    }

    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Select one or more files to import"),
                                                      QDir::homePath(),
                                                      "Images (*.jpg *.jpeg *.png *.bmp tiff ico *.ppm *.pgm");

    if (files.isEmpty()) return;

    QProgressDialog progress("Import...", "Cancel", 0, files.size() + 3, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    int count = 0;
    QFileInfo info;
    QString filename, filemeta, path, pathmeta;
    QStringList fields;
    Image *img;
    Feature *feature;
    foreach (QString file, files)
    {
        progress.setLabelText( QString("Import and extract features for %1...").arg(file) );
        progress.setValue(++count);
        progress.show();

        // copier l'image a la base d'images
        info.setFile(file);
        filename = info.fileName();

        do
        {
            path = Util::getMetadataPathOfImage(base->getPathOfDB(), filename);

            if (QFile::exists(path))
                filename = QString("1%1").arg(filename);
        }
        while (QFile::exists(path));

        try
        {
            fields = filename.split(".");
            filemeta = Util::getFilenameMetadata(fields[0]);
            pathmeta = Util::getMetadataPathOfImage(base->getPathMetadata(), filemeta);
            img = new Image(base->getSizeOfDB(), filename, path, pathmeta);

            QFile::copy(file, path);
            // extract features
            QStringList codeds = base->getFeatureCodedList();
            foreach (QString coded, codeds)
            {
                foreach (ExtractorInterface *ext, extractors)
                {
                    if (ext->isMyDescriptor(coded))
                    {
                        coded = coded.right(coded.size() - coded.indexOf(",") - 1);

                        feature = ext->extract(img, coded);

                        img->addFeature(feature);
                    }
                }
            }
            // mettre img a base
            base->addImage(img);
        }
        catch (std::exception &ex)
        {
            // effacer l'image dans la base
            QFile::remove(path);

            QMessageBox::information(this, "Error",
                                     QString::fromStdString(ex.what()),
                                     QMessageBox::Ok);
        }
    }
    img = 0;
    feature = 0;

    // enregistrer des changements
    progress.setLabelText( QString("Save database...") );
    progress.setValue(++count);
    progress.show();

    try
    {
        base->saveMetaOfDatabase();
        base->saveMetaOfImages();
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

    // re-mettre a jour grid et glsomscene, som
    if (gridNormal != 0)
        delete gridNormal;

    gridNormal = new GridSOM(base);
    if (glNormalScene != 0)
    {
        glNormalScene->hide();
        delete glNormalScene;
    }
    glNormalScene = 0;
    viewNormalScene();

    if (gridSOM != 0)
    {
        delete gridSOM;
        gridSOM = 0;
    }
    if (glSOMScene != 0)
    {
        glSOMScene->hide();
        delete glSOMScene;
        glSOMScene = 0;
    }
    if (gridRearrange != 0)
    {
        delete gridRearrange;
        gridRearrange = 0;
    }
    if (glRearrangeScene != 0)
    {
        glRearrangeScene->hide();
        delete glRearrangeScene;
        glRearrangeScene = 0;
    }
    ui->actionSOM_4->setEnabled(false);
    ui->actionRearrangement->setEnabled(false);

    // som
    if (som != 0)
        delete som;

    som = new MapSOM(base);
    som->addExtractors(extractors);

    progress.setValue(++count);
}

void MainWindow::search()
{
    if ((som == 0) ||
        ((glSOMScene != 0) && (glSOMScene->isHidden())) ||
        ((glRearrangeScene != 0) && (glRearrangeScene->isHidden()))) return;

    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Choose an image for search"),
                                                    base->getPathOfDB(),
                                                    "Images (*.jpg *.jpeg *.png *.bmp tiff ico *.ppm *.pgm");

    if (!filename.isEmpty())
    {
        QFileInfo fileInfo(filename);

        Image *img = new Image(0, fileInfo.fileName(), fileInfo.filePath(), "");

        Feature *feature;
        QStringList codeds = base->getFeatureCodedList();
        foreach (QString coded, codeds)
        {
            foreach (ExtractorInterface *ext, extractors)
            {
                if (ext->isMyDescriptor(coded))
                {
                    coded = coded.right(coded.size() - coded.indexOf(",") - 1);

                    feature = ext->extract(img, coded);

                    img->addFeature(feature);
                }
            }
        }
        feature = 0;

        QPoint point = som->search(img);

        if (glSOMScene != 0)
        {
            glSOMScene->search(point);
        }

        if (glRearrangeScene != 0)
        {
            glRearrangeScene->search(point);
        }

        delete img;
    }
}

void MainWindow::deleteImage(Image *img)
{
    // Normal
    if (glNormalScene != 0)
        glNormalScene->removeImageAt(img);

    // SOM
    if (glSOMScene != 0)
        glSOMScene->removeImageAt(img);

    // Rearrangement
    if (glRearrangeScene != 0)
        glRearrangeScene->removeImageAt(img);

    // xoa image trong BaseImage
    base->removeImage(img);

    som->setBaseImage(base);

    som->save();
}

void MainWindow::saveMap()
{
    if (som == 0) return;

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
}

void MainWindow::saveMapAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Choose a filename for save the map file"),
                                                Util::getFileMapUntitle(),
                                                tr("Map File (*.map)"));
    if (!fileName.isEmpty())
    {
        try
        {
            if (QFile::exists(fileName))
                QFile::remove(fileName);
            QFile::copy(Util::getFileMapMeta(base->getPathMetadata()), fileName);
        }
        catch (std::exception &ex)
        {
            QMessageBox::information(this, "Error",
                                     QString::fromStdString(ex.what()),
                                     QMessageBox::Ok);
        }
    }
}

void MainWindow::loadMap()
{
    if (som->isInitCodes())
    {
        int ret = QMessageBox::warning(this, "Warning",
                                       QString("When you load a map file, the calculed data will lost"
                                               "You should save before load other map file."
                                               "Do you want to load ?"),
                                       QMessageBox::Yes | QMessageBox::No,
                                       QMessageBox::Yes);

        if (ret == QMessageBox::No) return;
    }

    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Choose a map file"),
                                                    QDir::homePath(),
                                                    tr("Map file (*.map)"));

    if (!filename.isEmpty())
    {
        try
        {
            som->load(filename);
        }
        catch (std::exception &ex)
        {
            QMessageBox::information(this, "Error",
                                     QString::fromStdString(ex.what()),
                                     QMessageBox::Ok);
        }

        // mettre a jour l'interface
        updateGridSOMAndRearrange();
    }
}

void MainWindow::closeViewImage(QRect geo)
{
    geoViewImage = geo;
}

void MainWindow::closeViewMetadata(QRect geo)
{
    geoViewMetadata = geo;
}

void MainWindow::closeExtractFeature(QRect geo)
{
    geoExtractFeature = geo;
}

void MainWindow::closeIndexing(QRect geo)
{
    geoIndexing = geo;
}

void MainWindow::visual(GridSOM *grid)
{
    gridSOM = grid;

    if (glSOMScene != 0)
    {
        glSOMScene->hide();
        delete glSOMScene;
    }
    glSOMScene = 0;
    viewSOMScene();

    ui->actionSOM_4->setEnabled(true);
}

void MainWindow::rearrange(GridSOM *grid)
{
    gridRearrange = grid;

    if (glRearrangeScene != 0)
    {
        glRearrangeScene->hide();
        delete glRearrangeScene;
    }
    glRearrangeScene = 0;
    viewRearrangeScene();

    ui->actionRearrangement->setEnabled(true);
}

void MainWindow::updateMenus()
{
    if (activeSOMScene())
    {
        bool animable = activeSOMScene()->isAnimatable();
        bool changed = activeSOMScene()->isChangedPosition();

        ui->actionAnimation->setChecked(animable);
        ui->actionOriginal_Position->setEnabled(changed);
    }
}

void MainWindow::deleteExtractor(QList<ExtractorInterface *> extractors)
{
    this->extractors = extractors;

    if (base != 0)
    {
        ui->actionImport_2->setEnabled(base->isImportable(extractors));
        ui->actionSearch->setEnabled(base->isImportable(extractors));
    }
}

void MainWindow::addNewExtractor(QString newPlugin)
{
    QPluginLoader loader(newPlugin);
    QObject *plugin = loader.instance();
    if (ExtractorInterface *interface = qobject_cast<ExtractorInterface*>(plugin))
        extractors << interface;

    if (som != 0)
    {
        som->addExtractors(extractors);
    }
    dialogPlugins->addExtractors(extractors);
    if (base != 0)
    {
        ui->actionImport_2->setEnabled(base->isImportable(extractors));
        ui->actionSearch->setEnabled(base->isImportable(extractors));
    }
}

// PRIVATE

void MainWindow::createMenu()
{
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openDatabase()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionAnimation, SIGNAL(triggered(bool)), this, SLOT(onAnimation(bool)));
    connect(ui->actionOriginal_Position, SIGNAL(triggered()), this, SLOT(viewOriginPosition()));
    connect(ui->actionFeatures_Extract, SIGNAL(triggered()), this, SLOT(showFeaturesExtractDialog()));
    connect(ui->actionFullscreen, SIGNAL(triggered()), this, SLOT(showSOMSceneOnFullScreen()));
    connect(ui->actionInformation, SIGNAL(triggered()), this, SLOT(information()));
    connect(ui->actionImport_2, SIGNAL(triggered()), this, SLOT(import()));
    connect(ui->actionIndexing, SIGNAL(triggered()), this, SLOT(showIndexingDialog()));

    connect(ui->actionNormal, SIGNAL(triggered()), this, SLOT(viewNormal()));
    connect(ui->actionSOM_4, SIGNAL(triggered()), this, SLOT(viewSOM()));
    connect(ui->actionRearrangement, SIGNAL(triggered()), this, SLOT(viewRearrange()));

    connect(ui->actionClose, SIGNAL(triggered()), workspace, SLOT(closeActiveWindow()));
    connect(ui->actionClose_All, SIGNAL(triggered()), workspace, SLOT(closeAllWindows()));
    connect(ui->actionTile, SIGNAL(triggered()), workspace, SLOT(tile()));
    connect(ui->actionCascade, SIGNAL(triggered()), workspace, SLOT(cascade()));

    connect(ui->actionCapture_screen, SIGNAL(triggered()), this, SLOT(captureScreen()));
    connect(ui->actionPlugins, SIGNAL(triggered()), this, SLOT(showPluginsDialog()));

    connect(ui->actionSave_map, SIGNAL(triggered()), this, SLOT(saveMapAs()));
    connect(ui->actionSave_map_2, SIGNAL(triggered()), this, SLOT(saveMap()));
    connect(ui->actionLoad_map, SIGNAL(triggered()), this, SLOT(loadMap()));
    connect(ui->actionSearch, SIGNAL(triggered()), this, SLOT(search()));
}

void MainWindow::enableActions()
{
    ui->actionFullscreen->setEnabled(true);
    ui->actionAnimation->setEnabled(true);
    ui->actionInformation->setEnabled(true);
    ui->actionFeatures_Extract->setEnabled(true);
    ui->actionImport->setEnabled(true);
    ui->actionIndexing->setEnabled(true);
    ui->actionCapture_screen->setEnabled(true);
    ui->actionImport_2->setEnabled(base->isImportable(extractors));
    ui->actionSearch->setEnabled(base->isImportable(extractors));
}

void MainWindow::createDialogs()
{
    dialogExtractFeature = new ExtraireFeaturesDialog(this, ui->statusBar);
    dialogExtractFeature->addExtractors(extractors);
    connect(dialogExtractFeature, SIGNAL(close(QRect)), this, SLOT(closeExtractFeature(QRect)));

    dialogViewImage = new ViewImageDialog(this);
    connect(dialogViewImage, SIGNAL(close(QRect)), this, SLOT(closeViewImage(QRect)));

    dialogViewMetadata = new ViewMetadataDialog(this);
    connect(dialogViewMetadata, SIGNAL(close(QRect)), this, SLOT(closeViewMetadata(QRect)));

    dialogIndexing = new IndexationDialog(this);
    dialogIndexing->addExtractors(extractors);
    connect(dialogIndexing, SIGNAL(close(QRect)), this, SLOT(closeIndexing(QRect)));
    connect(dialogIndexing, SIGNAL(finishVisual(GridSOM*)), this, SLOT(visual(GridSOM*)));
    connect(dialogIndexing, SIGNAL(finishRearrange(GridSOM*)), this, SLOT(rearrange(GridSOM*)));
    connect(dialogIndexing, SIGNAL(saveMap(bool)), ui->actionSave_map, SLOT(setEnabled(bool)));

    dialogCaptureScreen = new CaptureScreenDialog(this);

    dialogPlugins = new PluginsDialog(this);
    connect(dialogPlugins, SIGNAL(deleteExtractor(QList<ExtractorInterface*>)), this, SLOT(deleteExtractor(QList<ExtractorInterface*>)));
    connect(dialogPlugins, SIGNAL(addExtractor(QString)), this, SLOT(addNewExtractor(QString)));

    geoViewImage = QRect(0, 0, 0, 0);
    geoViewMetadata = QRect(0, 0, 0, 0);
    geoExtractFeature = QRect(0, 0, 0, 0);
    geoIndexing = QRect(0, 0, 0, 0);
}

void MainWindow::loadPlugins()
{
    foreach (QObject *obj, QPluginLoader::staticInstances())
    {
        if (ExtractorInterface *interface = qobject_cast<ExtractorInterface*>(obj))
            extractors << interface;
    }

    QDir pluginsDir(QApplication::applicationDirPath());

    if (!pluginsDir.cd("plugins"))
        return;

    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (ExtractorInterface *interface = qobject_cast<ExtractorInterface*>(plugin))
            extractors << interface;
    }
}

void MainWindow::closeAllDialogs()
{
    dialogExtractFeature->hide();
    dialogViewMetadata->hide();
    dialogViewImage->hide();
    dialogIndexing->hide();
    dialogCaptureScreen->hide();
    dialogPlugins->hide();
}

void MainWindow::updateGridSOMAndRearrange()
{
    if (som->isHaveGridSOM())
    {
        visual(som->getGridSOM());
        ui->actionSave_map->setEnabled(true);
    }

    if (som->isHaveGridRearrange())
    {
        rearrange(som->getGridRearrange());
        ui->actionSave_map->setEnabled(true);
    }
}

void MainWindow::viewNormalScene()
{
    if (glNormalScene != 0)
    {
        glNormalScene->show();
        return;
    }

    glNormalScene = new GLSOMScene(gridNormal, som, this);
    connect(glNormalScene, SIGNAL(changePosition(bool)), ui->actionOriginal_Position, SLOT(setEnabled(bool)));
    connect(glNormalScene, SIGNAL(viewMetadata(QList<Image*>,QList<double>)), this, SLOT(showMetadataDialog(QList<Image*>,QList<double>)));
    connect(glNormalScene, SIGNAL(viewImage(QList<Image*>,QList<double>)), this, SLOT(viewImage(QList<Image*>,QList<double>)));
    connect(glNormalScene, SIGNAL(deleteImage(Image*)), this, SLOT(deleteImage(Image*)));

    workspace->addWindow(glNormalScene);
    glNormalScene->show();
}

void MainWindow::viewSOMScene()
{
    if (glSOMScene != 0)
    {
        glSOMScene->show();
        return;
    }

    glSOMScene = new GLSOMScene(gridSOM, som, this);
    connect(glSOMScene, SIGNAL(changePosition(bool)), ui->actionOriginal_Position, SLOT(setEnabled(bool)));
    connect(glSOMScene, SIGNAL(viewMetadata(QList<Image*>,QList<double>)), this, SLOT(showMetadataDialog(QList<Image*>,QList<double>)));
    connect(glSOMScene, SIGNAL(viewImage(QList<Image*>,QList<double>)), this, SLOT(viewImage(QList<Image*>,QList<double>)));
    connect(glSOMScene, SIGNAL(changed(bool)), ui->actionSave_map_2, SLOT(setEnabled(bool)));
    connect(glSOMScene, SIGNAL(deleteImage(Image*)), this, SLOT(deleteImage(Image*)));

    workspace->addWindow(glSOMScene);
    glSOMScene->show();
}

void MainWindow::viewRearrangeScene()
{
    if (glRearrangeScene != 0)
    {
        glRearrangeScene->show();
        return;
    }

    glRearrangeScene = new GLSOMScene(gridRearrange, som, this);
    connect(glRearrangeScene, SIGNAL(changePosition(bool)), ui->actionOriginal_Position, SLOT(setEnabled(bool)));
    connect(glRearrangeScene, SIGNAL(viewMetadata(QList<Image*>,QList<double>)), this, SLOT(showMetadataDialog(QList<Image*>,QList<double>)));
    connect(glRearrangeScene, SIGNAL(viewImage(QList<Image*>,QList<double>)), this, SLOT(viewImage(QList<Image*>,QList<double>)));
    connect(glRearrangeScene, SIGNAL(changed(bool)), ui->actionSave_map_2, SLOT(setEnabled(bool)));
    connect(glRearrangeScene, SIGNAL(deleteImage(Image*)), this, SLOT(deleteImage(Image*)));

    workspace->addWindow(glRearrangeScene);
    glRearrangeScene->show();
}

GLSOMScene *MainWindow::activeSOMScene()
{
    return qobject_cast<GLSOMScene*>(workspace->activeWindow());
}
