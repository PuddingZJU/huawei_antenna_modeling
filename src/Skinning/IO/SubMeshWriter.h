#ifndef SUBMESHWRITER_H
#define SUBMESHWRITER_H

#include "mfacommon.h"
#include  <QString>
#include "qfile.h"
#include <QTextStream>

namespace Caca
{

	class SubMesh;

	class SubMeshWriter
	{
	public:
		virtual MFAErrCode Write(SubMesh* subMesh, QTextStream& out);
	};
}

#endif