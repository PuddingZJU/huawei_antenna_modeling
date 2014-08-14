#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtOpenGL/qgl.h"
#include "QtOpenGL/QGLWidget"
#include "QtOpenGL/QtOpenGL"
#include "IO/AnduMeshReader.h"
#include "Mesh.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    antennaGLWidget = new Andu::AnduGLWidget();
	Andu::AnduMeshReader reader;
	Caca::Mesh* pMesh = new Caca::Mesh();
	reader.Read(pMesh, "D:\\Projects\\huawei_antenna_modeling\\win32_build\\Debug\\small.obj");
	antennaGLWidget->addGLList(1, pMesh);
	ui->horizontalLayout->setStretchFactor(ui->GLverticalLayout, 4);
	ui->horizontalLayout->setStretchFactor(ui->DataverticalLayout, 1);
    ui->GLverticalLayout->addWidget(antennaGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
