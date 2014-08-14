#ifndef MESHWRITER_H
#define MESHWRITER_H

#include "mfacommon.h"
#include  <QString>

namespace Caca
{

	class Mesh;

	class MeshWriter
	{
	public:
		 MFAErrCode Write(Mesh * mesh, QString fileName);
	};
}

#endif