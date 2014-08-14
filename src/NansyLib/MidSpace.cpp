#include "MidSpace.h"
#include <QMessageBox>
#include <QObject>
#include "ArrayToolBox.h"
#include <math.h>

QRgb colors[WINHEIGHT][WINWIDTH];

MidSpace::MidSpace(QImage* i)
: pMainBufferImage(i)
{
	ReserveVecCapacity(10000);
	init();
	//test();
}


MidSpace::~MidSpace()
{

}


void MidSpace::init()
{
	clearYBucket();
	clearLinebuf();
	bucketDataVec.clear();
	actLinePairList.clear();
}

void MidSpace::StartScan(bool smoothEnabled, bool lineEnabled)
{
	for(int i = 0; i < WINHEIGHT; i++){
		clearLinebuf();
		if(yBucketInt[i] != -1){
			BucketData* pBucketData = &(bucketDataVec[yBucketInt[i]]);
			ActLinePair actLinePair;
			
			if(actLinePair.FirstAdd(&(pBucketData->actPolygon))){
				actLinePairList.push_back(actLinePair);
			}			
			while(pBucketData->nextIndex != -1){
				pBucketData = &(bucketDataVec[pBucketData->nextIndex]);			
				if(actLinePair.FirstAdd(&(pBucketData->actPolygon))){
					actLinePairList.push_back(actLinePair);
				}
			}
		}
		list<ActLinePair>::iterator actLinePairIter = actLinePairList.begin();
		bool testFlag = false;
		while(actLinePairIter != actLinePairList.end()){
			if(testFlag){
				testFlag = testFlag;
			}
			testFlag = true;
			
			if(!lineEnabled){
				double zx = actLinePairIter->zl;
				for(int x = actLinePairIter->xl - 0.5; x <= actLinePairIter->xr - 0.5; x++){
					if(x >= 0 && x < WINWIDTH && zx < depthBuf[x]){
						depthBuf[x] = zx;
						colorBuf[x] = getColor(&(*actLinePairIter), x, i, smoothEnabled);
					}
					if(x + 1 <= actLinePairIter->xr - 0.5)
						zx -= actLinePairIter->dzx;				
				}
			} else{
				if((int)(actLinePairIter->xl - 0.5) >= 0){
					colorBuf[(int)(actLinePairIter->xl - 0.5)] = qRgb(0, 0, 0);
				}
				if((int)(actLinePairIter->xr - 0.5) < WINWIDTH){
					colorBuf[(int)(actLinePairIter->xr - 0.5)] = qRgb(0, 0, 0);
				}
			}
			actLinePairIter->dyl--;
			actLinePairIter->dyr--;
			if(actLinePairIter->dyl < 0){
				if(!actLinePairIter->AddLine()){					
					//绘制完一个三角形，移除之
					list<ActLinePair>::iterator tempIter = actLinePairIter;
					actLinePairIter++;
					actLinePairList.erase(tempIter);
					continue;
				} else{					
					actLinePairIter->dyl--;
					actLinePairIter->xl += actLinePairIter->dxl;
					actLinePairIter->zl += actLinePairIter->pLActLine->GetDzy();
				}
			} else{
				//更新左活化边
				actLinePairIter->xl += actLinePairIter->dxl;
				actLinePairIter->zl += actLinePairIter->pLActLine->GetDzy();
			}
			if(actLinePairIter->dyr < 0){
				if(!actLinePairIter->AddLine()){
					//绘制完一个三角形，移除之
					list<ActLinePair>::iterator tempIter = actLinePairIter;
					actLinePairIter++;
					actLinePairList.erase(tempIter);					
					continue;
				} else{
					actLinePairIter->dyr--;
					actLinePairIter->xr += actLinePairIter->dxr;
				}
			} else{	//更新右活化边
				actLinePairIter->xr += actLinePairIter->dxr;
			}
			actLinePairIter++;
		}
		for(int j = 0; j < WINWIDTH; j++){
			pMainBufferImage->setPixel(j, i, colorBuf[j]);			
		}
	}
	emit scanDone();
}

int MidSpace::pushBucketData(ActPolygon *actPolygon)
{
	BucketData bucketData;
	bucketData.actPolygon = *actPolygon;	
	bucketData.nextIndex = -1;
	bucketDataVec.push_back(bucketData);
	bucketDataVec.rbegin()->actPolygon.updatePointers();
	return bucketDataVec.size();
}

int MidSpace::pushBucketData(WindowPolygon* pWinPolygon)
{
	ActPolygon actPolygon(pWinPolygon);
	return pushBucketData(&actPolygon);
	
}

//int MidSpace::pushActPolygon(WindowPolygon* newPolygon)
//{
//	ActPolygon actPolygon(newPolygon);	
//	return pushActPolygon(&actPolygon);
//}
//
//int MidSpace::pushActPolygon(ActPolygon* pActPolygon)
//{
//	actPolygonList.push_back(*pActPolygon);
//	return actPolygonList.size();
//}

void MidSpace::ClearAll()
{
	init();
}

int MidSpace::pushWindowPolygon(WindowPolygon *pWp)
{
	ActPolygon actPolygon(pWp);
	int starty = actPolygon.GetStartY();
	if(starty >= WINHEIGHT || starty + actPolygon.GetDeltaY() < 0){
		return -1;
	} else if(starty < 0){
		starty = 0;
	}
	int index = yBucketInt[starty];
	if(index == -1){
		yBucketInt[starty] = pushBucketData(&actPolygon) - 1;
	}
	else{
		while(bucketDataVec[index].nextIndex != -1){
			index = bucketDataVec[index].nextIndex;
		}
		bucketDataVec[index].nextIndex = pushBucketData(&actPolygon) - 1;
	}
	return bucketDataVec.size();
}

//void MidSpace::delActPolygon(list<ActPolygon>::iterator actPolygonIter)
//{	
//	actPolygonList.erase(actPolygonIter);
//}

void MidSpace::clearLinebuf()
{
	for(int i = 0; i < WINWIDTH; i++){
		depthBuf[i] = MAXDBL;
		colorBuf[i] = qRgb(255,255,255);
	}
}

void MidSpace::clearYBucket()
{
	for(int i = 0; i < WINHEIGHT; i++){
		yBucketInt[i] = -1;
	}
}

QRgb MidSpace::getColor(ActLinePair* pActLinePair, int x, int y, bool smoothEnabled)
{
	if(smoothEnabled){
		return pActLinePair->pSrcPlygon->GetSrcWinPolygon()->GetColorInPos(x, y);
	} else{
		return pActLinePair->pSrcPlygon->GetSrcWinPolygon()->GetColor();
	}
}

void MidSpace::ReserveVecCapacity(int n)
{
	BucketData bd;
	for(int i = 0; i < n; i++){
		bucketDataVec.push_back(bd);
	}
	bucketDataVec.clear();
}