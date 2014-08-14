#define NOMINMAX
#include "Mesh.h"
#include "SubMesh.h"
#include "MeshToolbox.h"
#include "VertexBoneAssignmentData.h"
#include <basetsd.h>
#include "MeshVertexData.h"
#include <algorithm>
#include "EditableSubMesh.h"
#include "..\Util\LogWriter.h"
#include "..\QuasarMath\Vector3Cmp.h"
#include <map>
#include <list>
#include <vector>
#include "ComputeVector.h"
#include "Skeleton.h"
#include "VectorToolBox.h"
#include "ConsoleToolbox.h"
#include "MotionJoint.h"
#include "MotionClip.h"
#include <stack>
#include "ArrayToolBox.h"
#include "Line.h"

using namespace Caca;
using namespace Andu;

using std::list;
using std::map;
using std::vector;
using std::stack;

Vector3 getInitVertexPos(Caca::SubMesh* pSM, int idx)
{
	return pSM->GetVertexInitPos(idx);
}

Vector3 getVertexPos(Caca::SubMesh* pSM, int idx)
{
	return pSM->GetVertexPos(idx);
}

void MeshToolbox::generateDefaultBoneAssignmentData( Caca::Mesh* pMesh )
{
	for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
		generateDefaultBoneAssignmentData(pMesh->GetSubMesh(i));
	}
}

void MeshToolbox::generateDefaultBoneAssignmentData( Caca::SubMesh* pSubMesh )
{
	EditableSubMesh* pHelpEditSM = static_cast<EditableSubMesh*>(pSubMesh);
	Caca::Mesh* pCharMesh = pHelpEditSM->getParentMesh();

	Caca::Skeleton* pSke = pCharMesh->GetSkeleton();
	
	for(int i = 0; i < pSubMesh->GetVertexCount(); i++) {
		Vector3 vertexPos = pSubMesh->GetVertexInitPos(i);		
		vector<double> weights;
		double weightSum = 0;
		for(int j = 1; j < pSke->GetJointsCount(); j++) {
			Vector3 jointPos = pSke->GetJointPos(j);
			Vector3 pJointPos = pSke->GetJointPos(pSke->GetParent(j));
			Line l(jointPos, pJointPos);
			double dis = l.Distance(vertexPos, SEGMENT_LINE);
			weights.push_back(1.0/(dis*dis*dis*dis));
			weightSum += weights.back();
		}
		VectorToolBox<double>::mul(weights, 1.0/weightSum);
		int maxWeightIdx;
		double maxWeight = VectorToolBox<double>::maxEle(weights, &maxWeightIdx);
		for(int j = 0; j < weights.size(); j++) {
			pSubMesh->SetAssignment(i, j + 1, 0);
		}
		int parentJointIdx = pSke->GetParent(maxWeightIdx + 1);
		double parentDis = pSke->GetJointPos(parentJointIdx).Distance(vertexPos);
		double dis = pSke->GetJointPos(maxWeightIdx + 1).Distance(vertexPos);
		pSubMesh->SetAssignment(i, maxWeightIdx + 1, parentDis/(dis + parentDis));
		pSubMesh->SetAssignment(i, parentJointIdx, dis/(dis + parentDis));

		//pSubMesh->SetAssignment(i, 0, 1.0);
		
	}
}

void MeshToolbox::getMaxMinPos( Caca::Mesh* pMesh, Vector3& maxV, Vector3& minV )
{

	minV = Vector3((double)DBL_MAX, (double)DBL_MAX, (double)DBL_MAX);
	maxV = Vector3(-(double)DBL_MIN, -(double)DBL_MIN, -(double)DBL_MIN);

	for(int j = 0; j < pMesh->GetSubMeshCount(); j++) {
		Caca::SubMesh* pSubMesh = pMesh->GetSubMesh(j);
		const std::list<Patch>& patchList = pSubMesh->GetPatchList();
		for(std::list<Patch>::const_iterator i = patchList.begin();
			i != patchList.end() ; i++)
		{
			Caca::MeshVertex mv1 = pSubMesh->GetVertex(i->vertexIndexOne);
			Caca::MeshVertex mv2 = pSubMesh->GetVertex(i->vertexIndexTwo);
			Caca::MeshVertex mv3 = pSubMesh->GetVertex(i->vertexIndexThree);

			Vector3 v1 = mv1.pos;
			Vector3 v2 = mv2.pos;
			Vector3 v3 = mv3.pos;

			updateMaxV(v1, maxV);
			updateMaxV(v2, maxV);
			updateMaxV(v3, maxV);
			updateMinV(v1, minV);
			updateMinV(v2, minV);
			updateMinV(v3, minV);
		}
	}
}

void MeshToolbox::getMaxMinInitPos( Caca::Mesh* pMesh, Vector3& maxV, Vector3& minV )
{
	minV = Vector3((double)DBL_MAX, (double)DBL_MAX, (double)DBL_MAX);
	maxV = Vector3(-(double)DBL_MAX, -(double)DBL_MAX, -(double)DBL_MAX);

	for(int j = 0; j < pMesh->GetSubMeshCount(); j++) {
		Caca::SubMesh* pSubMesh = pMesh->GetSubMesh(j);

		ComputeMesh::getMaxMinInitPos(pSubMesh, maxV, minV);
	}
}

void MeshToolbox::updateMaxV( const Vector3& v, Vector3& maxv )
{
	ComputeVector::updateMaxV(v, maxv);
}

void MeshToolbox::updateMinV( const Vector3& v, Vector3& minv )
{
	ComputeVector::updateMinV(v, minv);
}

bool MeshToolbox::intersection( const Vector3& p, const Vector3& n,
	const Caca::Mesh& mesh, Vector3* ret, bool initVertexFlag /*= false*/ )
{
	double mindis = DBL_MAX;
	Vector3 nearestIp;
	for(int i = 0; i < mesh.GetSubMeshCount(); i++) {
		const SubMesh& sm = *mesh.GetSubMesh(i);
		Vector3 ip;
		if(!ComputeMesh::Intersection(p, n, sm, &ip, initVertexFlag)) {
			continue;
		}
		double dis = p.Distance(ip);
		if(dis < mindis) {
			mindis = dis;
			nearestIp = ip;
		}
	}
	if(mindis != DBL_MAX) {
		*ret = nearestIp;
		return true;
	} else {
		return false;
	}	
}

double MeshToolbox::disToMesh( const Vector3& p,
	const Caca::Mesh& mesh, Vector3* outInterP, 
	bool initVertexFlag /*= false*/,
	ComputeMesh::DisToMeshMethod method /*= DTM_USE_PREDEFINED_NORMAL*/)
{
	double mindis = DBL_MAX;
	Vector3 minip;
	Vector3 np;
	
	for(int i = 0; i < mesh.GetSubMeshCount(); i++) {
		const SubMesh& sm = *mesh.GetSubMesh(i);
		Vector3 ip;
		double d = ComputeMesh::nearestDistance(p, sm, &ip, initVertexFlag);
		if(d < mindis) {
			mindis = d;
			minip = ip;
		}
	}
	if(outInterP) {
		*outInterP = minip;
	}
	return mindis;
}

double MeshToolbox::disToMesh( const Vector3& p,
	const Vector3& n, const Caca::Mesh& mesh, 
	Vector3 *outInterP /*= 0*/, bool initVertexFlag /*= false*/ )
{
	double mindis = DBL_MAX;
	Vector3 minip;
	Vector3 np;

	for(int i = 0; i < mesh.GetSubMeshCount(); i++) {
		const SubMesh& sm = *mesh.GetSubMesh(i);
		Vector3 ip;
		double d = ComputeMesh::nearestDistance(p, n, sm, &ip, initVertexFlag);
		if(d < mindis) {
			mindis = d;
			minip = ip;
		}
	}
	if(outInterP) {
		*outInterP = minip;
	}
	return mindis;
}

void MeshToolbox::normalizeInitTranslation( Caca::Mesh* pMesh, 
	Vector3 cen /*= Vector3()*/ )
{
	Vector3 minPos, maxPos;
	getMaxMinInitPos(pMesh, maxPos, minPos);
// 	WriteLog(QString("max %1 %2 %3, min %4 %5 %6").arg(
// 		maxPos.x).arg(maxPos.y).arg(maxPos.z).arg(
// 		minPos.x).arg(minPos.y).arg(minPos.z));
	Vector3 currCen = (maxPos + minPos)/2.0;
	Vector3 t = cen - currCen;
	Matrix4 tMat;
	tMat.SetTranslate(t.x, t.y, t.z);
	WriteLog(QString("translate %1 %2 %3").arg(t.x).arg(t.y).arg(t.z));
	mapMeshVertexInitPos(pMesh, tMat);
}

void MeshToolbox::normalizeInitSize( Caca::Mesh* pMesh, 
	Vector3 tarSize /*= Vector3(1.0, 1.0, 1.0)*/ )
{
	Vector3 minPos, maxPos;
	getMaxMinInitPos(pMesh, maxPos, minPos);
	Vector3 currSize(abs(maxPos.x - minPos.x), 
		abs(maxPos.y - minPos.y),
		abs(maxPos.z - minPos.z));
	Vector3 scale(tarSize.x/currSize.x, tarSize.y/currSize.y, tarSize.z/currSize.z);
	Matrix4 sMat;
	sMat.SetScale(scale.x, scale.y, scale.z);
	WriteLog(QString("Scale %1 %2 %3").arg(scale.x).arg(scale.y).arg(scale.z));
	mapMeshVertexInitPos(pMesh, sMat);
}

void MeshToolbox::normalizeAverEdgeLen( Caca::Mesh* pMesh, 
	double tarLen /*= 3.44076*/ )
{
	double currAverEdgeLen = averInitEdgeLen(pMesh);
	if(currAverEdgeLen < M_LOW_TOLERANCE) {
		return;
	}
	double scale = tarLen/currAverEdgeLen;
	Matrix4 sMat;
	sMat.SetScale(scale, scale, scale);
	WriteLog(QString("scale %1").arg(scale));
	mapMeshVertexInitPos(pMesh, sMat);
}

void MeshToolbox::mapMeshVertexInitPos( Caca::Mesh* pMesh, Matrix4 mat )
{
	for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
		Caca::SubMesh* pSM = pMesh->GetSubMesh(i);
		for(int j = 0; j < pSM->GetVertexCount(); j++) {
			Vector3 pos = pSM->GetVertexInitPos(j);
			pos.Transform(mat);
			pSM->SetVertexPos(j, pos);
		}
	}
}

void MeshToolbox::mapMeshVertexSkinPosToScreen( Caca::Mesh* pMesh, 
	Matrix4 mat, QPainter& painter )
{
	for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
		Caca::SubMesh* pSM = pMesh->GetSubMesh(i);
		for(int j = 0; j < pSM->GetVertexCount(); j++) {
			Vector3 v = pSM->GetVertexPos(j);
			double in[4], out[4];
			in[0] = v.x;
			in[1] = v.y;
			in[2] = v.z;
			in[3] = 1.0;
			ArrayToolBox<double>::matrixMul41(mat.M, in, out);
			ArrayToolBox<double>::vectorScale(out, 4, 1.0/out[3]);		
			painter.drawPoint(out[0], out[1]);
		}
	}
}

Mesh* MeshToolbox::genEmptyMeshFrom( const Mesh* pMesh )
{
	Mesh* ret = new Caca::Mesh;
	for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
		Caca::SubMesh* pSM = new Caca::SubMesh(*pMesh->GetSubMesh(i), 
			ret);
		ret->AddSubMesh(pSM);
	}
	ret->SetSkeleton(pMesh->GetSkeleton());
	ret->AttachMotionClip(pMesh->GetMotionClip());
	return ret;
}

void MeshToolbox::genLevelSetMeshVertexData( const Mesh* pBaseMesh, 
	Mesh* pLevelSetMesh, double level )
{	
	AssertLog(level >= 0);
	if(level < 0) {
		level = 0;
	}
	
	{
		for(int j = 0; j < pBaseMesh->GetSubMeshCount(); j++) {
			SubMesh* pSubMesh = pBaseMesh->GetSubMesh(j);
			SubMesh* pLevelSubMesh = pLevelSetMesh->GetSubMesh(j);
			EditableSubMesh* proxySubMesh = static_cast<EditableSubMesh*>(pLevelSubMesh);
			const std::list<Patch>& patchList = pSubMesh->GetPatchList();
			for(std::list<Patch>::const_iterator i = patchList.begin();
				i != patchList.end() ; i++)
			{
				MeshVertex mv1 = pSubMesh->GetVertex(i->vertexIndexOne);
				MeshVertex mv2 = pSubMesh->GetVertex(i->vertexIndexTwo);
				MeshVertex mv3 = pSubMesh->GetVertex(i->vertexIndexThree);

				mv1.pos += mv1.normal*level;
				mv2.pos += mv2.normal*level;
				mv3.pos += mv3.normal*level;

				proxySubMesh->setSkinningVertex(i->vertexIndexOne, mv1);
				proxySubMesh->setSkinningVertex(i->vertexIndexTwo, mv2);
				proxySubMesh->setSkinningVertex(i->vertexIndexThree, mv3);
			}
		}
	}
}

Caca::Mesh* MeshToolbox::genLevelSetMesh( const Caca::Mesh* pBaseMesh, double level )
{
	Mesh* ret = genEmptyMeshFrom(pBaseMesh);
	genLevelSetMeshVertexData(pBaseMesh, ret, level);
	return ret;
}

void MeshToolbox::transformMesh( Caca::Mesh* pMesh, const Matrix4& mat )
{
	for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
		SubMesh* pSM = pMesh->GetSubMesh(i);
		EditableSubMesh* pESM = static_cast<EditableSubMesh*>(pSM);
		for(int j = 0; j < pSM->GetVertexCount(); j++) {
			Vector3 pos = pSM->GetVertexPos(j);
			pos.Transform(mat);
			pESM->setSkinningVertexPos(j, pos);
		}
	}
}

void setPatch(Patch* p, int i, int j, int k)
{
	p->vertexIndexOne = i;
	p->vertexIndexTwo = j;
	p->vertexIndexThree = k;
}

Caca::Mesh* MeshToolbox::generateBoxMesh()
{
	printf("generate box mesh\n");
	Caca::Mesh* pMesh = new Caca::Mesh;	
	Caca::SubMesh* pSM = new Caca::SubMesh;
	pMesh->AddSubMesh(pSM);

	pSM->AllocateVertexBuffer(12);
	pSM->SetVertexPos(0, Vector3());
	pSM->SetVertexPos(1, Vector3(0, 1.0, 0));
	pSM->SetVertexPos(2, Vector3(1.0, 0, 0));
	pSM->SetVertexPos(3, Vector3(1.0, 1.0, 0));
	pSM->SetVertexPos(4, Vector3(2.0, 0, 0));
	pSM->SetVertexPos(5, Vector3(2.0, 1.0, 0));
	pSM->SetVertexPos(6, Vector3(0, 0, 1.0));
	pSM->SetVertexPos(7, Vector3(0, 1.0, 1.0));
	pSM->SetVertexPos(8, Vector3(1.0, 0, 1.0));
	pSM->SetVertexPos(9, Vector3(1.0, 1.0, 1.0));
	pSM->SetVertexPos(10, Vector3(2.0, 0, 1.0));
	pSM->SetVertexPos(11, Vector3(2.0, 1.0, 1.0));
	
	Vector3 n(-1.0, -1.0, -1.0);
	n.Normalize();
	pSM->SetVertexNormal(0, n);
	n.Normalize(Vector3(-1.0, 1.0, -1.0));
	pSM->SetVertexNormal(1, n);
	n.Normalize(Vector3(0, -1.0, -1.0));
	pSM->SetVertexNormal(2, n);
	n.Normalize(Vector3(0, 1.0, -1.0));
	pSM->SetVertexNormal(3, n);
	n.Normalize(Vector3(1.0, -1.0, -1.0));
	pSM->SetVertexNormal(4, n);
	n.Normalize(Vector3(1.0, 1.0, -1.0));
	pSM->SetVertexNormal(5, n);
	n.Normalize(Vector3(-1.0, -1.0, 1.0));
	pSM->SetVertexNormal(6, n);
	n.Normalize(Vector3(-1.0, 1.0, 1.0));
	pSM->SetVertexNormal(7, n);
	n.Normalize(Vector3(0, -1.0, 1.0));
	pSM->SetVertexNormal(8, n);
	n.Normalize(Vector3(0, 1.0, 1.0));
	pSM->SetVertexNormal(9, n);
	n.Normalize(Vector3(1.0, -1.0, 1.0));
	pSM->SetVertexNormal(10, n);
	n.Normalize(Vector3(1.0, 1.0, 1.0));
	pSM->SetVertexNormal(11, n);

	pSM->AddPatch(0, 1, 2);
	pSM->AddPatch(2, 1, 3);
	pSM->AddPatch(2, 3, 4);
	pSM->AddPatch(4, 3, 5);
	pSM->AddPatch(6, 0, 8);
	pSM->AddPatch(8, 0, 2);
	pSM->AddPatch(8, 2, 10);
	pSM->AddPatch(10, 2, 4);
	pSM->AddPatch(6, 7, 8);
	pSM->AddPatch(8, 7, 9);
	pSM->AddPatch(8, 9, 10);
	pSM->AddPatch(10, 9, 11);
	pSM->AddPatch(7, 1, 9);
	pSM->AddPatch(9, 1, 3);
	pSM->AddPatch(9, 3, 11);
	pSM->AddPatch(11, 3, 5);
	pSM->AddPatch(6, 7, 0);
	pSM->AddPatch(0, 7, 1);
	pSM->AddPatch(4, 5, 11);
	pSM->AddPatch(4, 11, 10);

	//generateDefaultBoneAssignmentData(pMesh);


	return pMesh;
}

void MeshToolbox::mergeDuplacatedVertexes( Caca::Mesh* pMesh )
{
	for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
		Caca::SubMesh* pSM = pMesh->GetSubMesh(i);
		mergeDuplacatedVertexes(pSM);
	}
}
void writelogPosIdxMap(const map<Vector3Cmp, int>& posIdxMap)
{
	auto iter  = posIdxMap.begin();
	while(iter != posIdxMap.end()) {
		Vector3Cmp pos = iter->first;
		int idx = iter->second;
		WriteLog(QString("%1 %2 %3 %4").arg(
			pos.v().x).arg(pos.v().y).arg(
			pos.v().z).arg(idx));
		iter++;
	}
}
void MeshToolbox::mergeDuplacatedVertexes( Caca::SubMesh* pSubMesh )
{
	int newGlobalIdx = 0;
	map<Vector3Cmp, int> posIdxMap;
	vector<Caca::MeshVertex> mvVec;
	for(int i = 0; i < pSubMesh->GetVertexCount(); i++) {
		Vector3Cmp pos(pSubMesh->GetVertexInitPos(i));
		map<Vector3Cmp, int>::iterator piIter = posIdxMap.find(pos);
		if(piIter == posIdxMap.end()) {
			posIdxMap[pos] = newGlobalIdx;
			mvVec.push_back(pSubMesh->GetInitVertex(i));
			newGlobalIdx++;
		}
	}
	
	list<Patch> patchList = pSubMesh->GetPatchList();
	list<Patch>::iterator pIter = patchList.begin();
	int count = 0;
	while(pIter != patchList.end()) {
		Patch& patch = *pIter;
		//printf("debug count %d\n", count);

		Vector3Cmp pos0(pSubMesh->GetVertexInitPos(patch.vertexIndexOne));
		Vector3Cmp pos1(pSubMesh->GetVertexInitPos(patch.vertexIndexTwo));
		Vector3Cmp pos2(pSubMesh->GetVertexInitPos(patch.vertexIndexThree));
		map<Vector3Cmp, int>::iterator piIter = posIdxMap.find(pos0);
		if(piIter == posIdxMap.end()) {
			writelogPosIdxMap(posIdxMap);
			WriteLog(QString("%1 %2 %3").arg(
				pos0.v().x).arg(pos0.v().y).arg(pos0.v().z));
		}
		AssertLog(piIter != posIdxMap.end());
		patch.vertexIndexOne = piIter->second;
		
		piIter = posIdxMap.find(pos1);
		if(piIter == posIdxMap.end()) {
			writelogPosIdxMap(posIdxMap);
			WriteLog(QString("%1 %2 %3").arg(
				pos1.v().x).arg(pos1.v().y).arg(pos1.v().z));
		}
		AssertLog(piIter != posIdxMap.end());
		patch.vertexIndexTwo = piIter->second;
		piIter = posIdxMap.find(pos2);
		if(piIter == posIdxMap.end()) {
			writelogPosIdxMap(posIdxMap);
			WriteLog(QString("%1 %2 %3").arg(
				pos2.v().x).arg(pos2.v().y).arg(pos2.v().z));
		}
		AssertLog(piIter != posIdxMap.end());
		patch.vertexIndexThree = piIter->second;	
		
		if(patch.vertexIndexOne == patch.vertexIndexTwo || 
			patch.vertexIndexOne == patch.vertexIndexThree ||
			patch.vertexIndexTwo == patch.vertexIndexThree) {
				printf("erase patch %d %d %d\n", patch.vertexIndexOne,
					patch.vertexIndexTwo, patch.vertexIndexThree);
				pIter = patchList.erase(pIter);
		} else {
			pIter++;
			count++;		
		}		
	}

	pSubMesh->AllocateVertexBuffer(newGlobalIdx);
	for(int i = 0; i < mvVec.size(); i++) {
		pSubMesh->SetVertex(i, mvVec[i]);
	}
	pSubMesh->ClearPatchList();
	pIter = patchList.begin();
	while(pIter != patchList.end()) {
		pSubMesh->AddPatch(*pIter);
		pIter++;
	}
}

void MeshToolbox::printMeshVertexPos( Caca::Mesh* pMesh )
{
	return;
	for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
		Caca::SubMesh* pSM = pMesh->GetSubMesh(i);
		for(int j = 0; j < pSM->GetVertexCount(); j++) {
			Vector3 pos = pSM->GetVertexPos(j);
			WriteLog(QString("%1 %2 %3 %4").arg(j).arg(pos.x).arg(pos.y).arg(pos.z));
		}
	}
}

Caca::Mesh* MeshToolbox::generateSelectedMesh( const Caca::Mesh* pMesh,
	const map<int, vector<bool> >& vertexSelFlagMap )
{
	Mesh* ret = new Mesh;
	for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
		const Caca::SubMesh* pSM = pMesh->GetSubMesh(i);
		EditableSubMesh* pNewSM = new EditableSubMesh;
		auto iter = vertexSelFlagMap.find(i);
		if(iter == vertexSelFlagMap.end()) {
			continue;
		}
		const vector<bool>& selFlagVec = iter->second;
		
		map<int, int> vertexIdxMap;	//old to new
		vector<MeshVertex> newMVVec;
		vector<MeshVertex> newInitMVVec;
		const list<Patch>& patchLst = pSM->GetPatchList();
		auto piter = patchLst.begin();
		while(piter != patchLst.end()) {
			Patch patch = *piter;
			if(selFlagVec[patch.vertexIndexOne] && 
				selFlagVec[patch.vertexIndexTwo] &&
				selFlagVec[patch.vertexIndexThree]) {					
					newMVVec.push_back(pSM->GetVertex(patch.vertexIndexOne));
					newInitMVVec.push_back(pSM->GetInitVertex(patch.vertexIndexOne));
					patch.vertexIndexOne = newMVVec.size() - 1;
					newMVVec.push_back(pSM->GetVertex(patch.vertexIndexTwo));
					newInitMVVec.push_back(pSM->GetInitVertex(patch.vertexIndexTwo));
					patch.vertexIndexTwo = newMVVec.size() - 1;
					newMVVec.push_back(pSM->GetVertex(patch.vertexIndexThree));
					newInitMVVec.push_back(pSM->GetInitVertex(patch.vertexIndexThree));
					patch.vertexIndexThree = newMVVec.size() - 1;					

					pNewSM->AddPatch(patch);
			}
			piter++;
		}
		
		pNewSM->AllocateVertexBuffer(newMVVec.size());
		for(int j = 0; j < newMVVec.size(); j++) {
			pNewSM->SetVertex(j, newInitMVVec[j]);
			pNewSM->setSkinningVertex(j, newMVVec[j]);
		}

		ret->AddSubMesh(pNewSM);
	}

	return ret;
}

void MeshToolbox::mapToTexSpace( Caca::Mesh* pMesh,
	const vector<Vector3>& pos3DVec, 
	vector<Vector2>& tex2DVec )
{	
	tex2DVec.resize(pos3DVec.size());
	for(int i = 0; i < pos3DVec.size(); i++) {
		Vector3 pos = pos3DVec[i];
		double mindis = DBL_MAX;
		Vector3 minip;
		int minpidx = -1;
		int minvidx = -1;
		Caca::SubMesh* pMinSM = 0;
		for(int j = 0; j < pMesh->GetSubMeshCount(); j++) {
			Caca::SubMesh* pSM = pMesh->GetSubMesh(j);
			Vector3 ip;
			int pidx = -1;
			int vidx = -1;
			double dis = ComputeMesh::nearestDistance(pos, *pSM, 
				&ip, false, Caca::ComputeMesh::DTM_USE_PREDEFINED_NORMAL,
				&pidx, &vidx);
			if(dis < mindis) {
				mindis = dis;
				minip = ip;
				minpidx = pidx;
				minvidx = vidx;
				pMinSM = pSM;
			}
		}		
		if(minpidx >= 0) {
			Caca::Patch minPatch = pMinSM->GetPatch(minpidx);
			vector<MeshVertex> poly(3);
			poly[0] = pMinSM->GetVertex(minPatch.vertexIndexOne);
			poly[1] = pMinSM->GetVertex(minPatch.vertexIndexTwo);
			poly[2] = pMinSM->GetVertex(minPatch.vertexIndexThree);
			Vector3 v0 = poly[0].pos;
			Vector3 v1 = poly[1].pos;
			Vector3 v2 = poly[2].pos;
			AssertLog(ComputeVector::IsInTriangle(minip, v0, v1, v2));
			Vector2 t0 = poly[0].texture;
			Vector2 t1 = poly[1].texture;
			Vector2 t2 = poly[2].texture;
			Vector2 t3 = ComputeVector::interpolate(v0, v1, v2, t0, t1, t2, minip);
			tex2DVec[i] = t3;
		} else if(minvidx >= 0) {
			 MeshVertex mv = pMinSM->GetVertex(minvidx);
			 tex2DVec[i] = mv.texture;
		}		
	}
	
}

double _averEdgeLen( Caca::Mesh* pMesh, 
	Vector3 (*getVertexPos)(Caca::SubMesh*, int))
{
	double edgeLenSum = 0;
	int edgeCount = 0;
	for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
		Caca::SubMesh* pSM = pMesh->GetSubMesh(i);
		const list<Patch>& patchLst = pSM->GetPatchList();
		auto piter = patchLst.begin();
		while(piter != patchLst.end()) {
			Patch patch = *piter;
			Vector3 v0 = getVertexPos(pSM, patch.vertexIndexOne);
			Vector3 v1 = getVertexPos(pSM, patch.vertexIndexTwo);
			Vector3 v2 = getVertexPos(pSM, patch.vertexIndexThree);
			edgeLenSum += v0.Distance(v1);
			edgeLenSum += v0.Distance(v2);
			edgeLenSum += v1.Distance(v2);
			piter++;
		}
		edgeCount += patchLst.size()*3;
	}
	if(edgeCount == 0) {
		return -1.0;
	}
	return edgeLenSum/(double)edgeCount;
}

double MeshToolbox::averInitEdgeLen( Caca::Mesh* pMesh )
{
	return _averEdgeLen(pMesh, getInitVertexPos);
}

double MeshToolbox::averEdgeLen( Caca::Mesh* pMesh )
{
	return _averEdgeLen(pMesh, getVertexPos);
}

void MeshToolbox::resetSkinningVertexToInit( Caca::Mesh* pMesh )
{
	for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
		Caca::SubMesh* pSM = pMesh->GetSubMesh(i);
		EditableSubMesh* pHelpSM = (EditableSubMesh*)pSM;
		pHelpSM->resetVertexToInit();
	}
}

void MeshToolbox::mergeDuplacatedVertexBoneInfo( Caca::Mesh* pMesh )
{
	for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
		Caca::SubMesh* pSM = pMesh->GetSubMesh(i);
		for(int j = 0; j < pSM->GetVertexCount(); j++) {
			VertexBoneAssignment vba = pSM->GetBoneAssignment(j);
			auto biter = vba.assignmentList.begin();
			vector<BoneAssignment> newAssignments;
			while(biter != vba.assignmentList.end()) {
				auto preBiter = newAssignments.begin();
				unsigned int curBoneIdx = biter->boneIndex;
				while(preBiter != newAssignments.end()) {
					unsigned int preBoneIdx = preBiter->boneIndex;
					if(preBoneIdx == curBoneIdx) {
						preBiter->weight += biter->weight;
						break;
					}
					preBiter++;
				}
				if(preBiter == newAssignments.end()) {
					newAssignments.push_back(*biter);
				}
				biter++;
			}
			vba.assignmentList = newAssignments;
			pSM->SetAssignment(vba);
		}
	}
}

void MeshToolbox::normalizeVertexBoneWeightsToOne(Caca::Mesh* pMesh)
{
	for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
		Caca::SubMesh* pSM = pMesh->GetSubMesh(i);
		for(int j = 0; j < pSM->GetVertexCount(); j++) {
			VertexBoneAssignment vba = pSM->GetBoneAssignment(j);
			auto biter = vba.assignmentList.begin();
			double wSum = 0;
			while(biter != vba.assignmentList.end()) {
				wSum += biter->weight;
				biter++;
			}

			//AssertLog(wSum > 0.000000001);
	
			biter = vba.assignmentList.begin();
			while(biter != vba.assignmentList.end()) {
				biter->weight /= wSum;
				biter++;
			}

			pSM->SetAssignment(vba);
		}
	}
}

void MeshToolbox::filterSubmesh( Caca::Mesh* pMesh, QStringList nameFilter )
{
	for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
		Caca::SubMesh* pSM = pMesh->GetSubMesh(i);
		if(!nameFilter.isEmpty() && nameFilter.contains(pSM->Name().data())) {
			WriteLog(QString("added submesh %1").arg(pSM->Name().data()));
			//pMesh->AddSubMesh(pSM);
		} else {
			WriteLog(QString("ignore submesh %1").arg(pSM->Name().data()));
			pMesh->DeleteSubMesh(pSM);
			delete pSM;
		}
	}
}


void MeshToolbox::copyWithoutSkinningVertex( Caca::Mesh* pSrcMesh, Caca::Mesh* pTarMesh )
{
	for(int i = 0; i < pSrcMesh->GetSubMeshCount(); i++) {
		Caca::SubMesh* pSM = new Caca::SubMesh(*pSrcMesh->GetSubMesh(i), pSrcMesh);
		EditableSubMesh* pEditSM = (EditableSubMesh*)(pSM);
		for(int j = 0; j < pSM->GetVertexCount(); j++) {
			pEditSM->setSkinningVertexPos(j, Vector3());
		}
		pTarMesh->AddSubMesh(pSM);
	}
}
