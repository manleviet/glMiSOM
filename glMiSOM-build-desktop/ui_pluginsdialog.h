/********************************************************************************
** Form generated from reading UI file 'pluginsdialog.ui'
**
** Created: Sat Oct 15 11:19:11 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINSDIALOG_H
#define UI_PLUGINSDIALOG_H

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
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PluginsDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QListWidget *lstPlugins;
    QLabel *lblAbout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnCancel;

    void setupUi(QDialog *PluginsDialog)
    {
        if (PluginsDialog->objectName().isEmpty())
            PluginsDialog->setObjectName(QString::fromUtf8("PluginsDialog"));
        PluginsDialog->resize(548, 313);
        gridLayout = new QGridLayout(PluginsDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lstPlugins = new QListWidget(PluginsDialog);
        lstPlugins->setObjectName(QString::fromUtf8("lstPlugins"));
        lstPlugins->setMinimumSize(QSize(270, 0));
        lstPlugins->setMaximumSize(QSize(270, 16777215));

        horizontalLayout->addWidget(lstPlugins);

        lblAbout = new QLabel(PluginsDialog);
        lblAbout->setObjectName(QString::fromUtf8("lblAbout"));
        lblAbout->setMinimumSize(QSize(280, 0));
        lblAbout->setMaximumSize(QSize(500, 500));
        lblAbout->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        lblAbout->setWordWrap(true);
        lblAbout->setMargin(6);

        horizontalLayout->addWidget(lblAbout);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnAdd = new QPushButton(PluginsDialog);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        horizontalLayout_2->addWidget(btnAdd);

        btnDelete = new QPushButton(PluginsDialog);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));

        horizontalLayout_2->addWidget(btnDelete);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnCancel = new QPushButton(PluginsDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout_2->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(PluginsDialog);

        QMetaObject::connectSlotsByName(PluginsDialog);
    } // setupUi

    void retranslateUi(QDialog *PluginsDialog)
    {
        PluginsDialog->setWindowTitle(QApplication::translate("PluginsDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        lblAbout->setText(QApplication::translate("PluginsDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        btnAdd->setText(QApplication::translate("PluginsDialog", "Add...", 0, QApplication::UnicodeUTF8));
        btnDelete->setText(QApplication::translate("PluginsDialog", "Delete...", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("PluginsDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PluginsDialog: public Ui_PluginsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGINSDIALOG_H
