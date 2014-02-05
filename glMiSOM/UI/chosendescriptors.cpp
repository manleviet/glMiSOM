//
//
// chosendescriptors.h
//
// LE Viet Man
// 27/08/2011
//
//

#include "chosendescriptors.h"

ChosenDescriptors::ChosenDescriptors(QWidget *parent) :
    QTableWidget(parent)
{
    setAlternatingRowColors(true);

    deleteAction = new QAction(QObject::tr("Delete"), this);
    deleteAction->setStatusTip(QObject::tr("Delete an item"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    menu = new QMenu(this);
    menu->addAction(deleteAction);
}

ChosenDescriptors::~ChosenDescriptors()
{
    //delete deleteAction;
    //delete menu;
}

void ChosenDescriptors::addExtractors(QList<ExtractorInterface *> extractors)
{
    this->extractors = extractors;
}

void ChosenDescriptors::setFeatures(QStringList feas, QStringList coded)
{
    this->features = feas;
    featuresCoded = coded;
}

void ChosenDescriptors::addItems(FeaturesChosenList *feaChoosenList)
{
    int index;
    double weight;
    for (int i = 0; i < feaChoosenList->getSize(); i++)
    {
        index = feaChoosenList->getIndex(i);
        weight = feaChoosenList->getWeight(i);

        addItem(features[index], weight * 100);
    }
}

void ChosenDescriptors::dropEvent(QDropEvent *event)
{
    QListWidget *source = qobject_cast<QListWidget*>(event->source());
    int index;
    QString coded;
    if (source)
    {
        index = source->currentIndex().row();

        coded = featuresCoded[index];

        if (!isHavePlugin(coded))
        {
            QMessageBox::information(this, tr("Caution"), tr("System don't have the plugin supported for this descriptor"));

            event->ignore();
            return;
        }

        addItem(features[index], 0);

        // mettre a jour les poids
        updateWeight();

        emit chooseFeature();
        event->accept();
    }
    source = 0;
}

void ChosenDescriptors::contextMenuEvent(QContextMenuEvent *event)
{
    menu->exec(event->globalPos());
}

void ChosenDescriptors::addItem(QString feature, double weight)
{
    QTableWidgetItem *item;
    int row = rowCount() + 1;
    setRowCount(row);

    item = new QTableWidgetItem(feature);
    setItem(row - 1, COL_FEATURE, item);

    item = new QTableWidgetItem( QString("%1").arg(weight) );
    item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    setItem(row - 1, COL_WEIGHT, item);
}

void ChosenDescriptors::updateWeight()
{
    int numRow = rowCount();
    float weight;
    QString fea;
    int total = computeTotalFeatures();

    for (int i = 0; i < numRow; i++)
    {
        fea = item(i, COL_FEATURE)->text();

        for (int j = 0; j < features.size(); j++)
        {
            if (fea == features[j])
            {
                weight = computeWeight(featuresCoded[j], total);

                item(i, COL_WEIGHT)->setText(QString("%1").arg(weight));
            }
        }
    }
}

long ChosenDescriptors::computeTotalFeatures()
{
    int numRow = rowCount();
    long total = 0;
    QString fea;
    for (int i = 0; i < numRow; i++)
    {
        fea = item(i, COL_FEATURE)->text();

        for (int j = 0; j < features.size(); j++)
        {
            if (fea == features[j])
            {
                foreach (ExtractorInterface *ext, extractors)
                {
                    if (ext->isMyDescriptor(featuresCoded[j]))
                        total += ext->computeSizeTexture(featuresCoded[j]);
                }
            }
        }
    }
    return total;
}

float ChosenDescriptors::computeWeight(QString des, long total)
{
    float weight = 0;
    foreach (ExtractorInterface *ext, extractors)
    {
        if (ext->isMyDescriptor(des))
            weight = (float)ext->computeSizeTexture(des) / total * 100;
    }
    return weight;
}

void ChosenDescriptors::removeAllItems()
{
    while (rowCount() > 0)
    {
        removeRow(0);
    }
}

void ChosenDescriptors::deleteItem()
{
    int index = currentIndex().row();
    removeRow(index);

    updateWeight();
}

bool ChosenDescriptors::isHavePlugin(QString coded)
{
    foreach (ExtractorInterface *ext, extractors)
    {
        if (ext->isMyDescriptor(coded))
            return true;
    }
    return false;
}
