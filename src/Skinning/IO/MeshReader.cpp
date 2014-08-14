#include "meshreader.h"
#include "qfile.h"
#include "qtextstream.h"
#include "SubMesh.h"
#include "submeshreader.h"
#include "Mesh.h"

using namespace Caca;

MFAErrCode MeshReader::Read( Mesh* mesh, QString fileName, Skeleton* pSkl /*= NULL*/, MotionClip* pMC /*= NULL*/ )
{
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly)) {
		return MFA_OPEN_FAILED;
	}
	QTextStream in(&file);

	QString attrName;
	//read mesh info first
	int subMeshCount;
	in >> attrName >> subMeshCount;

	for(int i = 0; i < subMeshCount; i++) {
		int subMeshIndex;
		QString meshType;
		in >> subMeshIndex;
		in >> attrName >> meshType;
		SubMesh *sm;
		MFAErrCode err;
		if(meshType == "SubMesh") {
			sm = new SubMesh;
			SubMeshReader reader;
			err = reader.Read(sm, in);				
		} else {
			printf("unknown mesh type %s\n", meshType.data());
			err = MFA_UNKNOWN_ERR;
		}
		/* else if(meshType == "NeighborSubMesh") {
		 sm = new NeighborSubMesh;
		 NeighborSubMeshReader reader;
		 err = reader.Read(sm, in);			
		 } else if(meshType == "PhysicsSubMesh") {
		 sm = new PhysicsSubMesh;
		 PhysicsSubMeshReader reader;
		 err = reader.Read(sm, in);
		 }*/
		if( err != MFA_NO_ERR) {
			return err;
		}
		mesh->AddSubMesh(sm);		
	}

	if(pSkl && pMC) {
		mesh->SetSkeleton(pSkl);
		mesh->AttachMotionClip(pMC);
	}
	
	return MFA_NO_ERR;
}