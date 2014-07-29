/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_open;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionExit;
    QAction *actionHelo;
    QAction *actionAbout;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionExportOBJ;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *GLverticalLayout;
    QVBoxLayout *DataverticalLayout;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1131, 792);
        action_open = new QAction(MainWindow);
        action_open->setObjectName(QStringLiteral("action_open"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionHelo = new QAction(MainWindow);
        actionHelo->setObjectName(QStringLiteral("actionHelo"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        actionExportOBJ = new QAction(MainWindow);
        actionExportOBJ->setObjectName(QStringLiteral("actionExportOBJ"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        GLverticalLayout = new QVBoxLayout();
        GLverticalLayout->setSpacing(6);
        GLverticalLayout->setObjectName(QStringLiteral("GLverticalLayout"));
        GLverticalLayout->setContentsMargins(0, -1, 0, -1);

        horizontalLayout->addLayout(GLverticalLayout);

        DataverticalLayout = new QVBoxLayout();
        DataverticalLayout->setSpacing(6);
        DataverticalLayout->setObjectName(QStringLiteral("DataverticalLayout"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));

        DataverticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));

        DataverticalLayout->addWidget(groupBox);


        horizontalLayout->addLayout(DataverticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1131, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(actionNew);
        menu->addAction(actionOpen);
        menu->addAction(actionSave);
        menu->addAction(actionSave_as);
        menu->addAction(actionExportOBJ);
        menu->addAction(actionExit);
        menu_2->addAction(actionUndo);
        menu_2->addAction(actionRedo);
        menu_4->addAction(actionHelo);
        menu_4->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_open->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0));
        actionNew->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200...", 0));
        actionSave->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", 0));
        actionSave_as->setText(QApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272...", 0));
        actionExit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0));
        actionHelo->setText(QApplication::translate("MainWindow", "\345\270\256\345\212\251...", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216...", 0));
        actionUndo->setText(QApplication::translate("MainWindow", "\346\222\244\351\224\200", 0));
        actionRedo->setText(QApplication::translate("MainWindow", "\351\207\215\345\201\232", 0));
        actionExportOBJ->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272 obj ...", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\346\265\213\351\207\217\345\217\202\346\225\260", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "\350\256\241\347\256\227\345\217\202\346\225\260", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0));
        menu_2->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221", 0));
        menu_4->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
