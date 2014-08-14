#ifndef Vector3Cmp_h__
#define Vector3Cmp_h__

#include "Mathematics.h"

#define VECTOR3CMP_TOLERANCE M_LOW_TOLERANCE

class Vector3Cmp
{
	friend class Vector3Cmp;
public:
	Vector3Cmp()
	{}
	Vector3Cmp(const Vector3& v)
		: m_v(v)
	{}
	bool operator < (const Vector3Cmp& v) const
	{
		const double& x = m_v.x;
		const double& y = m_v.y;
		const double& z = m_v.z;
		if(x - v.m_v.x < -VECTOR3CMP_TOLERANCE) {
			return true;
		} else if(x - v.m_v.x > VECTOR3CMP_TOLERANCE) {
			return false;
		} else if(y - v.m_v.y < -VECTOR3CMP_TOLERANCE) {
			return true;
		} else if(y - v.m_v.y > VECTOR3CMP_TOLERANCE) {
			return false;
		} else if(z - v.m_v.z < -VECTOR3CMP_TOLERANCE) {
			return true;
		} else if(z - v.m_v.z > VECTOR3CMP_TOLERANCE) {
			return false;
		} else {
			return false;
		}
	}
	const Vector3& v() const { return m_v; }
protected:
	Vector3 m_v;

private:
};

#endif // Vector3Cmp_h__
