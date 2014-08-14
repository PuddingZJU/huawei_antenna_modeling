/** @file 
* @ brief ����㶨���ͷ�ļ�.
* @author ������
* @date 2008-10-27
* @version 0.1
*
* ���ļ��ж�������㼯�ϣ��Լ���صĲ���
*/


#pragma once

#ifndef MeshVertexData_h
#define MeshVertexData_h
#include <vector>
#include "Mathematics.h"
#include "MeshVertexData.h"


namespace Caca
{
	/**
	* Mesh vertex
	*/
	struct MeshVertex
	{
		Vector3 pos;
		Vector3 normal;
		Vector2 texture;
	};

	enum VertexType{VT_P,VT_PN,VT_PT,VT_PNT}; //vertex type: V_P:Position only, V_PN: pos & normal, V_PNT: pos & normal & texture
     /**
	* @class MeshVertexData MeshVertexData.h "MeshVertexData.h"
	* @brief ������������Ƕ�������Ƥ�����������еĵ�ļ��� 
	*
	* ����������Ƕ�������Ƥ�����������ļ��� �������������еĵ��һЩ������
	*/
	class MeshVertexData
	{
	public:
		MeshVertexData(void);

		/**
		* @brief ���һ�������
		*/
		void AddMeshVertex(MeshVertex mv);
        
		/**
		* @brief �õ�һ�������
		*/
		MeshVertex GetMeshVertex(int idx)const;

		/**
		* @brief �õ�һ�������λ��
		*/
		Vector3 GetMeshVertexPos(int idx)const;
		/**
		* @brief �õ�һ������㷨��
		*/
		Vector3 GetMeshVertexNormal(int idx)const;
		/**
		* @brief �õ�һ�����������
		*/
		Vector2 GetMeshVertexTexture(int idx)const;
        /**
		* @brief �õ������ĸ���
		*/
		int GetVertexCount()const;
        /**
		* @brief ����������λ��
		*/
		void SetMeshVertexPos(int idx, Vector3 newPos);
		/**
		* @brief ����������λ����
		*/
		void SetMeshVertexNormal(int idx, Vector3 newNormal);
		/**
		* @brief ��������������
		*/
		void SetMeshVertexTexture(int idx, Vector2 newTexture);
		/**
		* @brief ������������Ϣ
		*/
		void SetMeshVertex(int idx, MeshVertex newMV);
		/**
		* @brief ��������������
		*/
		void SetVertexType(VertexType type);
		/**
		* @brief �õ�����������
		*/
		VertexType GetVertexType()const;
		/**
		* @brief �������е�Ŀռ�
		*/
		void AllocateBuffer(const int nVertex);

		//////////////////////////////////////////////////////////////////////////

		/**
		* @brief �õ�һ��������ָ��
		*/
		MeshVertex* GetPMeshVertex(int idx);
	
	public:
		virtual ~MeshVertexData(void);
	protected:
		VertexType m_type;                              //�������
		std::vector<MeshVertex> m_meshVertexBuffer;    //���������
	};
}
#endif
