#ifndef WORLDPOLYGON_H
#define WORLDPOLYGON_H

#include "WorldDot.h"
#include <vector>

using std::vector;

class WorldPolygon
{
public:
	WorldPolygon();
	WorldPolygon(QRgb c);
	~WorldPolygon();
	void AddDot(WorldDot* pDot);
	WorldDot* GetDot(int n) {return &(dotVec[n]);};
	QRgb GetColor() {return color;};

private:
	vector<WorldDot> dotVec;
	QRgb color;
};

#endif