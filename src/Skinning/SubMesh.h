/** @file 
* @ brief �����������ʵ���ļ�.
* @author ������
* @date 2008-10-27
* @version 0.1
*
* ���ļ��ж��������Լ���صĲ���
*/

#pragma once

#ifndef SubMesh_h
#define SubMesh_h
#include <vector>
#include <list>
#include <map>
#include "Mathematics.h"

namespace Caca
{
	struct MeshVertex;
	class Mesh;
	class MeshVertexData;
	class VertexBoneAssignmentData;
	class BoundingBox;
	struct VertexBoneAssignment;

	/**
	 * triangle patch consist of three mesh vertex index 
	 */
	struct Patch
	{
		unsigned int vertexIndexOne;      
		unsigned int vertexIndexTwo;
		unsigned int vertexIndexThree;	
	};

	struct VertexBindInfo {
		unsigned int idx;
		std::vector<unsigned int> v;
		double s;
	};


	typedef std::map< unsigned int, VertexBindInfo > VertexBindMap;

    /**
	* @class SubMesh SubMesh.h "SubMesh.h"
	* @brief ������������Ƕ�������Ƥ����������ģ�� 
	*
	* ����������Ƕ�������Ƥ����������ģ�� �������������еĵ㡢��Ƭ��Ԫ�ؽ��е�һЩɾ������ӡ��޸ĵȲ�����
	*/
	class SubMesh
	{
		friend class Mesh;
		friend class PuppetRender;
		friend class ClothAlignWindow;
		friend class SubMeshReader;
		friend class ExpressionSubMesh;
		friend class ClothAlignWindow;
		friend class ClothesWidget;
		friend class ClothesWidget2D;
		friend class ClothesWidget3D;
		friend class ClothesInterpolation;
		friend class ClothesWidgetNew;
		friend class ClothNeighborMesh;
		friend class ClothesInterpolation;
	public:
		SubMesh(void);
		SubMesh(Mesh *pParent);

		SubMesh(const SubMesh& sub, Mesh* pParent);

		/**
		* @brief Ϊ������Ƭ����ռ�
		*/
		void AllocatePatchList(int nPatch);
		/**
		* @brief Ϊ������Ƭ�����ռ�
		*/
		void AllocateVertexBuffer(int nVertex);
        /**
		* @brief �õ���ĸ���
		*/		
		int GetVertexCount()const;
		/**
		* @brief �����������õ�һ�������
		*/	
		MeshVertex GetVertex(int idx)const;
		/**
		* @brief �����������õ�һ����ʼ�����
		*/	
		MeshVertex GetInitVertex(int idx)const;
		/**
		* @brief �����������õ�һ�����λ��
		*/	
		Vector3 GetVertexPos(int idx)const;
		/**
		* @brief �õ�mesh���ʼ�󶨵�λ��
		*/	
		Vector3 GetVertexInitPos(int idx)const; 
        /**
		* @brief ����mesh���λ����Ϣ
		*/	
		void SetVertexPos(int idx,Vector3 pos);
		 /**
		* @brief ����mesh��ķ�����Ϣ
		*/	
		void SetVertexNormal(int idx, Vector3 normal);
       /**
		* @brief ����mesh���������Ϣ
		*/	
		void SetVertexTexture(int idx, Vector2 texture);
		 /**
		* @brief ����mesh����Ϣ
		*/	
		void SetVertex(int idx, MeshVertex MV);

       /**
		* @brief ������Ƭ��Ϣ
		*/	
		void SetPatch(int idx, Patch p);

		Patch GetPatch(int idx);

		 /**
		* @brief������е���Ƭ   ///2007.12.14�������
		*/	
		virtual void ClearPatchList(void);

         /**
		* @brief �����Ƭ
		*/	
		virtual void AddPatch(unsigned int idx1, unsigned int idx2, unsigned int idx3);
		/**
		* @brief �����Ƭ
		*/	
		virtual void AddPatch(Patch p);
        /**
		* @brief ���ùǼܺ͵�Ĺ�ϵ
		*/	
		void AddAssignment(int vertexidx,int boneidx,double weight);

		/**
		* @brief ���ùǼܺ͵�Ĺ�ϵ
		*/	
		void AddAssignment(VertexBoneAssignment &vba);

		//�ɽ������� 2009-7-24 15:54:25
		/**
		* @brief ���ùǼܺ͵�Ĺ�ϵ
		*/
		void SetAssignment(VertexBoneAssignment &vba);

		/**
		* @brief ���ùǼܺ͵�Ĺ�ϵ
		*/	
		void SetAssignment(int vertexidx,int boneidx,double weight);


		/**
		* @brief �õ�Ӱ���vertexidxλ�õ����й����б�
		*/	
		std::vector<unsigned int> GetAffectingBoneList(int vertexidx)const; 
        /**
		* @brief �õ���Ƭ����
		*/	
		virtual int GetPatchCount()const;

		virtual const std::list< Patch >& GetPatchList(void) const;

		VertexBoneAssignment GetBoneAssignment(int vertexidx) const; 


		/**
		* @brief �õ�һ����Ƭ
		*/	
		//Patch GetPatch(int idx);

        /**
		* @brief �õ����е�ľֲ�λ�ã�����ڳ���
		*/	
		virtual void ComputerMeshVertexLocalCoord();
		/**
		* @brief ������Ƥ
		*/	
		virtual void GenerateSkinMesh(int frmNo);

		////////////////2007.12.17�����޸�Ϊvirtual///////////////

		///**
		//* @brief ��Ⱦ����
		//*/	
		//virtual void Render();
		///**
		//* @brief ��Ⱦ����
		//*/	
		//void DrawStencil();
  //      /**
		//* @brief ��Ⱦ����
		//*/	
		//void DrawWireSubMesh();
		///**
		//* @brief ��Ⱦ����
		//*/	
		//void DrawLightedSubMesh();
		///**
		//* @brief ��Ⱦ����
		//*/	
		//void DrawTexturedSubMesh();
		
		//////////////////////////////////////////////////////////////////////////
		std::string Name(void) const { return m_name; };
		void SetName(const std::string& name ) { m_name = name; };


		bool IsStencil(void) const{ return m_bIsStencil; };
		std::string StencilSubMesh(void) const{ return m_stencil; };

		void SetStencil(std::string name) { m_bIsStencil= true; m_stencil = name; };

		Vector3 ShortestDistance(const Vector3& pos) const;

		Vector3 Distance(const Vector3& pos, const Vector3& nor, 
			bool isFront = false) const;

		void Translate(const Vector3& v);

	public:
		virtual ~SubMesh(void);
	protected:
		Mesh *m_pParent;                        //ָ����Ƥ���������ָ��
		MeshVertexData *m_pMeshVertexData;      //���е�mesh���ָ��
		MeshVertexData *m_pSkinMeshVertexData;  //�Ǽ��˶�ʱ��̬���ɵ�meshdata
		VertexBoneAssignmentData *m_pVertexBoneAssignmentData;   //���������ϵ�����ָ��
		std::list<Patch> m_patchList;       //������Ƭ�б�
		//Material *m_pMaterial;   

		//2008.06.11 lixiang
		std::string m_name;            //����
		//BoundingBox* m_pBox;           //��Χ��
		//BoundingBox* m_pActiveBox;     //���Χ��

		bool m_bIsStencil;
		std::string m_stencil;
	};
}

#endif