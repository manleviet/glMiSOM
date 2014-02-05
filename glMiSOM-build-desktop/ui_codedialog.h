/********************************************************************************
** Form generated from reading UI file 'codedialog.ui'
**
** Created: Sat Oct 15 11:19:11 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODEDIALOG_H
#define UI_CODEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_CodeDialog
{
public:
    QGridLayout *gridLayout;
    QTextEdit *txtCode;

    void setupUi(QDialog *CodeDialog)
    {
        if (CodeDialog->objectName().isEmpty())
            CodeDialog->setObjectName(QString::fromUtf8("CodeDialog"));
        CodeDialog->resize(400, 300);
        gridLayout = new QGridLayout(CodeDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        txtCode = new QTextEdit(CodeDialog);
        txtCode->setObjectName(QString::fromUtf8("txtCode"));
        txtCode->setReadOnly(true);

        gridLayout->addWidget(txtCode, 0, 0, 1, 1);


        retranslateUi(CodeDialog);

        QMetaObject::connectSlotsByName(CodeDialog);
    } // setupUi

    void retranslateUi(QDialog *CodeDialog)
    {
        CodeDialog->setWindowTitle(QApplication::translate("CodeDialog", "View Code", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CodeDialog: public Ui_CodeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODEDIALOG_H
