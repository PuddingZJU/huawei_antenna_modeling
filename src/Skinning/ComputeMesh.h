#include "Mathematics.h"

namespace Caca{
	class SubMesh;
	class ComputeMesh
	{
	public:

		static Vector3 ComputeMidDyn(SubMesh* sb);

		static Vector3 ComputeMidInit(SubMesh* sb);

		static bool Intersection(const Vector3& p, const Vector3& n, 
			const SubMesh& subMesh, Vector3* ret, bool initVertexFlag = false);

		enum DisToMeshMethod {
			DTM_USE_PREDEFINED_NORMAL,
			DTM_USE_UNDEFINED_NORMAL
		};
		static double nearestDistance(const Vector3& p, const SubMesh& subMesh,
			Vector3* ip, bool initVertexFlag = false,
			DisToMeshMethod = DTM_USE_PREDEFINED_NORMAL,
			int *pPatchIdx = 0,
			int *pVertexIdx = 0);

		static double nearestDistance(const Vector3& p, const Vector3& n,
			const SubMesh& subMesh, 
			Vector3* ip, bool initVertexFlag = false,
			DisToMeshMethod = DTM_USE_PREDEFINED_NORMAL,
			int *pPatchIdx = 0,
			int *pVertexIdx = 0);

		static Vector3 findNearestPointInXYPlane(const Vector3& srcp, 
			const SubMesh& subMesh,
			bool initVertexFlag = false);

		static void getMaxMinInitPos(Caca::SubMesh* pSM, Vector3& maxV, Vector3& minV);
		static void getMaxMinPos(Caca::SubMesh* pSM, Vector3& maxV, Vector3& minV,
			void (*transPos)(Vector3&) = 0);

	protected:
		static void updateMaxV(const Vector3& v, Vector3& maxv);

		static void updateMinV(const Vector3& v, Vector3& minv);
	private:
	};
}