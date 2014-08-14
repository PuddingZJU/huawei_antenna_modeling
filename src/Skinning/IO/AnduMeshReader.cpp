#include "AnduMeshReader.h"
#include "Mesh.h"
#include "qfileinfo.h"
#include "AnduObjReader.h"
#include "IO\MeshReader.h"
#include "SubMesh.h"
#include "LogWriter.h"
#include "MeshToolbox.h"

bool Andu::AnduMeshReader::Read( Caca::Mesh* pMesh, QString filePath )
{
	QFileInfo fio(filePath);

	if(fio.suffix() == "mesh") {
		Caca::MeshReader mReader;
		mReader.Read(pMesh, filePath);
	} else if(fio.suffix() == "obj") {
		AnduObjReader objReader;
		objReader.ReadIt(filePath);
		Caca::Mesh *pReadedMesh = objReader.Mesh();
		for(int i = 0; i < pReadedMesh->GetSubMeshCount(); i++) {
			Caca::SubMesh* pSubMesh = pReadedMesh->GetSubMesh(i);
			pMesh->AddSubMesh(pSubMesh);
		}
		for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
			pReadedMesh->DeleteSubMesh(pMesh->GetSubMesh(i));
		}
	}
		
	MeshToolbox::resetSkinningVertexToInit(pMesh);

	for(int i = 0; i < pMesh->GetSubMeshCount(); i++) {
		Caca::SubMesh* pSM = pMesh->GetSubMesh(i);
		WriteLog(QString("mesh: %1 vertexes in submesh %2 loaded").arg(
			pSM->GetVertexCount()).arg(i));
	}	
	return true;
}

