//2009-2-24 19:29:21 by holybang

#include "SandboxGLWidget.h"
#include "ArrayToolBox.h"
#include <QMouseEvent>
#include <QTimer>
#include <math.h>
#include <GL\glu.h>
#include <GL\glut.h>
#include "Mathematics.h"
#include "OpenGLToolbox.h"
#include "MatrixTool.h"
#include "OpenGLToolbox.h"
#include <QMatrix4x4>

double lightPosition[4], whiteLight[4], blackLight[4];

SandboxGLWidget::SandboxGLWidget(QWidget *parent)
: QGLWidget(QGLFormat(QGL::DoubleBuffer | QGL::Rgba | QGL::AccumBuffer | QGL::StencilBuffer), parent)
, pMenu(NULL)
, m_movingFlag(false)
, m_doubleMovingFlag(false)
, m_ox(0)
, m_oy(0)
, m_oz(0)
, rx(0)
, ry(0)
, rz(0)
, m_sceneWidth(800)
, m_sceneHeight(600)
, m_axisLength(20)
, m_axisArrowRadius(10)
, m_isWinSizeGetted(false)
{
	m_preViewport[0] = 0;
	m_preViewport[1] = 0;
	m_preViewport[2] = 100;
	m_preViewport[3] = 100;
	//setMinimumSize(400, 400);
}

SandboxGLWidget::~SandboxGLWidget()
{

}

void SandboxGLWidget::resizeGL(int w, int h)
{
	makeCurrent();

	//printf("resize gl\n");

	if(w*h < M_LOW_TOLERANCE) {
		return;
	}

	if(!m_isWinSizeGetted) {
		glViewport(0, 0, w, h);
		initWinWH(QSize(w, h));
		repairHWRatio(QSizeF(w, h));
		m_preViewport[0] = 0;
		m_preViewport[1] = 0;
		m_preViewport[2] = w;
		m_preViewport[3] = h;
		return;
	}

	double oldSceneWidth = m_sceneWidth;
	double oldSceneHeight = m_sceneHeight;
	
	m_sceneWidth = (double)w/m_preViewport[2]*m_sceneWidth;
	m_sceneHeight = (double)h/m_preViewport[3]*m_sceneHeight;
// 	m_ox = m_ox + (m_sceneWidth - oldSceneWidth)/2.0;
// 	m_oy = m_oy + (m_sceneHeight - oldSceneHeight)/2.0;

	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 

	updateProjection();

	m_preViewport[2] = w;
	m_preViewport[3] = h;
}

void SandboxGLWidget::paintGL()
{
	makeCurrent();

//	glDisable(GL_LIGHTING);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glLoadIdentity ();             /* clear the matrix */

	//glOrtho(0, imgW, 0, imgH, 0, 200);
	//glFrustum (0, 200, 0, 250, 0, 300);
	/* viewing transformation  */
	//gluLookAt (100, 125, 200, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//glScalef (1.0, 1.0, 1.0);      /* modeling transformation */ 

	//glutWireCube (1.0);
	
// 	glDisable(GL_LIGHTING);
// 	double width, height;
// 	width = winWidth;
// 	height = winHeight;
	drawAxis();
	drawCross(1.0);		
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	glOrtho(ox - width/2, ox + width/2, oy - height/2, oy + height/2, oz - 1000.0, oz + 1000.0);
// 	glBegin(GL_LINES);
// 		glColor3i(255, 255, 255);
// 		glVertex3d(-100, 0, 0);
// 		glVertex3d(100, 0, 0);
// 		glVertex3d(0, -100, 0);
// 		glVertex3d(0, 100, 0);
// 		glVertex3d(0, 0, -100);
// 		glVertex3d(0, 0, 100);
// 	glEnd();
// 	glEnable(GL_LIGHTING);
	//swapBuffers();

	initDefaultLighting();
	callGLLists();
	
}

void SandboxGLWidget::initializeGL()
{
	makeCurrent();

	printf("init gl\n");
	glClearColor(0.5, 0.5, 0.5, 0);
	initLight();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	updateProjection();

	//glGenLists(1);

	glEnable(GL_POINT_SMOOTH);
// 	glEnable(GL_LINE_SMOOTH);
// 	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );

// 	glEnable(GL_BLEND);
// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool SandboxGLWidget::moving()
{
	return m_movingFlag;
}

void SandboxGLWidget::firstCreated()
{
// 	m_winWidth = width();
// 	m_winHeight = height();
// 
// 	printf("init win width %d win height %d\n", m_winWidth, m_winHeight);
}

void SandboxGLWidget::drawCross(double w)
{	
	makeCurrent();

	glPushAttrib(GL_LIGHTING);
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	qglColor(Qt::gray);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(m_ox - m_sceneWidth/2, m_ox + m_sceneWidth/2, m_oy - m_sceneHeight/2, m_oy + m_sceneHeight/2, m_oz + 1000, m_oz - 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_LINES);
	if(glIsEnabled(GL_LIGHTING)){
		glNormal3d(lightPosition[0], lightPosition[1], lightPosition[2]);
	}
	glVertex3d(-w, 0, 0);
	glVertex3d(w, 0, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3d(0, -w, 0);
	glVertex3d(0, w, 0);
	glEnd();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
	glPopAttrib();
}

QMenu* SandboxGLWidget::GetMenu()
{
	if(pMenu){
		return pMenu;
	} else{
		pMenu = new QMenu;
		return pMenu;
	}
}

void SandboxGLWidget::changeEvent(QEvent * event )
{

}

bool SandboxGLWidget::event(QEvent * event)
{
	return QGLWidget::event(event);
}

void SandboxGLWidget::enterEvent(QEvent *event)
{
	//emit mouseEntered(this);
}

void SandboxGLWidget::leaveEvent(QEvent *event)
{
	//emit mouseLeaved(this);
}

void SandboxGLWidget::mouseMoveEvent(QMouseEvent * event)
{
	makeCurrent();

	QPoint pos = event->pos();
	QPoint deltaPos = pos;
	deltaPos -= m_prePos;

	if(!m_doubleMovingFlag && event->buttons() == Qt::LeftButton){	
		//移动
		//printf("translating\n");
		m_ox -= (double)deltaPos.x()/width() * m_sceneWidth;
		m_oy += (double)deltaPos.y()/height() * m_sceneHeight;		
		updateProjection();
	} else if(!m_doubleMovingFlag && event->buttons() == Qt::RightButton){
		//旋转
		//printf("rotating\n");
		double rotateAxis[3];
		getRotateAxis(m_prePos.x(), m_prePos.y(), pos.x(), pos.y(), rotateAxis);
		double angle = -1.0*sqrtf(deltaPos.x()*deltaPos.x() + deltaPos.y()*deltaPos.y())/width()*180.0;
		glMatrixMode(GL_MODELVIEW);
		glRotated(angle, rotateAxis[0], rotateAxis[1], rotateAxis[2]);				
	} else if(event->buttons() == (Qt::LeftButton | Qt::RightButton)){
		//缩放
		//printf("scaling\n");
		m_doubleMovingFlag = true;
		m_sceneWidth *= (double)deltaPos.y()/height() + 1.0;
		m_sceneHeight *= (double)deltaPos.y()/height() + 1.0;		
		//checkWinWH();
		updateProjection();
	}
	update();
	m_prePos = event->pos();
	m_movingFlag = true;
}

void SandboxGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	makeCurrent();

	if(!m_doubleMovingFlag && !m_movingFlag && event->button() == Qt::RightButton){
		GetMenu()->popup(mapToGlobal(event->pos()));
	}
	if(event->buttons() == Qt::NoButton){
		m_doubleMovingFlag = false;
	}
	m_movingFlag = false;
}

void SandboxGLWidget::mousePressEvent(QMouseEvent *event)
{
	makeCurrent();

	m_prePos = event->pos();
}

void SandboxGLWidget::getRotateAxis(double startx, double starty, double x, double y,
	double *out)
//根据鼠标移动的前后坐标获得3D空间中的转动轴
{
	makeCurrent();

	double d1[3], d2[3];
	int i;
	GLint viewport[4];
	double t0[3],t1[3],t2[3];
	double mvmatrix[16], projmatrix[16];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
	y = viewport[3]-(GLint)y-1;
	starty = viewport[3]-(int)starty-1;
	gluUnProject(startx, starty, 0, mvmatrix, projmatrix, viewport, t0, t0+1, t0+2);
	gluUnProject(startx, starty, 1.0, mvmatrix, projmatrix, viewport, t1, t1+1, t1+2);
	gluUnProject(x, y, 1.0, mvmatrix, projmatrix, viewport, t2, t2+1, t2+2);
	for(i=0; i<3; i++){
		d1[i] = t1[i]-t0[i];
		d2[i] = t2[i]-t0[i];
	}
	ArrayToolBox<double>::crossprod3(d1, d2, out);
	ArrayToolBox<double>::normalize(out, out);
}

void SandboxGLWidget::unProject(int x, int y, double *wx, double *wy, double *wz
	, double shiftx, double shifty, double z)
//将屏幕坐标转换成3D空间坐标，取远裁剪面和近裁剪面上的点的连线的中点
{
	makeCurrent();
	OpenGLToolbox::unProject(x, y, wx, wy, wz, shiftx, shifty, z);
}

Vector3 SandboxGLWidget::unProject( QPoint pos, double z /*= -1.0*/ )
{
	Vector3 ret;
	unProject(pos.x(), pos.y(), &ret.x, &ret.y, &ret.z, 0, 0, z);
	return ret;
}

double SandboxGLWidget::unProject( double l )
{
	QPoint sv0, sv1(l, 0);
	Vector3 ov0 = unProject(sv0);
	Vector3 ov1 = unProject(sv1);
	return ov0.Distance(ov1);
}

void SandboxGLWidget::project(int *px, int *py,
	double wx, double wy, double wz, double *z /*= 0*/)
{
	makeCurrent();
	OpenGLToolbox::project(px, py, wx, wy, wz, z);
}

void SandboxGLWidget::project( double *px, double *py,
	double wx, double wy, double wz, double *z /*= 0*/ )
{
	makeCurrent();
	OpenGLToolbox::project(px, py, wx, wy, wz, z);
}

double SandboxGLWidget::project( double l )
{
	QPoint sv0, sv1(1.0, 0);
	Vector3 ov0 = unProject(sv0);
	Vector3 ov1 = unProject(sv1);
	return l/ov0.Distance(ov1);
}

Vector2 SandboxGLWidget::project( Vector3 v, double *z /*= 0*/)
{
	Vector2 ret;
	project(&ret.x, &ret.y, v.x, v.y, v.z, z);
	return ret;
}

Line SandboxGLWidget::getMousePressedDirLine( QPoint p )
{
	Vector3 nearPos;
	unProject(p.x(), p.y(), &nearPos.x, &nearPos.y, &nearPos.z, 0, 0, -1.0);
	Vector3 farPos;
	unProject(p.x(), p.y(), &farPos.x, &farPos.y, &farPos.z, 0, 0, 1.0);
	return Line(nearPos, farPos);
}

void SandboxGLWidget::initLightPara()
{
	for(int i=0; i<4; i++){
		mat_specular[i] = 1.0;
		white_light[i] = 1.0;
		lmodel_ambient[i] = 1.0;
		black_light[i] = 0;
	}
	mat_shininess = 100.0;
	light_position[0] = 0;
	light_position[1] = 0;
	light_position[2] = 1000.0;
	light_position[3] = 0.0;
	spot_direction[0] = 0;
	spot_direction[1] = 0;
	spot_direction[2] = -1.0;
}

void SandboxGLWidget::initLight()
{
	makeCurrent();

	initLightPara();
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, black_light);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &mat_shininess);
	glEnable(GL_NORMALIZE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void SandboxGLWidget::checkWinWH()
{
	if(m_sceneHeight <= 10.0){
		m_sceneHeight = 10.0;
		m_sceneWidth = (double)width()/height() * 10.0;
	}
	if(m_sceneWidth <= 10.0){
		m_sceneWidth = 10.0;
		m_sceneHeight = (double)height()/width() * 10.0;
	}
}

void SandboxGLWidget::drawAxis()
{
	makeCurrent();

 	GLint viewport[4];
 	glGetIntegerv(GL_VIEWPORT,viewport);
 
 	glViewport(0,0,100,100);

 	glMatrixMode(GL_PROJECTION);
 	glPushMatrix();
 	glLoadIdentity();
 
 	glOrtho(-50,50,-50,50,-50,50);
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	//x axis
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(m_axisLength,0.0f,0.0f);
	//y axis
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,m_axisLength,0.0f);
	//z axis
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,m_axisLength);
	glEnd();

	GLubyte bitX[12] = {0x00,0xe7,0x42,0x24,0x24,0x18,0x18,0x18,0x24,0x24,0x42,0xe7};
	GLubyte bitY[12] = {0x00,0x38,0x10,0x10,0x10,0x10,0x10,0x28,0x28,0x44,0x44,0xee};
	GLubyte bitZ[12] = {0x00,0xfc,0x42,0x42,0x20,0x20,0x10,0x08,0x08,0x04,0x84,0x7e};

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glColor3f(1.0f,0.0f,0.0f);
	glRasterPos3f(m_axisLength+m_axisArrowRadius+15.0f,10.0,0.0);
	glBitmap(8,12,0.0f,0.0f,10.0,15.0,bitX);

	glColor3f(0.0f,1.0f,0.0f);
	glRasterPos3f(0.0,m_axisLength+m_axisArrowRadius+15.0f,0.0);
	glBitmap(8,12,0.0f,0.0f,10.0,15.0,bitY);

	glColor3f(0.0f,0.0f,1.0f);
	glRasterPos3f(0.0,10.0,m_axisLength+m_axisArrowRadius+15.0f);
	glBitmap(8,12,0.0f,0.0f,10.0,15.0,bitZ);

	//z axis arrow
	glTranslatef(0.0f,0.0f,m_axisLength);
	//auxSolidCone(AxisArrowRadius,AxisArrowHeight);

	//y axis arrow
	glColor3f(0.0f,1.0f,0.0f);
	glTranslatef(0.0f,m_axisLength,-m_axisLength);
	glRotatef(-90.0f,1.0f,0.0f,0.0f);
	//auxSolidCone(AxisArrowRadius,AxisArrowHeight);

	//x axis arrow
	glColor3f(1.0f,0.0f,0.0f);
	glTranslatef(m_axisLength,0.0f,-m_axisLength);
	glRotatef(90.0f,0.0f,1.0f,0.0f);
	//auxSolidCone(AxisArrowRadius,AxisArrowHeight);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	//restore viewport
	glViewport(viewport[0],viewport[1],viewport[2],viewport[3]);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void SandboxGLWidget::resizeEvent( QResizeEvent* event )
{
	printf("resize sandbox glwidget\n");
	resizeGL(event->size().width(), event->size().height());	
}

void SandboxGLWidget::updateProjection()
{
	makeCurrent();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(m_ox - m_sceneWidth/2, m_ox + m_sceneWidth/2, 
		m_oy - m_sceneHeight/2, m_oy + m_sceneHeight/2, 
		m_oz - 1000, m_oz + 1000.0);
}

void SandboxGLWidget::initWinWH(QSize s)
{
	m_sceneWidth = s.width()/10;
	m_sceneHeight = s.height()/10;
	m_isWinSizeGetted = true;

	printf("init win width %f win height %f\n", m_sceneWidth, m_sceneHeight);
}

void SandboxGLWidget::repairHWRatio(QSizeF tarSize)
{
	double tarRatio = tarSize.width()/tarSize.height();	
	m_sceneWidth = tarRatio*m_sceneHeight;
	updateProjection();
}

void SandboxGLWidget::staticScene(QSizeF tarSize)
{
	
}

void SandboxGLWidget::callGLLists()
{
	makeCurrent();

	list<int>::iterator iter = m_glListIdxList.begin();
	while(iter != m_glListIdxList.end()) {
		//printf("call gl list %d\n", *iter);
// 		if(glIsList(*iter)) {
// 			printf("is list\n");
// 		}
		glCallList(*iter);
		iter++;
	}
}

QMatrix4x4 SandboxGLWidget::getProjectMulModelViewMatrix()
{
	makeCurrent();

	double mvmatrix[16], projmatrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

	QMatrix4x4 qmvmatrix(mvmatrix);
	QMatrix4x4 qprojmatrix(projmatrix);
	return qprojmatrix;
}

void SandboxGLWidget::getProjectMulModelViewMatrix(double* d)
{
	makeCurrent();

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	double viewportmatrix[16];
	OpenGLToolbox::genViewportMatrix(viewport, viewportmatrix);

	double mvmatrix[16], projmatrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
	ArrayToolBox<double>::matrixTranspos(mvmatrix, 4);
	ArrayToolBox<double>::matrixTranspos(projmatrix, 4);

	double tmpmatrix[16];
	ArrayToolBox<double>::matrixMul44(viewportmatrix, projmatrix, tmpmatrix);
	ArrayToolBox<double>::matrixMul44(tmpmatrix, mvmatrix, d);
}

void SandboxGLWidget::backupGLMatrix()
{
	makeCurrent();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
}

void SandboxGLWidget::restoreGLMatrix()
{
	makeCurrent();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void SandboxGLWidget::intoScreenDrawingMode()
{
	makeCurrent();

	glViewport(0, 0, width(), height());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width(), height(), 0, 0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

QRect SandboxGLWidget::getViewport()
{
	makeCurrent();

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	return QRect(viewport[0], viewport[1], viewport[2], viewport[3]);
}

void SandboxGLWidget::drawCircle( Vector3 o, double r, Vector3 norm, int prec )
{
	makeCurrent();

	glPushAttrib(GL_LIGHTING | GL_LINE_BIT);
	glDisable(GL_LIGHTING);
	glLineWidth(1.0);
	qglColor(Qt::darkGray);

	glBegin(GL_LINE_LOOP);
	double astep = 360.0/prec;	
	Vector3 s;
	if(norm != Vector3::UNIT_SCALE) {
		s = Vector3::UNIT_SCALE;		
	} else {
		s = Vector3::UNIT_X;	
	}
	s.Cross(norm);
	s.Normalize();
	s *= r;
	for(int i = 0; i < prec; i++) {
		double a = astep*i;
		Vector3 p = RotateMatrix3(a, norm).Mul(s) + o;
		glVertex3d(p.x, p.y, p.z);
	}
	glEnd();

	glPopAttrib();
}

void SandboxGLWidget::drawFinestCircle( Vector3 o, double r, Vector3 norm )
{
	drawCircle(o, r, norm, 2.0*3.14*r/pixelWidth());
}

double SandboxGLWidget::pixelWidth()
{
	makeCurrent();

	double x1, y1, z1;
	unProject(0, 0, &x1, &y1, &z1, 0, 0);
	double x2, y2, z2;
	unProject(0, 1, &x2, &y2, &z2, 0, 0);
	return Vector3(x1, y1, z1).Distance(Vector3(x2, y2, z2));
}

void SandboxGLWidget::drawSphereAt( double x, double y, double z, double r /*= 3.0*/, int row /*= 10*/, int column /*= 10*/ )
{
	makeCurrent();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(x, y, z);
	glutSolidSphere(r, column, row);
	glPopMatrix();
}

void SandboxGLWidget::mulModelViewMatrix( const Matrix4& mat )
{
	makeCurrent();

	glMatrixMode(GL_MODELVIEW);
	glMultMatrixd(mat.M);	
}

void SandboxGLWidget::rotateModelView( double rx, double ry, double rz )
{
	
}

void SandboxGLWidget::rotateModelView( double rx, double ry, double rz, double ax, double ay, double az )
{

}

void SandboxGLWidget::setModelViewMatrix( const Matrix4& mat )
{
	makeCurrent();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixd(mat.M);
}

Matrix4 SandboxGLWidget::getModelViewMatrix()
{
	makeCurrent();

	Matrix4 mat;
	glGetDoublev(GL_MODELVIEW_MATRIX, mat.M);
	return mat;
}

void SandboxGLWidget::rotateModelView( double angle, Vector3 axis )
{
	makeCurrent();

	glMatrixMode(GL_MODELVIEW);
	glRotated(angle, axis.x, axis.y, axis.z);
}

void SandboxGLWidget::initDefaultLighting()
{
	makeCurrent();

	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);

	//光照 
	GLfloat lmodel_ambient[]={1.0,1.0,1.0,1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);

	GLfloat lightAmbient[] = {0.0f,0.0f,0.0f,0.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

	GLfloat lightDiffuse[] = {0.6f,0.6f,0.6f,0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

	Vector3 v(-0.3, -0.4, -0.9);
	v.Normalize();
	//  
	GLfloat lightPosition[] = {v.x,v.y,v.z,0.0f};

	bool dependModelview = false;
	bool dependProjection = true;
	if(!dependProjection) {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
	}	
	if(!dependModelview) {		
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	}
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	if(!dependProjection) {
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	}
	if(!dependModelview) {
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}	
}

void SandboxGLWidget::getProjectionParams( vector<double>& vec )
{
	vec.resize(5);
	vec[0] = m_ox;
	vec[1] = m_oy;
	vec[2] = m_oz;
	vec[3] = m_sceneWidth;
	vec[4] = m_sceneHeight;
}

void SandboxGLWidget::setProjectionParams( const vector<double>& vec )
{
	if(vec.size() < 5) {
		return;
	}
	m_ox = vec[0];
	m_oy = vec[1];
	m_oz = vec[2];
	m_sceneWidth = vec[3];
	m_sceneHeight = vec[4];
	updateProjection();
}

void SandboxGLWidget::setProjection( const vector<double>& paramVec, 
	const QRect& viewportRect )
{
	makeCurrent();

	if(paramVec.size() < 5) {
		return;
	}
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	m_sceneWidth = paramVec[3]/viewportRect.width()*viewport[2];
	m_sceneHeight = paramVec[4]/viewportRect.height()*viewport[3];
	m_ox = paramVec[0];
	m_oy = paramVec[1];
	m_oz = paramVec[2];

	updateProjection();
}
