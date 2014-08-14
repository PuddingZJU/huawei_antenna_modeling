/** @file 
* @ brief 网格点定义的头文件.
* @author 任阳春
* @date 2008-10-27
* @version 0.1
*
* 该文件中定义网格点集合，以及相关的操作
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
	* @brief 在这个类中我们定义了蒙皮动画中网格中的点的集合 
	*
	* 这个类中我们定义了蒙皮动画中网格点的集合 ，包括对网格中的点的一些操作。
	*/
	class MeshVertexData
	{
	public:
		MeshVertexData(void);

		/**
		* @brief 添加一个网格点
		*/
		void AddMeshVertex(MeshVertex mv);
        
		/**
		* @brief 得到一个网格点
		*/
		MeshVertex GetMeshVertex(int idx)const;

		/**
		* @brief 得到一个网格点位置
		*/
		Vector3 GetMeshVertexPos(int idx)const;
		/**
		* @brief 得到一个网格点法线
		*/
		Vector3 GetMeshVertexNormal(int idx)const;
		/**
		* @brief 得到一个网格点纹理
		*/
		Vector2 GetMeshVertexTexture(int idx)const;
        /**
		* @brief 得到网格点的个数
		*/
		int GetVertexCount()const;
        /**
		* @brief 设置网格点的位置
		*/
		void SetMeshVertexPos(int idx, Vector3 newPos);
		/**
		* @brief 设置网格点的位法线
		*/
		void SetMeshVertexNormal(int idx, Vector3 newNormal);
		/**
		* @brief 设置网格点的纹理
		*/
		void SetMeshVertexTexture(int idx, Vector2 newTexture);
		/**
		* @brief 设置网格点的信息
		*/
		void SetMeshVertex(int idx, MeshVertex newMV);
		/**
		* @brief 设置网格点的类型
		*/
		void SetVertexType(VertexType type);
		/**
		* @brief 得到网格点的类型
		*/
		VertexType GetVertexType()const;
		/**
		* @brief 分配所有点的空间
		*/
		void AllocateBuffer(const int nVertex);

		//////////////////////////////////////////////////////////////////////////

		/**
		* @brief 得到一个网格点的指针
		*/
		MeshVertex* GetPMeshVertex(int idx);
	
	public:
		virtual ~MeshVertexData(void);
	protected:
		VertexType m_type;                              //点的类型
		std::vector<MeshVertex> m_meshVertexBuffer;    //所有网格点
	};
}
#endif
