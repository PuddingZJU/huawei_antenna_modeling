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
	//pushһ��BucketData���ݿ鲢����yͰ
	int pushWindowPolygon(WindowPolygon* pWp);
	void ClearAll();
	void ReserveVecCapacity(int n);

private:
	QImage* pMainBufferImage;
	int yBucketInt[WINHEIGHT];	//YͰ
	void clearYBucket();	//���YͰ
	
	vector<BucketData> bucketDataVec;	//Ͱ��������
	list<ActLinePair> actLinePairList;	//��߶��б�
	void init();

	//�����ǰ�һ��BucketData��push��ȥ���ѣ�������yͰ
	int pushBucketData(WindowPolygon* pWinPolygon);
	int pushBucketData(ActPolygon *actPolygon);

	double depthBuf[WINWIDTH];	//��Ȼ���
	QRgb colorBuf[WINWIDTH];	//��ɫ����
	void clearLinebuf();

	QRgb getColor(ActLinePair* pActLinePair, int x, int y, bool smoothEnabled);

public slots:
	void StartScan(bool smoothEnabled, bool lineEnabled);

signals:
	void scanDone();
};


#endif