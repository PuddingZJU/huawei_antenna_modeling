#ifndef ACTLINE_H
#define ACTLINE_H

#include "WindowLine.h"
#include "PlaneEquation.h"

class ActLine
{
public:
	ActLine();
	ActLine(int sx, int dx, int dy);
	ActLine(WindowDot *d1, WindowDot *d2);
	ActLine(WindowLine *wl);
	~ActLine();
	int GetStartx() {return startx;};
	double GetDxPerY() {return dxPerY;};
	int GetDy() {return deltay;};
	int GetDeltay() {return deltay;};
	double GetStartz() {return startz;};
	int GetStarty() {return starty;};
	double GetDeltaz() {return deltaz;};
	double GetDzx() {return dzPerX;};
	double GetDzy() {return dzPerY;};
	void SetStartx(int sx) {startx = sx;};
	void SetDxPerY(double dx) {dxPerY = dx;};
	void SetDeltaY(int dy) {deltay = dy;};
	void SetPlaneEq(PlaneEquation *p) {pPlaneEq = p;};
	PlaneEquation* GetPlaneEq() {return pPlaneEq;};
	void GenerateActLine(WindowDot *d1, WindowDot *d2);
	WindowDot* GetDot1() {return dot1;};
	WindowDot* GetDot2() {return dot2;};
	
private:
	int startx, starty;
	double startz;
	double dxPerY, dzPerX, dzPerY;
	int deltax;
	int deltay;
	double deltaz;
	PlaneEquation *pPlaneEq;
	WindowDot *dot1, *dot2;
	void generateActLine(WindowDot *d1, WindowDot *d2);
	void cut();
};

#endif