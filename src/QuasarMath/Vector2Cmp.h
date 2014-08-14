 #ifndef Vector2Cmp_h__
 #define Vector2Cmp_h__
 
 #include "Mathematics.h"

class Vector2Cmp
{
public:
	Vector2Cmp();
	Vector2Cmp(const Vector2& v);
	bool operator < (const Vector2Cmp& v) const;
	bool operator == (const Vector2Cmp& v) const;
	bool operator >= (const Vector2Cmp& v) const;
	void operator = (const Vector2Cmp& v);
	const Vector2& v() const { return m_v; }
	void setX(double x) { m_v.x = x; }
	void setY(double y) { m_v.y = y; }
protected:
	Vector2 m_v;

private:
};


 #endif // Vector2Cmp_h__
