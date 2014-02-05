//
//
// codedialog.h
//
// LE Viet Man
// 22/09/2011
//
//

#ifndef CODEDIALOG_H
#define CODEDIALOG_H

#include <QDialog>

namespace Ui {
    class CodeDialog;
}

class CodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CodeDialog(QWidget *parent = 0);
    ~CodeDialog();

    void addCode(int index, QString code);

private:
    Ui::CodeDialog *ui;
};

#endif // CODEDIALOG_H
