#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtOpenGL/qgl.h"
#include "QtOpenGL/QGLWidget"
#include "QtOpenGL/QtOpenGL"
#include "IO/AnduMeshReader.h"
#include "Mesh.h"
#include "SubMesh.h"
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    antennaGLWidget = new Andu::AnduGLWidget();
	
	ui->horizontalLayout->setStretchFactor(ui->GLverticalLayout, 4);
	ui->horizontalLayout->setStretchFactor(ui->DataverticalLayout, 1);
    ui->GLverticalLayout->addWidget(antennaGLWidget);
	connect(ui->calculateButton, &QPushButton::clicked,this, &MainWindow::CalCulateButtonClicked);
	connect(ui->ShowModelButton, &QPushButton::clicked,this, &MainWindow::ShowModelButtonClicked);
	connect(ui->actionNew, &QAction::triggered, this, &MainWindow::CalCulateButtonClicked);
	connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::OpenFile);
	connect(ui->actionSave, &QAction::triggered, this, &MainWindow::CalCulateButtonClicked);
	connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::CalCulateButtonClicked);
	connect(ui->actionExit, &QAction::triggered, this, &MainWindow::CalCulateButtonClicked);
	connect(ui->actionExportOBJ, &QAction::triggered, this, &MainWindow::ExportOBJ);

}

void MainWindow::CalCulateButtonClicked(){
	QString el_str,ml_str,th_str,gh_str,mw_str,ew_str;
	
	el_str = ui->lineEdit_el->text();
	ml_str = ui->lineEdit_ml->text();
	th_str = ui->lineEdit_th->text();
	gh_str = ui->lineEdit_gh->text();
	mw_str = ui->lineEdit_mw->text();
	ew_str = ui->lineEdit_ew->text();
	if (el_str.isEmpty() || ml_str.isEmpty() || th_str.isEmpty() || gh_str.isEmpty() || mw_str.isEmpty() || ew_str.isEmpty())
	{
		QMessageBox::warning(this, "Error", "测量参数都不能空");
		return;
	}
	bool isok = 0;
	int countok  = 0;
	el = el_str.toDouble(&isok);
	countok += isok;
	ml = ml_str.toDouble(&isok);
	countok += isok;
	th = th_str.toDouble(&isok);
	countok += isok;
	gh = gh_str.toDouble(&isok);
	countok += isok;
	mw = mw_str.toDouble(&isok);
	countok += isok;
	ew = ew_str.toDouble(&isok);
	countok += isok;
	if (countok != 6)
	{
		QMessageBox::warning(this, "Error", "参数输入有误");
		return;
	}
	L = el;
	W = ew;
	H = th - 2.00 * gh;
	r = (el - ml) / 2.00;
	R = ((mw - ew)*(mw - ew) + ml*ml / 4.00) / (2.00*(mw - ew)) + (el - ml) / 2.00;
	ui->lineEdit_L->setText(QString::number(L));
	ui->lineEdit_W->setText(QString::number(W));
	ui->lineEdit_H->setText(QString::number(H));
	ui->lineEdit_r->setText(QString::number(r));
	ui->lineEdit_R->setText(QString::number(R));
}
void MainWindow::ShowModelButtonClicked(){
	QString L_str, W_str, H_str, r_str, R_str;
	L_str = ui->lineEdit_L->text();
	W_str = ui->lineEdit_W->text();
	H_str = ui->lineEdit_H->text();
	r_str = ui->lineEdit_r->text();
	R_str = ui->lineEdit_R->text();
	L = L_str.toDouble();
	W = W_str.toDouble();
	H = H_str.toDouble();
	r = r_str.toDouble();
	R = R_str.toDouble();
	if (L<0 || W<0 || H <0 || r<0 || R<0 || R_str.compare("inf") == 0)
	{
		QMessageBox::warning(this, "Error", "Antenna is illegal");
	}
	BuildAntenna();
}

void MainWindow::FileProtect(){

}

void MainWindow::WriteFile(){

}

void MainWindow::NewFile(){

}

void MainWindow::OpenFile(){
	// filepath = QFileDialog::getOpenFileName(this, tr("open file"), " ", tr("HWTX file(*.hwtx)"));
	Andu::AnduMeshReader reader;
	Caca::Mesh* pMesh = new Caca::Mesh();
	reader.Read(pMesh, "test.obj");
	antennaGLWidget->addGLList(1, pMesh);
}

void MainWindow::SaveFile(){

}

void MainWindow::SaveFileAs(){

}

void MainWindow::ExportOBJ(){
	
	std::ofstream out("test.obj");
	out << "g default" << std::endl;
	for (int i = 0;	i < vp.size(); i++)
	{
		out << "v " << vp[i].x << " " << vp[i].y << " " << vp[i].z << std::endl;
	}
	for (int i = 0; i < vn.size(); i++)
	{
		out << "vn " << vn[i].x << " " << vn[i].y << " " << vn[i].z << std::endl;
	}
	for (int i = 0; i < face.size(); i++)
	{
		out << "f " << face[i].idx1 << "//" << face[i].idx1 << " " << face[i].idx2 << "//" << face[i].idx2 << " " << face[i].idx3 << "//" << face[i].idx3 << std::endl;
	}
	out.close();

}

void MainWindow::Exit(){

}

void MainWindow::BuildAntenna(){
	vp.clear();
	vn.clear();
	face.clear();
	face_cnt = 4000;
	BuildButtom();
	Sweepping();
	SetNormal();
	SetFace();
	std::ofstream mtlout("tmp.mtl");
	mtlout << "#tmp.mtl";
	mtlout.close();
	std::ofstream out("tmp.obj");
	out << "g default" << std::endl;
	for (int i = 0; i < vp.size(); i++)
	{
		out << "v " << vp[i].x << " " << vp[i].y << " " << vp[i].z << std::endl;
	}
	for (int i = 0; i < vn.size(); i++)
	{
		out << "vn " << vn[i].x << " " << vn[i].y << " " << vn[i].z << std::endl;
	}
	for (int i = 0; i < face.size(); i++)
	{
		out << "f " << face[i].idx1 << "//" << face[i].idx1 << " " << face[i].idx2 << "//" << face[i].idx2 << " " << face[i].idx3 << "//" << face[i].idx3 << std::endl;
	}
	out.close();
	antennaGLWidget->delAllGLList();
	Andu::AnduMeshReader reader;
	Caca::Mesh* pMesh = new Caca::Mesh();
	reader.Read(pMesh, "tmp.obj");
	antennaGLWidget->addGLList(1, pMesh);
	antennaGLWidget->updateGL();
}

void MainWindow::BuildButtom(){
	double rate = 10;
	for (double z = 0-r; z > 0 - r - W; z = z - W / rate){
		Vector3 tmp;
		tmp.x = 0;
		tmp.y = 0;
		tmp.z = z;
		vp.push_back(tmp);
	}
	double cx = r;
	double cz = 0 - (r + W);
	for (int x = 0; x < r; x++)
	{
		Vector3 tmp;
		tmp.x = x;
		tmp.y = 0;
		double t = r*r - (x - cx)*(x - cx);
		if (t != 0.00)
			tmp.z = 0 - sqrt(r*r - (x - cx)*(x - cx)) + cz;
		else
			tmp.z = cz;
		vp.push_back(tmp);
	}
	cx = (L+r+r) / 2.00;
	cz = sqrt(R*R - L*L / 4) - (W + r + r);
	for (double x = r; x < r+L; x = x + L/rate)
	{
		Vector3 tmp;
		tmp.x = x;
		tmp.y = 0;
		tmp.z = 0-sqrt(R*R - (x - cx)*(x - cx)) + cz;
		vp.push_back(tmp);
	}
	cx = r + L;
	cz = 0 - (r + W);
	for (double x = r+L; x < r + L + r; x++)
	{
		Vector3 tmp;
		tmp.x = x;
		tmp.y = 0;
		double t = r*r - (x - cx)*(x - cx);
		if (t != 0.00)
			tmp.z = 0 - sqrt(r*r - (x - cx)*(x - cx)) + cz;
		else
			tmp.z = cz;
		vp.push_back(tmp);
	}
	for (double z = 0-r-W; z < 0-r; z = z + W / rate){
		Vector3 tmp;
		tmp.x = r+r+L;
		tmp.y = 0;
		tmp.z = z;
		vp.push_back(tmp);
	}
	cx = r + L;
	cz = 0 - r;
	for (double x = r + L + r; x >  L + r; x--)
	{
		Vector3 tmp;
		tmp.x = x;
		tmp.y = 0;
		double t = r*r - (x - cx)*(x - cx);
		if (t != 0.00)
			tmp.z = sqrt(r*r - (x - cx)*(x - cx)) + cz;
		else
			tmp.z = cz;
		vp.push_back(tmp);
	}
	for (double x = r + L; x > r; x = x - L / rate){
		Vector3 tmp;
		tmp.x = x;
		tmp.y = 0;
		tmp.z = 0;
		vp.push_back(tmp);
	}
	cx = r ;
	cz = 0 - r;
	for (double x = r ; x >= 0 ; x--)
	{
		Vector3 tmp;
		tmp.x = x;
		tmp.y = 0;
		tmp.z = sqrt(r*r - (x - cx)*(x - cx)) + cz;
		vp.push_back(tmp);
	}
	h_cnt = vp.size();
}

void MainWindow::Sweepping(){
	double rate = 10;
	v_cnt = 2;
	for (int i = 1; i < H/rate; i++)
	{
		for (int j = 0; j < h_cnt; j++)
		{
			Vector3 tmp = vp[j];
			tmp.y = rate*i;
			vp.push_back(tmp);
		}
		v_cnt += 1;
	}
	for (int j = 0; j < h_cnt; j++)
	{
		Vector3 tmp = vp[j];
		tmp.y = H;
		vp.push_back(tmp);
	}
}
void MainWindow::SetNormal(){
	for (int i = 0; i < h_cnt; i++)
	{
		Vector3 tmp, a, b;
		a.x = vp[h_cnt + i].x - vp[i].x;
		a.y = vp[h_cnt + i].y - vp[i].y;
		a.z = vp[h_cnt + i].z - vp[i].z;
		b.x = vp[(i + 1) % h_cnt].x - vp[i].x;
		b.y = vp[(i + 1) % h_cnt].y - vp[i].y;
		b.z = vp[(i + 1) % h_cnt].z - vp[i].z;
		tmp.x = a.y*b.z - a.z*b.y;
		tmp.y = a.z*b.x - a.x*b.z;
		tmp.z = a.x*b.y - a.y*b.x;
		vn.push_back(tmp);
	}
	for (int i = 1; i < v_cnt; i++)
	{
		for (int j = 0; j < h_cnt; j++)
		{
			vn.push_back(vn[j]);
		}
	}
}
void MainWindow::SetFace(){
	for (int i = 1; i < v_cnt; i++)
	{
		for (int j = 0; j < h_cnt; j++)
		{
			FaceVec tmp;
			tmp.idx3 = j + (i - 1)*h_cnt + 1 ;
			tmp.idx2 = (j + 1) % h_cnt + (i - 1)*h_cnt + 1;
			tmp.idx1 = j + i*h_cnt + 1;
			face.push_back(tmp);
		}
		for (int j = 0; j < h_cnt; j++)
		{
			FaceVec tmp;
			tmp.idx3 = j + i*h_cnt + 1;
			tmp.idx1 = (j + 1) % h_cnt + i*h_cnt + 1;
			tmp.idx2 = (j + 1) % h_cnt + (i - 1)*h_cnt + 1;
			face.push_back(tmp);
		}
	}
}
MainWindow::~MainWindow()
{
    delete ui;
}
