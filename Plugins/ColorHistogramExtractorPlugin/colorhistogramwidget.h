//
//
// colorhistogramwidget.h
//
// LE Viet Man
// 03/08/2011
//
//

#ifndef COLORHISTOGRAMWIDGET_H
#define COLORHISTOGRAMWIDGET_H

#include "Extractor/extractorwidgetinterface.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QMessageBox>

class ColorHistogramWidget : public ExtractorWidgetInterface
{
    Q_OBJECT
public:
    ColorHistogramWidget(QWidget *parent = 0);

    ~ColorHistogramWidget();

    void resetDefault();
    QStringList getParams();
    bool isHaveError();

    bool isGlobalChecked();
    bool isLocalChecked();

private slots:
    void computeQuantity();

private:
    QLabel *lblQuantity, *lblBinNumber;
    QCheckBox *chkGlobal, *chkLocal;
    QSpinBox *spiBinNumber;

    void createUI();

    QString getParam(bool local, int numBin);
};

#endif // COLORHISTOGRAMWIDGET_H
