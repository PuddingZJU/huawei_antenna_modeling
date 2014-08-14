#include "PlaneEquation.h"
#include <math.h>
#include "ArrayToolBox.h"

PlaneEquation::PlaneEquation(double d1, double d2, double d3, double d4)
: a(d1)
, b(d2)
, c(d3)
, d(d4)
{

}

PlaneEquation::PlaneEquation()
: a(1)
, b(1)
, c(1)
, d(0)
{

}

PlaneEquation::PlaneEquation(WindowPolygon *wp)
{
	GenerateEquation(wp->GetDot(0), wp->GetDot(1), wp->GetDot(2));
}

PlaneEquation::PlaneEquation(WindowDot *wd1, WindowDot *wd2, WindowDot *wd3)
{
	GenerateEquation(wd1, wd2, wd3);
}

PlaneEquation::~PlaneEquation()
{

}

void PlaneEquation::SetEquation(double d1, double d2, double d3, double d4)
{
	a = d1;
	b = d2;
	c = d3;
	d = d4;
}

double PlaneEquation::CalZ(double x, double y)
{
	if(c != 0){
		return (d - x*a - y*b)/c;
	}
	else{
		return 0;
	}
}

void PlaneEquation::GetNorm(double *n)
{
	double len = sqrt(a*a + b*b + c*c);
	if(len != 0){
		n[0] = a/len;
		n[1] = b/len;
		n[2] = c/len;
	}
	else{
		n[0] = 0;
		n[1] = 0;
		n[2] = 0;
	}
}

void PlaneEquation::GenerateEquation(WindowDot *wd1, WindowDot *wd2, WindowDot *wd3)
{
	double d1[3], d2[3], d3[3];
	d1[0] = wd2->GetX() - wd1->GetX();
	d1[1] = wd2->GetY() - wd1->GetY();
	d1[2] = wd2->GetZ() - wd1->GetZ();
	d2[0] = wd3->GetX() - wd2->GetX();
	d2[1] = wd3->GetY() - wd2->GetY();
	d2[2] = wd3->GetZ() - wd2->GetZ();
	ArrayToolBox<double>::crossprod3(d1, d2, d3);
	ArrayToolBox<double>::normalize(d3, d3);
	a = d3[0];
	b = d3[1];
	c = d3[2];
	d = a*wd1->GetX() + b*wd1->GetY() + c*wd1->GetZ();
}