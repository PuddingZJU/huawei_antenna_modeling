#include "mfacommon.h"
#include "..\src\corelib\tools\qstring.h"
#ifndef MESHREADER_H
#define MESHREADER_H

namespace Caca
{

	class Mesh;
	class Skeleton;
	class MotionClip;

	class MeshReader
	{
	public:
		MFAErrCode Read(Mesh* mesh, QString fileName, 
			Skeleton* pSkl = NULL, MotionClip* pMC = NULL);
	};
}

#endif