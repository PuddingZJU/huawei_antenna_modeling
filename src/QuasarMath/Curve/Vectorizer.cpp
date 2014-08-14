#include "vectorizer.h"
#include "..\QuasarMath\Line.h"

/**
* @note		不穿过顶点的矢量化
* @param	QVector<QPointF> & points	线采样点数组
* @return	QVector<QPointF>	控制点数组
*/
QVector<QPointF> Vectorize( QVector<QPointF> &points )
{
	double p_a = 0.3;

	QVector<QPointF> midPoints;
	for(int i = 0; i < points.size() - 1; i++) {
		midPoints.push_back((points[i] + points[i + 1])/2);
	}
	QVector<QPointF> ret;
	for(int i = 0; i < midPoints.size() - 1; i++) {
		QPointF p1 = midPoints[i];
		QPointF p2 = midPoints[i + 1];
		QPointF a = points[i + 1];
		ret.push_back(p1);
		ret.push_back((p_a*p1 + (1.0 - p_a)*a));
		ret.push_back((p_a*p2 + (1.0 - p_a)*a));
		ret.push_back(p2);
	}
	return ret;
}

/**
* @note		穿过顶点的矢量化。
* @param	vector<Vector2> & points	线采样点数组
* @param	double a	平滑度。0~0.5，越大越平滑
* @param	double minAngle	最小容忍角度，若相邻三个采样点之间的夹角小于这个角则作为折线处理。
* @return	vector<Vector2>	控制点数组
*/
vector<Vector2> Vectorize( vector<Vector2> &points, 
						  double a,
						  double minAngle )
{	
	/*****************************************/
	vector<Vector2> ctrlPoints;
	vector<Vector2>& pVec = points;

	for(int i = 1; i < pVec.size() - 1; i++) {
		Vector2 p0 = pVec[i - 1];
		Vector2 p1 = pVec[i];
		Vector2 p2 = pVec[i + 1];

		Vector2 n10 = p0 - p1;
		if(n10.Length() > M_LOW_TOLERANCE) {
			n10.Normalize();
		}		
		Vector2 n12 = p2 - p1;
		if(n12.Length() > M_LOW_TOLERANCE) {
			n12.Normalize();
		}

		Vector2 p22 = p1 + n12*p0.Distance(p1);
		Vector2 n02 = p22 - p0;
		if(n02.Length() > M_LOW_TOLERANCE) {
			n02.Normalize();
		}

		double d = (p1 - p0).Dot(n02);
		Vector2 c0;
		if(abs(n10.Dot(n02)) < M_HIGH_TOLERANCE) {
			c0 = p1;
		} else {
			c0 = p1 - n02*(d*a/abs(n10.Dot(n02)));
		}

		Vector2 c1;
		if(abs(n12.Dot(n02)) < M_HIGH_TOLERANCE) {
			c1 = p1;
		} else {
			c1 = p1 + n02*(d*a/abs(n12.Dot(n02)));
		}

		double angle = abs(ACosD(n10.Dot(n12)));

		if(i == 1) {
			ctrlPoints.push_back(p0);

			if(angle < minAngle) {
				ctrlPoints.push_back(p1);
			} else {
				Vector2 pn01 = n10;
				pn01.Rotate(90);

				Vector2 mid01 = (p0 + p1)/2.0;
				Line l(mid01, mid01 + pn01);
				Vector2 f1 = l.PerpendicularFoot(Vector3(c0.x, c0.y, 0));

				ctrlPoints.push_back(f1*2.0 - c0);
			}
		}

		if(angle < minAngle) {
			ctrlPoints.push_back(p1);
			ctrlPoints.push_back(p1);
			//ctrlPoints.push_back(p1);
			//ctrlPoints.push_back(p1);
			//ctrlPoints.push_back(p1);
			//ctrlPoints.push_back(p1);
			ctrlPoints.push_back(p1);
			ctrlPoints.push_back(p1);
		} else {
			ctrlPoints.push_back(c0);
			ctrlPoints.push_back(p1);
			ctrlPoints.push_back(p1);
			ctrlPoints.push_back(c1);
		}		

		if(i == pVec.size() - 2) {
			if(angle < minAngle) {
				ctrlPoints.push_back(p1);
			} else {
				Vector2 pn12 = n12;
				pn12.Rotate(90);

				Vector2 mid12 = (p1 + p2)/2.0;
				Line l(mid12, mid12 + pn12);
				Vector2 f2 = l.PerpendicularFoot(Vector3(c1.x, c1.y, 0));

				ctrlPoints.push_back(f2*2.0 - c1);
			}
			ctrlPoints.push_back(p2);
		}
	}
	return ctrlPoints;
	/*****************************************/
	/*****************************************
	double p_a = 0.3;

	vector<Vector2> midPoints;
	for(int i = 0; i < points.size() - 1; i++) {
		midPoints.push_back((points[i] + points[i + 1])/2);
	}
	vector<Vector2> ret;
	for(int i = 0; i < midPoints.size() - 1; i++) {
		Vector2 p1 = midPoints[i];
		Vector2 p2 = midPoints[i + 1];
		Vector2 a = points[i + 1];
		ret.push_back(p1);
		ret.push_back((p1*p_a + a*(1.0 - p_a)));
		ret.push_back((p2*p_a + a*(1.0 - p_a)));
		ret.push_back(p2);
	}
	return ret;
	*****************************************/
}

//vector<Vector3> Vectorize( vector<Vector3> &points )
//{
//
//	return vector<Vector3>();
//}

QPainterPath toBezierPath(vector<Vector2> ctrlPoints)
{
	QPainterPath pp;

	if(ctrlPoints.empty()) {
		return pp;
	}
	pp.setFillRule(Qt::WindingFill);
	Vector2 frontV = ctrlPoints.front();
	pp.moveTo(QPointF(frontV.x, frontV.y));
	double sum = 0;
	for(int i = 0; i < ctrlPoints.size(); i += 4) {
		Vector2 p1 = ctrlPoints[i];
		Vector2 p2 = ctrlPoints[i + 1];
		Vector2 p3 = ctrlPoints[i + 2];
		Vector2 p4 = ctrlPoints[i + 3];		
		pp.cubicTo(QPointF(p2.x, p2.y), QPointF(p3.x, p3.y), QPointF(p4.x, p4.y));
		sum += p1.Distance(p4);
		if(sum >= 100000) {
			break;
		}
	}
	return pp;
}

Vector2 getPointOnBezier( double t, Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3 )
{
	double s = 1.0-t;
	return p0*s*s*s + p1*3*(s*s*t) + p2*3*(t*t*s) + p3*t*t*t;
}

//QPainterPath reVectorize( vector<Vector2> &points, 
//						 double step /*= 1.0*/,
//						 double a /*= 0.1*/, 
//						 double minAngle /*= 45*/ )
//{
//
//	for(int i = 0; i < points.size() - 1; i++) {
//		Vector2 now = points[i];
//		Vector2 nxt = points[i + 1];
//		if(now.Distance(nxt) <= step) {
//			
//		}
//	}
//}