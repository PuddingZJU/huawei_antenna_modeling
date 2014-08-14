#include "MFACommon.h"
#include "meshwriter.h"
#include "..\Mesh.h"

#include "..\SubMesh.h"
#include "..\src\gui\dialogs\qfiledialog.h"
//#include "..\VDModel\NeighborSubMesh.h"
//#include "neighborsubmeshwriter.h"
//#include "subdivisionsubmeshwriter.h"
// #include "..\CharacterModel\SubdivisionSubMesh.h"
// #include "..\Physics\PhysicsSubMesh.h"
// #include "physicssubmeshwriter.h"
#include "..\src\corelib\io\qtextstream.h"
#include "SubMeshWriter.h"

using namespace Caca;

MFAErrCode MeshWriter::Write( Mesh * mesh, QString fileName)
{
	//if(fileName.isEmpty()) {
	//	std::string prjFolder = CacaConfig::GetFolder();
	//	fileName = QFileDialog::getSaveFileName(
	//		0, 
	//		"Select a file to save", 
	//		QString::fromAscii(prjFolder));
	//}
	//if(fileName.isEmpty()) {
	//	return MFA_USER_CANCEL;
	//}
	QFile file(fileName);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return MFA_OPEN_FAILED;
	}
	QTextStream out(&file);

	//write mesh info first
	out << "SubMeshCount " << mesh->GetSubMeshCount() << "\n";
	
	//write all the sub-meshes
	for(int i = 0; i < mesh->GetSubMeshCount(); i++) {
		out << i << "\n";
		SubMesh * sm = mesh->GetSubMesh(i);
		SubMeshWriter smwriter;
		smwriter.Write(sm, out);
// 		NeighborSubMesh* nsm = dynamic_cast<NeighborSubMesh*>(sm);
// 		if(nsm) {
// 			NeighborSubMeshWriter nsmWriter;			
// 			nsmWriter.Write(nsm, out);
// 			continue;
// 		}
// 		PhysicsSubMesh* psb = dynamic_cast<PhysicsSubMesh*>(sm);
// 		if(psb) {
// 			PhysicsSubMeshWriter psmWriter;
// 			psmWriter.Write(psb, out);
// 			continue;
// 		} else {
// 			SubdivisionSubMesh* ssm = dynamic_cast<SubdivisionSubMesh*>(sm);
// 			if(ssm) {
// 				SubdivisionSubMeshWriter ssmWriter;
// 				ssmWriter.Write(ssm, out);
// 				continue;
// 			}
// 		}
	}
	file.flush();
	file.close();
	return MFA_NO_ERR;
}