#ifndef SUBMESHWRITER_H
#define SUBMESHWRITER_H

#include "mfacommon.h"
#include "..\src\corelib\tools\qstring.h"
#include "..\src\corelib\io\qfile.h"
#include "..\src\corelib\io\qtextstream.h"

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