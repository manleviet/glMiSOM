//
//
// mainwindow.h
//
// LE Viet Man
// 28/05/2011
//
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWorkspace>
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QErrorMessage>
#include <QMessageBox>
#include <QPluginLoader>
#include <exception>
#include "Scene/glsomscene.h"
#include "Core/baseimage.h"
#include "Core/gridsom.h"
#include "UI/extrairefeaturesdialog.h"
#include "UI/viewmetadatadialog.h"
#include "UI/viewimagedialog.h"
#include "UI/indexationdialog.h"
#include "UI/capturescreendialog.h"
#include "UI/pluginsdialog.h"
#include "SOM/mapsom.h"
#include "Extractor/extractorinterface.h"
#include "Extractor/extractorwidgetinterface.h"

namespace Ui {
    class MainWindow;
}

class CaptureScreenDialog;
class GLSOMScene;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void addWindowToWorkspace(GLSOMScene *scene);

signals:
    void keyPress(GLSOMScene *scene, QKeyEvent *event);

protected:
    void keyPressEvent(QKeyEvent *);
    void closeEvent(QCloseEvent *);

private slots:
    void openDatabase();
    void about();
    void information();
    void viewNormal();
    void viewSOM();
    void viewRearrange();
    void viewOriginPosition();
    void onAnimation(bool);
    void showSOMSceneOnFullScreen();
    void showFeaturesExtractDialog();
    void showIndexingDialog();
    void showMetadataDialog(QList<Image*> imgs, QList<double> diffs);
    void viewImage(QList<Image*> imgs, QList<double> diffs);
    void captureScreen();
    void showPluginsDialog();
    void import();
    void search();
    void deleteImage(Image *img);
    void saveMap();
    void saveMapAs();
    void loadMap();

    void closeViewImage(QRect geo);
    void closeViewMetadata(QRect geo);
    void closeExtractFeature(QRect geo);
    void closeIndexing(QRect geo);
    void visual(GridSOM *grid);
    void rearrange(GridSOM *grid);

    void updateMenus();

    void deleteExtractor(QList<ExtractorInterface*> extractors);
    void addNewExtractor(QString newPlugin);

private:
    Ui::MainWindow *ui;
    QWorkspace *workspace;

    BaseImage *base;
    MapSOM *som;

    GLSOMScene *glNormalScene;
    GridSOM *gridNormal;

    GLSOMScene *glSOMScene;
    GridSOM *gridSOM;

    GLSOMScene *glRearrangeScene;
    GridSOM *gridRearrange;

    // extractor
    QList<ExtractorInterface*> extractors;

    // dialogs
    ExtraireFeaturesDialog *dialogExtractFeature;
    ViewMetadataDialog *dialogViewMetadata;
    ViewImageDialog *dialogViewImage;
    IndexationDialog *dialogIndexing;
    CaptureScreenDialog *dialogCaptureScreen;
    PluginsDialog *dialogPlugins;

    // geometry des dialogs
    QRect geoViewImage;
    QRect geoViewMetadata;
    QRect geoExtractFeature;
    QRect geoIndexing;

    void createMenu();
    void enableActions();
    void createDialogs();
    void loadPlugins();

    void closeAllDialogs();

    void updateGridSOMAndRearrange();
    void viewNormalScene();
    void viewSOMScene();
    void viewRearrangeScene();

    GLSOMScene *activeSOMScene();
};

#endif // MAINWINDOW_H
