#ifndef EditableSubMesh_h__
#define EditableSubMesh_h__

#include "SubMesh.h"
#include "MeshVertexData.h"

namespace Andu
{
	class EditableSubMesh : public Caca::SubMesh
	{
	public:
		EditableSubMesh(void);
		EditableSubMesh(Caca::Mesh *pParent);
		EditableSubMesh(const Caca::SubMesh& sub, Caca::Mesh* pParent);

		Caca::MeshVertex getSkinningVertex(int idx) const;
		void setSkinningVertex(int idx, const Caca::MeshVertex& mv);

		Vector3 getSkinningVertexPos(int idx);
		void setSkinningVertexPos(int idx, const Vector3& pos);

		Caca::Mesh* getParentMesh() { return m_pParent; }

		void clearSkinningVertexData();

		void resetVertexToInit();
	protected:

	private:
	};
}

#endif // EditableSubMesh_h__