//
//
// weightdelegate.h
//
// LE Viet Man
// 04/09/2011
//
//

#ifndef WEIGHTDELEGATE_H
#define WEIGHTDELEGATE_H

#include <QItemDelegate>
#include <QDoubleSpinBox>

class WeightDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit WeightDelegate(int weightCol, QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private slots:
    void commitAndCloseEditor();

private:
    int weightCol;

};

#endif // WEIGHTDELEGATE_H
