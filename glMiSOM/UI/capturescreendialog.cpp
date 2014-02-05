//
//
// capturescreendialog.h
//
// LE Viet Man
// 05/09/2011
//
//

#include "capturescreendialog.h"
#include "ui_capturescreendialog.h"

CaptureScreenDialog::CaptureScreenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CaptureScreenDialog)
{
    ui->setupUi(this);
    screen = 0;
}

CaptureScreenDialog::~CaptureScreenDialog()
{
    delete ui;
    screen = 0;
}

void CaptureScreenDialog::addScreen(GLSOMScene *screen)
{
    this->screen = screen;

    ui->spiWidth->setValue(screen->width());
    ui->spiHeight->setValue(screen->height());
}

void CaptureScreenDialog::on_btnCancel_clicked()
{
    hide();
}

void CaptureScreenDialog::on_btnCapture_clicked()
{
    if (screen == 0)
    {
        hide();
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Choose a filename for save the screen"),
                                                Util::getFileImageUntitle(),
                                                tr("Images (*.png *.xpm *.jpg)"));
    if (!fileName.isEmpty())
    {
        QPixmap pixmap;

        pixmap = screen->renderPixmap(ui->spiWidth->value(), ui->spiHeight->value());

        pixmap.save(fileName);
    }

    hide();
}
