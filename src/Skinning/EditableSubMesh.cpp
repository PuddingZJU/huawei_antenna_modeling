#include "EditableSubMesh.h"

using namespace Caca;
using namespace Andu;

Andu::EditableSubMesh::EditableSubMesh( void )
	: SubMesh()
{

}

Andu::EditableSubMesh::EditableSubMesh(Mesh *pParent)
	: SubMesh(pParent)
{

}

Andu::EditableSubMesh::EditableSubMesh(const SubMesh& sub, Mesh* pParent)
	: SubMesh(sub, pParent)
{
	
}

Caca::MeshVertex Andu::EditableSubMesh::getSkinningVertex( int idx ) const
{
	return m_pSkinMeshVertexData->GetMeshVertex(idx);
}

void Andu::EditableSubMesh::setSkinningVertex( int idx, const MeshVertex& mv )
{
	m_pSkinMeshVertexData->SetMeshVertex(idx, mv);
}

Vector3 Andu::EditableSubMesh::getSkinningVertexPos( int idx )
{
	return m_pSkinMeshVertexData->GetMeshVertexPos(idx);
}

void Andu::EditableSubMesh::setSkinningVertexPos( int idx, const Vector3& pos )
{
	m_pSkinMeshVertexData->SetMeshVertexPos(idx, pos);
}

void Andu::EditableSubMesh::clearSkinningVertexData()
{
	int preCount = GetVertexCount();
	m_pSkinMeshVertexData->AllocateBuffer(0);
	m_pSkinMeshVertexData->AllocateBuffer(preCount);
}

void Andu::EditableSubMesh::resetVertexToInit()
{
	for(int i = 0; i < GetVertexCount(); i++) {
		setSkinningVertex(i, GetInitVertex(i));
	}
}

