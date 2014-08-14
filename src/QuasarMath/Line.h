#ifndef LINE_H
#define LINE_H

#include "Mathematics.h"

enum IntersectRull{
	BOUNDED_INTERSECT,
	UNBOUNDED_INTERSECT,
	HALFBOUNDED_INTERSECT
};

enum DistanceRull{
	SEGMENT_LINE,
	NOSEGMENT_LINE
};

class Line
{
public:
	Line() {};
	Line(Vector3 v1, Vector3 v2);
	Line(Vector2 v1, Vector2 v2);
	~Line() {};
	Vector3 GetPoint(double t);
	Vector3 GetStartPoint() { return m_sp;};
	Vector3 p0() { return m_sp; };
	Vector3 GetEndPoint() { return m_ep;};
	Vector3 p1() { return m_ep; };
	Vector3 GetDirection() {return m_n;};
	Vector3 n() { return m_n; };
	void SetStartPoint(Vector3 v) {m_sp = v;};
	void SetEndPoint(Vector3 v) {m_ep = v;};
	void UpdateDir() {updateDir();};
	double Distance(Vector3 p, DistanceRull rull = NOSEGMENT_LINE);
	double Distance(Line l) {return Distance(l.GetStartPoint());};
	double Length() {return (m_ep - m_sp).Length();};
	Vector3 PerpendicularFoot(Vector3 p);
	double GetParameter(Vector3 p);
	bool IsOnLine(Vector3 p);
	Vector3 IntersectWithLine(Line l);

protected:
private:
	Vector3 m_sp, m_ep, m_n;
	void updateDir() {
		m_n = (m_ep - m_sp);
		m_n.Normalize();
	}
};

#endif