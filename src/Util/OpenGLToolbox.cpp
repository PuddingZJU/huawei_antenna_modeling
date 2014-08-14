#include "OpenGLToolbox.h"
#include "ArrayToolBox.h"
#include <QGLWidget>
#include <GL\glut.h>

void OpenGLToolbox::genViewportMatrix(int viewport[4], double viewportmatrix[16])
{
	ArrayToolBox<double>::setArray(viewportmatrix, 16, 0);
	int& w = viewport[2];
	int& h = viewport[3];
	int& vx = viewport[0];
	int& vy = viewport[1];
	viewportmatrix[0] = w/2.0;
	viewportmatrix[3] = vx + w/2.0;
	viewportmatrix[5] = h/2.0;
	viewportmatrix[7] = vy + h/2.0;
	viewportmatrix[10] = 0.5;
	viewportmatrix[11] = 0.5;
	viewportmatrix[15] = 1.0;
}

void OpenGLToolbox::print_bitmap_string( void* font, char* s )
{
	if (s && strlen(s)) {
		while (*s) {
			glutBitmapCharacter(font, *s);
			s++;
		}
	}
}

void OpenGLToolbox::drawStrs( vector<Vector2>& posVec, char** s )
{
	for(int i = 0; i < posVec.size(); i++) {
		drawStr(posVec[i], s[i]);
	}
}

void OpenGLToolbox::drawStr( Vector2 pos, char* s )
{
	glRasterPos2f(pos.x, pos.y);
	print_bitmap_string(GLUT_BITMAP_9_BY_15, s);
}


void OpenGLToolbox::unProject(int x, int y, double *wx, double *wy, double *wz
	, double shiftx, double shifty, double z)
	//将屏幕坐标转换成3D空间坐标，取远裁剪面和近裁剪面上的点的连线的中点
{
	GLint viewport[4];
	double tx0,ty0,tz0,tx1,ty1,tz1;
	double mvmatrix[16], projmatrix[16];

	x += shiftx;
	y += shifty;
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
	y = viewport[3]-(GLint)y;
	if(z >= 0) {
		gluUnProject((double)x, (double)y, z, mvmatrix, projmatrix, viewport, &tx0, &ty0, &tz0);
		*wx = tx0;
		*wy = ty0;
		*wz = tz0;	
	} else {
		gluUnProject((double)x, (double)y, 0, mvmatrix, projmatrix, viewport, &tx0, &ty0, &tz0);
		gluUnProject((double)x, (double)y, 1.0, mvmatrix, projmatrix, viewport, &tx1, &ty1, &tz1);
		*wx = (tx0+tx1)/2;
		*wy = (ty0+ty1)/2;
		*wz = (tz0+tz1)/2;
	}	
}

Vector3 OpenGLToolbox::unProject( QPoint pos, double z /*= -1.0*/ )
{
	Vector3 ret;
	unProject(pos.x(), pos.y(), &ret.x, &ret.y, &ret.z, 0, 0, z);
	return ret;
}

double OpenGLToolbox::unProject( double l )
{
	QPoint sv0, sv1(l, 0);
	Vector3 ov0 = unProject(sv0);
	Vector3 ov1 = unProject(sv1);
	return ov0.Distance(ov1);
}

void OpenGLToolbox::project(int *px, int *py,
	double wx, double wy, double wz, double *pz /*= 0*/)
{
	double x, y, z;
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
	gluProject(wx, wy, wz, mvmatrix, projmatrix, viewport, &x, &y, &z);
	y = viewport[3]-(int)(y);
	*px = (int)x;
	*py = (int)y;
	if(pz) {
		*pz = z;
	}
}

void OpenGLToolbox::project( double *px, double *py,
	double wx, double wy, double wz, double *pz )
{
	double x, y, z;
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
	gluProject(wx, wy, wz, mvmatrix, projmatrix, viewport, &x, &y, &z);
	y = viewport[3]-(int)(y);
	*px = x;
	*py = y;
	if(pz) {
		*pz = z;
	}
}

double OpenGLToolbox::project( double l, Vector3 v/* = Vector3()*/ )
{
	double depth;
	Vector2 pv0 = project(v, &depth);	
	QPoint sv0(pv0.x, pv0.y), sv1(1.0 + pv0.x, pv0.y);
	Vector3 ov0 = unProject(sv0, depth);
	Vector3 ov1 = unProject(sv1, depth);
	return l/ov0.Distance(ov1);
}

Vector2 OpenGLToolbox::project( Vector3 v, double *z /*= 0*/ )
{
	Vector2 ret;
	project(&ret.x, &ret.y, v.x, v.y, v.z, z);
	return ret;
}
