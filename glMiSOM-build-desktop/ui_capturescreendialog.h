/********************************************************************************
** Form generated from reading UI file 'capturescreendialog.ui'
**
** Created: Sat Oct 15 11:19:11 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAPTURESCREENDIALOG_H
#define UI_CAPTURESCREENDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CaptureScreenDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spiWidth;
    QLabel *label_2;
    QSpinBox *spiHeight;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnCancel;
    QPushButton *btnCapture;

    void setupUi(QDialog *CaptureScreenDialog)
    {
        if (CaptureScreenDialog->objectName().isEmpty())
            CaptureScreenDialog->setObjectName(QString::fromUtf8("CaptureScreenDialog"));
        CaptureScreenDialog->resize(293, 82);
        verticalLayout = new QVBoxLayout(CaptureScreenDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CaptureScreenDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        spiWidth = new QSpinBox(CaptureScreenDialog);
        spiWidth->setObjectName(QString::fromUtf8("spiWidth"));
        spiWidth->setMinimum(300);
        spiWidth->setMaximum(2048);
        spiWidth->setValue(1000);

        horizontalLayout->addWidget(spiWidth);

        label_2 = new QLabel(CaptureScreenDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        spiHeight = new QSpinBox(CaptureScreenDialog);
        spiHeight->setObjectName(QString::fromUtf8("spiHeight"));
        spiHeight->setMinimum(300);
        spiHeight->setMaximum(2048);
        spiHeight->setValue(1000);

        horizontalLayout->addWidget(spiHeight);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnCancel = new QPushButton(CaptureScreenDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout_2->addWidget(btnCancel);

        btnCapture = new QPushButton(CaptureScreenDialog);
        btnCapture->setObjectName(QString::fromUtf8("btnCapture"));

        horizontalLayout_2->addWidget(btnCapture);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(CaptureScreenDialog);

        QMetaObject::connectSlotsByName(CaptureScreenDialog);
    } // setupUi

    void retranslateUi(QDialog *CaptureScreenDialog)
    {
        CaptureScreenDialog->setWindowTitle(QApplication::translate("CaptureScreenDialog", "Capture screen", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CaptureScreenDialog", "Width :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CaptureScreenDialog", "Height :", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("CaptureScreenDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        btnCapture->setText(QApplication::translate("CaptureScreenDialog", "Capture", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CaptureScreenDialog: public Ui_CaptureScreenDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAPTURESCREENDIALOG_H
