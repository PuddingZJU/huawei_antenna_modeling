#include "WindowPolygon.h"
#include "ArrayToolBox.h"
#include "PlaneEquation.h"
#include <math.h>
#include <QMessageBox>

WindowPolygon::WindowPolygon()
: color(0)
, worldPolygon(NULL)
, lastDotIndex(0)
, minYDotIndex(0)
, maxYDotIndex(0)
, deltaY(0)
, lineNum(0)
, normReverse(0)
{

}

WindowPolygon::WindowPolygon(QRgb c, WorldPolygon* wp)
: color(c)
, worldPolygon(wp)
, lastDotIndex(0)
, minYDotIndex(0)
, maxYDotIndex(0)
, deltaY(0)
, lineNum(0)
, normReverse(0)
{

}

WindowPolygon::~WindowPolygon()
{

}

WindowDot* WindowPolygon::GetDot(int n)
{
	if(n >= 0 && n < dotVec.size()){
		return dotVec[n];
	}
	else{
		return new WindowDot(-1.0, -1.0, -1.0, 0);
	}
}

int WindowPolygon::GetDeltaY()
{
	int maxy = dotVec[0]->GetY();
	int miny = dotVec[1]->GetY();
	minYDotIndex = 1;
	maxYDotIndex = 0;
	for(int i = 0; i < dotVec.size(); i++){
		if(maxy < dotVec[i]->GetY()){
			maxy = dotVec[i]->GetY();
			maxYDotIndex = i;
		} else if(maxy == dotVec[i]->GetY()){
			if(dotVec[maxYDotIndex]->GetX() < dotVec[i]->GetX()){
				maxYDotIndex = i;
			}
		}
		if(miny > dotVec[i]->GetY()){
			miny = dotVec[i]->GetY();
			minYDotIndex = i;
		} else if(miny == dotVec[i]->GetY()){
			if(dotVec[minYDotIndex]->GetX() > dotVec[i]->GetX()){
				minYDotIndex = i;
			}
		}
	}
	return maxy - miny;
}

void WindowPolygon::AddDot(WindowDot *wd)
{
	if(lastDotIndex < dotVec.size()){
		dotVec[lastDotIndex] = wd;
		lastDotIndex++;
	}
	else if(lastDotIndex == dotVec.size()){
		dotVec.push_back(wd);
		lastDotIndex++;
	}
	else{
		//error
		QMessageBox::warning(0, QObject::tr("WindowPolygon::AddDot"), QObject::tr("lastDotIndex > dotVec.size!"));
	}
	if(lastDotIndex == 3){
		SetNorm(&dotVec);
		color = wd->GetColor();
	}
}

void WindowPolygon::GetNorm(double *n)
{
	for(int i = 0; i < 3; i++){
		n[i] = norm[i];
	}		
}

void WindowPolygon::calNorm(double n[3])
{
	double d1[3], d2[3], d3[3], out[3];
	double v1[3], v2[3];
	d1[0] = dotVec[0]->GetX();
	d2[0] = dotVec[1]->GetX();
	d3[0] = dotVec[2]->GetX();
	d1[1] = dotVec[0]->GetY();
	d2[1] = dotVec[1]->GetY();
	d3[1] = dotVec[2]->GetY();
	d1[2] = dotVec[0]->GetZ();
	d2[2] = dotVec[1]->GetZ();
	d3[2] = dotVec[2]->GetZ();
	ArrayToolBox<double>::calVector(d1, d2, v1);
	ArrayToolBox<double>::calVector(d2, d3, v2);
	ArrayToolBox<double>::crossprod3(v1, v2, n);
	ArrayToolBox<double>::normalize(n, n);
}

void WindowPolygon::UpdateColor(double ld[3], QRgb lc, bool dirEnabled, bool normEnabled)
{
	if(normEnabled){
		calNorm(norm);
	} else{
		SetNorm(&dotVec);
	}
	
	double k = ArrayToolBox<double>::dotprod3(norm, ld);
	if(!dirEnabled){
		if(k < 0){
			k = -1.0*k;
		}
	} else{
		if(k < 0){
			k = 0;
		}
	}
	QRgb c = dotVec[0]->GetColor();
	int r = k * qRed(c);
	int g = k * qGreen(c);
	int b = k * qBlue(c);
	c = qRgb(r, g, b);
	color = c;
	if(normEnabled){
		for(int i = 0; i < 3; i++){
			dotVec[i]->SetColor(c);
		}
	}
}

void WindowPolygon::UpdateReverse()
{
	double dn[3];
	calNorm(dn);
	double k = ArrayToolBox<double>::dotprod3(dn, norm);
	if(k > 0){
		normReverse = 1;
	} else{
		normReverse = -1;
	}
}

//将三个顶点的法向相加获得多边形法向
void WindowPolygon::SetNorm(vector<WindowDot*>* pWinDotVec)
{
	for(int i = 0; i < 3; i++){
		norm[i] = 0;
	}
	for(int j = 0; j < 3; j++){
		double d[3];
		pWinDotVec->at(j)->GetNorm(d);
		ArrayToolBox<double>::vectorAdd(d, norm, norm, 3);
	}
	ArrayToolBox<double>::normalize(norm, norm);
}

//插值计算多边形上某点颜色
QRgb WindowPolygon::GetColorInPos(int x, int y)
{
	WindowDot wdr[3], wdg[3], wdb[3];
	for(int i = 0; i < 3; i++){
		wdr[i].SetXYZ(dotVec[i]->GetX(), dotVec[i]->GetY(), qRed(dotVec[i]->GetColor()));
		wdg[i].SetXYZ(dotVec[i]->GetX(), dotVec[i]->GetY(), qGreen(dotVec[i]->GetColor()));
		wdb[i].SetXYZ(dotVec[i]->GetX(), dotVec[i]->GetY(), qBlue(dotVec[i]->GetColor()));
	}
	PlaneEquation per, peg, peb;
	per.GenerateEquation(&wdr[0], &wdr[1], &wdr[2]);
	peg.GenerateEquation(&wdg[0], &wdg[1], &wdg[2]);
	peb.GenerateEquation(&wdb[0], &wdb[1], &wdb[2]);
	int r = (int)per.CalZ((double)x, (double)y);
	int g = (int)peg.CalZ((double)x, (double)y);
	int b = (int)peb.CalZ((double)x, (double)y);
	//if(r >= 255 && g >= 255 && b >= 255){
	//	return color;
	//}
	if(r > 255) r = 255;
	if(g > 255) g = 255;
	if(b > 255) b = 255;
	if(r < 0) r = 0;
	if(g < 0) g = 0;
	if(b < 0) b = 0;
	//if( r == 255 && g == 255 && b == 255)
	//	return color;
	//if(pow((double)(qRed(color) - r), 2) > 16250)
	//	return color;
	return qRgb(r, g, b);
}