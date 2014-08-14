#include "AnduObjReader.h"
#include "SubMesh.h"
#include <vector>
#include "WorldDot.h"
#include "MeshVertexData.h"
#include "Mesh.h"
#include "MeshToolbox.h"
#include "ConsoleToolbox.h"
#include "LogWriter.h"

using std::vector;

Andu::AnduObjReader::AnduObjReader()
	: m_pMesh(0)
{

}

Andu::AnduObjReader::~AnduObjReader()
{
	if(m_pMesh) {
		delete m_pMesh;
	}
}

bool Andu::AnduObjReader::ReadIt( QString filePath )
{
	if(isAnduBox(filePath)) {
		genAnduBoxMesh();
		return true;
	}

	vector<WorldDot> dotBuf;

	pWldDotVec = &dotBuf;

	bool err = ObjReader::ReadIt(filePath);
	if(!err) {
		return false;
	}

	if(dotBuf.size() % 3 != 0) {
		printf("at least one triangle patch is broken\n");
		return false;
	}

	if(m_pMesh) delete m_pMesh;

	m_pMesh = new Caca::Mesh;

	for(int j = 0; j < groupSepVec.size(); j++) {
		int si = groupSepVec[j];
		int ei = dotBuf.size();
		if(j != groupSepVec.size() - 1) {
			ei = groupSepVec[j + 1];
		}

		if(si == ei) {
			continue;
		}

		if((si - ei) %3 != 0) {
			printf("at least one triangle patch is broken in this group\n");
			continue;
		}

		Caca::SubMesh *pSM = new Caca::SubMesh;
		pSM->SetName(groupNameVec[j].toStdString());
		pSM->AllocateVertexBuffer(ei - si);
		for(int i = si; i < ei; i++) {
			WorldDot& dot = dotBuf[i];
			Caca::MeshVertex mv;
			mv.pos.x = dot.GetX();
			mv.pos.y = dot.GetY();
			mv.pos.z = dot.GetZ();		
			double norm[3];
			dot.GetNorm(norm);
			mv.normal.x = norm[0];
			mv.normal.y = norm[1];
			mv.normal.z = norm[2];
			double tex[2];
			dot.getTex(tex);
			mv.texture.x = tex[0];
			mv.texture.y = tex[1];
			pSM->SetVertex(i - si, mv);
		}

		for(int i = si; i < ei; i += 3) {		
			Caca::Patch patch;
			patch.vertexIndexOne = i - si;
			patch.vertexIndexTwo = i + 1 - si;
			patch.vertexIndexThree = i + 2 - si;
			pSM->AddPatch(patch);
		}

		m_pMesh->AddSubMesh(pSM);
		
		//if(pSM->Name() == "farmer:Body_1")
		//	m_pMesh->AddSubMesh(pSM);
	}

	MeshToolbox::mergeDuplacatedVertexes(m_pMesh);


	return true;
}

bool Andu::AnduObjReader::isAnduBox( QString filePath )
{
	QFile file(filePath);
	if(!file.open(QFile::Text | QFile::ReadOnly)) {
		printf("cannot open %s\n", filePath.toLatin1().data());
		return false;
	}
	QString l = file.readLine();
	if(l.contains("andu box")) {
		return true;
	} else {
		return false;
	}
}

void Andu::AnduObjReader::genAnduBoxMesh()
{
	if(m_pMesh) {
		delete m_pMesh;
	}
	m_pMesh = MeshToolbox::generateBoxMesh();
}

