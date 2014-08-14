/** @file 
* @ brief ������Ƥ�������������ʵ���ļ�.
* @author ������
* @date 2008-10-27
* @version 0.1
*
* ���ļ��ж�����Ƥ�����������Լ���صĲ���
*/
#include "Mesh.h"
#include "Skeleton.h"
#include "SubMesh.h"
#include "MeshVertexData.h"
#include "VertexBoneAssignmentData.h"
#include "MotionJoint.h"
#include "MotionClip.h"
//#include "MotionClipShow.h"
//#include "..\\CacaModel/include/SubdivisionSubMesh.h"

//#include "..//..//Physics/include/PhysicsSubMesh.h"

//#include "..\\VDModel\SubdivisionSubMesh.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;
using namespace Caca;


//constructor
Mesh::Mesh(void)
{
	//m_pMCS = NULL;
	m_pSkeleton = NULL;
	m_subMeshList.clear();
}


/**
 *@note  ���ļ��е�����Ƥ��������
 *
 * @param filename ��Ƥ������������
 *
 */
Mesh::Mesh(const string filename)
{
	//to do...

}


Mesh::~Mesh(void)
{
	FreeMesh();
}



/**
 *@note  �ͷ����е�mesh
 *
 * @return void 
 *
 */
void Mesh::FreeMesh()
{
	//if(m_pSkeleton)
	//	delete m_pSkeleton;

	for(unsigned int i = 0; i < m_subMeshList.size(); i++)
	{
		if(m_subMeshList[i])
			delete m_subMeshList[i];
	}
	m_subMeshList.clear();
}


/**
 *@note  ����һ������Ƭ��
 *
 * @param pMotionClip Ҫ�������˶�Ƭ��
 *
 * @return void
 */
void Mesh::AttachMotionClip(MotionClip *pMotionClip)
{
	m_pMotionClip = pMotionClip;	
}


/**
 *@note  ����һ��������Ϣ
 *
 * @param pMCS Ҫ�����Ķ�����Ϣ
 *
 * @return void
 */
//void Mesh::AttachMotionClipShow(MotionClipShow *pMCS)
//{
//	m_pMCS = pMCS;
//}



/**
 *@note  ����ÿ��MESH��ľֲ����꣨����ڹ����Ĺ�����
 *
 *
 * @return void
 */
void Mesh::ComputerMeshVertexLocalCoord()
{
	//m_pSkeleton->ComputerJointPositionAndOrientation(); //����Ǽܽڵ�ľ���λ�ã���������ϵ�£�

	for(unsigned int i = 0; i < m_subMeshList.size(); i++)
	{
		printf("compute for submesh %d\n", i);
		m_subMeshList[i]->ComputerMeshVertexLocalCoord();
	}
}


/**
 *@note  ����һ������Ƭ��
 *
 *
 * @return void
 */
void Mesh::DetachMotionClip()
{
	if(m_pMotionClip)
		m_pMotionClip = NULL;
}

/** @note ���һ������ģ�ͣ�ͬʱ�����丸����Ϊ��ǰmeshʵ��������ͬһ����ģ�Ͳ���
 * ͬʱ���ڶ��mesh
 *
 * @param pSubMesh Ҫ��ӵ�����ģ��
 *
 * @return void
 */
void Mesh::AddSubMesh(SubMesh *pSubMesh)
{
	pSubMesh->m_pParent = this;  //attch the parent
	m_subMeshList.push_back(pSubMesh);
}


/** @note ɾ��һ������ 
 * 
 * @param pSubMesh Ҫɾ��������ģ��
 *
 * @return void
 */
void Mesh::DeleteSubMesh(SubMesh *pSubMesh)
{
	vector<SubMesh *>::iterator pos = find(m_subMeshList.begin(),m_subMeshList.end(), pSubMesh);
	if(pos != m_subMeshList.end())
	{
		m_subMeshList.erase(pos);
	}
}


/** @note �õ�����ģ�͵ĸ���  
 *
 * @return ��������
 */
int Mesh::GetSubMeshCount()const
{
	return (int)m_subMeshList.size();
}



/** @note �õ�һ������ģ��  
 *
 *@param index Ҫ���ص�����ģ�͵�����
 *
 * @return �õ�������ģ��
 */
SubMesh* Mesh::GetSubMesh(int index)const
{
	return m_subMeshList[index]; 
}


/** @note �õ�����ģ��  
 *
 *
 * @return �õ��Ĺ���ģ��
 */
Skeleton* Mesh::GetSkeleton()const
{
	return m_pSkeleton;
}

MotionClip* Mesh::GetMotionClip() const
{ 
	return m_pMotionClip; 
}


/**@note ��Ⱦ����
 *
 * @param frmNo Ҫ��Ⱦ�����������
 *
 * @return void
 */
//void Mesh::Render(int frmNo)
//{
//	GenerateSkinMesh(frmNo); //generate the skin mesh with the motion data of frame frmNo
//
//	for(unsigned int i = 0; i < m_subMeshList.size(); i++)
//	{
//		(dynamic_cast<SubdivisionSubMesh*>(m_subMeshList[i]))->RenderLitSphere();
//	}
//
//	m_pMCS->SetShowMode(MODEL_WIREFRAME);
//	for(unsigned int i = 0; i < m_subMeshList.size(); i++)
//	{
//		/*if(!m_subMeshList[i]->IsStencil())*/
//			m_subMeshList[i]->Render();
//	}
//}


/** @note ����ѡ��֡��Ӧ����Ƥ 
 *
 * @param frmNo  ֡����
 *
 * @return void
 */
void Mesh::GenerateSkinMesh(int frmNo)
{
	m_pMotionClip->setCurrentFrame(frmNo);	//added by Jinbingwen 2013-12-6 11:31:04

	for(unsigned int i = 0; i < m_subMeshList.size(); i++)
	{
		m_subMeshList[i]->GenerateSkinMesh(frmNo);
	}
}
/** @note ���ù��� 
 *
 * @param pSkeleton  ���õĹ�����Ϣ
 *
 * @return void
 */
void Mesh::SetSkeleton(Skeleton* pSkeleton)
{
	if(m_pSkeleton)
		delete m_pSkeleton;

	m_pSkeleton=pSkeleton;
}

//void Mesh::SetBox(int frame, double dt)
//{
//	for(unsigned int i = 0; i < m_subMeshList.size(); i++)
//	{
//		m_subMeshList[i]->SetActiveBox(frame, dt);
//	}
//}
//
//BoundingBox* Mesh::GetBox(std::string name)
//{
//	for(unsigned int i = 0; i < m_subMeshList.size(); i++)
//	{
//		if(name == m_subMeshList[i]->Name())
//			return  m_subMeshList[i]->ActiveBox();
//	}
//	return 0;
//}


//void Mesh::PreCompute(void)
//{
//	for(unsigned int i = 0; i < m_subMeshList.size(); i++)
//	{
//		m_subMeshList[i]->PreCompute();
//	}
//}


/** @note ͨ�����֣��õ�����ģ�� 
 *
 * @param name Ҫ�õ����������
 *
 * @return �õ�������
 */
SubMesh* Mesh::GetSubMesh(std::string name) const
{
	for(unsigned int i = 0; i < m_subMeshList.size(); i++)
	{
		if(name == m_subMeshList[i]->Name())
			return  m_subMeshList[i];
	}
	return 0;
}