#include "WindowDot.h"
#include "ArrayToolBox.h"

WindowDot::WindowDot()
: x(0)
, y(0)
, color(0)
{
}

WindowDot::WindowDot(int d1, int d2, int d3, QRgb c)
: x(d1)
, y(d2)
, z(d3)
, color(c)
{
	
}

WindowDot::~WindowDot()
{

}

void WindowDot::SetDepth(double d)
{
	z = d;
}


void WindowDot::SetXYZ(int d1, int d2, double d3)
{
	x = d1;
	y = d2;
	z = d3;
}

void WindowDot::SetFromDot(WindowDot* wd)
{
	x = wd->GetX();
	y = wd->GetY();
	z = wd->GetZ();
	color = wd->GetColor();
}

void WindowDot::SetColor(QRgb c)
{
	color = c;
}

void WindowDot::SetNorm(double d[3])
{
	for(int i = 0; i < 3; i++){
		norm[i] = d[i];
	}
}

void WindowDot::GetNorm(double *out)
{
	for(int i = 0; i < 3; i++){
		out[i] = norm[i];
	}
}

//根据法向和光照计算顶点颜色
void WindowDot::UpdateColor(double ld[3], bool dirEnabled, bool normEnabled)
{
	if(normEnabled){
		return;
	}
	double k = ArrayToolBox<double>::dotprod3(ld, norm);
	if(!dirEnabled){
		if(k < 0){
			k *= -1.0;
		}
	} else{
		if(k < 0){
			k = 0;
		}
	}
	int r = qRed(color) * k;
	int g = qGreen(color) * k;
	int b = qBlue(color) * k;
	color = qRgb(r, g, b);
}