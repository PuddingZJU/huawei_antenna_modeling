#include "ActLine.h"
#include <QMessageBox>

ActLine::ActLine(WindowLine *wl)
: pPlaneEq(NULL)
{
	generateActLine(wl->GetSDot(), wl->GetEDot());
}

ActLine::ActLine(WindowDot *d1, WindowDot *d2)
: pPlaneEq(NULL)
{
	generateActLine(d1, d2);
}

ActLine::ActLine()
: startx(-1)
, starty(-1)
, dxPerY(0)
, deltay(-1)
, pPlaneEq(NULL)
{

}

ActLine::~ActLine()
{

}

void ActLine::generateActLine(WindowDot *d1, WindowDot *d2)
{
	dot1 = d1;
	dot2 = d2;
	WindowDot *sd, *ed;
	if(d1->GetY() < d2->GetY()){
		sd = d1;
		ed = d2;
	}
	else{
		sd = d2;
		ed = d1;
	}
	int sx = sd->GetX();
	int sy = sd->GetY();
	double sz = sd->GetZ();
	int ex = ed->GetX();
	int ey = ed->GetY();
	double ez = ed->GetZ();
	deltaz = ez - sz;
	deltax = ex - sx;
	deltay = ey - sy;
	if(deltay){
		startx = sx;
		starty = sy;
		startz = sz;
		dxPerY = 1.0*(ex - sx) / (ey - sy);
		dzPerY = 1.0*(ez - sz) / (ey - sy);
		if(ex != sx){
			dzPerX = 1.0*(ez - sz) / (ex - sx);
		}
		else{
			dzPerX = ez - sz;
		}				
	}
	else{	//sy == ey	
		if(sx < ex){
			dxPerY = ex - sx;
			startx = sx;
			starty = sy;
			startz = sz;
			deltax = ex - sx;
			if(deltax){
				dzPerX = 1.0*(ez - sz) / (ex - sx);
			}
			else{
				dzPerX = ez - sz;
			}
			dzPerY = ez - sz;
		}
		else if(sx > ex){
			dxPerY = sx - ex;
			startx = ex;
			starty = ey;
			startz = ez;
			deltax = sx - ex;
			if(deltax){
				dzPerX = 1.0*(sz - ez) / (sx - ex);
			}
			else{
				dzPerX = sz - ez;
			}
			dzPerY = sz - ez;
		}
		else{
			//QMessageBox::warning(0, QObject::tr("ActLine"), QObject::tr("sx = ex and sy = ey! not a line"));
		}
	}
	cut();
}

void ActLine::GenerateActLine(WindowDot *d1, WindowDot *d2)
{
	generateActLine(d1, d2);
}

void ActLine::cut()
{
	if(starty < 0){
		double x1 = dot1->GetX();
		double y1 = dot1->GetY();
		double z1 = dot1->GetZ();
		double x2 = dot2->GetX();
		double y2 = dot2->GetY();
		double z2 = dot2->GetZ();				
		double nstartx = (x2 - x1)/(y1 - y2)*y1 + x1;
		double nstarty = 0;
		double nstartz = (z2 - z1)/(y1 - y2)*y1 + z1;
		deltay += starty;
		deltax -= nstartx - startx;
		deltaz -= nstartz - startz;
		startx = nstartx;
		starty = nstarty;
		startz = nstartz;
	}
}