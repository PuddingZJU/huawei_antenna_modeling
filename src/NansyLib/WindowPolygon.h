#ifndef WINDOWPOLYGON_H
#define WINDOWPOLYGON_H

#include "WorldPolygon.h"

class WindowPolygon
{
	/*
	当把WorldDot中的世界坐标转换成窗口坐标之后就使用该类来表示在窗口坐标系中的
	三角形面片
	*/
public:
	WindowPolygon();
	WindowPolygon(QRgb c, WorldPolygon* wp);
	~WindowPolygon();
	void AddDot(WindowDot *wd);
	void SetColor(QRgb c) {color = c;};
	void SetWorldPolygon(WorldPolygon* wp) {worldPolygon = wp;};
	void GetNorm(double *n);
	int GetLineNum() {return lineNum;};
	WorldPolygon* GetWorldPolygon() {return worldPolygon;};
	QRgb GetColor() {return color;};
	WindowDot* GetDot(int n);
	int GetDeltaY();
	void ClearAllDot() {lastDotIndex = 0;};
	//调用一下两个函数之前必须调用GetDeltaY以更新minYDotIndex和maxYDotIndex的值
	int GetMinYDotIndex() {return minYDotIndex;};
	int GetMaxYDotIndex() {return maxYDotIndex;};
	void UpdateColor(double ld[3], QRgb lc, bool dirEnabled, bool normEnabled);
	void UpdateReverse();
	void SetNorm(vector<WindowDot*>* pWinDotVec);
	QRgb GetColorInPos(int x, int y);

private:
	unsigned char lineNum;
	vector<WindowDot*> dotVec;
	int lastDotIndex, minYDotIndex, maxYDotIndex;
	int deltaY;
	QRgb color;
	WorldPolygon* worldPolygon;
	double norm[3];
	int normReverse;
	void calNorm(double n[3]);

};

#endif