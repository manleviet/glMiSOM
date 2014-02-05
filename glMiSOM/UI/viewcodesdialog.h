//
//
// viewcodesdialog.h
//
// LE Viet Man
// 22/09/2011
//
//

#ifndef VIEWCODESDIALOG_H
#define VIEWCODESDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include "SOM/mapsom.h"
#include "UI/codedialog.h"

namespace Ui {
    class ViewCodesDialog;
}

class ViewCodesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewCodesDialog(QWidget *parent = 0);
    ~ViewCodesDialog();

    void addCodes(MapSOM *som);

private slots:
    void viewCode();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::ViewCodesDialog *ui;

    MapSOM *som;
    CodeDialog *dialogCode;

    void createUI();
};

#endif // VIEWCODESDIALOG_H
