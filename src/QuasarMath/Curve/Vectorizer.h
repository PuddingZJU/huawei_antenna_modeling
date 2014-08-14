
#ifndef VECTORIZER_H
#define VECTORIZER_H

#include "..\src\corelib\tools\qvector.h"
#include <QPointF>
#include <vector>
#include "Mathematics.h"
#include "..\src\gui\painting\qpainterpath.h"

using std::vector;

//把一个点序列矢量化成贝赛尔曲线，下面两个函数返回的都是贝赛尔曲线的控制点。
//每一小段贝赛尔曲线由4个控制点决定，返回的控制点数组中以4个控制点为一组，
//所以前一组的第4个控制点和后一组的第一个控制点相同。
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