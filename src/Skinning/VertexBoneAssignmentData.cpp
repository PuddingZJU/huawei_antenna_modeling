/** @file 
* @ brief �����˵������֮��Ĺ�ϵ��ʵ���ļ�.
* @author ������
* @date 2008-10-27
* @version 0.1
*
* ���ļ��ж��嶨���˵������֮��Ĺ�ϵ.���Լ�����Щ��Ϣ������ӡ�ɾ���͸�ֵ�Ȳ���
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

/** @note ���һ��ģ��
 *
 *@param  VBA Ҫ��ӵ�ģ��
 *
 * @return void  
 */
void VertexBoneAssignmentData::AddAssignment(VertexBoneAssignment VBA)
{
	m_assignmentBuffer.insert(make_pair(VBA.vertexIndex,VBA));
}


/** @note ���һ��ģ��
 *
 *@param  vertexidx Ҫ��ӵ�ģ�͵�����
 *@param  boneidx Ҫ��ӵ�ģ�͵Ĺ�������
 *@param  weight Ȩ��
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


/** @note �õ�һ��ģ��
 *
 *@param  vertexidx Ҫ��ӵ�ģ�͵�����
 *
 * @return VertexBoneAssignment �õ���ģ��  
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

/** @note �޸Ķ���ĹǼܰ���Ϣ������Ϊû�а���Ϣ�Ķ�������µİ���Ϣ��
 *
 *@param  VertexBoneAssignment  Ҫ���õİ���Ϣ
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

/** @note Ϊһ���������ùǼܰ���Ϣ��ֻ�������������Ϊû�а���Ϣ�Ķ�����Ӱ���Ϣ��
*
*@param  vertexidx ��������
*@param  boneidx ��������
*@param  weight ����Ȩ��
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