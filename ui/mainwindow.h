#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AnduGLWidget.h"
namespace Ui {
class MainWindow;
}
struct FaceVec
{
	int idx1, idx2, idx3;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	Andu::AnduGLWidget *antennaGLWidget;
	
	vector<Vector3> vp;
	vector<Vector3> vn;
	vector<FaceVec> face;
	int h_cnt, v_cnt,face_cnt;
	double el, ml, th, gh, mw, ew, L, W, H, r, R;
private:
    Ui::MainWindow *ui;
	QString filepath;
	void CalCulateButtonClicked();
	void ShowModelButtonClicked();
	void NewFile();
	void OpenFile();
	void SaveFile();
	void SaveFileAs();
	void ExportOBJ();
	void Exit();
	void FileProtect();
	void WriteFile();
	void ReadFile();
	void BuildButtom();
	void Sweepping();
	void SetNormal();
	void SetFace();
	void BuildAntenna();
};

#endif // MAINWINDOW_H
