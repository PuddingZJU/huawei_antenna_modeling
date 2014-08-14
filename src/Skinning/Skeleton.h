/** @file 
* @ brief ���������ͷ�ļ�.
* @author ������
* @date 2008-10-27
* @version 0.1
*
* ���ļ��ж���������Լ���صĲ���
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
		int parent;         //���ڵ����
		Vector3 pos;		//����ڸ��ڵ��ƫ��
		double rotateAngle;  //����2������Ϊ�ڵ�ĳ��򣬵�λΪ����
		Vector3 rotateAxis;  //��ת�� 
	};



	/**
	* @class Skeleton Skeleton.h "Skeleton.h"
	* @brief �����������
	*
	* ��Ҫ����Ӻ�ɾ���ؽڵ㣬�Լ��Ը��ؽڵ��������úͻ�ȡ��
	*/
	class Skeleton
	{
		friend class SubMesh;
		friend class Mesh;
	public:
		Skeleton(void);

	    /**
		* @brief ���һ���ؽڵ�
		*/
		void AddJoint(Joint j);

		/**
		* @brief �õ��ؽڵ����Ŀ
		*/
		int GetJointsCount()const;

		/**
		* @brief ͨ�����ֵõ��ؽڵ������
		*/
		int GetJointIndexByName(std::string name);

		/**
		* @brief ͨ�������õ��ؽڵ��λ��
		*/
		Vector3 GetJointPos(int jointIdx);
		
		void SetJointPos(int jointIdx, const Vector3& pos);

        /**
		* @brief ͨ�������õ��ؽڵ�ķ���
		*/
		Quaternion GetJointOrientation(int jointIdx);

		void SetJointOrientation(int jointIdx, const Quaternion& q);

		/**
		* @brief ���ø��ӹ�ϵ
		*/
		void SetParent(int childIdx, int parentIdx);

		int GetParent(int childIdx);

		/**
		* @brief  ��ȡ���ڵ�
		*/
		std::string GetParentName(std::string name);




        /**
		* @brief �������λ�úͷ���
		*/	
		void ComputerJointPositionAndOrientation();
	
	public:
		virtual ~Skeleton(void);
	protected:
		std::vector<Joint> m_skeletonJoints;          //��Źؽڵ�
		std::vector<Vector3> m_jointsPosition;        //�ؽڵ��λ��
		std::vector<Quaternion> m_jointsOrientation;  //�ؽڵ�ķ���
	};
}
#endif