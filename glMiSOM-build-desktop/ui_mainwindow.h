/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Oct 15 11:19:11 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionFullscreen;
    QAction *actionColor_Histogram;
    QAction *actionHu_Moments;
    QAction *actionMatrix_Cooccurrences;
    QAction *actionAnimation;
    QAction *actionTraining;
    QAction *actionNormal_2;
    QAction *actionSOM;
    QAction *actionSOM_rearranged;
    QAction *actionInformation;
    QAction *actionOriginal_Position;
    QAction *actionFeatures_Extract;
    QAction *actionImport;
    QAction *actionIndexing;
    QAction *actionLoad_map;
    QAction *actionSave_map;
    QAction *actionSearch;
    QAction *actionNormal;
    QAction *actionSOM_2;
    QAction *actionRearrangement;
    QAction *actionSOM_3;
    QAction *actionSOM_4;
    QAction *actionClose;
    QAction *actionClose_All;
    QAction *actionTile;
    QAction *actionCascade;
    QAction *actionCapture_screen;
    QAction *actionPlugins;
    QAction *actionImport_2;
    QAction *actionSave_map_2;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuOptions;
    QMenu *menuHelp;
    QMenu *menuDatabase;
    QMenu *menuTools;
    QMenu *menuWindow;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 450);
        MainWindow->setWindowTitle(QString::fromUtf8("MainWindow"));
        MainWindow->setAutoFillBackground(false);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionOpen->setCheckable(false);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionFullscreen = new QAction(MainWindow);
        actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
        actionFullscreen->setEnabled(false);
        actionColor_Histogram = new QAction(MainWindow);
        actionColor_Histogram->setObjectName(QString::fromUtf8("actionColor_Histogram"));
        actionColor_Histogram->setEnabled(false);
        actionHu_Moments = new QAction(MainWindow);
        actionHu_Moments->setObjectName(QString::fromUtf8("actionHu_Moments"));
        actionHu_Moments->setEnabled(false);
        actionMatrix_Cooccurrences = new QAction(MainWindow);
        actionMatrix_Cooccurrences->setObjectName(QString::fromUtf8("actionMatrix_Cooccurrences"));
        actionMatrix_Cooccurrences->setEnabled(false);
        actionAnimation = new QAction(MainWindow);
        actionAnimation->setObjectName(QString::fromUtf8("actionAnimation"));
        actionAnimation->setCheckable(true);
        actionAnimation->setEnabled(false);
        actionTraining = new QAction(MainWindow);
        actionTraining->setObjectName(QString::fromUtf8("actionTraining"));
        actionTraining->setEnabled(false);
        actionNormal_2 = new QAction(MainWindow);
        actionNormal_2->setObjectName(QString::fromUtf8("actionNormal_2"));
        actionNormal_2->setCheckable(true);
        actionNormal_2->setEnabled(false);
        actionSOM = new QAction(MainWindow);
        actionSOM->setObjectName(QString::fromUtf8("actionSOM"));
        actionSOM->setCheckable(true);
        actionSOM->setEnabled(false);
        actionSOM_rearranged = new QAction(MainWindow);
        actionSOM_rearranged->setObjectName(QString::fromUtf8("actionSOM_rearranged"));
        actionSOM_rearranged->setCheckable(true);
        actionSOM_rearranged->setEnabled(false);
        actionInformation = new QAction(MainWindow);
        actionInformation->setObjectName(QString::fromUtf8("actionInformation"));
        actionInformation->setEnabled(false);
        actionOriginal_Position = new QAction(MainWindow);
        actionOriginal_Position->setObjectName(QString::fromUtf8("actionOriginal_Position"));
        actionOriginal_Position->setEnabled(false);
        actionFeatures_Extract = new QAction(MainWindow);
        actionFeatures_Extract->setObjectName(QString::fromUtf8("actionFeatures_Extract"));
        actionFeatures_Extract->setEnabled(false);
        actionImport = new QAction(MainWindow);
        actionImport->setObjectName(QString::fromUtf8("actionImport"));
        actionImport->setEnabled(false);
        actionIndexing = new QAction(MainWindow);
        actionIndexing->setObjectName(QString::fromUtf8("actionIndexing"));
        actionIndexing->setEnabled(false);
        actionLoad_map = new QAction(MainWindow);
        actionLoad_map->setObjectName(QString::fromUtf8("actionLoad_map"));
        actionLoad_map->setEnabled(false);
        actionSave_map = new QAction(MainWindow);
        actionSave_map->setObjectName(QString::fromUtf8("actionSave_map"));
        actionSave_map->setEnabled(false);
        actionSearch = new QAction(MainWindow);
        actionSearch->setObjectName(QString::fromUtf8("actionSearch"));
        actionSearch->setEnabled(false);
        actionNormal = new QAction(MainWindow);
        actionNormal->setObjectName(QString::fromUtf8("actionNormal"));
        actionNormal->setEnabled(false);
        actionSOM_2 = new QAction(MainWindow);
        actionSOM_2->setObjectName(QString::fromUtf8("actionSOM_2"));
        actionSOM_2->setEnabled(false);
        actionRearrangement = new QAction(MainWindow);
        actionRearrangement->setObjectName(QString::fromUtf8("actionRearrangement"));
        actionRearrangement->setEnabled(false);
        actionSOM_3 = new QAction(MainWindow);
        actionSOM_3->setObjectName(QString::fromUtf8("actionSOM_3"));
        actionSOM_4 = new QAction(MainWindow);
        actionSOM_4->setObjectName(QString::fromUtf8("actionSOM_4"));
        actionSOM_4->setEnabled(false);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionClose_All = new QAction(MainWindow);
        actionClose_All->setObjectName(QString::fromUtf8("actionClose_All"));
        actionTile = new QAction(MainWindow);
        actionTile->setObjectName(QString::fromUtf8("actionTile"));
        actionCascade = new QAction(MainWindow);
        actionCascade->setObjectName(QString::fromUtf8("actionCascade"));
        actionCapture_screen = new QAction(MainWindow);
        actionCapture_screen->setObjectName(QString::fromUtf8("actionCapture_screen"));
        actionCapture_screen->setEnabled(false);
        actionPlugins = new QAction(MainWindow);
        actionPlugins->setObjectName(QString::fromUtf8("actionPlugins"));
        actionPlugins->setEnabled(true);
        actionImport_2 = new QAction(MainWindow);
        actionImport_2->setObjectName(QString::fromUtf8("actionImport_2"));
        actionImport_2->setEnabled(false);
        actionSave_map_2 = new QAction(MainWindow);
        actionSave_map_2->setObjectName(QString::fromUtf8("actionSave_map_2"));
        actionSave_map_2->setEnabled(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 25));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuDatabase = new QMenu(menuBar);
        menuDatabase->setObjectName(QString::fromUtf8("menuDatabase"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QString::fromUtf8("menuWindow"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuDatabase->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuOptions->addAction(actionFullscreen);
        menuOptions->addAction(actionAnimation);
        menuOptions->addAction(actionOriginal_Position);
        menuHelp->addAction(actionAbout);
        menuDatabase->addAction(actionOpen);
        menuDatabase->addAction(actionInformation);
        menuDatabase->addSeparator();
        menuDatabase->addAction(actionLoad_map);
        menuDatabase->addAction(actionSave_map_2);
        menuDatabase->addAction(actionSave_map);
        menuDatabase->addAction(actionImport_2);
        menuDatabase->addSeparator();
        menuDatabase->addAction(actionExit);
        menuTools->addAction(actionFeatures_Extract);
        menuTools->addAction(actionIndexing);
        menuTools->addAction(actionSearch);
        menuTools->addSeparator();
        menuTools->addAction(actionCapture_screen);
        menuTools->addAction(actionPlugins);
        menuWindow->addAction(actionClose);
        menuWindow->addAction(actionClose_All);
        menuWindow->addSeparator();
        menuWindow->addAction(actionTile);
        menuWindow->addAction(actionCascade);
        menuWindow->addSeparator();
        menuWindow->addAction(actionNormal);
        menuWindow->addAction(actionSOM_4);
        menuWindow->addAction(actionRearrangement);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        actionOpen->setText(QApplication::translate("MainWindow", "&Open...", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "&Exit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "&About glMiSOM...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAbout->setToolTip(QApplication::translate("MainWindow", "Acerca de Visualizador de Mol\303\251culas", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionFullscreen->setText(QApplication::translate("MainWindow", "Fullscreen", 0, QApplication::UnicodeUTF8));
        actionColor_Histogram->setText(QApplication::translate("MainWindow", "Color Histogram", 0, QApplication::UnicodeUTF8));
        actionHu_Moments->setText(QApplication::translate("MainWindow", "Hu Moments", 0, QApplication::UnicodeUTF8));
        actionMatrix_Cooccurrences->setText(QApplication::translate("MainWindow", "Matrix Cooccurrences", 0, QApplication::UnicodeUTF8));
        actionAnimation->setText(QApplication::translate("MainWindow", "Animation", 0, QApplication::UnicodeUTF8));
        actionTraining->setText(QApplication::translate("MainWindow", "Training...", 0, QApplication::UnicodeUTF8));
        actionNormal_2->setText(QApplication::translate("MainWindow", "Normal", 0, QApplication::UnicodeUTF8));
        actionSOM->setText(QApplication::translate("MainWindow", "SOM", 0, QApplication::UnicodeUTF8));
        actionSOM_rearranged->setText(QApplication::translate("MainWindow", "SOM rearranged", 0, QApplication::UnicodeUTF8));
        actionInformation->setText(QApplication::translate("MainWindow", "Information", 0, QApplication::UnicodeUTF8));
        actionOriginal_Position->setText(QApplication::translate("MainWindow", "Original Position", 0, QApplication::UnicodeUTF8));
        actionFeatures_Extract->setText(QApplication::translate("MainWindow", "Features Extract...", 0, QApplication::UnicodeUTF8));
        actionImport->setText(QApplication::translate("MainWindow", "Import...", 0, QApplication::UnicodeUTF8));
        actionIndexing->setText(QApplication::translate("MainWindow", "Indexing...", 0, QApplication::UnicodeUTF8));
        actionLoad_map->setText(QApplication::translate("MainWindow", "Load map...", 0, QApplication::UnicodeUTF8));
        actionSave_map->setText(QApplication::translate("MainWindow", "Save map as...", 0, QApplication::UnicodeUTF8));
        actionSearch->setText(QApplication::translate("MainWindow", "Search...", 0, QApplication::UnicodeUTF8));
        actionNormal->setText(QApplication::translate("MainWindow", "Normal", 0, QApplication::UnicodeUTF8));
        actionSOM_2->setText(QApplication::translate("MainWindow", "SOM", 0, QApplication::UnicodeUTF8));
        actionRearrangement->setText(QApplication::translate("MainWindow", "Rearrangement", 0, QApplication::UnicodeUTF8));
        actionSOM_3->setText(QApplication::translate("MainWindow", "SOM", 0, QApplication::UnicodeUTF8));
        actionSOM_4->setText(QApplication::translate("MainWindow", "SOM", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        actionClose_All->setText(QApplication::translate("MainWindow", "Close All", 0, QApplication::UnicodeUTF8));
        actionTile->setText(QApplication::translate("MainWindow", "Tile", 0, QApplication::UnicodeUTF8));
        actionCascade->setText(QApplication::translate("MainWindow", "Cascade", 0, QApplication::UnicodeUTF8));
        actionCapture_screen->setText(QApplication::translate("MainWindow", "Capture screen...", 0, QApplication::UnicodeUTF8));
        actionPlugins->setText(QApplication::translate("MainWindow", "Plugins", 0, QApplication::UnicodeUTF8));
        actionImport_2->setText(QApplication::translate("MainWindow", "Import...", 0, QApplication::UnicodeUTF8));
        actionSave_map_2->setText(QApplication::translate("MainWindow", "Save map...", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("MainWindow", "&View", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menuDatabase->setTitle(QApplication::translate("MainWindow", "&Database", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
        menuWindow->setTitle(QApplication::translate("MainWindow", "Window", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
