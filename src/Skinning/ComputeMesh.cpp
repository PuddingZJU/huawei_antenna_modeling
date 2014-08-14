#include "computemesh.h"
#include <list>
#include "ComputeVector.h"
#include "SubMesh.h"

using std::list;
using namespace Caca;

Vector3 Caca::ComputeMesh::ComputeMidDyn( SubMesh* sb )
{
	Vector3 ret;
	for(int i = 0; i < sb->GetVertexCount(); i++) {
		ret += sb->GetVertexPos(i);
	}
	return ret/sb->GetVertexCount();
}

Vector3 Caca::ComputeMesh::ComputeMidInit( SubMesh* sb )
{
	Vector3 ret;
	for(int i = 0; i < sb->GetVertexCount(); i++) {
		ret += sb->GetVertexInitPos(i);
	}
	return ret/sb->GetVertexCount();
}

bool Caca::ComputeMesh::Intersection( const Vector3& p, const Vector3& n,
										const SubMesh& subMesh, Vector3* ret,
										bool initVertexFlag)
{
	const list<Patch>& patches = subMesh.GetPatchList();
	list<Patch>::const_iterator pi;
	double mindis = 0xffff;
	Vector3 nearestIp;

	if(!initVertexFlag) {
		for(pi = patches.begin(); pi != patches.end(); pi++) {
			Patch patch = *pi;
			Vector3 p1 = subMesh.GetVertexPos(patch.vertexIndexOne);
			Vector3 p2 = subMesh.GetVertexPos(patch.vertexIndexTwo);
			Vector3 p3 = subMesh.GetVertexPos(patch.vertexIndexThree);
			Vector3 ip = ComputeVector::Intersection(p, n, p1, p2, p3);
			if(ComputeVector::IsInTriangle(ip, p1, p2, p3)) {
				double dis = p.Distance(ip);
				if(dis < mindis) {
					mindis = dis;
					nearestIp = ip;
				}
			}
		}
	} else {
		for(pi = patches.begin(); pi != patches.end(); pi++) {
			Patch patch = *pi;
			Vector3 p1 = subMesh.GetVertexInitPos(patch.vertexIndexOne);
			Vector3 p2 = subMesh.GetVertexInitPos(patch.vertexIndexTwo);
			Vector3 p3 = subMesh.GetVertexInitPos(patch.vertexIndexThree);
			Vector3 ip = ComputeVector::Intersection(p, n, p1, p2, p3);
			if(ComputeVector::IsInTriangle(ip, p1, p2, p3)) {
				double dis = p.Distance(ip);
				if(dis < mindis) {
					mindis = dis;
					nearestIp = ip;
				}
			}
		}
	}
	if(mindis != 0xffff) {
		*ret = nearestIp;
		return true;
	} else {
		return false;
	}
}

double Caca::ComputeMesh::nearestDistance( const Vector3& p, 
	const SubMesh& subMesh, Vector3* outip,
	bool initVertexFlag /*= false*/,
	DisToMeshMethod method/*= DTM_USE_PREDEFINED_NORMAL*/,
	int *patchIdx /*= 0*/,
	int *pVertexIdx /*= 0*/)
{
	const list<Patch>& patches = subMesh.GetPatchList();
	list<Patch>::const_iterator pi;
	double mindis = DBL_MAX;
	int vertexMinDisIdx = -1;
	
	Vector3 minip;
	int minpidx = -1;

	if(!initVertexFlag) {

		for(int i = 0; i < subMesh.GetVertexCount(); i++) {
			Vector3 vertexPos = subMesh.GetVertexPos(i);
			double dis = vertexPos.Distance(p);
			if(dis < mindis) {
				mindis = dis;
				vertexMinDisIdx = i;
				minip = vertexPos;
			}
		}

		int pidx = 0;
		for(pi = patches.begin(); pi != patches.end(); pi++) {
			Patch patch = *pi;
			if(patch.vertexIndexOne != vertexMinDisIdx &&
				patch.vertexIndexTwo != vertexMinDisIdx &&
				patch.vertexIndexThree != vertexMinDisIdx) {
					pidx++;
					continue;
			}
			Vector3 p1 = subMesh.GetVertexPos(patch.vertexIndexOne);
			Vector3 p2 = subMesh.GetVertexPos(patch.vertexIndexTwo);
			Vector3 p3 = subMesh.GetVertexPos(patch.vertexIndexThree);
			Vector3 ip;

			double dis = abs(ComputeVector::pointPlaneDistance(p, p1, p2, p3, &ip));
			if(dis < mindis && ComputeVector::IsInTriangle(ip, p1, p2, p3)) {				
				mindis = dis;
				minip = ip;
				minpidx = pidx;
			}

			pidx++;
		}
	} else {
		for(int i = 0; i < subMesh.GetVertexCount(); i++) {
			Vector3 vertexPos = subMesh.GetVertexInitPos(i);
			double dis = vertexPos.Distance(p);
			if(dis < mindis) {
				mindis = dis;
				vertexMinDisIdx = i;
				minip = vertexPos;
			}
		}

		int pidx = 0;
		for(pi = patches.begin(); pi != patches.end(); pi++) {
			Patch patch = *pi;
			if(patch.vertexIndexOne != vertexMinDisIdx &&
				patch.vertexIndexTwo != vertexMinDisIdx &&
				patch.vertexIndexThree != vertexMinDisIdx) {
					pidx++;
					continue;
			}
			Vector3 p1 = subMesh.GetVertexInitPos(patch.vertexIndexOne);
			Vector3 p2 = subMesh.GetVertexInitPos(patch.vertexIndexTwo);
			Vector3 p3 = subMesh.GetVertexInitPos(patch.vertexIndexThree);
			Vector3 ip;
			double dis = abs(ComputeVector::pointPlaneDistance(p, p1, p2, p3, &ip));
			if(dis < mindis && ComputeVector::IsInTriangle(ip, p1, p2, p3)) {
				mindis = dis;
				minip = ip;
				minpidx = pidx;
			}
			pidx++;
		}
	}
	if(outip) {
		*outip = minip;
	}	
	if(patchIdx) {
		*patchIdx = minpidx;
	}
	if(pVertexIdx) {
		*pVertexIdx = vertexMinDisIdx;
	}
	return mindis;
}

double Caca::ComputeMesh::nearestDistance( 
	const Vector3& p, 
	const Vector3& n, 
	const SubMesh& subMesh, 
	Vector3* outip,
	bool initVertexFlag /*= false*/,
	DisToMeshMethod method/*= DTM_USE_PREDEFINED_NORMAL*/,
	int *patchIdx /*= 0*/,
	int *pVertexIdx /*= 0*/)
{
	const list<Patch>& patches = subMesh.GetPatchList();
	list<Patch>::const_iterator pi;
	double mindis = DBL_MAX;
	int vertexMinDisIdx = -1;

	Vector3 minip;
	int minpidx = -1;

	if(!initVertexFlag) {

		for(int i = 0; i < subMesh.GetVertexCount(); i++) {
			Vector3 vertexPos = subMesh.GetVertexPos(i);
			double dis = vertexPos.Distance(p);
			if(dis < mindis) {
				mindis = dis;
				vertexMinDisIdx = i;
				minip = vertexPos;
			}
		}
		
	} else {
		for(int i = 0; i < subMesh.GetVertexCount(); i++) {
			Vector3 vertexPos = subMesh.GetVertexInitPos(i);
			double dis = vertexPos.Distance(p);
			if(dis < mindis) {
				mindis = dis;
				vertexMinDisIdx = i;
				minip = vertexPos;
			}
		}

	}
	if(outip) {
		*outip = minip;
	}	
	if(patchIdx) {
		*patchIdx = minpidx;
	}
	if(pVertexIdx) {
		*pVertexIdx = vertexMinDisIdx;
	}
	return mindis;
}

void Caca::ComputeMesh::getMaxMinInitPos( Caca::SubMesh* pSubMesh, Vector3& maxV, Vector3& minV )
{
	const std::list<Patch>& patchList = pSubMesh->GetPatchList();
	for(std::list<Patch>::const_iterator i = patchList.begin();
		i != patchList.end() ; i++)
	{
		Vector3 v1 = pSubMesh->GetVertexInitPos(i->vertexIndexOne);
		Vector3 v2 = pSubMesh->GetVertexInitPos(i->vertexIndexTwo);
		Vector3 v3 = pSubMesh->GetVertexInitPos(i->vertexIndexThree);

		updateMaxV(v1, maxV);
		updateMaxV(v2, maxV);
		updateMaxV(v3, maxV);
		updateMinV(v1, minV);
		updateMinV(v2, minV);
		updateMinV(v3, minV);
	}
}

void Caca::ComputeMesh::updateMaxV( const Vector3& v, Vector3& maxv )
{
	ComputeVector::updateMaxV(v, maxv);
}

void Caca::ComputeMesh::updateMinV( const Vector3& v, Vector3& minv )
{
	ComputeVector::updateMinV(v, minv);
}

void Caca::ComputeMesh::getMaxMinPos( Caca::SubMesh* pSubMesh, 
	Vector3& maxV, Vector3& minV, void (*transPos)(Vector3&) /*= 0*/ )
{
	const std::list<Patch>& patchList = pSubMesh->GetPatchList();
	for(std::list<Patch>::const_iterator i = patchList.begin();
		i != patchList.end() ; i++)
	{
		Vector3 v1 = pSubMesh->GetVertexPos(i->vertexIndexOne);
		Vector3 v2 = pSubMesh->GetVertexPos(i->vertexIndexTwo);
		Vector3 v3 = pSubMesh->GetVertexPos(i->vertexIndexThree);

		if(transPos) {
			transPos(v1);
			transPos(v2);
			transPos(v3);
		}

		updateMaxV(v1, maxV);
		updateMaxV(v2, maxV);
		updateMaxV(v3, maxV);
		updateMinV(v1, minV);
		updateMinV(v2, minV);
		updateMinV(v3, minV);
	}
}

Vector3 ComputeMesh::findNearestPointInXYPlane( const Vector3& srcp, 
											const SubMesh& subMesh,
											bool initVertexFlag /*= false*/ )
{
	double mindis = 0xffff;
	Vector3 nearestp;
	Vector2 srcp2(srcp.x, srcp.y);
	if(!initVertexFlag) {
		for(int i = 0; i < subMesh.GetVertexCount(); i++) {
			Vector3 p = subMesh.GetVertexPos(i);
			Vector2 p2(p.x, p.y);
			double dis = p2.Distance(srcp2);
			if(dis < mindis) {
				mindis = dis;
				nearestp = p;
			}
		}
	} else {
		for(int i = 0; i < subMesh.GetVertexCount(); i++) {
			Vector3 p = subMesh.GetVertexInitPos(i);
			Vector2 p2(p.x, p.y);
			double dis = p2.Distance(srcp2);
			if(dis < mindis) {
				mindis = dis;
				nearestp = p;
			}
		}
	}
	return nearestp;	
}