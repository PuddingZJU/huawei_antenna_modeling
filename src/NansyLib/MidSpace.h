#ifndef MIDSPACE_H
#define MIDSPACE_H

#include <QImage>
//#include <list>
#include <vector>
#include "WindowLine.h"
#include "ActLinePair.h"
#include "WindowPolygon.h"
#include "ActPolygon.h"

#define WINHEIGHT 600
#define WINWIDTH 800

using std::list;
using std::vector;


typedef struct 
{
	ActPolygon actPolygon;
	int nextIndex;
}BucketData;

class MidSpace : public QObject
{
	Q_OBJECT

public:
	MidSpace(QImage*);
	~MidSpace();
	//push一个BucketData数据块并更新y桶
	int pushWindowPolygon(WindowPolygon* pWp);
	void ClearAll();
	void ReserveVecCapacity(int n);

private:
	QImage* pMainBufferImage;
	int yBucketInt[WINHEIGHT];	//Y桶
	void clearYBucket();	//清除Y桶
	
	vector<BucketData> bucketDataVec;	//桶数据数组
	list<ActLinePair> actLinePairList;	//活化边对列表
	void init();

	//仅仅是把一个BucketData块push进去而已，不更新y桶
	int pushBucketData(WindowPolygon* pWinPolygon);
	int pushBucketData(ActPolygon *actPolygon);

	double depthBuf[WINWIDTH];	//深度缓冲
	QRgb colorBuf[WINWIDTH];	//颜色缓冲
	void clearLinebuf();

	QRgb getColor(ActLinePair* pActLinePair, int x, int y, bool smoothEnabled);

public slots:
	void StartScan(bool smoothEnabled, bool lineEnabled);

signals:
	void scanDone();
};


#endif