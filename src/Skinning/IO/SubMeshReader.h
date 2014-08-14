#ifndef SUBMESHREADER_H
#define SUBMESHREADER_H

#include "..\src\corelib\io\qtextstream.h"
#include "mfacommon.h"
#include "..\src\corelib\tools\qstringlist.h"

namespace Caca
{
	class SubMesh;

	class SubMeshReader
	{
	public:
		virtual MFAErrCode Read(SubMesh* subMesh, QTextStream &in);
	protected:
		QString m_AttrName;
		QStringList m_LineStrList;
	};
}

#endif