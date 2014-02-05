/********************************************************************************
** Form generated from reading UI file 'extrairefeaturesdialog.ui'
**
** Created: Sat Oct 15 11:19:11 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTRAIREFEATURESDIALOG_H
#define UI_EXTRAIREFEATURESDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExtraireFeaturesDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QLabel *lblTotal;
    QListWidget *lstDescriptors;
    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *cmdDefault;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cmdCancel;
    QPushButton *cmdExtract;

    void setupUi(QDialog *ExtraireFeaturesDialog)
    {
        if (ExtraireFeaturesDialog->objectName().isEmpty())
            ExtraireFeaturesDialog->setObjectName(QString::fromUtf8("ExtraireFeaturesDialog"));
        ExtraireFeaturesDialog->resize(457, 386);
        ExtraireFeaturesDialog->setModal(true);
        gridLayout = new QGridLayout(ExtraireFeaturesDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        lblTotal = new QLabel(ExtraireFeaturesDialog);
        lblTotal->setObjectName(QString::fromUtf8("lblTotal"));

        verticalLayout_7->addWidget(lblTotal);

        lstDescriptors = new QListWidget(ExtraireFeaturesDialog);
        lstDescriptors->setObjectName(QString::fromUtf8("lstDescriptors"));
        lstDescriptors->setMinimumSize(QSize(0, 100));
        lstDescriptors->setMaximumSize(QSize(16777215, 150));

        verticalLayout_7->addWidget(lstDescriptors);


        verticalLayout_8->addLayout(verticalLayout_7);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        scrollArea = new QScrollArea(ExtraireFeaturesDialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setAutoFillBackground(false);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 433, 196));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_6->addWidget(scrollArea);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        cmdDefault = new QPushButton(ExtraireFeaturesDialog);
        cmdDefault->setObjectName(QString::fromUtf8("cmdDefault"));

        horizontalLayout_4->addWidget(cmdDefault);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        cmdCancel = new QPushButton(ExtraireFeaturesDialog);
        cmdCancel->setObjectName(QString::fromUtf8("cmdCancel"));

        horizontalLayout_4->addWidget(cmdCancel);

        cmdExtract = new QPushButton(ExtraireFeaturesDialog);
        cmdExtract->setObjectName(QString::fromUtf8("cmdExtract"));
        cmdExtract->setDefault(true);

        horizontalLayout_4->addWidget(cmdExtract);


        verticalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout_8->addLayout(verticalLayout_6);


        gridLayout->addLayout(verticalLayout_8, 0, 0, 1, 1);


        retranslateUi(ExtraireFeaturesDialog);

        QMetaObject::connectSlotsByName(ExtraireFeaturesDialog);
    } // setupUi

    void retranslateUi(QDialog *ExtraireFeaturesDialog)
    {
        ExtraireFeaturesDialog->setWindowTitle(QApplication::translate("ExtraireFeaturesDialog", "Features Extract", 0, QApplication::UnicodeUTF8));
        lblTotal->setText(QApplication::translate("ExtraireFeaturesDialog", "List of descriptors :", 0, QApplication::UnicodeUTF8));
        cmdDefault->setText(QApplication::translate("ExtraireFeaturesDialog", "Default", 0, QApplication::UnicodeUTF8));
        cmdCancel->setText(QApplication::translate("ExtraireFeaturesDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        cmdExtract->setText(QApplication::translate("ExtraireFeaturesDialog", "Extract", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExtraireFeaturesDialog: public Ui_ExtraireFeaturesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRAIREFEATURESDIALOG_H
