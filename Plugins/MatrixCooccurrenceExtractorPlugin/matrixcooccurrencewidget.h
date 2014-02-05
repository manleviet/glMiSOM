//
//
// colorhistogramwidget.h
//
// LE Viet Man
// 03/08/2011
//
//

#ifndef MATRIXCOOCCURRENCEWIDGET_H
#define MATRIXCOOCCURRENCEWIDGET_H

#include "Extractor/extractorwidgetinterface.h"
#include "matrixcooccurrenceextractor.h"
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>

class MatrixCooccurrenceWidget : public ExtractorWidgetInterface
{
    Q_OBJECT
public:
    MatrixCooccurrenceWidget(QWidget *parent = 0);
    ~MatrixCooccurrenceWidget();

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
    QComboBox *cmbGreyLevel;
    QCheckBox *chk1, *chk2, *chk3, *chk4;
    QCheckBox *chkContrast, *chkEntropy;
    QCheckBox *chkDissimilarity, *chkMean;
    QCheckBox *chkHomogeneity, *chkVariance;
    QCheckBox *chkASM, *chkStd, *chkMaxProbabilite;
    QCheckBox *chkCorrelation, *chkEnergy;

    void createUI();

    QList<bool> getValuesDistances();
    QList<bool> getValuesDescriptors();

    QString convertToStrDes(QList<bool> list);

    QString getParam(bool local, QList<bool> distances, int greyLevel, QList<bool> descriptors);
};

#endif // MATRIXCOOCCURRENCEWIDGET_H
