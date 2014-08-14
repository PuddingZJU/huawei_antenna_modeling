/** @file 
* @ brief ������Ƥ�������������ͷ�ļ�.
* @author ������
* @date 2008-10-27
* @version 0.1
*
* ���ļ��ж�����Ƥ�����������Լ���صĲ���
*/

#pragma once

#ifndef Mesh_h
#define Mesh_h
#include <vector>
#include <map>
#include <fstream>

namespace Caca
{
	//class MotionClipShow;
	class MotionClip;
	class SubMesh;
	class Skeleton;
	class SubdivisionSubMesh;
	class PhysicsSubMesh;
	class BoundingBox;


	/**
	* @class Mesh Mesh.h "bMesh.h"
	* @brief ������������Ƕ�������Ƥ��������ģ�� 
	*
	* ����������Ƕ�������Ƥ��������ģ�� ��������ģ���е�Ԫ�ؽ��е�һЩɾ������ӡ��޸ĵȲ�����
	*/
	class Mesh
	{
		friend class MeshSerializer;
		friend class SubMesh;
		friend class SubdivisionSubMesh;
		friend class PhysicsSubMesh;
		friend class PuppetRender;
		friend class ClothAlignWindow;

	public:
		Mesh(void);
		Mesh(const std::string filename);

		virtual ~Mesh(void);

		/////////////////////
		/**
		* @brief ���һ������ģ��
		*/
		void AddSubMesh(SubMesh *pSubMesh);
		/**
		* @brief ɾ��һ������ģ��
		*/
		void DeleteSubMesh(SubMesh *pSubMesh);
		/**
		* @brief �õ�����ģ�͵ĸ���
		*/
		int GetSubMeshCount()const;
		/**
		* @brief �õ�һ������ģ��
		*/
		SubMesh* GetSubMesh(int index)const;
		/**
		* @brief �õ��Ǽ�ģ��
		*/
		Skeleton* GetSkeleton()const;
        /**
		* @brief ����mesh��ľֲ����� 
		*/
		void ComputerMeshVertexLocalCoord();
		/**
		* @brief ������Ƥ
		*/
		void GenerateSkinMesh(int frmNo);
		/**
		* @brief  ��Ⱦ
		*/
		//void Render(int frmNo);

		/**
		* @brief �ͷ�����
		*/
		void FreeMesh();
        /**
		* @brief ����һ������Ƭ��
		*/
		void AttachMotionClip(MotionClip *pMotionClip);
		/**
		* @brief ����һ������Ƭ��
		*/
		void DetachMotionClip();
		/**
		* @brief �õ�һ������Ƭ��
		*/
		MotionClip* GetMotionClip() const;

		/**
		* @brief ����һ��������Ϣ
		*/
		//void AttachMotionClipShow(MotionClipShow *pMCS);

		/**
		* @brief ���ù�����Ϣ
		*/
		void SetSkeleton(Skeleton* pSkeleton);

        /**
		* @brief �õ�������Ϣ
		*/
		//MotionClipShow* GetMCS(void) {return m_pMCS;};
       /**
		* @brief �õ���Χ��
		*/
		//BoundingBox* GetBox(std::string name);
		///**
		//* @brief ���ð�Χ��
		//*/
		//void SetBox(int frame, double dt);

		/**
		* @brief �õ�����ģ�ͣ���������
		*/
		SubMesh* GetSubMesh(std::string name) const;
        /**
		* @brief Ԥ����
		*/
		//void PreCompute(void);
		/**
		* @brief �������������
		*/
		void ClearAllSubMesh() {m_subMeshList.clear();};

	protected:

		//MotionClipShow *m_pMCS;                 
		MotionClip* m_pMotionClip;				//����Ƭ������,2008.11.11����
		Skeleton *m_pSkeleton;                  //����
		std::vector<SubMesh *> m_subMeshList;  //����ģ���б�
		std::map<int,int> m_jointMapping;      //���������еĹ�������Ƥ�����й�����Ӧ��Ϣ
	};
}
#endif