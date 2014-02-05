//
//
// viewmetadatadialog.h
//
// LE Viet Man
// 07/07/2011
//
//

#ifndef VIEWMETADATADIALOG_H
#define VIEWMETADATADIALOG_H

#include <QDialog>
#include <Core/baseimage.h>
#include "Core/image.h"

namespace Ui {
    class ViewMetadataDialog;
}

class ViewMetadataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewMetadataDialog(QWidget *parent = 0);
    ~ViewMetadataDialog();

    void setMetadata(QList<Image*> imgs, QList<double> diffs, BaseImage *b);

signals:
    void close(QRect geo);

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void on_lstDescriptors_currentRowChanged(int currentRow);
    void on_cmbImage_currentIndexChanged(int index);

private:
    Ui::ViewMetadataDialog *ui;
    int currentRow;

    int curr;
    QList<Image*> imgs;
    QList<double> diffs;
    BaseImage *base;

    void addItemsToListDescriptors();
    void changeContent();
};

#endif // VIEWMETADATADIALOG_H
