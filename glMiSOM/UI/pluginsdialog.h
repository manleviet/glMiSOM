//
//
// pluginsdialog.h
//
// LE Viet Man
// 16/09/2011
//
//

#ifndef PLUGINSDIALOG_H
#define PLUGINSDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include "Extractor/extractorinterface.h"
#include "util.h"

namespace Ui {
    class PluginsDialog;
}

class PluginsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PluginsDialog(QWidget *parent = 0);
    ~PluginsDialog();

    void addExtractors(QList<ExtractorInterface*> extractors);

signals:
    void addExtractor(QString filename);
    void deleteExtractor(QList<ExtractorInterface*> extractors);

private slots:
    void on_btnCancel_clicked();
    void on_lstPlugins_currentRowChanged(int currentRow);
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();

private:
    Ui::PluginsDialog *ui;
    QList<ExtractorInterface*> extractors;

    void addItemsToListPlugins();
};

#endif // PLUGINSDIALOG_H
