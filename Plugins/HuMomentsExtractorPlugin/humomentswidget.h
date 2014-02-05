//
//
// humomentswidget.h
//
// LE Viet Man
// 03/08/2011
//
//

#ifndef HUMOMENTSWIDGET_H
#define HUMOMENTSWIDGET_H

#include "Extractor/extractorwidgetinterface.h"
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QMessageBox>

class HuMomentsWidget : public ExtractorWidgetInterface
{
    Q_OBJECT
public:
    HuMomentsWidget(QWidget *parent = 0);
    ~HuMomentsWidget();

    void resetDefault();
    QStringList getParams();
    bool isHaveError();

    bool isGlobalChecked();
    bool isLocalChecked();

private slots:
    void computeQuantity();

private:
    QCheckBox *chkGlobal, *chkLocal;
    QLabel *lblGreyLevel, *lblQuantity;
    QSpinBox *spiGreyLevel;

    void createUI();

    QString getParam(bool local, int greyLevel);
};

#endif // HUMOMENTSWIDGET_H
