#ifndef WINDOWLINE_H
#define WINDOWLINE_H

#include "WindowDot.h"

class WindowLine
{
public:
	WindowLine();
	WindowLine(WindowDot*, WindowDot*, QRgb);
	~WindowLine();
	WindowDot* GetSDot() {return &sDot;};
	WindowDot* GetEDot() {return &eDot;};
	QRgb GetColor() {return color;};
	void SetSDot(WindowDot *wd) {sDot = *wd;};
	void SetEDot(WindowDot *wd) {eDot = *wd;};
	void SetColor(QRgb c) {color = c;};

private:
	WindowDot sDot, eDot;
	QRgb color;
};

#endif