#include "ActPolygon.h"
#include "ArrayToolBox.h"

ActPolygon::ActPolygon(WindowPolygon *wp)
{
	GenerateActPolygon(wp);
}

ActPolygon::ActPolygon()
: deltay(-1)
, color(0)
, acted(0)
{
	planeEq.SetEquation(1, 1, 1, 0);
}

ActPolygon::ActPolygon(int dy, QRgb c, PlaneEquation* pe)
: deltay(dy)
, color(c)
, planeEq(*pe)
, acted(0)
{

}

ActPolygon::~ActPolygon()
{

}

double ActPolygon::CalZ(double x, double y)
{
	return planeEq.CalZ(x, y);
}

void ActPolygon::GenerateActPolygon(WindowPolygon *wp)
{
	winPolygon = wp;
	deltay = wp->GetDeltaY();
	color = wp->GetColor();
	planeEq.GenerateEquation(wp->GetDot(0), wp->GetDot(1), wp->GetDot(2));
	int max, min, mid;
	max = wp->GetMaxYDotIndex();
	min = wp->GetMinYDotIndex();
	mid = 3 - max - min;
	WindowDot *pYMinDot = wp->GetDot(min);
	WindowDot *pYMaxDot = wp->GetDot(max);
	WindowDot *pYMidDot = wp->GetDot(mid);
	starty = pYMinDot->GetY();
	double kMinMid = ArrayToolBox<double>::slope(pYMinDot->GetX(), pYMinDot->GetY(), pYMidDot->GetX(), pYMidDot->GetY());
	double kMinMax = ArrayToolBox<double>::slope(pYMinDot->GetX(), pYMinDot->GetY(), pYMaxDot->GetX(), pYMaxDot->GetY());
	int eDoti0, eDoti1;
	if(kMinMid > 0 && kMinMax > 0 || kMinMid < 0 && kMinMax < 0){
		if(kMinMid > kMinMax){
			eDoti0 = mid;
			eDoti1 = max;
		} else{
			eDoti0 = max;
			eDoti1 = mid;
		}
	} else{
		if(kMinMid < 0){
			eDoti0 = mid;
			eDoti1 = max;
		} else{
			eDoti0 = max;
			eDoti1 = mid;
		}
	}
	actLine[0].GenerateActLine(wp->GetDot(min), wp->GetDot(eDoti0));
	actLine[1].GenerateActLine(wp->GetDot(min), wp->GetDot(eDoti1));
	actLine[2].GenerateActLine(wp->GetDot(mid), wp->GetDot(max));
	acted = 0;
	updatePointers();
	check();
}

ActLine* ActPolygon::GetNextLine()
{
	if(acted >= 0 && acted < 3){
		return &(actLine[acted++]);
	}
	else{
		return NULL;
	}
}

//更新活化边中储存的平面方程指针
void ActPolygon::updatePointers()
{
	actLine[0].SetPlaneEq(&planeEq);
	actLine[1].SetPlaneEq(&planeEq);
	actLine[2].SetPlaneEq(&planeEq);
}

bool ActPolygon::check()
{
	actLine[0].GetDeltay();
	return true;
}