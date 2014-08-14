#ifndef PLANEEQUATION_H
#define PLANEEQUATION_H

#include "WindowPolygon.h"


class PlaneEquation
{
public:
	PlaneEquation(double d1, double d2, double d3, double d4);
	PlaneEquation(WindowPolygon *wp);
	PlaneEquation(WindowDot *wd1, WindowDot *wd2, WindowDot *wd3);
	PlaneEquation();
	~PlaneEquation();
	void SetEquation(double d1, double d2, double d3, double d4);
	double CalZ(double x, double y);
	void GetNorm(double *n);
	void GenerateEquation(WindowDot *wd1, WindowDot *wd2, WindowDot *wd3);
	double a, b, c, d;
	
};

#endif