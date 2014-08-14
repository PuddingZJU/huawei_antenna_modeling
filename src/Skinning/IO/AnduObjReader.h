#ifndef ObjReader_h__
#define ObjReader_h__

#include "ObjReader.h"
#include <QString>

namespace Caca
{
	class SubMesh;
	class Mesh;
}

namespace Andu
{
	class AnduObjReader : public ObjReader
	{
	public:
		AnduObjReader();
		~AnduObjReader();

		virtual bool ReadIt(QString filePath);

		Caca::Mesh* Mesh() const { return m_pMesh; }
		void Mesh(Caca::Mesh* val) { m_pMesh = val; }

		bool isAnduBox(QString filePath);

	protected:
		Caca::Mesh* m_pMesh;

		void genAnduBoxMesh();

	private:
	};
}

#endif // ObjReader_h__
