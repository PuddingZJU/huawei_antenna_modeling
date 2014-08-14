#include "ItemSpace.h"
#include "ArrayToolBox.h"
#include "math.h"
#include <QFileDialog>
#include <QDir>
#include "Mathematics.h"

ItemSpace::ItemSpace(MidSpace* p)
: pMidSpace(p)
, viewMode(Fixed)
, wldWidth(WINWIDTH)
, wldHeight(WINHEIGHT)
, lightEnabled(true)
, dirEnabled(true)
, normEnabled(false)
, colorEnabled(true)
, smoothEnabled(true)
, lineEnabled(false)
{	
	ArrayToolBox<double>::loadOneMatrix(viewMatrix);
	ArrayToolBox<double>::loadOneMatrix(viewMatrixInv);
	ArrayToolBox<double>::loadOneMatrix(portMatrix);
	ArrayToolBox<double>::loadOneMatrix(normRotateMatrix);
	//nansyScale(0, 0, -WINWIDTH*10, 0, viewMatrix);
	initLight();
	portMatrix[5] *= -1.0;
	portMatrix[10] *= -1.0;
	nansyMove(0, 0, WINWIDTH/2, WINHEIGHT/2, portMatrix);
}

void ItemSpace::initLight()
{
	lightDirMatrix[0] = 1.0;
	lightDirMatrix[1] = 1.0;
	lightDirMatrix[2] = 2.0;
	ArrayToolBox<double>::normalize(lightDirMatrix, lightDirMatrix);
	lightColor = qRgb(255, 255, 255);
}

ItemSpace::~ItemSpace()
{

}

void ItemSpace::reDraw()
{	
	allWldDot2WinDot(&wldDotVec, &winDotVec);
	pMidSpace->ClearAll();
	vector<WindowPolygon>::iterator winPolygonIter = winPolygonVec.begin();
	while(winPolygonIter != winPolygonVec.end()){
		if(lightEnabled && !lineEnabled){
			(*winPolygonIter).UpdateColor(lightDirMatrix, lightColor, dirEnabled, normEnabled);	//根据光照和顶点本身的颜色计算当前顶点的颜色
		}
		pMidSpace->pushWindowPolygon(&(*winPolygonIter));
		winPolygonIter++;
	}
	pMidSpace->StartScan(smoothEnabled, lineEnabled);
}

void ItemSpace::ShowRandomTriangle()
{
	QRgb c1 = qRgb(255, 0, 0);
	QRgb c2 = qRgb(0, 255, 0);
	QRgb c3 = qRgb(0, 0, 255);
	QRgb c4 = qRgb(0, 0, 0);

	WorldDot tdot1(10.0, 10.0, 0, c1);
	WorldDot tdot2(300.0, 300.0, 0, c1);
	WorldDot tdot3(100.0, 300.0, 0, c1);
	
	for(int i = 0; i < 3; i++){
		c2 = qRgb(ArrayToolBox<double>::randomInt(0, 255), ArrayToolBox<double>::randomInt(0, 255), ArrayToolBox<double>::randomInt(0, 255));
		tdot1.SetColor(c2);
		tdot1.SetXYZ(ArrayToolBox<double>::randomInt(-WINWIDTH/2, WINWIDTH/2), ArrayToolBox<double>::randomInt(-WINHEIGHT/2, WINHEIGHT/2), ArrayToolBox<double>::randomInt(-WINHEIGHT/2, WINHEIGHT/2));
		tdot2.SetColor(c2);
		tdot2.SetXYZ(ArrayToolBox<double>::randomInt(-WINWIDTH/2, WINWIDTH/2), ArrayToolBox<double>::randomInt(-WINHEIGHT/2, WINHEIGHT/2), ArrayToolBox<double>::randomInt(-WINHEIGHT/2, WINHEIGHT/2));
		tdot3.SetColor(c2);
		tdot3.SetXYZ(ArrayToolBox<double>::randomInt(-WINWIDTH/2, WINWIDTH/2), ArrayToolBox<double>::randomInt(-WINHEIGHT/2, WINHEIGHT/2), ArrayToolBox<double>::randomInt(-WINHEIGHT/2, WINHEIGHT/2));
		wldDotVec.push_back(tdot1);
		wldDotVec.push_back(tdot2);
		wldDotVec.push_back(tdot3);
	}
	RebuildWinPolygon();
	emit changed();
}

void ItemSpace::ShowElf()
{
	Clear();
	//读取elf obj
	QString path(tr("../OBJ/Elf.obj"));
	ObjReader reader(&wldDotVec, &winPolygonVec);
	reader.ReadIt(path);
	RebuildWinPolygon();

	//设置相关矩阵
	
	for(int i = 0; i < 4; i++){
		nansyScale(0, 0, 3000, 0, viewMatrix);
	}
	nansyMove(0, 0, 0, -100, viewMatrix);
	/*lightEnabled = 1;
	dirEnabled = 1;
	normEnabled = 0;
	colorEnabled = 1;
	smoothEnabled = 1;*/

	emit changed();
}

void ItemSpace::ShowPlant()
{
	Clear();
	QString path(tr("../OBJ/G_zhiwu.obj"));
	ObjReader reader(&wldDotVec, &winPolygonVec);
	reader.ReadIt(path);
	RebuildWinPolygon();
	nansyMove(0, 0, 50, 50, viewMatrix);
	/*lightEnabled = 1;
	dirEnabled = 1;
	normEnabled = 0;
	colorEnabled = 1;
	smoothEnabled = 1;*/

	emit changed();
}

void ItemSpace::ShowGirl()
{
	Clear();
	QString path(tr("../OBJ/girl.obj"));
	ObjReader reader(&wldDotVec, &winPolygonVec);
	reader.ReadIt(path);
	RebuildWinPolygon();
	//nansyMove(0, 0, 50, 50, viewMatrix);
	nansyScale(0, 0, 2000, 0, viewMatrix);
	nansyScale(0, 0, 500, 0, viewMatrix);
	/*lightEnabled = 1;
	dirEnabled = 1;
	normEnabled = 0;
	colorEnabled = 1;
	smoothEnabled = 1;*/

	emit changed();	
}

void ItemSpace::MouseMoved(int sx, int sy, int ex, int ey)
{
	sy *= -1;
	ey *= -1;
	switch(viewMode)
	{
	case Fixed:
		break;
	case Move:
		nansyMove(sx, sy, ex, ey, viewMatrix);
		break;
	case Rotate:
		nansyRotate(sx, sy, ex, ey, viewMatrix);
		nansyRotate(sx, sy, ex, ey, normRotateMatrix);
		break;
	case Scale:
		nansyScale(sx, sy, ex, ey, viewMatrix);
		break;
	case Default:
		nansyReset();
		break;
	default:
		break;
	}
}

//平移
void ItemSpace::nansyMove(int sx, int sy, int ex, int ey, double matrix[16])
{
	static int dxSum = 0;
	static int dySum = 0;
	dxSum += ex - sx;
	dySum += ey - sy;
	double m[16] = {1.0,   0,   0,   ex - sx,
					  0, 1.0,   0,   ey - sy,
					  0,   0, 1.0,   0,
					  0,   0,   0,	 1.0};
	double out[16];
	ArrayToolBox<double>::matrixMul44(m, matrix, out);
	ArrayToolBox<double>::loadMatrix44(matrix, out);
	emit changed();
}

//旋转
void ItemSpace::nansyRotate(int sx, int sy, int ex, int ey, double matrix[16])
{
	static int dxSum = 0;
	static int dySum = 0;
	dxSum += ex - sx;
	dySum += ey - sy;

	double rx = -M_PI*(ey - sy)/WINHEIGHT;
	double ry = M_PI*(ex - sx)/WINWIDTH;

	double r1[16] = {1.0,       0,          0,   0,
					   0, cos(rx), -1*sin(rx),   0,
					   0, sin(rx),    cos(rx),   0,
					   0,       0,          0, 1.0};

	double r2[16] = {cos(ry),   0,    sin(ry),   0,
					       0, 1.0,          0,   0,
				  -1*sin(ry),   0,    cos(ry),   0,
						   0,   0,          0, 1.0};

	double out[16];
	ArrayToolBox<double>::matrixMul44(r1, matrix, out);
	ArrayToolBox<double>::matrixMul44(r2, out, matrix);
	emit changed();
}

//缩放
void ItemSpace::nansyScale(int sx, int sy, int ex, int ey, double matrix[16])
{
	static int dxSum = 0;
	static int dySum = 0;
	dxSum += ex - sx;
	dySum += ey - sy;

	double dx = ex - sx;
	double newWidth = wldWidth + dx;
	double x = newWidth/wldWidth;
	double y = newWidth/wldWidth;
	double z = newWidth/wldWidth;
	//wldWidth = newWidth;
	double s[16] = {  x,   0,   0,   0,
					  0,   y,   0,   0,
					  0,   0,   z,   0,
					  0,   0,   0, 1.0};
	double out[16];
	ArrayToolBox<double>::matrixMul44(s, matrix, out);
	ArrayToolBox<double>::loadMatrix44(matrix, out);
	emit changed();
}

//恢复到初始状态
void ItemSpace::nansyReset()
{
	ArrayToolBox<double>::loadOneMatrix(viewMatrix);
	ArrayToolBox<double>::loadOneMatrix(normRotateMatrix);
	emit changed();
}

//窗口坐标->世界坐标
void ItemSpace::nansyUnProject(int winx, int winy, int winz, double *wldx, double *wldy, double *wldz)
{
	double x[4] = {(double)winx, (double)winy, (double)winz, 1.0};
	double out[4];
	ArrayToolBox<double>::matrixMul41(viewMatrixInv, x, out);
	*wldx = out[0];
	*wldy = out[1];
	*wldz = out[2];
}

//世界坐标->窗口坐标
void ItemSpace::nansyProject(int *pwinx, int *pwiny, int *pwinz, double wldx, double wldy, double wldz)
{
	double x[4] = {wldx, wldy, wldz, 1.0};
	double out[4];
	ArrayToolBox<double>::matrixMul41(viewMatrix, x, out);
	*pwinx = out[0];
	*pwiny = out[1];
	*pwinz = out[2];
}

WindowDot ItemSpace::toWinDot(WorldDot *wldd)
{
	double d[4];
	d[0] = wldd->GetX();
	d[1] = wldd->GetY();
	d[2] = wldd->GetZ();
	d[3] = 1.0;
	double out4[4];
	ArrayToolBox<double>::matrixMul41(viewMatrix, d, out4);
	ArrayToolBox<double>::matrixMul41(portMatrix, out4, d);
	if(!lineEnabled){
		double n[4];
		wldd->GetNorm(n);
		n[3] = 1.0;
		ArrayToolBox<double>::matrixMul41(normRotateMatrix, n, out4);
		ArrayToolBox<double>::normalize(out4, out4);
	}
	WindowDot wind(d[0], d[1], d[2], wldd->GetColor());
	if(!lineEnabled){
		if(!colorEnabled){
			wind.SetColor(qRgb(255, 255, 255));
		}
		wind.SetNorm(out4);
		if(lightEnabled){
			wind.UpdateColor(lightDirMatrix, dirEnabled, normEnabled);
		}
	}
	return wind;
}

QRgb ItemSpace::calColor(WorldDot* wd)
{
	return wd->GetColor();
}

void ItemSpace::allWldDot2WinDot(vector<WorldDot>* wldvec, vector<WindowDot>* winvec)
{
	vector<WorldDot>::iterator wldDotIter = wldvec->begin();
	vector<WindowDot>::iterator winDotIter = winvec->begin();
	winvec->clear();
	while(wldDotIter != wldvec->end()){
		winvec->push_back(toWinDot(&(*wldDotIter)));		
		wldDotIter++;
	}
}

void ItemSpace::buildWinPolygon(vector<WindowDot>* dotvec, vector<WindowPolygon>* polygonvec)
{
	polygonvec->clear();
	vector<WindowDot>::iterator winDotIter = dotvec->begin();
	while (winDotIter != dotvec->end()){		
		WindowPolygon winPolygon;
		for(int i = 0; i < 3; i++){
			winPolygon.AddDot(&(*winDotIter));
			winDotIter++;
		}
		polygonvec->push_back(winPolygon);
	}
}

void ItemSpace::SetViewMode(ViewMode mode)
{
	viewMode = mode;
	if(mode == Default){
		nansyReset();
	}
	if(mode != Scale){
		wldWidth = WINWIDTH;
		wldHeight = WINHEIGHT;
	}
}

void ItemSpace::Clear()
{
	worldPolygonVec.clear();
	wldDotVec.clear();
	winPolygonVec.clear();
	winDotVec.clear();
	pMidSpace->ClearAll();
	ArrayToolBox<double>::loadOneMatrix(viewMatrix);
	ArrayToolBox<double>::loadOneMatrix(viewMatrixInv);
	ArrayToolBox<double>::loadOneMatrix(normRotateMatrix);
	wldWidth = WINWIDTH;
	wldHeight = WINHEIGHT;
	emit changed();
}

void ItemSpace::OpenObj()
{
	ObjReader reader(&wldDotVec, &winPolygonVec);
	reader.ReadIt(QFileDialog::getOpenFileName(0, tr("Open Obj File"), QDir::currentPath(), tr("*.obj")));
	RebuildWinPolygon();
	emit changed();
}

void ItemSpace::RebuildWinPolygon()
{
	allWldDot2WinDot(&wldDotVec, &winDotVec);
	buildWinPolygon(&winDotVec, &winPolygonVec);
}

void ItemSpace::SwitchLight()
{
	lightEnabled = 1 - lightEnabled;
	RebuildWinPolygon();
	emit changed();
}

void ItemSpace::SwitchDir()
{
	dirEnabled = 1 - dirEnabled;
	emit changed();
}

void ItemSpace::SwitchNorm()
{
	normEnabled = 1 - normEnabled;
	emit changed();
}

void ItemSpace::SwitchColor()
{
	colorEnabled = 1 - colorEnabled;
	emit changed();
}

void ItemSpace::SwitchSmooth()
{
	smoothEnabled = 1 - smoothEnabled;
	emit changed();
}

void ItemSpace::SwitchLine()
{
	lineEnabled = 1 - lineEnabled;
	emit changed();
}