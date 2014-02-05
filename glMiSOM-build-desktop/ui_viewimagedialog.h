/********************************************************************************
** Form generated from reading UI file 'viewimagedialog.ui'
**
** Created: Sat Oct 15 11:19:11 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWIMAGEDIALOG_H
#define UI_VIEWIMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ViewImageDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *lblImage;

    void setupUi(QDialog *ViewImageDialog)
    {
        if (ViewImageDialog->objectName().isEmpty())
            ViewImageDialog->setObjectName(QString::fromUtf8("ViewImageDialog"));
        ViewImageDialog->resize(400, 300);
        gridLayout = new QGridLayout(ViewImageDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lblImage = new QLabel(ViewImageDialog);
        lblImage->setObjectName(QString::fromUtf8("lblImage"));

        gridLayout->addWidget(lblImage, 0, 0, 1, 1);


        retranslateUi(ViewImageDialog);

        QMetaObject::connectSlotsByName(ViewImageDialog);
    } // setupUi

    void retranslateUi(QDialog *ViewImageDialog)
    {
        ViewImageDialog->setWindowTitle(QApplication::translate("ViewImageDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        lblImage->setText(QApplication::translate("ViewImageDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ViewImageDialog: public Ui_ViewImageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWIMAGEDIALOG_H
