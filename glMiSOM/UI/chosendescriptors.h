//
//
// chosendescriptors.h
//
// LE Viet Man
// 27/08/2011
//
//

#ifndef CHOSENDESCRIPTORS_H
#define CHOSENDESCRIPTORS_H

#include <QTableWidget>
#include <QDropEvent>
#include <QContextMenuEvent>
#include <QAction>
#include <QMenu>
#include <QListWidget>
#include "UI/indexationdialog.h"
#include "Core/baseimage.h"
#include "Extractor/extractorinterface.h"
#include "SOM/featureschosenlist.h"

#define COL_FEATURE 0
#define COL_WEIGHT 1

class ChosenDescriptors : public QTableWidget
{
    Q_OBJECT
public:
    explicit ChosenDescriptors(QWidget *parent = 0);
    ~ChosenDescriptors();

    void addExtractors(QList<ExtractorInterface*> extractors);
    void setFeatures(QStringList feas, QStringList coded);

    void addItems(FeaturesChosenList *feaChoosenList);

    bool isChoosenFeatures() { return rowCount() > 0; }

    void removeAllItems();

signals:
    void chooseFeature();

public slots:
    void deleteItem();

protected:
    void dropEvent(QDropEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

private:
    QMenu *menu;
    QAction *deleteAction;

    QStringList features;
    QStringList featuresCoded;

    QList<ExtractorInterface*> extractors;

    void addItem(QString feature, double weight);
    void updateWeight();
    long computeTotalFeatures();
    float computeWeight(QString des, long total);
    bool isHavePlugin(QString coded);
};

#endif // CHOSENDESCRIPTORS_H
