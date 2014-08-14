/** @file 
* @ brief 整个蒙皮动画参数定义的头文件.
* @author 任阳春
* @date 2008-10-27
* @version 0.1
*
* 该文件中定义蒙皮动画参数，以及相关的操作
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
	* @brief 在这个类中我们定义了蒙皮动画参数模型 
	*
	* 这个类中我们定义了蒙皮动画参数模型 ，包括对模型中的元素进行的一些删除、添加、修改等操作。
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
		* @brief 添加一个网格模型
		*/
		void AddSubMesh(SubMesh *pSubMesh);
		/**
		* @brief 删除一个网格模型
		*/
		void DeleteSubMesh(SubMesh *pSubMesh);
		/**
		* @brief 得到网格模型的个数
		*/
		int GetSubMeshCount()const;
		/**
		* @brief 得到一个网格模型
		*/
		SubMesh* GetSubMesh(int index)const;
		/**
		* @brief 得到骨架模型
		*/
		Skeleton* GetSkeleton()const;
        /**
		* @brief 计算mesh点的局部坐标 
		*/
		void ComputerMeshVertexLocalCoord();
		/**
		* @brief 产生蒙皮
		*/
		void GenerateSkinMesh(int frmNo);
		/**
		* @brief  渲染
		*/
		//void Render(int frmNo);

		/**
		* @brief 释放网格
		*/
		void FreeMesh();
        /**
		* @brief 关联一个动作片断
		*/
		void AttachMotionClip(MotionClip *pMotionClip);
		/**
		* @brief 分离一个动作片断
		*/
		void DetachMotionClip();
		/**
		* @brief 得到一个动作片断
		*/
		MotionClip* GetMotionClip() const;

		/**
		* @brief 关联一个动作信息
		*/
		//void AttachMotionClipShow(MotionClipShow *pMCS);

		/**
		* @brief 设置骨骼信息
		*/
		void SetSkeleton(Skeleton* pSkeleton);

        /**
		* @brief 得到动作信息
		*/
		//MotionClipShow* GetMCS(void) {return m_pMCS;};
       /**
		* @brief 得到包围盒
		*/
		//BoundingBox* GetBox(std::string name);
		///**
		//* @brief 设置包围盒
		//*/
		//void SetBox(int frame, double dt);

		/**
		* @brief 得到网格模型，根据名字
		*/
		SubMesh* GetSubMesh(std::string name) const;
        /**
		* @brief 预计算
		*/
		//void PreCompute(void);
		/**
		* @brief 清除所有子网格
		*/
		void ClearAllSubMesh() {m_subMeshList.clear();};

	protected:

		//MotionClipShow *m_pMCS;                 
		MotionClip* m_pMotionClip;				//动作片断数据,2008.11.11李响
		Skeleton *m_pSkeleton;                  //骨骼
		std::vector<SubMesh *> m_subMeshList;  //网格模型列表
		std::map<int,int> m_jointMapping;      //动作数据中的骨骼和蒙皮动画中骨骼对应信息
	};
}
#endif