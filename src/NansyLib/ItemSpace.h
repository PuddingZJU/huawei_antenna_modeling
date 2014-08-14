#ifndef ITEMSPACE_H
#define ITEMSPACE_H

#include <vector>
#include <QObject>
#include "WorldPolygon.h"
#include "WindowPolygon.h"
#include "MidSpace.h"
#include "Skinning/IO/ObjReader.h"

using std::vector;

enum ViewMode
{
	Fixed,
	Move,
	Rotate,
	Scale,
	Default
};

class ItemSpace : public QObject
{
	Q_OBJECT

public:
	ItemSpace(MidSpace* p);
	~ItemSpace();
	void test();
	void reDraw();
	void MouseMoved(int sx, int sy, int ex, int ey);
	void SetViewMode(ViewMode mode);

private:
	bool lightEnabled, dirEnabled, normEnabled, colorEnabled, smoothEnabled, lineEnabled;
	vector<WorldPolygon> worldPolygonVec;
	vector<WorldDot> wldDotVec;
	vector<WindowPolygon> winPolygonVec;
	vector<WindowDot> winDotVec;
	MidSpace* pMidSpace;
	ViewMode viewMode;
	void nansyMove(int sx, int sy, int ex, int ey, double matrix[16]);
	void nansyRotate(int sx, int sy, int ex, int ey, double matrix[16]);
	void nansyScale(int sx, int sy, int ex, int ey, double matrix[16]);
	void nansyReset();
	void nansyProject(int *pwinx, int *pwiny, int *pwinz,
					double wldx, double wldy, double wldz);
	void nansyUnProject(int winx, int winy, int winz,
					double *wldx, double *wldy, double *wldz);
	double viewMatrix[16];
	double viewMatrixInv[16];
	double portMatrix[16];
	double normRotateMatrix[16];
	double lightDirMatrix[3];
	int wldWidth, wldHeight;

	WindowDot toWinDot(WorldDot* wd);
	void allWldDot2WinDot(vector<WorldDot>* wldvec, vector<WindowDot>* winvec);
	void buildWinPolygon(vector<WindowDot>* dotvec, vector<WindowPolygon>* polygonvec);

	//π‚’’
	QRgb calColor(WorldDot* wd);
	QRgb lightColor;
	void initLight();

signals:
	void changed();

public slots:
	void ShowRandomTriangle();
	void ShowElf();
	void ShowPlant();
	void ShowGirl();
	void Clear();
	void OpenObj();
	void RebuildWinPolygon();
	void SwitchLight();
	void SwitchDir();
	void SwitchNorm();
	void SwitchColor();
	void SwitchSmooth();
	void SwitchLine();
};

#endif