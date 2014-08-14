/** @file 
* @ brief 定义了点与骨骼之间的关系的实现文件.
* @author 任阳春
* @date 2008-10-27
* @version 0.1
*
* 该文件中定义定义了点与骨骼之间的关系.，以及对这些信息进行添加、删除和赋值等操作
*/
//#include "StdAfx.h"
#include "VertexBoneAssignmentData.h"
using namespace std;
using namespace Caca;

VertexBoneAssignmentData::VertexBoneAssignmentData(void)
{
}

VertexBoneAssignmentData::~VertexBoneAssignmentData(void)
{
}

/** @note 添加一个模型
 *
 *@param  VBA 要添加的模型
 *
 * @return void  
 */
void VertexBoneAssignmentData::AddAssignment(VertexBoneAssignment VBA)
{
	m_assignmentBuffer.insert(make_pair(VBA.vertexIndex,VBA));
}


/** @note 添加一个模型
 *
 *@param  vertexidx 要添加的模型的索引
 *@param  boneidx 要添加的模型的骨骼索引
 *@param  weight 权重
 *
 * @return void  
 */
void VertexBoneAssignmentData::AddAssignment(int vertexidx,int boneidx, double weight)
{
	BoneAssignment assign;
	assign.boneIndex = boneidx;
	assign.weight = weight;

	//find whether there is a such an assignment struct in the map
	map<unsigned int, VertexBoneAssignment>::iterator pos = m_assignmentBuffer.find(vertexidx);
	if(pos != m_assignmentBuffer.end())//find it
	{	
		for( std::vector<BoneAssignment>::iterator i = 
			pos->second.assignmentList.begin(); 
			i != pos->second.assignmentList.end(); i++)
		{
			if( i->boneIndex == boneidx )
			{
				i->weight += weight;
				return;
			}
		}

		pos->second.assignmentList.push_back(assign);  //add the assignement
	}
	else //not find,insert it
	{
		VertexBoneAssignment VBA;
		VBA.vertexIndex = vertexidx;
		VBA.assignmentList.push_back(assign);
		m_assignmentBuffer.insert(make_pair(VBA.vertexIndex,VBA));
	}
}


/** @note 得到一个模型
 *
 *@param  vertexidx 要添加的模型的索引
 *
 * @return VertexBoneAssignment 得到的模型  
 */
VertexBoneAssignment VertexBoneAssignmentData::GetAssignment(unsigned int vertexIndex)const
{
	map<unsigned int, VertexBoneAssignment>::const_iterator pos = m_assignmentBuffer.find(vertexIndex);
	if(pos != m_assignmentBuffer.end())
	{
		return pos->second; //return value
	}
	else
	{
		//printf("bone assignment for vertex %d does not exist\n", vertexIndex);
		return VertexBoneAssignment();
	}
}

/** @note 修改顶点的骨架绑定信息（不能为没有绑定信息的顶点添加新的绑定信息）
 *
 *@param  VertexBoneAssignment  要设置的绑定信息
 *
 * @return void 
 */
void VertexBoneAssignmentData::SetAssignment(VertexBoneAssignment VBA)
{
	map<unsigned int, VertexBoneAssignment>::iterator pos = m_assignmentBuffer.find(VBA.vertexIndex);
	if(pos != m_assignmentBuffer.end())
	{
		pos->second = VBA;  //set the value
	}
	else
	{
		;
	}
}

/** @note 为一个顶点设置骨架绑定信息。只有这个函数可以为没有绑定信息的顶点添加绑定信息。
*
*@param  vertexidx 顶点索引
*@param  boneidx 骨骼索引
*@param  weight 骨骼权重
*
* @return void  
*/
void VertexBoneAssignmentData::SetAssignment(int vertexidx,int boneidx, double weight)
{
	BoneAssignment assign;
	assign.boneIndex = boneidx;
	assign.weight = weight;

	//find whether there is a such an assignment struct in the map
	map<unsigned int, VertexBoneAssignment>::iterator pos = m_assignmentBuffer.find(vertexidx);
	if(pos != m_assignmentBuffer.end())//find it
	{	
		for( std::vector<BoneAssignment>::iterator i = 
			pos->second.assignmentList.begin(); 
			i != pos->second.assignmentList.end(); i++)
		{
			if( i->boneIndex == boneidx )
			{
				i->weight = weight;
				return;
			}
		}

		pos->second.assignmentList.push_back(assign);  //add the assignement
	}
	else //not find,insert it
	{
		VertexBoneAssignment VBA;
		VBA.vertexIndex = vertexidx;
		VBA.assignmentList.push_back(assign);
		m_assignmentBuffer.insert(make_pair(VBA.vertexIndex,VBA));
	}
}