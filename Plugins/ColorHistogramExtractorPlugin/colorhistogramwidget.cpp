//
//
// colorhistogramwidget.cpp
//
// Implementation de la classe colorhistogramwidget.h
//
// LE Viet Man
// 03/08/2011
//
//

#include "colorhistogramwidget.h"

ColorHistogramWidget::ColorHistogramWidget(QWidget *parent)
{
    Q_UNUSED(parent)

    setTitle(QString("Color Histogram"));
    setFlat(false);
    setCheckable(true);
    setChecked(false);

    createUI();

    computeQuantity();
}

ColorHistogramWidget::~ColorHistogramWidget()
{
    delete lblQuantity;
    delete lblBinNumber;
    delete chkGlobal;
    delete chkLocal;
    delete spiBinNumber;
}

void ColorHistogramWidget::resetDefault()
{
    setChecked(false);
    chkGlobal->setChecked(false);
    chkLocal->setChecked(true);
    spiBinNumber->setValue(5);

    computeQuantity();
}

QStringList ColorHistogramWidget::getParams()
{
    QStringList list;
    if (chkGlobal->isChecked())
    {
        list << getParam(!chkGlobal->isChecked(), spiBinNumber->value());
    }
    if (chkLocal->isChecked())
    {
        list << getParam(chkLocal->isChecked(), spiBinNumber->value());
    }
    return list;
}

bool ColorHistogramWidget::isHaveError()
{
    if ((isChecked()) && (!chkGlobal->isChecked()) && (!chkLocal->isChecked()))
    {
        QMessageBox::information(this, tr("Error"), tr("You should choose local or global in Color Histogram."));

        return true;
    }
    return false;
}

bool ColorHistogramWidget::isGlobalChecked()
{
    return chkGlobal->isChecked();
}

bool ColorHistogramWidget::isLocalChecked()
{
    return chkLocal->isChecked();
}

void ColorHistogramWidget::computeQuantity()
{
    int global = 3 * spiBinNumber->value();
    int local = 5 * global;

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

void ColorHistogramWidget::createUI()
{
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    // quantity of features
    lblQuantity = new QLabel(this);
    QFont font;
    font.setItalic(true);
    lblQuantity->setText(QString("Quantity of features :"));
    lblQuantity->setFont(font);

    verticalLayout->addWidget(lblQuantity);

    // line 1 : Global or Local
    QHBoxLayout *horizontalLayout_1 = new QHBoxLayout();

    chkGlobal = new QCheckBox(this);
    chkGlobal->setText(QString("Global"));
    connect(chkGlobal, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    horizontalLayout_1->addWidget(chkGlobal);

    chkLocal = new QCheckBox(this);
    chkLocal->setText(QString("Local"));
    chkLocal->setChecked(true);
    connect(chkLocal, SIGNAL(stateChanged(int)), this, SLOT(computeQuantity()));

    horizontalLayout_1->addWidget(chkLocal);

    QSpacerItem *horizontalSpacer_1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_1->addItem(horizontalSpacer_1);

    verticalLayout->addLayout(horizontalLayout_1);

    // line 2 : Bin number
    QHBoxLayout *horizontalLayout_2 = new QHBoxLayout();
    lblBinNumber = new QLabel(this);
    lblBinNumber->setText(QString("Bin number :"));

    horizontalLayout_2->addWidget(lblBinNumber);

    spiBinNumber = new QSpinBox(this);
    spiBinNumber->setMinimum(1);
    spiBinNumber->setMaximum(256);
    spiBinNumber->setValue(5);
    connect(spiBinNumber, SIGNAL(valueChanged(int)), this, SLOT(computeQuantity()));

    horizontalLayout_2->addWidget(spiBinNumber);

    QSpacerItem *horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_2);

    verticalLayout->addLayout(horizontalLayout_2);
}

QString ColorHistogramWidget::getParam(bool local, int numBin)
{
    QString param = QString("%1,%2").arg(local?1:0).arg(numBin);
    return param;
}
