#include "submeshwriter.h"
#include "mfacommon.h"
#include "SubMesh.h"
#include "qfile.h"
#include "Mathematics.h"
#include "MeshVertexData.h"
#include "VertexBoneAssignmentData.h"

using namespace Caca;

MFAErrCode SubMeshWriter::Write( SubMesh* subMesh, QTextStream& out )
{
	out << "MeshType " << "SubMesh" << "\n";

	//write attributes
	out << "name " << QString::fromLatin1(subMesh->Name().data()) << "\n";
	out << "bIsStencil " << subMesh->IsStencil() << "\n";
	//out << "stencil" << subMesh->

	//write all vertexes info
	out << "vertexCount " << subMesh->GetVertexCount() << "\n";
	out << "MeshVertexData " << "\n";
	for(int i = 0; i < subMesh->GetVertexCount(); i++) {
		out << i << " " ;
		MeshVertex mv = subMesh->GetInitVertex(i);
		Vector3 pos = mv.pos;
		out << "pos " << pos.x << " " << pos.y << " " << pos.z << " " ;
		Vector3 norm = mv.normal;
		out << "normal " << norm.x << " " << norm.y << " " << norm.z << " " ;
		Vector2 texture = mv.texture;
		out << "texture " << texture.x << " " << texture.y << "\n";
	}
	out << "SkinMeshVertexData" << "\n";
	for(int i = 0; i < subMesh->GetVertexCount(); i++) {
		out << i << " " ;
		MeshVertex mv = subMesh->GetVertex(i);
		Vector3 pos = mv.pos;
		out << "pos " << pos.x << " " << pos.y << " " << pos.z << " " ;
		Vector3 norm = mv.normal;
		out << "normal " << norm.x << " " << norm.y << " " << norm.z << " " ;
		Vector2 texture = mv.texture;
		out << "texture " << texture.x << " " << texture.y << "\n";
	}

	//write all bone assignment data
	out << "VertexBoneAssignmentData" << "\n";
	for(int i = 0; i < subMesh->GetVertexCount(); i++) {
		VertexBoneAssignment vba = subMesh->GetBoneAssignment(i);
		out << vba.vertexIndex << " ";
		out << "nearestBoneNum " << vba.nearestBoneNum << "\n";
		std::vector<BoneAssignment> vec = vba.assignmentList;
		out << "assignmentListSize " << vec.size() << "\n";
		for(int j = 0; j < vec.size(); j++) {
			BoneAssignment ba = vec[j];
			out << "boneIndex " << ba.boneIndex << " " << "weight " << ba.weight << " ";
			Vector3 pos = ba.pos;
			out << "pos " << pos.x << " " << pos.y << " " << pos.z << " " ;
			Vector3 norm = ba.normal;
			out << "normal " << norm.x << " " << norm.y << " " << norm.z << "\n";			
		}
	}
	
	//write all patches info
	out << "PatchList" << "\n";
	out << "patchCount " << subMesh->GetPatchCount() << "\n";
	const std::list<Patch> &patchList = subMesh->GetPatchList();
	std::list<Patch>::const_iterator piter = patchList.begin();
	for(int i = 0; piter != patchList.end(); i++, piter++){
		out << i << " " ;
		Patch p = *piter;
		out << p.vertexIndexOne << " " << p.vertexIndexTwo << " " << p.vertexIndexThree << "\n";
	}
	//
	return MFA_NO_ERR;
}