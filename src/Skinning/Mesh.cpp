/** @file 
* @ brief 整个蒙皮动画参数定义的实现文件.
* @author 任阳春
* @date 2008-10-27
* @version 0.1
*
* 该文件中定义蒙皮动画参数，以及相关的操作
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
 *@note  从文件中导入蒙皮动画参数
 *
 * @param filename 蒙皮动画参数名字
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
 *@note  释放所有的mesh
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
 *@note  关联一个动作片断
 *
 * @param pMotionClip 要关联的运动片断
 *
 * @return void
 */
void Mesh::AttachMotionClip(MotionClip *pMotionClip)
{
	m_pMotionClip = pMotionClip;	
}


/**
 *@note  关联一个动作信息
 *
 * @param pMCS 要关联的动作信息
 *
 * @return void
 */
//void Mesh::AttachMotionClipShow(MotionClipShow *pMCS)
//{
//	m_pMCS = pMCS;
//}



/**
 *@note  计算每个MESH点的局部坐标（相对于关联的骨骼）
 *
 *
 * @return void
 */
void Mesh::ComputerMeshVertexLocalCoord()
{
	//m_pSkeleton->ComputerJointPositionAndOrientation(); //计算骨架节点的绝对位置（场景坐标系下）

	for(unsigned int i = 0; i < m_subMeshList.size(); i++)
	{
		printf("compute for submesh %d\n", i);
		m_subMeshList[i]->ComputerMeshVertexLocalCoord();
	}
}


/**
 *@note  分离一个动作片断
 *
 *
 * @return void
 */
void Mesh::DetachMotionClip()
{
	if(m_pMotionClip)
		m_pMotionClip = NULL;
}

/** @note 添加一个网格模型，同时设置其父网格为当前mesh实例，所以同一网格模型不能
 * 同时属于多个mesh
 *
 * @param pSubMesh 要添加的网格模型
 *
 * @return void
 */
void Mesh::AddSubMesh(SubMesh *pSubMesh)
{
	pSubMesh->m_pParent = this;  //attch the parent
	m_subMeshList.push_back(pSubMesh);
}


/** @note 删除一个网格 
 * 
 * @param pSubMesh 要删除的网格模型
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


/** @note 得到网格模型的个数  
 *
 * @return 整形数据
 */
int Mesh::GetSubMeshCount()const
{
	return (int)m_subMeshList.size();
}



/** @note 得到一个网格模型  
 *
 *@param index 要返回的网格模型的索引
 *
 * @return 得到的网格模型
 */
SubMesh* Mesh::GetSubMesh(int index)const
{
	return m_subMeshList[index]; 
}


/** @note 得到骨骼模型  
 *
 *
 * @return 得到的骨骼模型
 */
Skeleton* Mesh::GetSkeleton()const
{
	return m_pSkeleton;
}

MotionClip* Mesh::GetMotionClip() const
{ 
	return m_pMotionClip; 
}


/**@note 渲染网格
 *
 * @param frmNo 要渲染的网格的索引
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


/** @note 产生选择帧对应的蒙皮 
 *
 * @param frmNo  帧索引
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
/** @note 设置骨骼 
 *
 * @param pSkeleton  设置的骨骼信息
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


/** @note 通过名字，得到网格模型 
 *
 * @param name 要得到网格的名字
 *
 * @return 得到的网格
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