/** @file 
* @ brief �����˵������֮��Ĺ�ϵ��ͷ�ļ�.
* @author ������
* @date 2008-10-27
* @version 0.1
*
* ���ļ��ж��嶨���˵������֮��Ĺ�ϵ.���Լ�����Щ��Ϣ������ӡ�ɾ���͸�ֵ�Ȳ���
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
		Vector3 pos; //����ڹ���boneIndex�ľֲ�����
		Vector3 normal; //����ڹ���boneIndex�ľֲ�������
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
	* @brief ������������Ƕ����˵������֮��Ĺ�ϵ
	*
	* ����������Ƕ����˵������֮��Ĺ�ϵģ�� ��������ģ���е�Ԫ�ؽ��е�һЩɾ������ӡ��޸ĵȲ�����
	*/
	class VertexBoneAssignmentData
	{
	public:
		VertexBoneAssignmentData(void);
        /**
		* @brief ���һ��ģ��
		*/
		void AddAssignment(VertexBoneAssignment VBA);
		 /**
		* @brief ���һ��ģ��
		*/
		void AddAssignment(int vertexidx,int boneidx,double weight);

		 /**
		* @brief �õ�һ��ģ��
		*/
		VertexBoneAssignment GetAssignment(unsigned int vertexIndex)const;
		 /**
		* @brief ����һ��ģ��
		*/
		void SetAssignment(VertexBoneAssignment VBA);

		/**
		* @brief ����һ��ģ��
		*/
		void SetAssignment(int vertexidx,int boneidx,double weight);
	public:
		~VertexBoneAssignmentData(void);
	private:
		std::map<unsigned int, VertexBoneAssignment> m_assignmentBuffer;     //������ģ�Ͷ�Ӧ��ϵ
	};
}
#endif
