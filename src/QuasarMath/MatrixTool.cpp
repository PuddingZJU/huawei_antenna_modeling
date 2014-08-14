#include "matrixtool.h"

Matrix3 RotateMatrix3( double a, Vector3 raxis )
{
	Vector3 u = raxis;
	u.Normalize();
	Matrix3 S;
	S.m[0][0] = 0;
	S.m[0][1] = -u.z;
	S.m[0][2] = u.y;
	S.m[1][0] = u.z;
	S.m[1][1] = 0;
	S.m[1][2] = -u.x;
	S.m[2][0] = -u.y;
	S.m[2][1] = u.x;
	S.m[2][2] = 0;
	Matrix3 M;
	Matrix3 I;
	I.SetIdentity();
	Matrix3 uut(u.x*u.x, u.x*u.y, u.x*u.z, u.x*u.y, u.y*u.y, u.z*u.y, u.x*u.z, u.y*u.z, u.z*u.z);
	M = uut;
	I.Add(uut.Mul(-1.0));
	I.Mul(CosD(a));
	M.Add(I);
	
	S.Mul(SinD(a));

	M.Add(S);

	//M.Add(I.Add(uut.Mul(-1.0)).Mul(CosD(a))).Add(S.Mul(SinD(a)));
	return M;
}

Matrix3 RotateMatrix3( double thetax, double thetay, double thetaz )
{
	Matrix3 rx = RotateMatrix3(thetax, Vector3(1.0, 0, 0));
	Matrix3 ry = RotateMatrix3(thetay, Vector3(0, 1.0, 0));
	Matrix3 rz = RotateMatrix3(thetaz, Vector3(0, 0, 1.0));
	return rx*ry*rz;
}

Matrix4 RotateMatrix4( double a, Vector3 raxis )
{
	Matrix3 src = RotateMatrix3(a, raxis);
	Matrix4 ret;
	ret.SetIdentity();
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			ret.m[i][j] = src.m[i][j];
		}
	}
	return ret;
}

Matrix4 TranslateMatrix4( Vector3 t )
{
	Matrix4 ret;
	ret.SetIdentity();
	ret.m[0][3] = t.x;
	ret.m[1][3] = t.y;
	ret.m[2][3] = t.z;
	return ret;
}

Matrix3 TransposeMatrix3( Matrix3 m )
{
	Matrix3 ret;
	ret.m[0][0] = m.m[0][0];
	ret.m[0][1] = m.m[1][0];
	ret.m[0][2] = m.m[2][0];
	ret.m[1][0] = m.m[0][1];
	ret.m[1][1] = m.m[1][1];
	ret.m[1][2] = m.m[2][1];
	ret.m[2][0] = m.m[0][2];
	ret.m[2][1] = m.m[1][2];
	ret.m[2][2] = m.m[2][2];
	return ret;
}

Matrix4 TransposeMatrix4( Matrix4 m )
{
	Matrix4 ret;
	ret.m[0][0] = m.m[0][0];
	ret.m[0][1] = m.m[1][0];
	ret.m[0][2] = m.m[2][0];
	ret.m[0][3] = m.m[3][0];
	ret.m[1][0] = m.m[0][1];
	ret.m[1][1] = m.m[1][1];
	ret.m[1][2] = m.m[2][1];
	ret.m[1][3] = m.m[3][1];
	ret.m[2][0] = m.m[0][2];
	ret.m[2][1] = m.m[1][2];
	ret.m[2][2] = m.m[2][2];
	ret.m[2][3] = m.m[3][2];
	ret.m[3][0] = m.m[0][3];
	ret.m[3][1] = m.m[1][3];
	ret.m[3][2] = m.m[2][3];
	ret.m[3][3] = m.m[3][3];
	return ret;

}

Matrix3 TransposeMul3( Matrix3 m1, Matrix3 m2 )
{
	Matrix3 ret;
	const double *a = m1.M;              //矩阵m1赋给b
	const double *b = m2.M;              //矩阵m2赋给a
	double *prod = ret.M;

	for(int i = 0; i < 9; i += 3)          //执行a[9]和b[9]相乘,结果存在prod[9]中
	{
		double a0 = a[i];
		double a1 = a[i + 1];
		double a2 = a[i + 2];
		prod[i]     = a0 * b[0] + a1 * b[1] + a2 * b[2];
		prod[i + 1] = a0 * b[3] + a1 * b[4] + a2 * b[5];
		prod[i + 2] = a0 * b[6] + a1 * b[7] + a2 * b[8];
	}
	return ret;
}
