//2009-2-24 19:29:34 by holybang
#ifndef SANDBOXGLWIDGET_H
#define SANDBOXGLWIDGET_H

#include <QGLWidget>
#include <QMenu>
#include <QPoint>

#include <list>
#include <vector>
#include "Mathematics.h"
#include "Line.h"

using std::list;
using std::vector;

class SandboxGLWidget : public QGLWidget
{
Q_OBJECT

public:
	SandboxGLWidget(QWidget *parent = NULL);
	~SandboxGLWidget();
	QMenu* GetMenu();
	QMatrix4x4 getProjectMulModelViewMatrix();
	void getProjectMulModelViewMatrix(double* d);
	QRect getViewport();

	Matrix4 getModelViewMatrix();
	void setModelViewMatrix(const Matrix4& mat);
	void mulModelViewMatrix(const Matrix4& mat);
	void rotateModelView(double rx, double ry, double rz,
		double ax, double ay, double az);
	void rotateModelView(double rx, double ry, double rz);

	void unProject(int x, int y, double *wx, double *wy, double *wz, 
		double shiftx = 0, double shifty = 0, double z = -1.0);
	Vector3 unProject(QPoint pos, double z = -1.0);
	void project(int *x, int *y, double wx, double wy, double wz, double* z = 0);
	void project(double *x, double *y, double wx, double wy, double wz, double *z = 0);
	double project(double l);
	Vector2 project(Vector3 v, double* z = 0);
	double unProject(double l);
	void getRotateAxis(double startx, double starty, double x, double y, double *out);
	Line getMousePressedDirLine(QPoint p);
	
	void rotateModelView(double angle, Vector3 axis);

	void initDefaultLighting();

	void getProjectionParams(vector<double>& vec);
	void setProjectionParams(const vector<double>& vec);
	void setProjection(const vector<double>& paramVec, const QRect& viewportRect);

	void backupGLMatrix();
	void restoreGLMatrix();

	void intoScreenDrawingMode();

protected:
	void resizeGL(int width, int height);
	void paintGL();
	void initializeGL();
	void drawCross(double w);
	void drawAxis();
	void drawCircle(Vector3 o, double r, Vector3 norm, int prec);
	void drawFinestCircle(Vector3 o, double r, Vector3 norm);
	bool moving();

	virtual void changeEvent ( QEvent * event );
	virtual bool event(QEvent * event);
	virtual void enterEvent(QEvent *event);
	virtual void leaveEvent(QEvent *event);
	virtual void mouseMoveEvent ( QMouseEvent * event );
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void resizeEvent(QResizeEvent* event);

	void callGLLists();

	void updateProjection();
	void repairHWRatio(QSizeF tarSize);
	void staticScene(QSizeF tarSize);

	QMenu *pMenu;
	bool m_movingFlag;
	bool m_doubleMovingFlag;
	double m_ox, m_oy, m_oz, rx, ry, rz;
	QPoint m_prePos;
	double m_sceneWidth, m_sceneHeight;
	float mat_specular[4];	//π‚’’≤Œ ˝
	float mat_shininess;
	float light_position[4] ;
	float white_light[4] ;
	float lmodel_ambient[4] ;
	float black_light[4] ;
	float spot_direction[3] ;

	list<int> m_glListIdxList;

	int m_preViewport[4];

	//
	int m_axisLength;
	int m_axisArrowRadius;

	bool m_isWinSizeGetted;

private:
	void initLightPara();
	void initLight();
	void checkWinWH();
	void initWinWH(QSize s);

private slots:
	void firstCreated();
//signals:
//	void mouseEntered(SandboxGLWidget *);
//	void mouseLeaved(SandboxGLWidget *);

protected:
	double pixelWidth();
	void drawSphereAt( double x, double y, double z, 
		double r = 3.0, int row = 10, int column = 10 );
};

#endif