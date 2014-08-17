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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_ew;
    QLineEdit *lineEdit_ml;
    QLabel *label_6;
    QLabel *label_2;
    QLineEdit *lineEdit_mw;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *lineEdit_el;
    QLineEdit *lineEdit_gh;
    QLineEdit *lineEdit_th;
    QLabel *label_5;
    QPushButton *calculateButton;
    QGroupBox *groupBox;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_W;
    QLabel *label_10;
    QLabel *label_9;
    QLabel *label_8;
    QLineEdit *lineEdit_R;
    QLabel *label_11;
    QLineEdit *lineEdit_L;
    QLineEdit *lineEdit_r;
    QLabel *label_12;
    QLineEdit *lineEdit_H;
    QPushButton *ShowModelButton;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_4;

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
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 181, 261));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_ew = new QLineEdit(layoutWidget);
        lineEdit_ew->setObjectName(QStringLiteral("lineEdit_ew"));

        gridLayout->addWidget(lineEdit_ew, 5, 1, 1, 1);

        lineEdit_ml = new QLineEdit(layoutWidget);
        lineEdit_ml->setObjectName(QStringLiteral("lineEdit_ml"));

        gridLayout->addWidget(lineEdit_ml, 1, 1, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_mw = new QLineEdit(layoutWidget);
        lineEdit_mw->setObjectName(QStringLiteral("lineEdit_mw"));

        gridLayout->addWidget(lineEdit_mw, 4, 1, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_el = new QLineEdit(layoutWidget);
        lineEdit_el->setObjectName(QStringLiteral("lineEdit_el"));

        gridLayout->addWidget(lineEdit_el, 0, 1, 1, 1);

        lineEdit_gh = new QLineEdit(layoutWidget);
        lineEdit_gh->setObjectName(QStringLiteral("lineEdit_gh"));

        gridLayout->addWidget(lineEdit_gh, 3, 1, 1, 1);

        lineEdit_th = new QLineEdit(layoutWidget);
        lineEdit_th->setObjectName(QStringLiteral("lineEdit_th"));

        gridLayout->addWidget(lineEdit_th, 2, 1, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        calculateButton = new QPushButton(groupBox_2);
        calculateButton->setObjectName(QStringLiteral("calculateButton"));
        calculateButton->setGeometry(QRect(50, 300, 111, 23));

        DataverticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        layoutWidget_2 = new QWidget(groupBox);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 20, 231, 201));
        gridLayout_2 = new QGridLayout(layoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit_W = new QLineEdit(layoutWidget_2);
        lineEdit_W->setObjectName(QStringLiteral("lineEdit_W"));

        gridLayout_2->addWidget(lineEdit_W, 1, 1, 1, 1);

        label_10 = new QLabel(layoutWidget_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 2, 0, 1, 1);

        label_9 = new QLabel(layoutWidget_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 3, 0, 1, 1);

        label_8 = new QLabel(layoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 1, 0, 1, 1);

        lineEdit_R = new QLineEdit(layoutWidget_2);
        lineEdit_R->setObjectName(QStringLiteral("lineEdit_R"));

        gridLayout_2->addWidget(lineEdit_R, 4, 1, 1, 1);

        label_11 = new QLabel(layoutWidget_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_2->addWidget(label_11, 0, 0, 1, 1);

        lineEdit_L = new QLineEdit(layoutWidget_2);
        lineEdit_L->setObjectName(QStringLiteral("lineEdit_L"));

        gridLayout_2->addWidget(lineEdit_L, 0, 1, 1, 1);

        lineEdit_r = new QLineEdit(layoutWidget_2);
        lineEdit_r->setObjectName(QStringLiteral("lineEdit_r"));

        gridLayout_2->addWidget(lineEdit_r, 3, 1, 1, 1);

        label_12 = new QLabel(layoutWidget_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 4, 0, 1, 1);

        lineEdit_H = new QLineEdit(layoutWidget_2);
        lineEdit_H->setObjectName(QStringLiteral("lineEdit_H"));

        gridLayout_2->addWidget(lineEdit_H, 2, 1, 1, 1);

        ShowModelButton = new QPushButton(groupBox);
        ShowModelButton->setObjectName(QStringLiteral("ShowModelButton"));
        ShowModelButton->setGeometry(QRect(50, 240, 111, 23));

        DataverticalLayout->addWidget(groupBox);


        horizontalLayout->addLayout(DataverticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1131, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(actionNew);
        menu->addAction(actionOpen);
        menu->addAction(actionSave);
        menu->addAction(actionSave_as);
        menu->addAction(actionExportOBJ);
        menu->addAction(actionExit);
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
        label_6->setText(QApplication::translate("MainWindow", "\350\276\271\347\274\230\345\256\275\345\272\246 (ew):", 0));
        label_2->setText(QApplication::translate("MainWindow", "\345\206\205\351\203\250\351\225\277\345\272\246 (ml):", 0));
        label_4->setText(QApplication::translate("MainWindow", "\351\241\266\347\233\226\351\253\230\345\272\246 (gh):", 0));
        label_3->setText(QApplication::translate("MainWindow", "\345\244\251\347\272\277\351\253\230\345\272\246 (th):", 0));
        label->setText(QApplication::translate("MainWindow", "\350\276\271\347\274\230\351\225\277\345\272\246 (el):", 0));
        label_5->setText(QApplication::translate("MainWindow", "\344\270\255\345\277\203\347\202\271\345\256\275\345\272\246 (mw):", 0));
        calculateButton->setText(QApplication::translate("MainWindow", "\350\256\241\347\256\227", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "\350\256\241\347\256\227\345\217\202\346\225\260", 0));
        label_10->setText(QApplication::translate("MainWindow", "\345\244\251\347\272\277\346\250\241\345\236\213\351\253\230\345\272\246 (H):", 0));
        label_9->setText(QApplication::translate("MainWindow", "\345\244\251\347\272\277\346\250\241\345\236\213\346\250\252\346\210\252\351\235\242\345\234\206\350\247\222\345\215\212\345\276\204 (r):", 0));
        label_8->setText(QApplication::translate("MainWindow", "\345\244\251\347\272\277\346\250\241\345\236\213\345\256\275\345\272\246 (W):", 0));
        label_11->setText(QApplication::translate("MainWindow", "\345\244\251\347\272\277\346\250\241\345\236\213\351\225\277\345\272\246 (L):", 0));
        label_12->setText(QApplication::translate("MainWindow", "\345\244\251\347\272\277\345\244\226\350\241\250\351\235\242\345\234\206\345\274\247\345\215\212\345\276\204 (R):", 0));
        ShowModelButton->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\346\250\241\345\236\213", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0));
        menu_4->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
