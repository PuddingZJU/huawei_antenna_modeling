#include "Vector2Cmp.h"

Vector2Cmp::Vector2Cmp()
{

}

Vector2Cmp::Vector2Cmp( const Vector2& v )
	: m_v(v.x, v.y)
{

}

bool Vector2Cmp::operator<( const Vector2Cmp& v ) const
{
	const double &x = m_v.x;
	const double &y = m_v.y;
 	if(x - v.v().x < -M_LOW_TOLERANCE) {
 		return true;
	} else if(x - v.v().x > M_LOW_TOLERANCE) {
		return false;
 	} else if(y - v.v().y < -M_LOW_TOLERANCE) {
 		return true;
	} else if(y - v.v().y > M_LOW_TOLERANCE) {
		return false;
 	} else {
 		return false;
 	}
}
 
bool Vector2Cmp::operator==( const Vector2Cmp& v ) const
{
	const double &x = m_v.x;
	const double &y = m_v.y;
 	return abs(x - v.v().x) < M_LOW_TOLERANCE && abs(y - v.v().y) < M_LOW_TOLERANCE;
}
 
bool Vector2Cmp::operator>=( const Vector2Cmp& v ) const
{
 	return !(*this < v);
}

void Vector2Cmp::operator=( const Vector2Cmp& v )
{
	m_v = v.v();
}



