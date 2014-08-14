#include "WorldDot.h"

WorldDot::WorldDot()
: x(0)
, y(0)
, z(0)
, color(0)
{
	for(int i = 0; i < 3; i++){
		norm[i] = 0;
	}
}

WorldDot::WorldDot(double d1, double d2, double d3, QRgb c, double n[3])
: x(d1)
, y(d2)
, z(d3)
, color(c)
{
	for(int i = 0; i < 3; i++){
		norm[i] = n[i];
	}
}

WorldDot::WorldDot(double d1, double d2, double d3, QRgb c)
: x(d1)
, y(d2)
, z(d3)
, color(c)
{

}

WorldDot::WorldDot(WorldDot* wd)
{
	fromWorldDot(wd);
}

WorldDot::~WorldDot()
{

}

void WorldDot::fromWorldDot(WorldDot* wd)
{
	x = wd->GetX();
	y = wd->GetY();
	z = wd->GetZ();
	color = wd->GetColor();
	double d[3];
	wd->GetNorm(d);
	SetNorm(d);
	wd->getTex(d);
	setTex(d);
	setIdx(wd->getIdx());
}

void WorldDot::GetNorm(double out[3])
{
	for(int i = 0; i < 3; i++){
		out[i] = norm[i];
	}
}

void WorldDot::SetNorm(double d[3])
{
	for(int i = 0; i < 3; i++){
		norm[i] = d[i];
	}
}


void WorldDot::SetXYZ(double d1, double d2, double d3)
{
	x = d1;
	y = d2;
	z = d3;
}

void WorldDot::SetColor(QRgb c)
{
	color = c;
}

void WorldDot::setTex( double d[2] )
{
	tex[0] = d[0];
	tex[1] = d[1];
}

void WorldDot::getTex( double d[2] )
{
	d[0] = tex[0];
	d[1] = tex[1];
}
