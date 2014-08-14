#include "WindowLine.h"

WindowLine::WindowLine(WindowDot *wd1, WindowDot *wd2, QRgb c)
: sDot(*wd1)
, eDot(*wd2)
, color(c)
{
	
}

WindowLine::~WindowLine()
{

}

WindowLine::WindowLine()
: sDot(WindowDot())
, eDot(WindowDot())
, color(0)
{

}