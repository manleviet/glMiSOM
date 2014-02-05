//
//
// indexationdialog.h
//
// LE Viet Man
// 27/08/2011
//
//

#ifndef INDEXATIONDIALOG_H
#define INDEXATIONDIALOG_H

#include <QMainWindow>
#include <QDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QFileDialog>
#include "SOM/mapsom.h"
#include "UI/weightdelegate.h"
#include "UI/viewcodesdialog.h"
#include "Extractor/extractorinterface.h"

namespace Ui {
    class IndexationDialog;
}

class IndexationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IndexationDialog(QMainWindow *main, QWidget *parent = 0);
    ~IndexationDialog();

    void addExtractors(QList<ExtractorInterface*> exts);
    void setMapSOM(MapSOM *mapSOM);

signals:
    void close(QRect geo);
    void finishVisual(GridSOM *grid);
    void finishRearrange(GridSOM *grid);
    void saveMap(bool enable);

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void on_btnDefault_clicked();
    void on_btnCancel_clicked();

    void viewCodes();
    void chooseFeature();
    void init();
    void saveWeight();
    void loadWeight();
    void ordering();
    void converge();
    void visual();
    void rearrange();

private:
    Ui::IndexationDialog *ui;
    QMainWindow *mainWindow;

    MapSOM *som;
    BaseImage *base;

    GridSOM *gridSOM;
    GridSOM *gridRearrange;

    ViewCodesDialog *dialogViewCodes;

    FeaturesChosenList *createFeaturesChosenList();

    void setValuesFromSOM();
    void updateStatusOfGroups();
    void addItemsToListDescriptors();

    bool isHaveError();
    int calTotalOfWeights();

    void printGridSOM(GridSOM *grid);
    void printGridSOMtoFile(GridSOM *grid);
};

#endif // INDEXATIONDIALOG_H
