//
//
// viewimagedialog.h
//
// LE Viet Man
// 07/07/2011
//
//

#ifndef VIEWIMAGEDIALOG_H
#define VIEWIMAGEDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "Core/image.h"

namespace Ui {
    class ViewImageDialog;
}

class ViewImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewImageDialog(QWidget *parent = 0);
    ~ViewImageDialog();

    void setImages(QList<Image*> imgs, QList<double> diffs);

signals:
    void close(QRect geo);

protected:
    void closeEvent(QCloseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    Ui::ViewImageDialog *ui;
    QPoint lastPos;

    int curr; // current index
    QList<Image*> imgs;
    QList<double> diffs;

    void paint();
    void setTitle(const QString &name, double diff, int curr, int size);
};

#endif // VIEWIMAGEDIALOG_H
