/** @file 
* @ brief 骨骼定义的实现文件.
* @author 任阳春
* @date 2008-10-27
* @version 0.1
*
* 该文件中定义骨骼，以及相关的操作
*/




#include "Skeleton.h"
#include <string>
using namespace std;
using namespace Caca;

const double PI = 3.1415926535897932384626433832795;


Skeleton::Skeleton(void)
{
}

Skeleton::~Skeleton(void)
{
}


/*
 * @note添加一个骨骼结点
 *
 * @param j 要添加的结点
 *
 * @return void
 */
void Skeleton::AddJoint(Joint j)
{
	m_skeletonJoints.push_back(j);
}


/*
 * @note得到骨骼关节点的个数
 * 
 * @return a 整形
 */
int Skeleton::GetJointsCount()const
{
	return (int)m_skeletonJoints.size();
}


/**  
 * @note 通过名字来得到关节点的索引号 
 *
 * @param name关节点的名字
 *
 * @return 如果成功，返回骨骼的索引号，否则返回 -1
 */
int Skeleton::GetJointIndexByName(string name)
{
	for(unsigned int i = 0; i < m_skeletonJoints.size(); ++i)
	{
		if( name == (m_skeletonJoints[i].name))
			return i;
	}

	return -1; //not find
}


/*
 * @note给两个关节点之间建立父子关系
 *
 * @param childIdx 孩子节点的索引
 * @param parentIdx 父节点的索引
 *
 * @return void
 */
void Skeleton::SetParent(int childIdx, int parentIdx)
{
	m_skeletonJoints[childIdx].parent = parentIdx;
}

int Skeleton::GetParent(int childIdx)
{
	return m_skeletonJoints[childIdx].parent;
}

std::string Skeleton::GetParentName(std::string name)
{
	int i = GetJointIndexByName(name);
	int j = -1;

	if(i >= 0)
	{
		j = m_skeletonJoints[i].parent;
	}

	if(j >= 0)
	{
		return m_skeletonJoints[j].name;
	}

	return "";
}



/**
 * @note计算绝对位置和方向(相对于场景)
 *
 * @return void
 */
void Skeleton::ComputerJointPositionAndOrientation()
{
	int nJoint = (int)m_skeletonJoints.size();
	m_jointsPosition.resize(nJoint);
	m_jointsOrientation.resize(nJoint);

	Vector3 pos,relativePos;
	Quaternion q, qTotal;
	//for(int i = 0; i < nJoint; ++i)
	//{
	//	pos.Assign(0.0,0.0,0.0);
	//	qTotal.Assign(0.0,0.0,0.0,1.0);

	//	int idx = i;
	//	while(idx != -1)
	//	{
	//		//position
	//		relativePos = m_skeletonJoints[idx].pos;
	//		int parentIdx = m_skeletonJoints[idx].parent;
	//			
	//		if(parentIdx != -1 && m_skeletonJoints[parentIdx].rotateAngle != 0)
	//		{
	//			double angle = m_skeletonJoints[parentIdx].rotateAngle * 180.0 / PI;
	//			q.SetRotate(angle,m_skeletonJoints[parentIdx].rotateAxis);
	//		}
	//		else
	//			q.Assign(0.0,0.0,0.0,1.0); //no rotation
	//	
	//		pos = q * (relativePos + pos);

	//		//orientation
	//		if(m_skeletonJoints[idx].rotateAngle != 0)
	//		{
	//			double angle = m_skeletonJoints[idx].rotateAngle * 180.0 / PI;
	//			q.SetRotate(angle,m_skeletonJoints[idx].rotateAxis);
	//			qTotal = q * qTotal; 
	//		}
	//		
	//		idx = m_skeletonJoints[idx].parent;
	//	}

	//	m_jointsPosition[i] = pos;
	//	m_jointsOrientation[i] = qTotal;
	//}

}


/*
 * @note得到关节点的位置
 * 
 * @param jointIdx 关节点的索引号
 *
 * @return 以Vector3 的形式返回关节点的位置
 */
Vector3 Skeleton::GetJointPos(int jointIdx)
{
	return m_jointsPosition[jointIdx];
}

void Skeleton::SetJointPos(int jointIdx, const Vector3& pos)
{
	m_jointsPosition[jointIdx] = pos;
}


/*
 * @note得到关节点的方向
 * 
 * @param jointIdx关节点的索引
 *
 * @return 以 quaternion的形式返回关节点的方向 
 */
Quaternion Skeleton::GetJointOrientation(int jointIdx)
{
	return m_jointsOrientation[jointIdx];

	//Quaternion q;
	//q.SetRotate(m_skeletonJoints[jointIdx].rotateAngle,
	//	m_skeletonJoints[jointIdx].rotateAxis);

	//return q;
}

void Skeleton::SetJointOrientation(int jointIdx, const Quaternion& q)
{
	m_jointsOrientation[jointIdx] = q;
}