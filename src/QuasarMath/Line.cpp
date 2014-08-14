#include "Line.h"
#include "..\src\corelib\global\qglobal.h"

Line::Line( Vector3 v1, Vector3 v2 )
{
	m_sp = v1;
	m_ep = v2;
	updateDir();
}

Line::Line( Vector2 v1, Vector2 v2 )
{
	m_sp.Assign(v1.x, v1.y, 0);
	m_ep.Assign(v2.x, v2.y, 0);
	updateDir();
}

/**
* @note		计算从点p到该线段的垂足。当该线段退化为一个点时返回零。
* @param	Vector3 p
* @return	Vector3
*/
Vector3 Line::PerpendicularFoot( Vector3 p )
{
	updateDir();
	return m_sp + m_n*(m_n.Dot(p - m_sp));
}

Vector3 Line::GetPoint( double t )
{
	return m_sp + m_n*t;
}

double Line::Distance( Vector3 p, DistanceRull rull )
{	
	Vector3 s2e = m_ep - m_sp;
	Vector3 s2p = p - m_sp;
	double linedis;
	if(s2e.Length() != 0) {
		linedis = sqrt(s2p.Dot(s2p)*s2e.Dot(s2e) - pow(s2p.Dot(s2e), 2)) / s2e.Length();
	} else {
		linedis = p.Distance(m_sp);
	}
	
	switch(rull){
		case NOSEGMENT_LINE:
			return linedis;
		case SEGMENT_LINE: 
			{
				Vector3 foot = PerpendicularFoot(p);
				double t = GetParameter(foot);
				if(t < 0){
					return p.Distance(m_sp);
				} else if(t > GetParameter(m_ep)){
					return p.Distance(m_ep);
				} else{
					return linedis;
				}
			}
		default:
			break;
	}	
	return -1.0;
}

bool Line::IsOnLine( Vector3 p )
{
	Vector3 foot = PerpendicularFoot(p);
	if(p.Distance(foot) <= M_LOW_TOLERANCE){
		return true;
	} else{
		return false;
	}
}

double Line::GetParameter( Vector3 p )
{
	if(m_n.x != 0){
		return (p.x - m_sp.x)/m_n.x;
	} else if (m_n.y != 0){
		return (p.y - m_sp.y)/m_n.y;
	} else if (m_n.z != 0){
		return (p.z - m_sp.z)/m_n.z;
	} else {
		return 0;
	}
}

Vector3 Line::IntersectWithLine( Line l )
{
	Vector3 ua = m_sp;
	Vector3 ub = m_ep;
	Vector3 va = l.GetStartPoint();
	Vector3 vb = l.GetEndPoint();

	Vector3 ret = ua; 
	double t;
	double m = (ua.x - ub.x) * (va.y - vb.y) - (ua.y - ub.y) * (va.x - vb.x);
	if(abs(m) > M_HIGH_TOLERANCE) {
		t = ((ua.x - va.x) * (va.y - vb.y) - (ua.y - va.y) * (va.x - vb.x)) / m;
	} else {
		m = (ua.x - ub.x) * (va.z - vb.z) - (ua.z - ub.z) * (va.x - vb.x);
		if(abs(m) > M_HIGH_TOLERANCE) {
			t = ((ua.x - va.x) * (va.z - vb.z) - (ua.z - va.z) * (va.x - vb.x)) / m;
		} else {
			m = (ua.y - ub.y) * (va.z - vb.z) - (ua.z - ub.z) * (va.y - vb.y);
			if(abs(m) > M_HIGH_TOLERANCE) {
				t = ((ua.y - va.y) * (va.z - vb.z) - (ua.z - va.z) * (va.y - vb.y)) / m;
			} else {
				return Vector3::ZERO;
			}
		}
	}
	
	ret += (ub - ua)*t;

	return ret;
}