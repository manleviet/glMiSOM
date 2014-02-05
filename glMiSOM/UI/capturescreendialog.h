//
//
// capturescreendialog.h
//
// LE Viet Man
// 05/09/2011
//
//

#ifndef CAPTURESCREENDIALOG_H
#define CAPTURESCREENDIALOG_H

#include <QDialog>
#include "Scene/glsomscene.h"

namespace Ui {
    class CaptureScreenDialog;
}

class GLSOMScene;

class CaptureScreenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CaptureScreenDialog(QWidget *parent = 0);
    ~CaptureScreenDialog();

    void addScreen(GLSOMScene *screen);

private slots:
    void on_btnCancel_clicked();

    void on_btnCapture_clicked();

private:
    Ui::CaptureScreenDialog *ui;
    GLSOMScene *screen;
};

#endif // CAPTURESCREENDIALOG_H
