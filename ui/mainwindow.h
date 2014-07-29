#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "antennaglwidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    AntennaGLWidget *antennaGLWidget;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
