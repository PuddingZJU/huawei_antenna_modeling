#ifndef ACTLINEPAIR_H
#define ACTLINEPAIR_H


#include "ActPolygon.h"

class ActLinePair
{
public:
	ActLinePair();
	~ActLinePair();
	double xl, xr, dyl, dyr;
	double dxl, dxr, zl, dzx, dzy;
	ActLine *pLActLine, *pRActLine;
	bool AddLine();
	bool FirstAdd(ActLine* pL, ActLine* pR);
	bool FirstAdd(ActPolygon* pActPolygon);
	ActPolygon* pSrcPlygon;
	
};

#endif