#ifndef OpenGLToolbox_h__
#define OpenGLToolbox_h__

#include "Mathematics.h"
#include <vector>
#include <QPoint>

using namespace std;

class OpenGLToolbox
{
public:
	static void genViewportMatrix(int viewport[4], double viewportmatrix[16]);

	static void drawStr(Vector2 pos, char* s);
	static void drawStrs( vector<Vector2>& posVec, char** s);
	static void print_bitmap_string( void* font, char* s );

	static void OpenGLToolbox::unProject(int x, int y, 
		double *wx, double *wy, double *wz
		, double shiftx, double shifty, double z);
	static Vector3 OpenGLToolbox::unProject( QPoint pos, double z = -1.0 );
	static double OpenGLToolbox::unProject( double l );
	static void OpenGLToolbox::project(int *px, int *py,
		double wx, double wy, double wz, double *z = 0);
	static void OpenGLToolbox::project( double *px, double *py,
		double wx, double wy, double wz, double *pz = 0 );
	static double OpenGLToolbox::project( double l, Vector3 v = Vector3() );
	static Vector2 OpenGLToolbox::project( Vector3 v, double* z = 0 );
};

#endif //OpenGLToolbox_h__