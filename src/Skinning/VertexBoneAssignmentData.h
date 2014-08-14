/** @file 
* @ brief 定义了点与骨骼之间的关系的头文件.
* @author 任阳春
* @date 2008-10-27
* @version 0.1
*
* 该文件中定义定义了点与骨骼之间的关系.，以及对这些信息进行添加、删除和赋值等操作
*/

#pragma once

#ifndef VertexBoneAssignmentData_h
#define VertexBoneAssignmentData_h
#include <vector>
#include <map>
#include "Mathematics.h"

namespace Caca
{

	/**
     * assignment bone and its weight
	 */
	struct BoneAssignment
	{
		unsigned int boneIndex;
		Vector3 pos; //相对于骨骼boneIndex的局部坐标
		Vector3 normal; //相对于骨骼boneIndex的局部法向量
		double weight;
	};


	/**
	 * all bone assignments for one mesh vertex 
     */
	struct VertexBoneAssignment
	{
		unsigned int vertexIndex;		
		std::vector<BoneAssignment> assignmentList;
		int nearestBoneNum;
	};

    /**
	* @class VertexBoneAssignmentData VertexBoneAssignmentData.h "VertexBoneAssignmentData.h"
	* @brief 在这个类中我们定义了点与骨骼之间的关系
	*
	* 这个类中我们定义了点与骨骼之间的关系模型 ，包括对模型中的元素进行的一些删除、添加、修改等操作。
	*/
	class VertexBoneAssignmentData
	{
	public:
		VertexBoneAssignmentData(void);
        /**
		* @brief 添加一个模型
		*/
		void AddAssignment(VertexBoneAssignment VBA);
		 /**
		* @brief 添加一个模型
		*/
		void AddAssignment(int vertexidx,int boneidx,double weight);

		 /**
		* @brief 得到一个模型
		*/
		VertexBoneAssignment GetAssignment(unsigned int vertexIndex)const;
		 /**
		* @brief 设置一个模型
		*/
		void SetAssignment(VertexBoneAssignment VBA);

		/**
		* @brief 设置一个模型
		*/
		void SetAssignment(int vertexidx,int boneidx,double weight);
	public:
		~VertexBoneAssignmentData(void);
	private:
		std::map<unsigned int, VertexBoneAssignment> m_assignmentBuffer;     //索引和模型对应关系
	};
}
#endif
