/** @file 
* @ brief 整个网格定义的实现文件.
* @author 任阳春
* @date 2008-10-27
* @version 0.1
*
* 该文件中定义网格，以及相关的操作
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
	* @brief 在这个类中我们定义了蒙皮动画中网格模型 
	*
	* 这个类中我们定义了蒙皮动画中网格模型 ，包括对网格中的点、面片等元素进行的一些删除、添加、修改等操作。
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
		* @brief 为所有面片分配空间
		*/
		void AllocatePatchList(int nPatch);
		/**
		* @brief 为所有面片点分配空间
		*/
		void AllocateVertexBuffer(int nVertex);
        /**
		* @brief 得到点的个数
		*/		
		int GetVertexCount()const;
		/**
		* @brief 根据索引，得到一个网格点
		*/	
		MeshVertex GetVertex(int idx)const;
		/**
		* @brief 根据索引，得到一个初始网格点
		*/	
		MeshVertex GetInitVertex(int idx)const;
		/**
		* @brief 根据索引，得到一个点的位置
		*/	
		Vector3 GetVertexPos(int idx)const;
		/**
		* @brief 得到mesh点初始绑定的位置
		*/	
		Vector3 GetVertexInitPos(int idx)const; 
        /**
		* @brief 设置mesh点的位置信息
		*/	
		void SetVertexPos(int idx,Vector3 pos);
		 /**
		* @brief 设置mesh点的法线信息
		*/	
		void SetVertexNormal(int idx, Vector3 normal);
       /**
		* @brief 设置mesh点的纹理信息
		*/	
		void SetVertexTexture(int idx, Vector2 texture);
		 /**
		* @brief 设置mesh点信息
		*/	
		void SetVertex(int idx, MeshVertex MV);

       /**
		* @brief 设置面片信息
		*/	
		void SetPatch(int idx, Patch p);

		Patch GetPatch(int idx);

		 /**
		* @brief清除所有的面片   ///2007.12.14李响添加
		*/	
		virtual void ClearPatchList(void);

         /**
		* @brief 添加面片
		*/	
		virtual void AddPatch(unsigned int idx1, unsigned int idx2, unsigned int idx3);
		/**
		* @brief 添加面片
		*/	
		virtual void AddPatch(Patch p);
        /**
		* @brief 设置骨架和点的关系
		*/	
		void AddAssignment(int vertexidx,int boneidx,double weight);

		/**
		* @brief 设置骨架和点的关系
		*/	
		void AddAssignment(VertexBoneAssignment &vba);

		//由金秉文添加 2009-7-24 15:54:25
		/**
		* @brief 设置骨架和点的关系
		*/
		void SetAssignment(VertexBoneAssignment &vba);

		/**
		* @brief 设置骨架和点的关系
		*/	
		void SetAssignment(int vertexidx,int boneidx,double weight);


		/**
		* @brief 得到影响点vertexidx位置的所有骨骼列表
		*/	
		std::vector<unsigned int> GetAffectingBoneList(int vertexidx)const; 
        /**
		* @brief 得到面片个数
		*/	
		virtual int GetPatchCount()const;

		virtual const std::list< Patch >& GetPatchList(void) const;

		VertexBoneAssignment GetBoneAssignment(int vertexidx) const; 


		/**
		* @brief 得到一个面片
		*/	
		//Patch GetPatch(int idx);

        /**
		* @brief 得到所有点的局部位置，相对于场景
		*/	
		virtual void ComputerMeshVertexLocalCoord();
		/**
		* @brief 产生蒙皮
		*/	
		virtual void GenerateSkinMesh(int frmNo);

		////////////////2007.12.17李响修改为virtual///////////////

		///**
		//* @brief 渲染函数
		//*/	
		//virtual void Render();
		///**
		//* @brief 渲染函数
		//*/	
		//void DrawStencil();
  //      /**
		//* @brief 渲染函数
		//*/	
		//void DrawWireSubMesh();
		///**
		//* @brief 渲染函数
		//*/	
		//void DrawLightedSubMesh();
		///**
		//* @brief 渲染函数
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
		Mesh *m_pParent;                        //指向蒙皮参数对象的指针
		MeshVertexData *m_pMeshVertexData;      //所有的mesh点的指针
		MeshVertexData *m_pSkinMeshVertexData;  //骨架运动时动态生成的meshdata
		VertexBoneAssignmentData *m_pVertexBoneAssignmentData;   //点与骨骼关系对象的指针
		std::list<Patch> m_patchList;       //所有面片列表
		//Material *m_pMaterial;   

		//2008.06.11 lixiang
		std::string m_name;            //名称
		//BoundingBox* m_pBox;           //包围盒
		//BoundingBox* m_pActiveBox;     //活动包围盒

		bool m_bIsStencil;
		std::string m_stencil;
	};
}

#endif