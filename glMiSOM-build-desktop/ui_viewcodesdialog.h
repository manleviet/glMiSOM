/********************************************************************************
** Form generated from reading UI file 'viewcodesdialog.ui'
**
** Created: Sat Oct 15 11:19:11 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWCODESDIALOG_H
#define UI_VIEWCODESDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ViewCodesDialog
{
public:

    void setupUi(QDialog *ViewCodesDialog)
    {
        if (ViewCodesDialog->objectName().isEmpty())
            ViewCodesDialog->setObjectName(QString::fromUtf8("ViewCodesDialog"));
        ViewCodesDialog->resize(400, 300);

        retranslateUi(ViewCodesDialog);

        QMetaObject::connectSlotsByName(ViewCodesDialog);
    } // setupUi

    void retranslateUi(QDialog *ViewCodesDialog)
    {
        ViewCodesDialog->setWindowTitle(QApplication::translate("ViewCodesDialog", "Grid of codes", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ViewCodesDialog: public Ui_ViewCodesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWCODESDIALOG_H
