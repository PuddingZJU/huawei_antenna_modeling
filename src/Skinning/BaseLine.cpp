#include "BaseLine.h"
#include "MeshVertexData.h"
#include "EmitSurface.h"
#include <QVector>
#include <QList>
using namespace Caca;
using std::pair;

BaseLine::BaseLine()
: pContainer(NULL)
{

}

BaseLine::~BaseLine()
{

}

Vector3 BaseLine::GetVertexInitPos(unsigned int i )
{
	if(pContainer){
		return pContainer->GetMeshVertexDataVec()->GetMeshVertexPos(this->at(i));
	} else{
		return Vector3::ZERO;
	}
}

Vector3 BaseLine::GetVertexInitPos( vector<unsigned int>::iterator iter )
{
	if(pContainer){
		return pContainer->GetMeshVertexDataVec()->GetMeshVertexPos(*iter);
	} else{
		return Vector3::ZERO;
	}
}

void BaseLine::Tighten()
{
	if(empty()){
		return;
	}
	vector<unsigned int> temp;
	BaseLine::iterator iter = begin();
	temp.push_back(*iter);
	for(; iter != end(); iter++){
		if(GetVertexInitPos(iter) != GetVertexInitPos(temp.end() - 1)){
			temp.push_back(*iter);
		}
	}
	resize(temp.size());
	for(int i = 0; i < temp.size(); i++){
		(*this)[i] = temp[i];
	}
}

Vector3 BaseLine::GetNorm()
{
	Vector3 norm;
	Vector3 midPoint = GetMidPoint();
	for(vector<unsigned int>::iterator iter = begin(); iter != end(); iter++){
		int index = *iter;
		Vector3 now = GetVertexInitPos(iter);
		Vector3 next;
		if(index != back()){
			next = GetVertexInitPos(iter + 1);
		} else{
			next = GetVertexInitPos(begin());
		}
		now -= midPoint;
		next -= midPoint;
		now.Cross(next);
		norm += now;
	}
	norm.Normalize();
	//if(norm.Dot(midPoint - GetContainer()->GetMidPointOf(GetContainerName())) < 0){
	//	norm *= -1.0;
	//}
	return norm;
}

Vector3 BaseLine::GetMidPoint()
{
	Vector3 ret;
	for(int i = 0; i < size(); i++){
		ret += GetVertexInitPos(i);
	}
	//pContainer->createFlag(ret/size());
	return ret /= size();
}

unsigned int BaseLine::GetInternalPoint(unsigned int sp )
{	
	Caca::NeighborSubMesh *pMesh = GetContainer();
	Vector3 midp = GetMidPoint();
	vector<unsigned int> neighbors = pMesh->GetVertexNeighbors(sp);
	double min = (unsigned int)(-1);
	unsigned int nearest;
	for(int i = 0; i < neighbors.size(); i++){
		unsigned int idx = neighbors[i];
		if(isOnLine(idx)){
			continue;
		}
		Vector3 p = pMesh->GetVertexInitPos(idx);
		p -= midp;
		if(p.Length() < min){
			min = p.Length();
			nearest = idx;
		}
	}
	return nearest;
}

unsigned int BaseLine::GetInternalPoint()
{
	Vector3 midp = GetMidPoint();
	//GetContainer()->createFlag1(midp);
	double min = (unsigned int)(-1);
	unsigned int minidx;
	for(int i = 0; i < size(); i++) {
		vector<unsigned int> neighbors = GetContainer()->GetVertexNeighbors(at(i));
		for(int j = 0; j < neighbors.size(); j++) {
			if(isOnLine(neighbors[j])) {
				continue;
			}
			double dis = midp.Distance(GetContainer()->GetVertexInitPos(neighbors[j]));
			if(dis < min) {
				min = dis;
				minidx = neighbors[j];
			}
		}
	}
	return minidx;
}

bool BaseLine::isInternal( Vector3 p )
{
	Vector3 midp = GetMidPoint();
	Vector3 norm = GetNorm();
	EmitSurface eface(Line(p, p + norm), Line(midp, midp + norm));
	for(BaseLine::iterator iter = begin(); iter != end(); iter++){
		Vector3 now = GetVertexInitPos(iter);
		Vector3 next;
		if(iter != end() - 1){
			next = GetVertexInitPos(iter + 1);
		} else{
			next = GetVertexInitPos(0);
		}
		Vector3 interPoint = eface.IntersectedWith(Line(now, next));
		if(interPoint == Vector3::ZERO){
			return true;
		}
	}
	return false;
}

void BaseLine::GetAllInternalPoints(unsigned int idx, vector<unsigned int> &internalPoints )
{
	vector<unsigned int> neighbors = GetContainer()->GetVertexNeighbors(idx);
	for(int i = 0; i < neighbors.size(); i++){
		unsigned int j = neighbors[i];
		if(!isOnLine(j)){
			if(push2UIVec(j, internalPoints)){
				GetAllInternalPoints(j, internalPoints);
			}
		}
	}
}

bool BaseLine::isOnLine( unsigned int i )
{
	for(BaseLine::iterator iter = begin(); iter != end(); iter++){
		if(*iter == i){
			return true;
		}
	}
	return false;
}

bool BaseLine::push2UIVec( unsigned int idx, vector<unsigned int> &vec )
{
	for(int i = 0; i < vec.size(); i++){
		if(vec[i] == idx){
			return false;
		}
	}
	vec.push_back(idx);
	return true;
}

void BaseLine::RemovePatchesInside( vector<unsigned int> &vertexes )
{
	GetContainer()->InitPatchIter();
	for(int i = 0; i < vertexes.size(); i++){
		GetContainer()->SetVertexValid(vertexes[i], false);
	}
	while(!pContainer->IsPatchIterEnd()){
		Caca::Patch patch = pContainer->GetNowPatch();
		if(!GetContainer()->IsVertexValid(patch.vertexIndexOne)){
			GetContainer()->ErasePatch();
		} else if(!GetContainer()->IsVertexValid(patch.vertexIndexTwo)){
			GetContainer()->ErasePatch();
		} else if(!GetContainer()->IsVertexValid(patch.vertexIndexThree)){
			GetContainer()->ErasePatch();
		} else{
			pContainer->PatchIterSelfPlus();
		}
	}
}

void BaseLine::Gen( std::string name, std::string anothername )
{	
	this->clear();
	if(!pContainer){
		qDebug("Container of this baseline is not set yet. Can't generate baseline!");
		return;
	}
	if(pContainer->GetPatchCount() == 0) {
		//return;
	}
	VertexMatrix vm = pContainer->GetVertexMatrix(name);
	vector< BaseLine > baseLineVec;
	if(vm.name != "null"){	
		//If has vertex matrix
		//(this means the submesh(named by param-name) comes from subdivision mesh)
		vector<int> rowVec;
		switch(vm.type){
			case CLOSE_SPHERE:
				//no baseline in this case...
				break;
			case OPEN_RECTANGLE:
				//I'm thinking about it...
				break;
			case OPEN_CYLINDER:
				//en, it's easy.
				rowVec.push_back(0);
				rowVec.push_back(vm.matrix.size() - 1);
				break;
			case HEMI_SPHERE:
				//only one
				rowVec.push_back(vm.matrix.size() - 1);
				break;
			default:
				break;
		}		
		for(int i = 0; i < rowVec.size(); i++){
			baseLineVec.resize(i + 1);
			baseLineVec[i].SetContainer(pContainer);
			int row = rowVec[i];
			for(int j = 0; j < vm.matrix[row].size(); j++){
				if(GetContainer()->IsVertexValid(vm.matrix[row][j])){
					baseLineVec[i].push_back(vm.matrix[row][j]);
				}
			}
		}
	} else{	//Ok... we have to get baseline from the vertex neighbor info.
		
	}
	if(!baseLineVec.empty()){	//Sometimes there're so many baselines to choose...In fact, just two ...
		//First, check if any baselines is invalid.
		//Let's get the middle point of the mesh with the name "anothername"
		Vector3 midp = pContainer->GetMidPointOf(anothername);
		if(midp == Vector3::ZERO){
			qDebug("The submesh with the name anothername doesn't exist.");
			return;
		}
		vector<BaseLine>::iterator iter = baseLineVec.begin();
		while(iter != baseLineVec.end()){
			//Make a line from the mid point of the "another" mesh and the mid point of a baseline and
			//see if the line is intersected with the "container" of the baseline. 
			//If true, the baseline is invalid and erase it.
			Line l(midp, iter->GetMidPoint());
			Vector3 interpoint;
			if(pContainer->IntersectedWithPatch(name, &l, &interpoint, BOUNDED_INTERSECT) == 0){
				iter = baseLineVec.erase(iter);
				continue;
			}
			iter++;
		}
		//If still more than one baselines left, find a baseline which is the nearest
		//one to the mid point of the "another" mesh.
		double min = (unsigned int)(-1);
		vector<BaseLine>::iterator nearest = baseLineVec.end();
		for(vector<BaseLine>::iterator iter = baseLineVec.begin(); iter != baseLineVec.end(); iter ++){
			Vector3 baselineMidp = iter->GetMidPoint();
			double s = (baselineMidp - midp).Length();
			if(min > s){
				min = s;
				nearest = iter;
			}
		}
		if(nearest != baseLineVec.end() && !nearest->empty()){
			*this = *nearest;
		}
	}
	if(!empty()){
		//The norm of this baseline should toward outside of the mesh, otherwise, try to revers it.
		Vector3 norm = GetNorm();
		Vector3 mid = GetMidPoint();
		Line l(mid, mid + norm);
		if(pContainer->IntersectedWithPatch(&l, NULL, HALFBOUNDED_INTERSECT)){
			Revers();
		}
	}
	//last set... almost forget...
	m_ContainerName = name;
}

void BaseLine::Revers()
{
	BaseLine::reverse_iterator riter = rbegin();
	BaseLine temp = *this;
	temp.clear();
	while(riter != rend()){
		temp.push_back(*riter);
		riter ++;
	}
	*this = temp;
}

void BaseLine::show()
{
	for(int i = 0; i < size(); i++){
		Vector3 v = GetVertexInitPos(i);
		pContainer->createFlag(v);
	}
}

vector<Vector3>& BaseLine::CopyInitPos()
{
	vector<Vector3> *ret = new vector<Vector3>;
	for(int i = 0; i < size(); i ++){
		ret->push_back(GetVertexInitPos(i));
	}
	return *ret;
}

//return 0 already cling
//return 1 not cling. cling 2 mesh successful now
//return 2 not cling. cling 2 mesh failed!
int BaseLine::Cling2Mesh()
{
	int ret = 0;
	list<unsigned int> tempBaseLine;
	for(int i = 0; i < size(); i ++){
		tempBaseLine.push_back(at(i));
	}
	list<unsigned int>::iterator iter = tempBaseLine.begin();
	while(iter != tempBaseLine.end()){
		list<unsigned int>::iterator nextIter;
		list<unsigned int>::iterator tempIter = iter;
		tempIter ++;
		if(tempIter == tempBaseLine.end()){
			nextIter = tempBaseLine.begin();
		} else{
			nextIter = tempIter;
		}
		bool isClinged = false;
		GetContainer()->InitPatchIter(GetContainerName());
		while(!GetContainer()->IsPatchIterEnd()){
			Patch p = GetContainer()->GetNowPatch();
			if(GetContainer()->IsOnPatch(p, *iter) &&
				GetContainer()->IsOnPatch(p, *nextIter)){
					isClinged = true;
					break;
			}
			GetContainer()->PatchIterSelfPlus();
		}
		if(!isClinged){
			ret = 1;
			//cling the segment
			unsigned int startIdx = *iter;
			unsigned int endIdx = *nextIter;
			vector< pair<int, int> > nodeVec;
			nodeVec.push_back(pair<int, int>(-1, startIdx));
			int s, e;
			s = 0;
			e = 0;
			int nearest;
			while(s != nodeVec.size()){
				for(int i = s; i <= e; i++){
					vector<unsigned int> neighbors = GetContainer()->GetVertexNeighbors(nodeVec[i].second);
					nearest = -1;
					for(int j = 0; j < neighbors.size(); j++){						
						if(neighbors[j] == endIdx){
							nearest = i;
							break;
						}
						if(isOnLine(neighbors[j])){
							continue;
						}
						int k;
						for(k = 0; k < nodeVec.size(); k++){
							if(nodeVec[k].second == neighbors[j]){
								break;
							}
						}
						if(k == nodeVec.size()){
							nodeVec.push_back(pair<int, int>(i, neighbors[j]));
						}
					}
					if(nearest > -1){
						break;
					}
				}
				if(nearest > -1){
					break;
				} else{
					s = e + 1;
					e = nodeVec.size() - 1;
				}
			}
			if(nearest > -1){
				vector<unsigned int> insertVertexes;				
				int idx = nearest;
				while(idx != 0){
					insertVertexes.push_back(nodeVec[idx].second);
					idx = nodeVec[idx].first;
				}
				for(int i = 0; i < insertVertexes.size() ; i++){
					nextIter = tempBaseLine.insert(nextIter, insertVertexes[i]);
				}				
			} else{
				return 2;
			}
		}
		iter++;
	}
	clear();
	iter = tempBaseLine.begin();
	while(iter != tempBaseLine.end()){
		push_back(*iter);
		iter++;
	}
	return ret;
}