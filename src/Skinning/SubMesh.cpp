/** @file 
* @ brief �����������ʵ���ļ�.
* @author ������
* @date 2008-10-27
* @version 0.1
*
* ���ļ��ж��������Լ���صĲ���
*/

//#include <QtOpenGL>
#include "SubMesh.h"
#include "Mesh.h"
#include "MeshVertexData.h"
#include "Skeleton.h"
#include "VertexBoneAssignmentData.h"
//#include "MotionClipShow.h"
#include "MotionJoint.h"
#include "MotionClip.h"
#include "ComputeVector.h"

//#include "..//..//Physics/include/BoundingBox.h"

using namespace Caca;

SubMesh::SubMesh(void)
: m_name("SubMesh")
//, m_pBox(0)
//, m_pActiveBox(0)
, m_stencil("Invalid")
, m_bIsStencil(false)
{
	m_pParent = NULL;
	m_pMeshVertexData = new MeshVertexData;
	m_pSkinMeshVertexData = new MeshVertexData;
	m_pVertexBoneAssignmentData = new VertexBoneAssignmentData;
	m_patchList.clear();
}



/**  ���캯��
 *
 * @param pParent ��Ƥ����ģ��ָ��
 *
 *
 */
SubMesh::SubMesh(Mesh *pParent)
{
	m_pParent = pParent;
	m_pMeshVertexData = new MeshVertexData;
	m_pSkinMeshVertexData = new MeshVertexData;
	m_pVertexBoneAssignmentData = new VertexBoneAssignmentData;
	m_patchList.clear();
}

SubMesh::SubMesh(const SubMesh& sub, Mesh *pParent)
{
	m_pParent = pParent;
	m_pMeshVertexData = new MeshVertexData;
	m_pSkinMeshVertexData = new MeshVertexData;
	m_pVertexBoneAssignmentData = new VertexBoneAssignmentData;
	m_patchList.clear();

	AllocateVertexBuffer( sub.GetVertexCount() );

	for(int i = 0; i != sub.GetVertexCount(); ++i)
	{
		SetVertex( i, sub.GetInitVertex(i) );

		VertexBoneAssignment VBA = sub.GetBoneAssignment( i );

		AddAssignment(VBA);

	}

	m_patchList = sub.GetPatchList();

	m_name = sub.Name();

	m_bIsStencil = sub.IsStencil();

	m_stencil = sub.StencilSubMesh();

	//ComputerMeshVertexLocalCoord();
}


SubMesh::~SubMesh(void)
{
	m_pParent = NULL;
	delete m_pMeshVertexData;
	delete m_pSkinMeshVertexData;
	delete m_pVertexBoneAssignmentData;
	m_patchList.clear();

	//if(m_pBox)
	//	delete m_pBox;
	//if(m_pActiveBox)
	//	delete m_pActiveBox;
}


/**
 *@note����Ƭ�б������һ��������Ƭ
 *
 * @param idx1 ��һ���������
 * @param idx2 �ڶ����������
 * @param idx3 �������������
 *
 * @return void
 */
void SubMesh::AddPatch(unsigned int idx1,unsigned int idx2,unsigned int idx3)
{
	Patch p;
	p.vertexIndexOne = idx1;
	p.vertexIndexTwo = idx2;
	p.vertexIndexThree = idx3;
	m_patchList.push_back(p);
}


/** 
 *@note����Ƭ�б������һ��������Ƭ
 *
 * @param p Ҫ��ӵ���Ƭ
 *
 * @return void
 */
void SubMesh::AddPatch(Patch p)
{
	m_patchList.push_back(p);
}


/** 
 * @noteΪ��Ƭ�б����ռ�
 *
 * @param nPatch ��Ƭ������
 *
 * @return void
 */
void SubMesh::AllocatePatchList(int nPatch)
{
	m_patchList.resize(nPatch);
}


/** 
 *@note Ϊ���еĵ����ռ�
 *
 * @param nVertex ��ĸ���
 *
 * @return void
 */
void SubMesh::AllocateVertexBuffer(int nVertex)
{
	m_pMeshVertexData->AllocateBuffer(nVertex);
	m_pSkinMeshVertexData->AllocateBuffer(nVertex);
}



/** 
 *@note �õ���ĸ���
 *
 * @return void
 */
int SubMesh::GetVertexCount()const
{
	return m_pSkinMeshVertexData->GetVertexCount();
}


/** 
 *@note �õ�һ�������
 *
 * @param idx  ��ĸ�������
 *
 * @return һ�������
 */
MeshVertex SubMesh::GetVertex(int idx)const
{
	return m_pSkinMeshVertexData->GetMeshVertex(idx);
}

MeshVertex SubMesh::GetInitVertex(int idx)const
{
	return m_pMeshVertexData->GetMeshVertex(idx);
}

/** 
 *@note �õ�һ����λ��
 *
 * @param idx  ��ĸ�������
 *
 * @return һ�����λ��
 */	
Vector3 SubMesh::GetVertexPos(int idx)const
{
	return m_pSkinMeshVertexData->GetMeshVertexPos(idx);
}


/** 
 *@note �õ�һ���������ĳ�ʼλ��
 *
 * @param idx  ��ĸ�������
 *
 * @return һ��������ʼλ��
 */
Vector3 SubMesh::GetVertexInitPos(int idx)const
{
	return m_pMeshVertexData->GetMeshVertexPos(idx);
}


/** 

 * @note ������Ƭֵ
 *
 * @param idx Ҫ���õ���Ƭ���±�
 * @param p   ���õ���Ƭ��ֵ
 *
 * @return void
 */
//void SubMesh::SetPatch(int idx, Patch p)
//{
//	m_patchList[idx] = p;
//}

/** 
 *@note �õ���Ƭ������

 */
int SubMesh::GetPatchCount()const
{
	return (int)m_patchList.size();
}

/** 
 *@note �õ�һ����Ƭ
 *
 * @param idx  ��Ƭ������
 *
 * @return һ����Ƭ
 */
//Patch SubMesh::GetPatch(int idx)
//{
//	return m_patchList[idx];
//}


/** computer each mesh vertex's local coordinate relative to the influcing bones  
 *
 * @return void
 */

/** 
 *@note ����ÿ�������ľֲ����꣨����ں͸õ���صĹ�����
 *

 */
void SubMesh::ComputerMeshVertexLocalCoord()
{
	printf("\n");
	for(int i = 0; i < m_pMeshVertexData->GetVertexCount(); ++i)
	{
		printf("vertex %d\r", i);
		Vector3 pos = m_pMeshVertexData->GetMeshVertexPos(i); //����ڳ���ԭ�������ֵ
		Vector3 norm = m_pMeshVertexData->GetMeshVertexNormal(i);
		VertexBoneAssignment vba = m_pVertexBoneAssignmentData->GetAssignment(i);
	
		//���㹫ʽ��meshPos = bonePos + boneOrient * localPos
		//meshNormal = boneOrient * localNormal
		for(unsigned int j = 0; j < vba.assignmentList.size(); ++j)
		{
			int boneidx = vba.assignmentList[j].boneIndex;
			
			//local position
			Vector3 localPos = pos - m_pParent->m_pSkeleton->GetJointPos(boneidx);  //����ڹ����ľֲ�����
			Quaternion orient = m_pParent->m_pSkeleton->GetJointOrientation(boneidx); //�����ĳ���

			localPos = (orient.Inverse()) * localPos;

			//local normal
			Vector3 localNorm = (orient.Inverse()) * norm;

			vba.assignmentList[j].pos = localPos;
			vba.assignmentList[j].normal = localNorm;
		}
		
		m_pVertexBoneAssignmentData->SetAssignment(vba);
	}

}


/** generate the skin mesh vertex data
 * 
 * @param frmNo the motion frame 
 *
 * @return void
 */


/** 
 *@note ������Ƥ�����
 *
 * @param frmNo  �˶���֡
 *
 * @return 
 */
void SubMesh::GenerateSkinMesh(int frmNo)
{	
	if(!m_pParent) {
		printf("cannot generate skin mesh since no parent mesh\n");
		return;
	}

	MotionClip *pMotionClip = m_pParent->m_pMotionClip;
	
	// 2009.11.17 
	if( frmNo >= pMotionClip->getFrameCount() )
	{
		frmNo = pMotionClip->getFrameCount()-1;
	}

	int nJoint = pMotionClip->getJointCount();
	std::vector<Vector3> posToScene; //����ڳ�������ϵ������
	std::vector<Quaternion> quatToScene; //����ڳ�������ϵ�ĳ���
	Vector3 rootPos; //root �ڵ��ڳ�������ϵ�µ�����

	posToScene.resize(nJoint);
	quatToScene.resize(nJoint);

	MotionJoint *pRoot = pMotionClip->getRoot();
	rootPos = pRoot->getAbsolutePosition(frmNo);

	MotionJoint *pMJ;
	Vector3 pos,norm;
	Quaternion q,qTemp;

	for(int i = 0; i < nJoint; ++i)
	{
		q.Assign(0.0,0.0,0.0,1.0);

		pMJ = pMotionClip->findJoint(i);
		
		posToScene[i] = pMJ->getAbsolutePosition(frmNo);

	/*	while(pMJ != pRoot)
		{
			qTemp = pMJ->getOrientation(frmNo);
			q = qTemp * q;

			pMJ = pMotionClip->getParent(pMJ);
		}

		q = pRoot->getOrientation(frmNo) * q;
	
		quatToScene[i] = q;		*/

		quatToScene[i] = pMJ->OrientationTillParent(frmNo) * pMJ->getOrientation(frmNo);
	}

	//std::map<int,int>* pMapping = m_pParent->m_pMCS->GetMappingInformation();
	//����ÿ��mesh����Ը��ڵ�ľֲ�����,�ͷ�����
	for(int i = 0; i < m_pMeshVertexData->GetVertexCount(); ++i)
	{
		pos.Assign(0.0,0.0,0.0);
		norm.Assign(0.0,0.0,0.0);

		VertexBoneAssignment vba = m_pVertexBoneAssignmentData->GetAssignment(i);
				
		for(unsigned int j = 0; j < vba.assignmentList.size(); ++j)
		{
			int boneidx = vba.assignmentList[j].boneIndex;
			//std::map<int,int>::iterator iter = pMapping->find(boneidx);
			//boneidx = iter->second;   //the mapped joint index
		
			Vector3 localPos = vba.assignmentList[j].pos;
			Vector3 localNorm = vba.assignmentList[j].normal;
			double weight = vba.assignmentList[j].weight;

			pos += (posToScene[boneidx] + quatToScene[boneidx] * localPos) * weight;
			norm += quatToScene[boneidx] * localNorm * weight;

		}	
		m_pSkinMeshVertexData->SetMeshVertexPos(i,pos);
		m_pSkinMeshVertexData->SetMeshVertexNormal(i,norm);
		m_pSkinMeshVertexData->SetMeshVertexTexture(i,
			m_pMeshVertexData->GetMeshVertexTexture(i)); //2009.01.06 lixiang
	}
}

/** 
 *@note ��Ⱦ����
 *
 *
 */
//void SubMesh::Render()
//{
//	ShowMode mode = m_pParent->m_pMCS->GetShowMode();
//
//	switch(mode)
//	{
//	case MODEL_WIREFRAME: DrawWireSubMesh();break;
//	case MODEL_FLAT: 
//	case MODEL_LIGHTED: DrawLightedSubMesh();break;
//	case MODEL_TEXTURE: DrawTexturedSubMesh();break;
//	default:;
//	}
//}
//
//
///** 
// *@note ����ģ��
// *
// */
//void SubMesh::DrawWireSubMesh()
//{
//	glPushMatrix();
//
//	glEnable (GL_CULL_FACE);				// �����޳�����ι���
//	glDisable (GL_LIGHTING);				// ʹ OpenGL �ƹⲻ����
//
//	Patch p;
//	MeshVertex v1,v2,v3;
//	
//	glColor4f(1.0,1.0,1.0,1.0);
//	for(unsigned int i = 0; i < m_patchList.size(); i++)
//	{
//		p = m_patchList[i];
//		v1 = m_pSkinMeshVertexData->GetMeshVertex(p.vertexIndexOne);
//		v2 = m_pSkinMeshVertexData->GetMeshVertex(p.vertexIndexTwo);
//		v3 = m_pSkinMeshVertexData->GetMeshVertex(p.vertexIndexThree);
//
//	/*	v1 = m_pMeshVertexData->GetMeshVertex(p.vertexIndexOne);
//		v2 = m_pMeshVertexData->GetMeshVertex(p.vertexIndexTwo);
//		v3 = m_pMeshVertexData->GetMeshVertex(p.vertexIndexThree);*/
//
//		glBegin(GL_LINE_LOOP);
//		glColor4f(1.0,1.0,1.0,1.0);
//		glVertex3f(v1.pos.x,v1.pos.y,v1.pos.z);
//		glVertex3f(v2.pos.x,v2.pos.y,v2.pos.z);
//		glVertex3f(v3.pos.x,v3.pos.y,v3.pos.z);
//		glEnd();
//	}
//	
//	glPopMatrix();
//}
//
//
//
///** 
// *@note ��ģ��
// *
// */
//void SubMesh::DrawStencil()
//{
//	//if(m_bIsStencil)
//	//{
//	//	m_pParent->GetSubMesh(m_stencil)->DrawStencil;
//	//	glStencilFunc(GL_ALWAYS, 1, 1);						// �����ɰ��������ͨ�����ο�ֵ��Ϊ1������ֵҲ��Ϊ1
//	//	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);			// ���õ���Ȳ��Բ�ͨ��ʱ�������ɰ��е�ֵ���䡣���ͨ����ʹ�òο�ֵ�滻�ɰ�ֵ
//	//	glDisable(GL_DEPTH_TEST);							// ������Ȳ���
//	//}
//	glClear(GL_STENCIL_BUFFER_BIT);
//	glEnable(GL_STENCIL_TEST);							// �����ɰ建��
//	glStencilFunc(GL_ALWAYS, 1, 1);						// �����ɰ��������ͨ�����ο�ֵ��Ϊ1������ֵҲ��Ϊ1
//	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);			// ���õ���Ȳ��Բ�ͨ��ʱ�������ɰ��е�ֵ���䡣���ͨ����ʹ�òο�ֵ�滻�ɰ�ֵ
//	glDisable(GL_DEPTH_TEST);							// ������Ȳ���
//
//
//	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);	// ���ñ������λ��Ʒ�ʽ
//	glColorMask(0,0,0,0);	
//	
//	Patch p;
//	MeshVertex v1,v2,v3;
//
//
//	for(unsigned int i = 0; i < m_patchList.size(); i++)
//	{
//		p = m_patchList[i];
//		v1 = m_pSkinMeshVertexData->GetMeshVertex(p.vertexIndexOne);
//		v2 = m_pSkinMeshVertexData->GetMeshVertex(p.vertexIndexThree);
//		v3 = m_pSkinMeshVertexData->GetMeshVertex(p.vertexIndexTwo);
//
//		glBegin(GL_TRIANGLES);
//		glVertex3f(v1.pos.x,v1.pos.y,v1.pos.z);
//		glVertex3f(v2.pos.x,v2.pos.y,v2.pos.z);
//		glVertex3f(v3.pos.x,v3.pos.y,v3.pos.z);
//		glEnd();
//	}
//
//}
//
//
///** 
// *@note ���й��ģ��
// *
// */
//void SubMesh::DrawLightedSubMesh()
//{
//
//	glEnable (GL_CULL_FACE);				// �����޳�����ι���
//	glCullFace(GL_BACK);
//
//
//	GLfloat ambient[] = {0.2f,0.2f,0.2f,1.0f};
//	GLfloat diffuse[] = {0.8f,0.8f,0.8f,1.0f};
//	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
//	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
//
//	GLfloat lightAmbient[] = {0.0f,1.0f,0.0f,1.0f};
//	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
//
//	glPushMatrix();
//
//	Patch p;
//	MeshVertex v1,v2,v3;
//	
//	glEnable(GL_LIGHTING);
//	for(unsigned int i = 0; i < m_patchList.size(); i++)
//	{
//		p = m_patchList[i];
//		v1 = m_pSkinMeshVertexData->GetMeshVertex(p.vertexIndexOne);
//		v2 = m_pSkinMeshVertexData->GetMeshVertex(p.vertexIndexThree);
//		v3 = m_pSkinMeshVertexData->GetMeshVertex(p.vertexIndexTwo);
//
//		glBegin(GL_TRIANGLES);
//		glNormal3f(-v1.normal.x,-v1.normal.y,-v1.normal.z);
//		glVertex3f(v1.pos.x,v1.pos.y,v1.pos.z);
//		glNormal3f(-v2.normal.x,-v2.normal.y,-v2.normal.z);
//		glVertex3f(v2.pos.x,v2.pos.y,v2.pos.z);
//		glNormal3f(-v3.normal.x,-v3.normal.y,-v3.normal.z);
//		glVertex3f(v3.pos.x,v3.pos.y,v3.pos.z);
//		glEnd();
//	}
//
//	glDisable(GL_LIGHTING);
//	
//	glPopMatrix();
//
//}
//
//void SubMesh::DrawTexturedSubMesh()
//{
//
//}





/** 
 *@note ���õ��λ��
 *
 * @param idx  �������
 * @param pos  ���ֵ
 *
 * @return
 */
void SubMesh::SetVertexPos(int idx,Vector3 pos)
{
	m_pMeshVertexData->SetMeshVertexPos(idx,pos);
}



/** 
 *@note ���õ�ķ���
 *
 * @param idx  �������
 * @param normal  ��ķ���ֵ
 *
 * @return
 */
	
void SubMesh::SetVertexNormal(int idx, Vector3 normal)
{
	m_pMeshVertexData->SetMeshVertexNormal(idx,normal);
}

/** 
 *@note ���õ������
 *
 * @param idx  �������
 * @param texture  �������ֵ
 *
 * @return
 */	
void SubMesh::SetVertexTexture(int idx, Vector2 texture)
{
	m_pMeshVertexData->SetMeshVertexTexture(idx,texture);
}


/** 
 *@note ���õ�
 *
 * @param idx  �������
 * @param MV  ���ֵ
 *
 * @return
 */
void SubMesh::SetVertex(int idx, MeshVertex MV)
{
	m_pMeshVertexData->SetMeshVertex(idx,MV);
}


/** 
 *@note ��ӹ�ϵ
 *
 * @param idx  �������
 * @param boneidx  ��������
 * @param weight  Ȩ��
 * @return
 */
void SubMesh::AddAssignment(int vertexidx,int boneidx,double weight)
{
	if( boneidx < 0 )
	{
		throw "Bone Invalid!";
	}

	m_pVertexBoneAssignmentData->AddAssignment(vertexidx,boneidx,weight);
}

void SubMesh::AddAssignment( VertexBoneAssignment &vba )
{
	m_pVertexBoneAssignmentData->AddAssignment(vba);
}

/** 
*@note ���ù�ϵ
*
* @param idx  �������
* @param boneidx  ��������
* @param weight  Ȩ��
* @return
*/
void SubMesh::SetAssignment(int vertexidx,int boneidx,double weight)
{
	if( boneidx < 0 )
	{
		throw "Bone Invalid!";
	}

	m_pVertexBoneAssignmentData->SetAssignment(vertexidx,boneidx,weight);
}

/** 
 *@note �õ��˶�����
 *
 * @param idx  �������
 *
 * @return
 */
std::vector<unsigned int> SubMesh::GetAffectingBoneList(int vertexidx)const
{
	VertexBoneAssignment VBA = m_pVertexBoneAssignmentData->GetAssignment(vertexidx);

	std::vector<unsigned int> bonelist;
	size_t size = VBA.assignmentList.size();
//	bonelist.resize(size);
	for(size_t i = 0; i < size; ++i)
	{
		if(VBA.assignmentList[i].weight >= 0.5)
			bonelist.push_back(VBA.assignmentList[i].boneIndex);
//		bonelist[i] = VBA.assignmentList[i].boneIndex;
	}
	
	return bonelist;	
}

////////2007.12.14�������//////////////////

/** 
 *@note �����Ƭ�б�
 *

 *
 * @return
 */
void SubMesh::ClearPatchList(void)
{
	m_patchList.clear();
}


Vector3 SubMesh::ShortestDistance(const Vector3& pos) const
{
	double distance = 1000000.0;

	Vector3 v;

	for(int i = 0; i < m_pMeshVertexData->GetVertexCount(); ++i)
	{
		Vector3 p = m_pMeshVertexData->GetMeshVertexPos(i); //����ڳ���ԭ�������ֵ

		if( p.DistanceSqr(pos) < distance )
		{
			distance = p.DistanceSqr(pos);
			v = p - pos;
		}
	}

	return v;
}

Vector3 SubMesh::Distance(const Vector3& pos, const Vector3& nor, 
						  bool isFront) const
{
	double distance = 1000000.0;

	Vector3 v;

	bool isIn = false;

	for( std::list<Patch>::const_iterator i = m_patchList.begin(); 
		i != m_patchList.end(); i++ )
	{
		Vector3 p1 = m_pMeshVertexData->GetMeshVertexPos(i->vertexIndexOne);
		Vector3 p2 = m_pMeshVertexData->GetMeshVertexPos(i->vertexIndexTwo);
		Vector3 p3 = m_pMeshVertexData->GetMeshVertexPos(i->vertexIndexThree);

		if( isFront )
		{

			Vector3 n1 = m_pMeshVertexData->GetMeshVertexNormal(i->vertexIndexOne);
			Vector3 n2 = m_pMeshVertexData->GetMeshVertexNormal(i->vertexIndexTwo);
			Vector3 n3 = m_pMeshVertexData->GetMeshVertexNormal(i->vertexIndexThree);

			Vector3 n = n1+n2+n3;
			n.Normalize();

			if( n.Dot( Vector3(0.0,0.0,1.0) ) > 0.0 )
			{
				continue;
			}
		}

		Vector3 p = ComputeVector::Intersection(pos, nor, p1, p2, p3);

		if( ComputeVector::IsInTriangle(p, p1, p2, p3) 
			&& p.DistanceSqr(pos) < distance )
		{
			distance = p.DistanceSqr(pos);
			v = p - pos;
			isIn = true;
		}
	}

	if(!isIn)
	{
		v = ShortestDistance(pos);
		v = nor * v.Dot(nor);
	}

	return v;
}

void SubMesh::Translate(const Vector3& v)
{
	Matrix4 m;
	m.SetTranslate(v.x, v.y, v.z);

	for(int i = 0; i < m_pMeshVertexData->GetVertexCount(); ++i)
	{
		Vector3 p = m_pMeshVertexData->GetMeshVertexPos(i); //����ڳ���ԭ�������ֵ

		p.Transform(m);

		m_pMeshVertexData->SetMeshVertexPos(i, p);
	}

}


//BoundingBox* SubMesh::AddBox(BoundingBox* pb)
//{
//	return m_pBox = pb;
//}
//
//BoundingBox* SubMesh::AddActiveBox(BoundingBox* pb)
//{
//	return m_pActiveBox = pb;
//}
//
//void SubMesh::PreCompute(void)
//{
//	GenerateSkinMesh(0);
//}
//
//BoundingBox* SubMesh::SetActiveBox(int frmNo, double dt)
//{
//	if(!m_pBox)
//		return 0;
//
//	MotionClip *pMotionClip = m_pParent->m_pMCS->GetMotionClip();
//
//	Vector3 posToScene; //����ڳ�������ϵ������
//	Quaternion quatToScene; //����ڳ�������ϵ�ĳ���
//
//	MotionJoint *pMJ = pMotionClip->findJoint(m_pBox->GetBone());
//	posToScene = pMJ->getAbsolutePosition(frmNo);
//	quatToScene = pMJ->OrientationTillParent(frmNo) * pMJ->getOrientation(frmNo);
//
//	if(frmNo == m_pParent->m_pMCS->GetFrameCount()-1)
//	{
//		m_pActiveBox->GenerateActive(m_pBox, posToScene, quatToScene);
//	}
//	else
//	{
//		Vector3 posToScene1; //����ڳ�������ϵ������
//		Quaternion quatToScene1; //����ڳ�������ϵ�ĳ���
//
//		posToScene1 = pMJ->getAbsolutePosition(frmNo+1);
//		quatToScene1 = pMJ->OrientationTillParent(frmNo+1) * pMJ->getOrientation(frmNo+1);
//
//		Vector3 posToScene2; //����ڳ�������ϵ������
//		Quaternion quatToScene2; //����ڳ�������ϵ�ĳ���
//
//		posToScene2.Lerp(posToScene,posToScene1,dt);
//		quatToScene2.Lerp(quatToScene,quatToScene1,dt);
//
//		m_pActiveBox->GenerateActive(m_pBox, posToScene2, quatToScene2);
//	}
//
//	return m_pActiveBox;
//}

const std::list< Patch >& SubMesh::GetPatchList(void) const
{
	return m_patchList;
}

VertexBoneAssignment SubMesh::GetBoneAssignment(int vertexidx) const
{
	return m_pVertexBoneAssignmentData->GetAssignment(vertexidx);
}

void SubMesh::SetPatch( int idx, Patch p )
{
	std::list<Patch>::iterator iter = m_patchList.begin();
	for(int i = 0; i < idx; i++){
		iter++;
	}
	*iter = p;
}

Patch SubMesh::GetPatch( int idx )
{
	std::list<Patch>::iterator iter = m_patchList.begin();
	for(int i = 0; i < idx; i++){
		iter++;
	}
	return *iter;
}

void SubMesh::SetAssignment( VertexBoneAssignment &vba )
{
	m_pVertexBoneAssignmentData->SetAssignment(vba);
}