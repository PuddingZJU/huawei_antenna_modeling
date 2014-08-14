#include "ObjReader.h"
#include <QMessageBox>

ObjReader::ObjReader()
: pWldDotVec(NULL)
, pWinPolygonVec(NULL)
{

}

ObjReader::ObjReader(vector<WorldDot>* p1, vector<WindowPolygon>* p2)
: pWldDotVec(p1)
, pWinPolygonVec(p2)
{

}

ObjReader::~ObjReader()
{

}

bool ObjReader::ReadIt(QString nameStr)
{
	if(nameStr.isEmpty()){
		return false;
	}
	setFileName(nameStr);
	if(!open(QIODevice::ReadOnly | QIODevice::Text)){
		QMessageBox::warning(0, tr("ObjReader::ReadIt"), tr("Open Obj File Failed!"));
		return false;
	}
	mtlVec.clear();
	bool mtlExist = readMtlFile(nameStr);	//读取材质文件
	wldDotVec.clear();
	pWldDotVec->clear();
	normVec.clear();
	texVec.clear();	
	groupSepVec.clear();
	groupNameVec.clear();
	int dotCount = 0;
	ObjMtl currentMtl;
	currentMtl.kd = qRgb(255, 255, 255);
	QRgb defaultColor = qRgb(255, 255, 255);
	QString mtlName;
	while(!atEnd()){
		QString lineStr(readLine().trimmed());
		if(lineStr.isEmpty()) {
			continue;
		}
		if(lineStr.left(1) == tr("#")){
			continue;
		}
		QStringList itemList = lineStr.split(" ");
		if(itemList.indexOf(tr("")) != -1){
			itemList.takeAt(itemList.indexOf(""));
		}
		QString what = itemList[0];
		if(what == tr("mtllib")){
			mtlName = itemList[1];
		} else if(what == tr("usemtl")){
			if(mtlExist){
				currentMtl = getObjMtl(itemList[1]);
			}
		} else if(what == tr("v")){			
			pushWldDot(itemList, currentMtl.kd);
			dotCount++;
		} else if(what == tr("vn")){
			pushNorm(itemList);
		} else if(what == tr("f")){
			pushFace(itemList, &currentMtl);
		} else if(what == tr("vt")) {
			pushTex(itemList);
		} else if(what == tr("g")) {
			pushGroup(itemList);
		} else {
			printf("unknown flag %s\n", what.data());
		}
	}
	return true;
}

void ObjReader::pushWldDot(QStringList sl, QRgb c)
{
	wldDotVec.push_back(WorldDot(sl[1].toDouble(), sl[2].toDouble(), sl[3].toDouble(), c));
	wldDotVec.back().setIdx(wldDotVec.size() - 1);
}

void ObjReader::pushNorm(QStringList sl)
{
	vector<double> dblVec;
	for(int i = 0; i < 3; i++){
		dblVec.push_back(sl[i + 1].toDouble());
	}
	normVec.push_back(dblVec);
}

void ObjReader::getNorm(QStringList sl, WorldDot *wld)
{
	int ni;
	if(sl.size() >= 3){
		ni = sl[2].toInt() - 1;
		if(ni != -1){
			double d[3];
			for(int j = 0; j < 3; j++){
				d[j] = normVec[ni][j];
			}
			wld->SetNorm(d);
		}
	} else {
		printf("invalid norm vector %s\n", sl.join(" ").toAscii().data());
	}
}

void ObjReader::pushTex( QStringList sl )
{
	vector<double> tex(2);
	if(sl.size() < 3) {
		printf("invalid texture coordinates %s\n", sl.join(" ").toAscii().data());
		return;
	}
	tex[0] = sl[1].toDouble();
	tex[1] = sl[2].toDouble();
	texVec.push_back(tex);
}

void ObjReader::getTex( QStringList sl, WorldDot *wld )
{
	if(sl.size() >= 2) {
		int ti = sl[1].toInt() - 1;
		if(ti >= 0) {
			vector<double> tex = texVec[ti];
			wld->setTex(&tex[0]);
		}
	}
}

//这个函数适用于n（n>=3）边形的情况，其方法是把这个n边形分割成许多小三角形，分
//割方法是以n边形的第一个顶点为原点的扇形分割法
void ObjReader::pushFace(QStringList sl, ObjMtl* pObjMtl)
{
	int vi = -1;
	WorldDot wld;
	QStringList tsl;
	for(int j = 1; j + 2 < sl.size(); j++){
		//以第一个顶点为所有三角形的起始顶点
		tsl = sl[1].split(tr("/"));
		vi = tsl[0].toInt() - 1;
		
		wld.fromWorldDot(&wldDotVec[vi]);
		getTex(tsl, &wld);
		getNorm(tsl, &wld);

		wld.SetColor(pObjMtl->kd);
		pWldDotVec->push_back(wld);
		
		for(int i = j; i < j + 2; i++){
			tsl = sl[i+1].split(tr("/"));
			vi = tsl[0].toInt() - 1;
			//获得点坐标
			wld.fromWorldDot(&wldDotVec[vi]);
			//获取贴图坐标
			getTex(tsl, &wld);
			//获得法向
			getNorm(tsl, &wld);
			//储存点
			wld.SetColor(pObjMtl->kd);
			pWldDotVec->push_back(wld);
		}
	}
}

bool ObjReader::readMtlFile(QString nameStr)
{
	QString mtlNameStr(nameStr);
	mtlNameStr.replace(mtlNameStr.lastIndexOf(tr("obj")), 3, tr("mtl"));
	QFile mtlReader(mtlNameStr);
	if(!mtlReader.open(QIODevice::ReadOnly | QIODevice::Text)){
		QMessageBox::warning(0, tr("ObjReader::ReadIt"), tr("Open Mtl File Failed!"));
		return false;
	}
	mtlVec.clear();
	ObjMtl currentMtl;
	if(mtlReader.atEnd())
		return false;
	while(!mtlReader.atEnd()){
		QString lineStr(mtlReader.readLine());
		if(lineStr.left(1) == tr("#")){
			continue;
		}
		QStringList itemList = lineStr.split(" ");
		if(itemList.indexOf(tr("")) != -1){
			itemList.takeAt(itemList.indexOf(""));
		}
		QString what = itemList[0];		
		if(what == tr("newmtl")){			
			pushMtl(currentMtl);
			currentMtl.name = itemList[1];			
		} else if(what == tr("Kd")){
			currentMtl.kd = getColorFSL(itemList);
		} else if(what == tr("Ka")){
			currentMtl.ka = getColorFSL(itemList);
		} else if(what == tr("Ks")){
			currentMtl.ks = getColorFSL(itemList);
		}
	}

	pushMtl(currentMtl);
	return true;
}

QRgb ObjReader::getColorFSL(QStringList sl)
{
	int r = sl[1].toDouble()*255;
	int g = sl[2].toDouble()*255;
	int b = sl[3].toDouble()*255;
	return qRgb(r, g, b);
}

void ObjReader::pushMtl(ObjMtl mtl)
{
	if(!mtl.name.isEmpty()){
		mtlVec.push_back(mtl);
	}
}

ObjMtl ObjReader::getObjMtl(QString mtlName)
{
	vector<ObjMtl>::iterator objmtlIter = mtlVec.begin();
	while(objmtlIter != mtlVec.end()){
		if((*objmtlIter).name == mtlName){
			return *objmtlIter;
		}
		objmtlIter++;
	}
	return *(mtlVec.begin());
}

void ObjReader::pushGroup( QStringList sl )
{
	groupSepVec.push_back(pWldDotVec->size());
	if(sl.size() >= 2) {
		groupNameVec.push_back(sl[1]);
	} else {
		groupNameVec.push_back("");
	}	
}

