//
//
// humomentswidget.cpp
//
// Implementation de la classe humomentswidget.h
//
// LE Viet Man
// 03/08/2011
//
//

#include "humomentswidget.h"

HuMomentsWidget::HuMomentsWidget(QWidget *parent)
{
    Q_UNUSED(parent)

    setTitle(QString("Hu Moments"));
    setCheckable(true);
    setChecked(false);

    createUI();

    computeQuantity();
}

HuMomentsWidget::~HuMomentsWidget()
{
    delete chkGlobal;
    delete chkLocal;
    delete lblGreyLevel;
    delete lblQuantity;
    delete spiGreyLevel;
}

void HuMomentsWidget::resetDefault()
{
    setChecked(false);
    chkGlobal->setChecked(false);
    chkLocal->setChecked(true);
    spiGreyLevel->setValue(64);

    computeQuantity();
}

QStringList HuMomentsWidget::getParams()
{
    QStringList list;
    if (chkGlobal->isChecked())
    {
        list << getParam(!chkGlobal->isChecked(), spiGreyLevel->value());
    }
    if (chkLocal->isChecked())
    {
        list << getParam(chkLocal->isChecked(), spiGreyLevel->value());
    }
    return list;
}

bool HuMomentsWidget::isHaveError()
{
    if ((isChecked()) && (!chkGlobal->isChecked()) && (!chkLocal->isChecked()))
    {
        QMessageBox::information(this, tr("Error"), tr("You should choose local or global in Hu Moments."));

        return true;
    }
    return false;
}

bool HuMomentsWidget::isGlobalChecked()
{
    return chkGlobal->isChecked();
}

bool HuMomentsWidget::isLocalChecked()
{
    return chkLocal->isChecked();
}

void HuMomentsWidget::computeQuantity()
{
    int global = 7;
    int local = global * 5;

    QString quantity = tr("Quantity of features : ");
    if (chkGlobal->isChecked())
    {
        quantity += tr("Global - %1     ").arg(global);
    }
    if (chkLocal->isChecked())
    {
        quantity += tr("Local - %1").arg(local);
    }

    lblQuantity->setText(quantity);
}

void HuMomentsWidget::createUI()
{
    QGridLayout *gridLayout = new QGridLayout(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QHBoxLayout *horizontalLayout = new QHBoxLayout();

    chkGlobal = new QCheckBox(this);
    chkGlobal->setText(QString("Global"));
    connect(chkGlobal, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    horizontalLayout->addWidget(chkGlobal);

    chkLocal = new QCheckBox(this);
    chkLocal->setText(QString("Local"));
    chkLocal->setChecked(true);
    connect(chkLocal, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    horizontalLayout->addWidget(chkLocal);

    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(spacer);

    verticalLayout->addLayout(horizontalLayout);

    QHBoxLayout *horizontalLayout1 = new QHBoxLayout();

    lblGreyLevel = new QLabel(this);
    lblGreyLevel->setText(QString("Grey Level :"));

    horizontalLayout1->addWidget(lblGreyLevel);

    spiGreyLevel = new QSpinBox(this);
    spiGreyLevel->setMinimum(1);
    spiGreyLevel->setMaximum(256);
    spiGreyLevel->setValue(64);

    horizontalLayout1->addWidget(spiGreyLevel);

    spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout1->addItem(spacer);

    verticalLayout->addLayout(horizontalLayout1);

    gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

    lblQuantity = new QLabel(this);
    QFont font;
    font.setItalic(true);
    lblQuantity->setFont(font);
    lblQuantity->setText(QString("Quantity of features :"));

    gridLayout->addWidget(lblQuantity, 0, 0, 1, 1);
}

QString HuMomentsWidget::getParam(bool local, int greyLevel)
{
    QString param = QString("%1,%2").arg(local?1:0).arg(greyLevel);
    return param;
}
