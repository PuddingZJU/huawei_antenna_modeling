#ifndef SUBMESHREADER_H
#define SUBMESHREADER_H

#include "qtextstream.h"
#include "mfacommon.h"
#include "qstringlist.h"

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