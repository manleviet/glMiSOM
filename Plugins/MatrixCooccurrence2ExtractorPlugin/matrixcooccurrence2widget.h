//
//
// matrixcooccurren2widget.h
//
// LE Viet Man
// 12/09/2011
//
//

#ifndef MATRIXCOOCCURRENCE2WIDGET_H
#define MATRIXCOOCCURRENCE2WIDGET_H

#include "Extractor/extractorwidgetinterface.h"
#include "matrixcooccurrence2extractor.h"
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>

class MatrixCooccurrence2Widget : public ExtractorWidgetInterface
{
    Q_OBJECT
public:
    MatrixCooccurrence2Widget(QWidget *parent = 0);
    ~MatrixCooccurrence2Widget();

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

#endif // MATRIXCOOCCURRENCE2WIDGET_H
