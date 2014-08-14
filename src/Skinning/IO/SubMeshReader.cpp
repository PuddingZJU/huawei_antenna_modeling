#include "submeshreader.h"
#include "..\SubMesh.h"
#include "..\MeshVertexData.h"
#include "..\VertexBoneAssignmentData.h"

using namespace Caca;

MFAErrCode SubMeshReader::Read( SubMesh* subMesh, QTextStream &in )
{
	QString type;

	if(in.pos() == 0) {
		in >> m_AttrName >> type;
	}	

	QString name;
	
	in >> m_AttrName >> name;

	subMesh->SetName(name.toAscii().data());

	int bIsStencil;
	in >> m_AttrName >> bIsStencil;

	unsigned int vertexCount;
	in >> m_AttrName >> vertexCount;

	in >> m_AttrName;
	if(m_AttrName == "MeshVertexData") {
		subMesh->AllocateVertexBuffer(vertexCount);
		for(int i = 0; i < vertexCount; i++) {
			int index;
			in >> index;

			//pos
			Vector3 pos;
			in >> m_AttrName >> pos.x >> pos.y >> pos.z;

			//normal
			Vector3 normal;
			in >> m_AttrName >> normal.x >> normal.y >> normal.z;

			//texture
			Vector2 texture;
			in >> m_AttrName >> texture.x >> texture.y;

			MeshVertex mv;
			mv.normal = normal;
			mv.pos = pos;
			mv.texture = texture;

			subMesh->SetVertex(index, mv);
		}
	} else {
		return MFA_READER_FAILED;
	}

	in >> m_AttrName;
	if(m_AttrName == "SkinMeshVertexData") {
		for(int i = 0; i < vertexCount; i++) {
			int index;
			in >> index;

			//pos
			Vector3 pos;
			in >> m_AttrName >> pos.x >> pos.y >> pos.z;

			//normal
			Vector3 normal;
			in >> m_AttrName >> normal.x >> normal.y >> normal.z;

			//texture
			Vector2 texture;
			in >> m_AttrName >> texture.x >> texture.y;

			MeshVertex mv;
			mv.normal = normal;
			mv.pos = pos;
			mv.texture = texture;

			//subMesh->SetVertex(index, mv);
		}
	}

	in >> m_AttrName;
	if(m_AttrName == "VertexBoneAssignmentData") {
		for(int i = 0; i < vertexCount; i++) {
			int index;
			in >> index;
			
			int nearestBoneNum;
			in >> m_AttrName >> nearestBoneNum;

			int assignmentListSize;
			in >> m_AttrName >> assignmentListSize;

			std::vector<BoneAssignment> assignmentList;
			assignmentList.resize(assignmentListSize);

			for(int j = 0; j < assignmentListSize; j++) {
				int boneIndex;
				in >> m_AttrName >> boneIndex;
				double weight;
				in >> m_AttrName >> weight;
				//pos
				Vector3 pos;
				in >> m_AttrName >> pos.x >> pos.y >> pos.z;
				//normal
				Vector3 normal;
				in >> m_AttrName >> normal.x >> normal.y >> normal.z;
				BoneAssignment ba;
				ba.boneIndex = boneIndex;
				ba.normal = normal;
				ba.pos = pos;
				ba.weight = weight;
				assignmentList[j] = ba;
			}

			VertexBoneAssignment vba;
			vba.assignmentList = assignmentList;
			vba.nearestBoneNum = nearestBoneNum;
			vba.vertexIndex = index;
			subMesh->AddAssignment(vba);
		}
	}

	
	in >> m_AttrName;
	if(m_AttrName == "PatchList") {
		int patchCount;
		in >> m_AttrName >> patchCount;	
		subMesh->AllocatePatchList(patchCount);
		std::list<Patch> &pList = subMesh->m_patchList;
		std::list<Patch>::iterator pIter = pList.begin();
		for(int i = 0; i < patchCount, pIter != pList.end(); pIter++, i++) {
			int index;
			unsigned int v1, v2, v3;
			in >> index >> v1 >> v2 >> v3;
			pIter->vertexIndexOne = v1;
			pIter->vertexIndexTwo = v2;
			pIter->vertexIndexThree = v3;						
		}
	}	
	
	return MFA_NO_ERR;
}