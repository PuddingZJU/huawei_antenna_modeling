#ifndef MeshToolbox_h__
#define MeshToolbox_h__

#include <map>
#include <vector>
#include "Vector3Cmp.h"
#include "ComputeMesh.h"
#include <QSize>
#include <QStringList>
#include <QPainter>

using std::map;
using std::vector;

namespace Caca
{
	class Mesh;
	class SubMesh;
	class NeighborSubMesh;
}

using Caca::ComputeMesh;

class MeshToolbox
{
public:
	static void generateDefaultBoneAssignmentData(Caca::Mesh* pMesh);
	static void generateDefaultBoneAssignmentData(Caca::SubMesh* pSubMesh);

	static void getMaxMinPos(Caca::Mesh* pMesh, Vector3& maxV, Vector3& minV);
	static void getMaxMinInitPos(Caca::Mesh* pMesh, Vector3& maxV, Vector3& minV);

	static bool intersection(const Vector3& p, const Vector3& n, 
		const Caca::Mesh& mesh, Vector3* ret, bool initVertexFlag = false);

	static double disToMesh(const Vector3& p,
		const Caca::Mesh& mesh, Vector3* interP,
		bool initVertexFlag = false,
		ComputeMesh::DisToMeshMethod method = ComputeMesh::DTM_USE_PREDEFINED_NORMAL);

	static double disToMesh(const Vector3& p, 
		const Vector3& n,		
		const Caca::Mesh& mesh,
		Vector3 *interP = 0,
		bool initVertexFlag = false);

	static void normalizeInitTranslation(Caca::Mesh* pMesh, Vector3 cen = Vector3());
	static void normalizeInitSize(Caca::Mesh* pMesh, Vector3 tarSize = Vector3(1.0, 1.0, 1.0));
	static void normalizeAverEdgeLen(Caca::Mesh* pMesh, double tarLen = 3.44076);

	static void mapMeshVertexInitPos(Caca::Mesh* pMesh, Matrix4 mat);
	static void mapMeshVertexSkinPosToScreen(Caca::Mesh* pMesh, Matrix4 mat, 
		QPainter& painter);

	static double averInitEdgeLen(Caca::Mesh* pMesh);
	static double averEdgeLen(Caca::Mesh* pMesh);
	
	static Caca::Mesh* genLevelSetMesh(const Caca::Mesh* pBaseMesh,
		double level);
	static Caca::Mesh* genEmptyMeshFrom(const Caca::Mesh* pMesh);
	static void genLevelSetMeshVertexData(const Caca::Mesh* pBaseMesh, Caca::Mesh* pLevelSetMesh, 
		double level);

	static void transformMesh(Caca::Mesh* pMesh, const Matrix4& mat);

	static Caca::Mesh* generateBoxMesh();

	static void mergeDuplacatedVertexes(Caca::Mesh* pMesh);
	static void mergeDuplacatedVertexes(Caca::SubMesh* pSubMesh);

	static Caca::Mesh* generateSelectedMesh(const Caca::Mesh* pMesh,
		const map<int, vector<bool> >& vertexSelFlagMap);

	static void printMeshVertexPos(Caca::Mesh* pMesh);

	static void mapToTexSpace(Caca::Mesh* pMesh, 
		const vector<Vector3>& pos3DVec,
		vector<Vector2>& tex2DVec);

	static void resetSkinningVertexToInit(Caca::Mesh* pMesh);

	static void mergeDuplacatedVertexBoneInfo(Caca::Mesh* pMesh);
	 
	static void normalizeVertexBoneWeightsToOne(Caca::Mesh* pMesh);

	static void filterSubmesh(Caca::Mesh* pMesh, QStringList nameFilter);
	

	static void copyWithoutSkinningVertex(Caca::Mesh* pSrcMesh, 
		Caca::Mesh* pTarMesh);
protected:
	static void updateMaxV(const Vector3& v, Vector3& maxv);

	static void updateMinV(const Vector3& v, Vector3& minv);
private:
};

#endif // MeshToolbox_h__
