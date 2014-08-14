#ifndef WINDOWDOT_H
#define WINDOWDOT_H


#include <QColor>

class WindowDot
{
public:
	WindowDot(int, int, int, QRgb);
	WindowDot();
	~WindowDot();
	void SetX(int d) {x = d;};
	void SetY(int d) {y = d;};
	void SetZ(int d) {z = d;};
	int GetX() {return x;};
	int GetY() {return y;};	
	int GetZ() {return z;};
	void SetColor(QRgb c);
	QRgb GetColor() {return color;};
	void SetXYZ(int d1, int d2, double d);
	void SetDepth(double d);
	void SetFromDot(WindowDot* wd);
	void SetNorm(double d[3]);
	void GetNorm(double *out);
	double GetDepth() {return z;};
	WindowDot* GetSrcDot() {return pSrcDot;};
	void SetSrcDot(WindowDot* psrc) {pSrcDot = psrc;};
	void UpdateColor(double ld[3], bool dirEnabled, bool normEnabled);

private:
	int x, y;
	double z;
	QRgb color;
	double norm[3];
	WindowDot* pSrcDot;
};

#endif