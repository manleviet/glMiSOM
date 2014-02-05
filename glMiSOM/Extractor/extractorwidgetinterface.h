//
//
// extractorwidgetinterface.h
//
// Un interface pour tous les interfaces de l'extracteur des descripteurs
//
// LE Viet Man
// 02/09/2011
//
//

#ifndef EXTRACTORWIDGETINTERFACE_H
#define EXTRACTORWIDGETINTERFACE_H

#include <QGroupBox>

class ExtractorWidgetInterface : public QGroupBox
{
    Q_OBJECT
public:
    ExtractorWidgetInterface(QWidget *parent = 0) : QGroupBox(parent) {}
    virtual ~ExtractorWidgetInterface() {}

    virtual void resetDefault() = 0;
    virtual QStringList getParams() = 0;
    virtual bool isHaveError() = 0;

    virtual bool isGlobalChecked() = 0;
    virtual bool isLocalChecked() = 0;

private slots:
    virtual void computeQuantity() = 0;
};

#endif // EXTRACTORWIDGETINTERFACE_H
