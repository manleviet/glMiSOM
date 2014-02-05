/********************************************************************************
** Form generated from reading UI file 'viewmetadatadialog.ui'
**
** Created: Sat Oct 15 11:19:11 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWMETADATADIALOG_H
#define UI_VIEWMETADATADIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ViewMetadataDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lblDescriptor;
    QListWidget *lstDescriptors;
    QComboBox *cmbImage;
    QTextEdit *txtMetadata;

    void setupUi(QDialog *ViewMetadataDialog)
    {
        if (ViewMetadataDialog->objectName().isEmpty())
            ViewMetadataDialog->setObjectName(QString::fromUtf8("ViewMetadataDialog"));
        ViewMetadataDialog->resize(457, 457);
        verticalLayout = new QVBoxLayout(ViewMetadataDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lblDescriptor = new QLabel(ViewMetadataDialog);
        lblDescriptor->setObjectName(QString::fromUtf8("lblDescriptor"));

        verticalLayout->addWidget(lblDescriptor);

        lstDescriptors = new QListWidget(ViewMetadataDialog);
        lstDescriptors->setObjectName(QString::fromUtf8("lstDescriptors"));
        lstDescriptors->setMinimumSize(QSize(0, 100));
        lstDescriptors->setMaximumSize(QSize(16777215, 150));

        verticalLayout->addWidget(lstDescriptors);

        cmbImage = new QComboBox(ViewMetadataDialog);
        cmbImage->setObjectName(QString::fromUtf8("cmbImage"));

        verticalLayout->addWidget(cmbImage);

        txtMetadata = new QTextEdit(ViewMetadataDialog);
        txtMetadata->setObjectName(QString::fromUtf8("txtMetadata"));

        verticalLayout->addWidget(txtMetadata);


        retranslateUi(ViewMetadataDialog);

        QMetaObject::connectSlotsByName(ViewMetadataDialog);
    } // setupUi

    void retranslateUi(QDialog *ViewMetadataDialog)
    {
        ViewMetadataDialog->setWindowTitle(QApplication::translate("ViewMetadataDialog", "View Metadata", 0, QApplication::UnicodeUTF8));
        lblDescriptor->setText(QApplication::translate("ViewMetadataDialog", "List of descriptors :", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ViewMetadataDialog: public Ui_ViewMetadataDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWMETADATADIALOG_H
