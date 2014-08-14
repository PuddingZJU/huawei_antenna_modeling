#ifndef COMPUTEVECTOR_H
#define COMPUTEVECTOR_H

#include "Mathematics.h"
#include <vector>

using std::vector;

enum Axis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS
};

class ComputeVector
{
public:

	Vector3 Interpolate2P(const Vector3& vBase,const Vector3& vRef, 
		const Vector3& vP1, const Vector3& vP2);

	Vector3 Interpolate3P(const Vector3& vBase,const Vector3& vP1, 
		const Vector3& vP2);

	Vector3 InterpolateEllipse(const Vector3& v1, const Vector3& v2,
		double theta, Axis axis = X_AXIS);

	//       2    *
	//      /    /
	//     1    b
	Vector3 ParallelP(const Vector3& vBase,const Vector3& vP1, 
		const Vector3& vP2);


	//     r------b--*
	Vector3 TipPoint(const Vector3& vBase,const Vector3& vRef);

	//     r----*----b
	Vector3 MidPoint(const Vector3& vBase,const Vector3& vRef);

	static Matrix4 OrthoProject(int a, int b, int x = 0, int y = 0, int z = 0);

	static Matrix4 PlaneTransform(Vector3 vb1, Vector3 vb2, 
		Vector2 pb1, Vector2 pb2);

	static Vector3 ComputeAngle(int lon, int lat);

	//check if p0 is in triangle (p1, p2, p3)
	static bool IsInTriangle(const Vector3& p0, const Vector3& p1, 
		const Vector3& p2, const Vector3& p3);

	static Vector3 Intersection(const Vector3& p0, const Vector3& n0,
		const Vector3& p1, const Vector3& p2, const Vector3& p3);

	static Vector3 Intersection(const Vector3& p0, const Vector3& n0,
		const Vector3& n, const Vector3& p);

	static double PlaneRotate( const Vector2& ps1, const Vector2& ps2, 
		const Vector2& pt1, const Vector2& pt2);

	static double PlaneRotate( Vector2 vs0, Vector2 vt0);

	static double AreaOfTriangle( Vector3 v1, Vector3 v2, Vector3 v3 );

	//vs and vt should be normalized
	static Quaternion ComputeRotation( const Vector3& vs, const Vector3& vt );

	static Vector2 ProjectVector(const Vector3& vec, const Quaternion& ort);

	//check if p4 is coplane with (p1, p2, p3)
	static bool coPlane(const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector3& p4 );

	static bool coLine(const Vector3& p1, const Vector3& p2, const Vector3& p3);

	static int findVector2(const vector<Vector2> &vec, const Vector2& v);

	//vec must contains 3 Vector3
	static Vector3 planeNorm(const vector<Vector3>& vec);
	static Vector3 planeNorm(const Vector3& p0, const Vector3& p1, const Vector3& p2);

	static double pointLineDistance(const Vector3& o, const Vector3& n,
		const Vector3& p);
	static double pointPlaneDistance(const Vector3& p, const Vector3& o,
		const Vector3& n);
	static double pointPlaneDistance(const Vector3& p, 
		const Vector3& p0, const Vector3& p1, const Vector3& p2,
		Vector3* ip = 0);

	static Vector3 planePerpendicularFoot(const Vector3& p,
		const Vector3& o, const Vector3& n);
	static Vector3 planePerpendicularFoot(const Vector3& p,
		const Vector3& p0, const Vector3& p1, const Vector3& p2);

	static Quaternion fromTwoVec(const Vector3& v0, const Vector3& v1);

	static void updateMaxV(const Vector3& v, Vector3& maxv);

	static void updateMinV(const Vector3& v, Vector3& minv);

	static double angle( Vector2 s, Vector2 e );
	static double angleX( Vector2 );

	static Vector2 toViewPoint(Matrix4 mat);

	static double interpolate(Vector2 v0, Vector2 v1, Vector2 v2,
		double d0, double d1, double d2, Vector2 v3);
	static double interpolate(Vector3 v0, Vector3 v1, Vector3 v2,
		double t0, double t1, double t2, Vector3 v3);
	static Vector2 interpolate(Vector2 v0, Vector2 v1, Vector2 v2,
		Vector2 t0, Vector2 t1, Vector2 t2, Vector2 v3);
	static Vector2 interpolate(Vector3 v0, Vector3 v1, Vector3 v2,
		Vector2 t0, Vector2 t1, Vector2 t2, Vector3 v3);
};


#endif //COMPUTEVECTOR_H