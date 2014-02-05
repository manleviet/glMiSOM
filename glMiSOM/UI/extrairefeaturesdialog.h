//
//
// extrairefeaturesdialog.h
//
// LE Viet Man
// 01/07/2011
//
//

#ifndef EXTRAIREFEATURESDIALOG_H
#define EXTRAIREFEATURESDIALOG_H

#include <QMainWindow>
#include <QSplitter>
#include <QDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <Core/baseimage.h>
#include <Core/image.h>
#include <Core/feature.h>
#include "Extractor/extractorinterface.h"
#include <Extractor/extractorwidgetinterface.h>

namespace Ui {
    class ExtraireFeaturesDialog;
}

class ExtraireFeaturesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExtraireFeaturesDialog(QMainWindow *mainWindow, QWidget *parent = 0);
    ~ExtraireFeaturesDialog();

    void addBaseImage(BaseImage *base);
    void addExtractors(QList<ExtractorInterface*> extractors);

signals:
    void close(QRect geo);

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void on_cmdCancel_clicked();
    void on_cmdExtract_clicked();
    void on_cmdDefault_clicked();

private:
    Ui::ExtraireFeaturesDialog *ui;
    QMainWindow *mainWindow;

    BaseImage *base;

    QList<ExtractorInterface*> extractors;
    QStringList nameExtractors;

    bool isHaveError();

    int computeMaxOfProgress();

    void addItemsToListDescriptors();
    bool isAddedToUI(QString nameExtractor);
};

#endif // EXTRAIREFEATURESDIALOG_H
