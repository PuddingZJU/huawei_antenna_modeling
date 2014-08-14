#ifndef OBJREADER_H
#define OBJREADER_H

#include <QFile>
#include <vector>
#include "WorldDot.h"
#include "WindowPolygon.h"

typedef struct  
{
	QRgb ka, kd, ks;
	QString name;
}ObjMtl;

class ObjReader : public QFile
{
public:
	ObjReader();
	ObjReader(vector<WorldDot>* p1, vector<WindowPolygon>* p2);
	~ObjReader();
	virtual bool ReadIt(QString nameStr);

protected:
	vector<WorldDot>* pWldDotVec;
	vector<WindowPolygon>* pWinPolygonVec;
	vector<WorldDot> wldDotVec;
	vector< vector<double> > normVec;
	vector< vector<double> > texVec;
	vector<ObjMtl> mtlVec;
	vector<int> groupSepVec;
	vector<QString> groupNameVec;
	void pushWldDot(QStringList sl, QRgb c);
	void pushNorm(QStringList sl);
	void pushTex(QStringList sl);
	void pushFace(QStringList sl, ObjMtl* pObjMtl);
	void pushMtl(ObjMtl);
	void pushGroup(QStringList sl);
	bool readMtlFile(QString);
	QRgb getColorFSL(QStringList sl);
	ObjMtl getObjMtl(QString mtlName);
	void getNorm(QStringList sl, WorldDot *wld);
	void getTex(QStringList sl, WorldDot *wld);
};

#endif