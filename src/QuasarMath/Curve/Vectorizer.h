
#ifndef VECTORIZER_H
#define VECTORIZER_H

#include "..\src\corelib\tools\qvector.h"
#include <QPointF>
#include <vector>
#include "Mathematics.h"
#include "..\src\gui\painting\qpainterpath.h"

using std::vector;

//��һ��������ʸ�����ɱ��������ߣ����������������صĶ��Ǳ��������ߵĿ��Ƶ㡣
//ÿһС�α�����������4�����Ƶ���������صĿ��Ƶ���������4�����Ƶ�Ϊһ�飬
//����ǰһ��ĵ�4�����Ƶ�ͺ�һ��ĵ�һ�����Ƶ���ͬ��
QVector<QPointF> Vectorize(QVector<QPointF> &points);
vector<Vector2> Vectorize(vector<Vector2> &points,
						  double a = 0.1, 
						  double minAngle = 45);

QPainterPath toBezierPath(vector<Vector2> ctrlPoints);

QPainterPath reVectorize(vector<Vector2> &points,
						 double step = 1.0,
						 double a = 0.1, 
						 double minAngle = 45);

Vector2 getPointOnBezier( double t, Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3 );

#endif