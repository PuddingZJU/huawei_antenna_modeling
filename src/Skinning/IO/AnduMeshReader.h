#ifndef AnduMeshReader_h__
#define AnduMeshReader_h__
#include <QString>

namespace Caca
{
	class Mesh;
}

namespace Andu
{
	class AnduMeshReader
	{
	public:
		bool Read(Caca::Mesh* mesh, QString filePath);
	protected:
	private:
	};
}
#endif // AnduMeshReader_h__
