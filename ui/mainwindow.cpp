#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtOpenGL/qgl.h"
#include "QtOpenGL/QGLWidget"
#include "QtOpenGL/QtOpenGL"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   /* antennaGLWidget = new AntennaGLWidget();
	ui->horizontalLayout->setStretchFactor(ui->GLverticalLayout, 4);
	ui->horizontalLayout->setStretchFactor(ui->DataverticalLayout, 1);
    ui->GLverticalLayout->addWidget(antennaGLWidget);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
