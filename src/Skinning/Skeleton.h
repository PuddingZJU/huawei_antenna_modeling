/** @file 
* @ brief 骨骼定义的头文件.
* @author 任阳春
* @date 2008-10-27
* @version 0.1
*
* 该文件中定义骨骼，以及相关的操作
*/


#pragma once

#ifndef Skeleton_h
#define Skeleton_h

#include <vector>
#include "Mathematics.h"

namespace Caca
{
	struct Joint
	{
		std::string name;
		int parent;         //父节点序号
		Vector3 pos;		//相对于父节点的偏移
		double rotateAngle;  //以下2个变量为节点的朝向，单位为弧度
		Vector3 rotateAxis;  //旋转轴 
	};



	/**
	* @class Skeleton Skeleton.h "Skeleton.h"
	* @brief 骨骼定义的类
	*
	* 主要是添加和删除关节点，以及对各关节点属性设置和获取。
	*/
	class Skeleton
	{
		friend class SubMesh;
		friend class Mesh;
	public:
		Skeleton(void);

	    /**
		* @brief 添加一个关节点
		*/
		void AddJoint(Joint j);

		/**
		* @brief 得到关节点的数目
		*/
		int GetJointsCount()const;

		/**
		* @brief 通过名字得到关节点的索引
		*/
		int GetJointIndexByName(std::string name);

		/**
		* @brief 通过索引得到关节点的位置
		*/
		Vector3 GetJointPos(int jointIdx);
		
		void SetJointPos(int jointIdx, const Vector3& pos);

        /**
		* @brief 通过索引得到关节点的方向
		*/
		Quaternion GetJointOrientation(int jointIdx);

		void SetJointOrientation(int jointIdx, const Quaternion& q);

		/**
		* @brief 设置父子关系
		*/
		void SetParent(int childIdx, int parentIdx);

		int GetParent(int childIdx);

		/**
		* @brief  获取父节点
		*/
		std::string GetParentName(std::string name);




        /**
		* @brief 计算绝对位置和方向
		*/	
		void ComputerJointPositionAndOrientation();
	
	public:
		virtual ~Skeleton(void);
	protected:
		std::vector<Joint> m_skeletonJoints;          //存放关节点
		std::vector<Vector3> m_jointsPosition;        //关节点的位置
		std::vector<Quaternion> m_jointsOrientation;  //关节点的方向
	};
}
#endif