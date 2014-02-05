//
//
// weightdelegate.h
//
// LE Viet Man
// 04/09/2011
//
//

#include "weightdelegate.h"

WeightDelegate::WeightDelegate(int weightCol, QObject *parent) :
    QItemDelegate(parent)
{
    this->weightCol = weightCol;
}

void WeightDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == weightCol)
    {
        float weight = index.model()->data(index).toFloat();

        QString text = QString("%1 %").arg(weight);

        QStyleOptionViewItem myOption = option;
        myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

        drawDisplay(painter, myOption, myOption.rect, text);
        drawFocus(painter, myOption, myOption.rect);
    }
    else
    {
        QItemDelegate::paint(painter, option, index);
    }
}

QWidget *WeightDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == weightCol)
    {
        QDoubleSpinBox *spinBox = new QDoubleSpinBox(parent);
        spinBox->setMaximum(100);
        connect(spinBox, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
        return spinBox;
    }
    else
    {
        return QItemDelegate::createEditor(parent, option, index);
    }
}

void WeightDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == weightCol)
    {
        float weight = index.model()->data(index).toFloat();
        QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(weight);
    }
    else
    {
        QItemDelegate::setEditorData(editor, index);
    }
}

void WeightDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() == weightCol)
    {
        QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(editor);
        float weight = spinBox->value();
        model->setData(index, weight);
    }
    else
    {
        QItemDelegate::setModelData(editor, model, index);
    }
}

void WeightDelegate::commitAndCloseEditor()
{
    QDoubleSpinBox *editor = qobject_cast<QDoubleSpinBox*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
