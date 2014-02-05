/********************************************************************************
** Form generated from reading UI file 'indexationdialog.ui'
**
** Created: Sat Oct 15 11:19:11 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INDEXATIONDIALOG_H
#define UI_INDEXATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include "UI/chosendescriptors.h"

QT_BEGIN_NAMESPACE

class Ui_IndexationDialog
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *lblTotal;
    QListWidget *lstDescriptors;
    QVBoxLayout *verticalLayout_2;
    ChosenDescriptors *tabChosenDescriptors;
    QFrame *line;
    QGroupBox *grpInit;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_12;
    QSpinBox *spiXdim;
    QLabel *label_13;
    QSpinBox *spiYdim;
    QLabel *label_2;
    QSpinBox *spbRandomize;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *lblInitTime;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnInit;
    QPushButton *btnLoadWeight;
    QPushButton *btnSaveWeight;
    QFrame *line_2;
    QGroupBox *grpTraining;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *cmbNeighType;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_8;
    QComboBox *cmbAlphaType;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_17;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpinBox *spbLengthOrdering;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QDoubleSpinBox *spbAlpha_Ordering;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QDoubleSpinBox *spbRadius_Ordering;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lblOrderingTime;
    QPushButton *btnOrdering;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_18;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpinBox *spbLengthConvergence;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_9;
    QDoubleSpinBox *spbAlpha_Conver;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_10;
    QDoubleSpinBox *spbRadius_Conver;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_4;
    QLabel *lblConvergeTime;
    QPushButton *btnConverge;
    QFrame *line_3;
    QGroupBox *grpVisual;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_20;
    QPushButton *btnViewCodes;
    QPushButton *btnVisual;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label;
    QSpinBox *spiStepRearr;
    QPushButton *btnRearrange;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnDefault;
    QPushButton *btnCancel;

    void setupUi(QDialog *IndexationDialog)
    {
        if (IndexationDialog->objectName().isEmpty())
            IndexationDialog->setObjectName(QString::fromUtf8("IndexationDialog"));
        IndexationDialog->resize(676, 719);
        verticalLayout_4 = new QVBoxLayout(IndexationDialog);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lblTotal = new QLabel(IndexationDialog);
        lblTotal->setObjectName(QString::fromUtf8("lblTotal"));

        verticalLayout->addWidget(lblTotal);

        lstDescriptors = new QListWidget(IndexationDialog);
        lstDescriptors->setObjectName(QString::fromUtf8("lstDescriptors"));

        verticalLayout->addWidget(lstDescriptors);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabChosenDescriptors = new ChosenDescriptors(IndexationDialog);
        if (tabChosenDescriptors->columnCount() < 2)
            tabChosenDescriptors->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tabChosenDescriptors->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tabChosenDescriptors->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tabChosenDescriptors->setObjectName(QString::fromUtf8("tabChosenDescriptors"));
        tabChosenDescriptors->setMinimumSize(QSize(256, 150));
        tabChosenDescriptors->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabChosenDescriptors->horizontalHeader()->setDefaultSectionSize(100);

        verticalLayout_2->addWidget(tabChosenDescriptors);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_9->addLayout(horizontalLayout);

        line = new QFrame(IndexationDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_9->addWidget(line);


        verticalLayout_4->addLayout(verticalLayout_9);

        grpInit = new QGroupBox(IndexationDialog);
        grpInit->setObjectName(QString::fromUtf8("grpInit"));
        grpInit->setFlat(false);
        verticalLayout_3 = new QVBoxLayout(grpInit);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_12 = new QLabel(grpInit);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_2->addWidget(label_12);

        spiXdim = new QSpinBox(grpInit);
        spiXdim->setObjectName(QString::fromUtf8("spiXdim"));
        spiXdim->setMinimum(1);
        spiXdim->setMaximum(1000000);

        horizontalLayout_2->addWidget(spiXdim);

        label_13 = new QLabel(grpInit);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_2->addWidget(label_13);

        spiYdim = new QSpinBox(grpInit);
        spiYdim->setObjectName(QString::fromUtf8("spiYdim"));
        spiYdim->setMinimum(1);
        spiYdim->setMaximum(1000000);

        horizontalLayout_2->addWidget(spiYdim);

        label_2 = new QLabel(grpInit);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        spbRandomize = new QSpinBox(grpInit);
        spbRandomize->setObjectName(QString::fromUtf8("spbRandomize"));
        spbRandomize->setMaximum(1000000);

        horizontalLayout_2->addWidget(spbRandomize);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        lblInitTime = new QLabel(grpInit);
        lblInitTime->setObjectName(QString::fromUtf8("lblInitTime"));
        QFont font;
        font.setBold(false);
        font.setItalic(true);
        font.setWeight(50);
        lblInitTime->setFont(font);

        horizontalLayout_8->addWidget(lblInitTime);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        btnInit = new QPushButton(grpInit);
        btnInit->setObjectName(QString::fromUtf8("btnInit"));

        horizontalLayout_8->addWidget(btnInit);

        btnLoadWeight = new QPushButton(grpInit);
        btnLoadWeight->setObjectName(QString::fromUtf8("btnLoadWeight"));

        horizontalLayout_8->addWidget(btnLoadWeight);

        btnSaveWeight = new QPushButton(grpInit);
        btnSaveWeight->setObjectName(QString::fromUtf8("btnSaveWeight"));

        horizontalLayout_8->addWidget(btnSaveWeight);


        verticalLayout_3->addLayout(horizontalLayout_8);


        verticalLayout_4->addWidget(grpInit);

        line_2 = new QFrame(IndexationDialog);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_2);

        grpTraining = new QGroupBox(IndexationDialog);
        grpTraining->setObjectName(QString::fromUtf8("grpTraining"));
        gridLayout_4 = new QGridLayout(grpTraining);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(grpTraining);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        cmbNeighType = new QComboBox(grpTraining);
        cmbNeighType->setObjectName(QString::fromUtf8("cmbNeighType"));

        horizontalLayout_3->addWidget(cmbNeighType);


        gridLayout_4->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_8 = new QLabel(grpTraining);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_11->addWidget(label_8);

        cmbAlphaType = new QComboBox(grpTraining);
        cmbAlphaType->setObjectName(QString::fromUtf8("cmbAlphaType"));

        horizontalLayout_11->addWidget(cmbAlphaType);


        gridLayout_4->addLayout(horizontalLayout_11, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(grpTraining);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        spbLengthOrdering = new QSpinBox(groupBox_3);
        spbLengthOrdering->setObjectName(QString::fromUtf8("spbLengthOrdering"));
        spbLengthOrdering->setMaximum(1000000);

        horizontalLayout_4->addWidget(spbLengthOrdering);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        spbAlpha_Ordering = new QDoubleSpinBox(groupBox_3);
        spbAlpha_Ordering->setObjectName(QString::fromUtf8("spbAlpha_Ordering"));

        horizontalLayout_6->addWidget(spbAlpha_Ordering);


        verticalLayout_5->addLayout(horizontalLayout_6);


        horizontalLayout_17->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_7->addWidget(label_7);

        spbRadius_Ordering = new QDoubleSpinBox(groupBox_3);
        spbRadius_Ordering->setObjectName(QString::fromUtf8("spbRadius_Ordering"));

        horizontalLayout_7->addWidget(spbRadius_Ordering);


        verticalLayout_6->addLayout(horizontalLayout_7);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_3);

        lblOrderingTime = new QLabel(groupBox_3);
        lblOrderingTime->setObjectName(QString::fromUtf8("lblOrderingTime"));
        QFont font1;
        font1.setItalic(true);
        lblOrderingTime->setFont(font1);

        horizontalLayout_13->addWidget(lblOrderingTime);

        btnOrdering = new QPushButton(groupBox_3);
        btnOrdering->setObjectName(QString::fromUtf8("btnOrdering"));

        horizontalLayout_13->addWidget(btnOrdering);


        verticalLayout_6->addLayout(horizontalLayout_13);


        horizontalLayout_17->addLayout(verticalLayout_6);


        gridLayout_2->addLayout(horizontalLayout_17, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 1, 0, 1, 2);

        groupBox_4 = new QGroupBox(grpTraining);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        spbLengthConvergence = new QSpinBox(groupBox_4);
        spbLengthConvergence->setObjectName(QString::fromUtf8("spbLengthConvergence"));
        spbLengthConvergence->setMaximum(1000000);

        horizontalLayout_5->addWidget(spbLengthConvergence);


        verticalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_14->addWidget(label_9);

        spbAlpha_Conver = new QDoubleSpinBox(groupBox_4);
        spbAlpha_Conver->setObjectName(QString::fromUtf8("spbAlpha_Conver"));

        horizontalLayout_14->addWidget(spbAlpha_Conver);


        verticalLayout_7->addLayout(horizontalLayout_14);


        horizontalLayout_18->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_15->addWidget(label_10);

        spbRadius_Conver = new QDoubleSpinBox(groupBox_4);
        spbRadius_Conver->setObjectName(QString::fromUtf8("spbRadius_Conver"));

        horizontalLayout_15->addWidget(spbRadius_Conver);


        verticalLayout_8->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_4);

        lblConvergeTime = new QLabel(groupBox_4);
        lblConvergeTime->setObjectName(QString::fromUtf8("lblConvergeTime"));
        lblConvergeTime->setFont(font1);

        horizontalLayout_16->addWidget(lblConvergeTime);

        btnConverge = new QPushButton(groupBox_4);
        btnConverge->setObjectName(QString::fromUtf8("btnConverge"));

        horizontalLayout_16->addWidget(btnConverge);


        verticalLayout_8->addLayout(horizontalLayout_16);


        horizontalLayout_18->addLayout(verticalLayout_8);


        gridLayout_3->addLayout(horizontalLayout_18, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_4, 2, 0, 1, 2);


        verticalLayout_4->addWidget(grpTraining);

        line_3 = new QFrame(IndexationDialog);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_3);

        grpVisual = new QGroupBox(IndexationDialog);
        grpVisual->setObjectName(QString::fromUtf8("grpVisual"));
        gridLayout_5 = new QGridLayout(grpVisual);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        btnViewCodes = new QPushButton(grpVisual);
        btnViewCodes->setObjectName(QString::fromUtf8("btnViewCodes"));

        horizontalLayout_20->addWidget(btnViewCodes);

        btnVisual = new QPushButton(grpVisual);
        btnVisual->setObjectName(QString::fromUtf8("btnVisual"));

        horizontalLayout_20->addWidget(btnVisual);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_5);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label = new QLabel(grpVisual);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_19->addWidget(label);

        spiStepRearr = new QSpinBox(grpVisual);
        spiStepRearr->setObjectName(QString::fromUtf8("spiStepRearr"));
        spiStepRearr->setMinimum(1);
        spiStepRearr->setMaximum(1000);

        horizontalLayout_19->addWidget(spiStepRearr);


        horizontalLayout_20->addLayout(horizontalLayout_19);

        btnRearrange = new QPushButton(grpVisual);
        btnRearrange->setObjectName(QString::fromUtf8("btnRearrange"));

        horizontalLayout_20->addWidget(btnRearrange);


        gridLayout_5->addLayout(horizontalLayout_20, 0, 0, 1, 1);


        verticalLayout_4->addWidget(grpVisual);

        line_4 = new QFrame(IndexationDialog);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_4);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_2);

        btnDefault = new QPushButton(IndexationDialog);
        btnDefault->setObjectName(QString::fromUtf8("btnDefault"));

        horizontalLayout_12->addWidget(btnDefault);

        btnCancel = new QPushButton(IndexationDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout_12->addWidget(btnCancel);


        verticalLayout_4->addLayout(horizontalLayout_12);


        retranslateUi(IndexationDialog);

        QMetaObject::connectSlotsByName(IndexationDialog);
    } // setupUi

    void retranslateUi(QDialog *IndexationDialog)
    {
        IndexationDialog->setWindowTitle(QApplication::translate("IndexationDialog", "Indexing", 0, QApplication::UnicodeUTF8));
        lblTotal->setText(QApplication::translate("IndexationDialog", "List of descriptors :", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tabChosenDescriptors->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("IndexationDialog", "Feature", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tabChosenDescriptors->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("IndexationDialog", "Weight", 0, QApplication::UnicodeUTF8));
        grpInit->setTitle(QApplication::translate("IndexationDialog", "Init", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("IndexationDialog", "Number of rows :", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("IndexationDialog", "Number of cols :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("IndexationDialog", "Random seed :", 0, QApplication::UnicodeUTF8));
        lblInitTime->setText(QApplication::translate("IndexationDialog", "Init time :", 0, QApplication::UnicodeUTF8));
        btnInit->setText(QApplication::translate("IndexationDialog", "Init map", 0, QApplication::UnicodeUTF8));
        btnLoadWeight->setText(QApplication::translate("IndexationDialog", "Load weights", 0, QApplication::UnicodeUTF8));
        btnSaveWeight->setText(QApplication::translate("IndexationDialog", "Save weights", 0, QApplication::UnicodeUTF8));
        grpTraining->setTitle(QApplication::translate("IndexationDialog", "Training", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("IndexationDialog", "Neighbour function type :", 0, QApplication::UnicodeUTF8));
        cmbNeighType->clear();
        cmbNeighType->insertItems(0, QStringList()
         << QApplication::translate("IndexationDialog", "Bubble", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IndexationDialog", "Gaussian", 0, QApplication::UnicodeUTF8)
        );
        label_8->setText(QApplication::translate("IndexationDialog", "Learning rate function type :", 0, QApplication::UnicodeUTF8));
        cmbAlphaType->clear();
        cmbAlphaType->insertItems(0, QStringList()
         << QApplication::translate("IndexationDialog", "Linear", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IndexationDialog", "Inverse_t", 0, QApplication::UnicodeUTF8)
        );
        groupBox_3->setTitle(QApplication::translate("IndexationDialog", "Ordering", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("IndexationDialog", "Number of step :", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("IndexationDialog", "Initial learning rate parameter :", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("IndexationDialog", "Initial radius of neighbour function :", 0, QApplication::UnicodeUTF8));
        lblOrderingTime->setText(QApplication::translate("IndexationDialog", "Ordering time :", 0, QApplication::UnicodeUTF8));
        btnOrdering->setText(QApplication::translate("IndexationDialog", "Ordering", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("IndexationDialog", "Convergence", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("IndexationDialog", "Number of step :", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("IndexationDialog", "Initial learning rate parameter :", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("IndexationDialog", "Initial radius of neighbour function :", 0, QApplication::UnicodeUTF8));
        lblConvergeTime->setText(QApplication::translate("IndexationDialog", "Convergence time :", 0, QApplication::UnicodeUTF8));
        btnConverge->setText(QApplication::translate("IndexationDialog", "Converge", 0, QApplication::UnicodeUTF8));
        grpVisual->setTitle(QApplication::translate("IndexationDialog", "Visualization", 0, QApplication::UnicodeUTF8));
        btnViewCodes->setText(QApplication::translate("IndexationDialog", "View codes", 0, QApplication::UnicodeUTF8));
        btnVisual->setText(QApplication::translate("IndexationDialog", "Visual", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("IndexationDialog", "Number of step :", 0, QApplication::UnicodeUTF8));
        btnRearrange->setText(QApplication::translate("IndexationDialog", "Re-arrange", 0, QApplication::UnicodeUTF8));
        btnDefault->setText(QApplication::translate("IndexationDialog", "Default", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("IndexationDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IndexationDialog: public Ui_IndexationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INDEXATIONDIALOG_H
