//
//
// codedialog.h
//
// LE Viet Man
// 22/09/2011
//
//

#include "codedialog.h"
#include "ui_codedialog.h"

CodeDialog::CodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CodeDialog)
{
    ui->setupUi(this);
}

CodeDialog::~CodeDialog()
{
    delete ui;
}

void CodeDialog::addCode(int index, QString code)
{
    setWindowTitle(QString("View Code - id : %1").arg(index));
    ui->txtCode->setText(code);
}
