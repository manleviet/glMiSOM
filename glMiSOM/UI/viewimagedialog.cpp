//
//
// viewimagedialog.h
//
// LE Viet Man
// 07/07/2011
//
//

#include "viewimagedialog.h"
#include "ui_viewimagedialog.h"

ViewImageDialog::ViewImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewImageDialog)
{
    ui->setupUi(this);
}

ViewImageDialog::~ViewImageDialog()
{
    delete ui;
}

void ViewImageDialog::closeEvent(QCloseEvent *e)
{
    Q_UNUSED(e);

    emit close(geometry());
}

void ViewImageDialog::mousePressEvent(QMouseEvent *e)
{
    if (imgs.size() == 1) return;

    if (e->buttons() & Qt::LeftButton)
    {
        setCursor(Qt::ClosedHandCursor);
        lastPos = e->pos();
    }
}

void ViewImageDialog::mouseReleaseEvent(QMouseEvent *e)
{
    if (imgs.size() == 1) return;

    if (e->button() & Qt::LeftButton) {
        if ((lastPos.x() - e->x()) < 0)
        {
            // changer curr
            curr--;
            if (curr == -1) curr = imgs.size() - 1;
        }
        else
        {
            // changer curr
            curr++;
            if (curr == imgs.size()) curr = 0;
        }

        setCursor(Qt::ArrowCursor);
        paint();
    }
}

void ViewImageDialog::setImages(QList<Image *> imgs, QList<double> diffs)
{
    curr = 0;
    this->imgs = imgs;
    this->diffs = diffs;

    paint();
}

void ViewImageDialog::paint()
{
    Image *img = imgs[curr];

    setTitle(img->getName(), diffs[curr], curr + 1, imgs.size());

    ui->lblImage->setBackgroundRole(QPalette::Base);

    QImage image;
    image.load(img->getPath());

    ui->lblImage->setPixmap(QPixmap::fromImage(image));
    ui->lblImage->adjustSize();
    adjustSize();
}

void ViewImageDialog::setTitle(const QString &name, double diff, int curr, int size)
{
    setWindowTitle(QString("View Image - %1 - %2 (%3 / %4 images)")
                   .arg(name)
                   .arg(diff)
                   .arg(curr)
                   .arg(size));
}
