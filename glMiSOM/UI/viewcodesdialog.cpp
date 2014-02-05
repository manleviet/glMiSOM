//
//
// viewcodesdialog.h
//
// LE Viet Man
// 22/09/2011
//
//

#include "viewcodesdialog.h"
#include "ui_viewcodesdialog.h"

ViewCodesDialog::ViewCodesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewCodesDialog)
{
    ui->setupUi(this);

    dialogCode = new CodeDialog(this);
}

ViewCodesDialog::~ViewCodesDialog()
{
    delete ui;
    som = 0;
    delete dialogCode;
}

void ViewCodesDialog::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    dialogCode->hide();
}

void ViewCodesDialog::addCodes(MapSOM *som)
{
    this->som = som;

    createUI();
}

void ViewCodesDialog::viewCode()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    QString tooltip = button->toolTip();

    QStringList fields = tooltip.split(" ");
    int index = fields[1].toInt();

    EntrySOM *entry = som->getCode(index);

    int num = som->getNumFeaChoosen();

    QString code = "";
    for (int i = 0; i < num; i++)
    {
        code += QString("%1; ").arg(entry->getFeature(i)->getFeature());
    }
    code.remove(code.size() - 2, 2);

    dialogCode->addCode(index, code);
    dialogCode->show();
}

void ViewCodesDialog::createUI()
{
    int xdim = som->getXdim();
    int ydim = som->getYdim();

    QGridLayout *layout = new QGridLayout(this);
    QPushButton *button;

    for (int i = 0; i < xdim; i++)
    {
        for (int j = 0; j < ydim; j++)
        {
            button = new QPushButton( QString("<%1, %2>").arg(i).arg(j) , this );
            button->setToolTip(QString("Code %1").arg(i * ydim + j));
            connect(button, SIGNAL(clicked()), this, SLOT(viewCode()));

            layout->addWidget(button, i, j, 1, 1);
        }
    }

    this->setLayout(layout);
}
