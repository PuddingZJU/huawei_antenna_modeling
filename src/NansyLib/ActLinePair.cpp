#include "ActLinePair.h"
#include <QMessageBox>

ActLinePair::ActLinePair()
: xl(0)
, dxl(0)
, dyl(0)
, xr(0)
, dxr(0)
, dyr(0)
, zl(0)
, dzx(0)
, dzy(0)
{

}

ActLinePair::~ActLinePair()
{

}

bool ActLinePair::FirstAdd(ActLine* pL, ActLine* pR)
{
	xl = pL->GetStartx();
	dxl = pL->GetDxPerY();
	dyl = pL->GetDeltay();
	pLActLine = pL;
	xr = pR->GetStartx();
	dxr = pR->GetDxPerY();
	dyr = pR->GetDeltay();
	zl = pL->GetStartz();
	pRActLine = pR;
	
	PlaneEquation* pEq = pL->GetPlaneEq();
	if(pEq){
		double a, b, c;
		a = pEq->a;
		b = pEq->b;
		c = pEq->c;
		if(c){
			dzx = a/c;
			dzy = b/c;
		}
		else{	//两条边组成的平面垂直于屏幕
			if(pL->GetStartz() + pL->GetDeltaz() > pR->GetStartz() + pR->GetDeltaz()){	//pL在前
				dzx = pL->GetDzx();
				dzy = pL->GetDzy();
			}
			else if(pL->GetStartz() + pL->GetDeltaz() < pR->GetStartz() + pR->GetDeltaz()){	//pR在前
				dzx = pR->GetDzx();
				dzy = pR->GetDzy();
			}
			else{	//两条边重合，不是三角形!
				return false;
				QMessageBox::warning(0, QObject::tr("FirstAdd"), QObject::tr("two line superpose! not a triangle"));
			}
		}
	}
	else{
		return false;
		QMessageBox::warning(0, QObject::tr("FirstAdd"), QObject::tr("Plane Equation of the active line is not set yet!"));
	}
	return true;
}

bool ActLinePair::FirstAdd(ActPolygon *pActPolygon)
{
	ActLine *pl, *pr;
	pActPolygon->updatePointers();
	pSrcPlygon = pActPolygon;
	pl = pActPolygon->GetNextLine();
	pr = pActPolygon->GetNextLine();
	if(pl == NULL || pr == NULL){
		return false;
	}
	if(pl->GetDeltay() < 0){
		pl = pActPolygon->GetNextLine();
	}
	if(pr->GetDeltay() < 0){
		pr = pActPolygon->GetNextLine();
	}
	if(pl == NULL || pr == NULL){
		return false;
	}
	if(pl && pr){
		return FirstAdd(pl, pr);
	}
	else{
		return false;
		QMessageBox::warning(0, QObject::tr("FirstAdd"), QObject::tr("The input active polygon is old."));
	}
}

bool ActLinePair::AddLine()
{
	ActLine* pActLine = pSrcPlygon->GetNextLine();
	if(!pActLine){
		if(dyl != dyr){
			//QMessageBox::warning(0, QObject::tr("ActLinePair::AddLine"), QObject::tr("Lost a active line!"));
		}
		return false;
	}
	if(dyl < 0){
		xl = pActLine->GetStartx();
		dxl = pActLine->GetDxPerY();
		dyl = pActLine->GetDy();
		pLActLine = pActLine;
		zl = pActLine->GetStartz();
		if(dyl < 1)
			int i = 0;
	} else if(dyr < 0){
		xr = pActLine->GetStartx();
		dxr = pActLine->GetDxPerY();
		dyr = pActLine->GetDy();
		pRActLine = pActLine;		
		if(dyl < 1)
			int i = 0;
	} else{
		QMessageBox::warning(0, QObject::tr("AddLine"), QObject::tr("no need to add new active line!"));
		return false;
	}
	if(!pActLine->GetPlaneEq()->c){	//c == 0 no use
		if(2*pRActLine->GetStartz() + pRActLine->GetDeltaz() > 2*pLActLine->GetStartz() + pLActLine->GetDeltaz()){
			dzx = pLActLine->GetDzx();
			dzy = pLActLine->GetDzy();
		} else if(2*pRActLine->GetStartz() + pRActLine->GetDeltaz() < 2*pLActLine->GetStartz() + pLActLine->GetDeltaz()){
			dzx = pRActLine->GetDzx();
			dzy = pRActLine->GetDzy();
		} else{	//两条边重合，不是三角形!
			//QMessageBox::warning(0, QObject::tr("AddLine"), QObject::tr("two line superpose! not a triangle"));
			return false;
		}
	}
	return true;
}
