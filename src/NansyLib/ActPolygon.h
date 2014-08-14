#ifndef ACTPOLYGON_H
#define ACTPOLYGON_H


#include "ActLine.h"
#include "PlaneEquation.h"


class ActPolygon
{
public:	
	ActPolygon();
	ActPolygon(int dy, QRgb c, PlaneEquation *pe);
	ActPolygon(WindowPolygon *wp);
	~ActPolygon();
	double CalZ(double x, double y);
	QRgb GetColor() {return color;};
	double GetDeltaY() {return deltay;};
	void GenerateActPolygon(WindowPolygon *wp);
	int GetActed() {return acted;};
	int GetStartY() {return starty;};
	ActLine *GetNextLine();
	void updatePointers();
	WindowPolygon* GetSrcWinPolygon() {return winPolygon;};
	

private:
	int deltay;
	QRgb color;
	PlaneEquation planeEq;
	//先按照起点Y的值从小到大排列，起点Y相等的再按照终点X的值从小到大排列
	ActLine actLine[3];
	int acted;
	int starty;
	WindowPolygon* winPolygon;
	bool check();
	
};

#endif