#ifndef BASELINE_H
#define BASELINE_H

#include <vector>
#include "NeighborSubMesh.h"



namespace Caca{

	class BaseLine : public std::vector<unsigned int>
	{
	public:
		BaseLine();
		~BaseLine();
		void SetContainer(NeighborSubMesh *p) {pContainer = p;};
		NeighborSubMesh* GetContainer() {return pContainer;};
		Vector3 GetVertexInitPos(unsigned int i);
		Vector3 GetVertexInitPos(BaseLine::iterator iter);
		void Tighten();
		Vector3 GetMidPoint();
		Vector3 GetNorm();
		unsigned int GetInternalPoint(unsigned int sp);
		unsigned int GetInternalPoint();
		void GetAllInternalPoints(unsigned int idx, vector<unsigned int> &internalPoints);
		void RemovePatchesInside(vector<unsigned int> &vertexes);
		void Gen(std::string name, std::string anothername);
		void Revers();
		std::string GetContainerName() {return m_ContainerName;};
		vector<Vector3>& CopyInitPos();
		int Cling2Mesh();
		//for test
		void show();

	protected:
	private:
		NeighborSubMesh *pContainer;
		std::string m_ContainerName;
		bool isInternal(Vector3 p);
		bool isOnLine(unsigned int i);
		bool push2UIVec(unsigned idx, vector<unsigned int> &vec);

	};
}
#endif