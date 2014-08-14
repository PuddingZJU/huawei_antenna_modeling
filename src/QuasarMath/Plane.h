/** @file 
* @brief  数学库
* @author 赵洪德
* @date 2008-10-29
* @version 0.1
*
* 面的方法
*/

#ifndef _mathematics_h_
#error "Dont include Plane directly!!! Use Mathematics.h instead."
#endif

inline Plane::Plane()
{}

// copy by hand avoids call to Vector3::operator=(...)
inline Plane::Plane(const Vector3& _n, double _d)
{
	a = _n.x; b = _n.y; c = _n.z; d = _d;
}

inline Plane::Plane(double _a, double _b, double _c, double _d)
{
	a = _a; b = _b; c = _c; d = _d;
}

inline Plane::Plane(double* other)
{
	a = other[0]; b = other[1]; c = other[2]; d = other[3];
}

inline Plane::Plane(const Plane& other)
{
	a = other.a; b = other.b; c = other.c; d = other.d;
}

// Assignment

inline Plane& Plane::operator=(const Plane& other)
{
	a = other.a; b = other.b; c = other.c; d = other.d;
	return *this;
}

inline void Plane::Assign(const Vector3& _n, double _d)
{
	a = _n.x; b = _n.y; c = _n.z; d = _d;
}

inline void Plane::Assign(double _a, double _b, double _c, double _d)
{
	a = _a; b = _b; c = _c; d = _d;
}

inline void Plane::Assign(double* other)
{
	a = other[0]; b = other[1]; c = other[2]; d = other[3];
}

inline void Plane::Assign(const Plane& other)
{
	a = other.a; b = other.b; c = other.c; d = other.d;
}

// Functions

inline double Plane::Distance(const Vector3& v) const
{
	//return n.Dot(v) - d;
	//edit by jinbingwen 2009-7-13 20:33:44
	double ret = n.Dot(v) - d;
	if(ret < 0){
		ret = -ret;
	}
	return ret;
}

inline void Plane::Transform(const Matrix4& mat)
{
  const double* m = mat.M;
  double fx = a;
  double fy = b;
  double fz = c;
  double fw = d;
  a = m[0] * fx + m[4] * fy + m[8] * fz + m[12] * fw;
  b = m[1] * fx + m[5] * fy + m[9] * fz + m[13] * fw;
  c = m[2] * fx + m[6] * fy + m[10] * fz + m[14] * fw;
  d = m[3] * fx + m[7] * fy + m[11] * fz + m[15] * fw;
}

inline void Plane::Transform(const Matrix4& mat, const Plane& other)
{
  const double* m = mat.M;
  double fx = other.a;
  double fy = other.b;
  double fz = other.c;
  double fw = other.d;
  a = m[0] * fx + m[4] * fy + m[8] * fz + m[12] * fw;
  b = m[1] * fx + m[5] * fy + m[9] * fz + m[13] * fw;
  c = m[2] * fx + m[6] * fy + m[10] * fz + m[14] * fw;
  d = m[3] * fx + m[7] * fy + m[11] * fz + m[15] * fw;
}
