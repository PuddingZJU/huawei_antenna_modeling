/** @file 
* @ brief 网格点定义的实现文件.
* @author 任阳春
* @date 2008-10-27
* @version 0.1
*
* 该文件中定义网格点集合，以及相关的操作
*/
#include "MeshVertexData.h"
using namespace Caca;

MeshVertexData::MeshVertexData(void)
{
	m_meshVertexBuffer.clear();
	m_type = VT_P; //position only by default
}

MeshVertexData::~MeshVertexData(void)
{
}


/** @note 添加一个网格点
 *
 *@param mv  要添加的点
 *
 * @return void 
 */
void MeshVertexData::AddMeshVertex(MeshVertex mv)
{
	m_meshVertexBuffer.push_back(mv);
}

/** @note 得到网格点的个数
 *
 *
 * @return int 点的个数 
 */
int MeshVertexData::GetVertexCount()const
{
	return (int)m_meshVertexBuffer.size();
}

/** @note 得到一个网格点
 *
 *@param idx   点的索引
 *
 * @return MeshVertex 
 */
MeshVertex MeshVertexData::GetMeshVertex(int idx) const
{
	return m_meshVertexBuffer[idx];
}

/** @note 得到一个网格点位置
 *
 *@param idx   点的索引
 *
 * @return Vector3 点的位置 
 */
Vector3 MeshVertexData::GetMeshVertexPos(int idx)const
{
	if( idx < 0 || idx >= m_meshVertexBuffer.size() )
	{
		throw "Vertex Index Invalid!";
	}

	return m_meshVertexBuffer[idx].pos;
}

/** @note 得到一个网格点的法线
 *
 *@param idx   点的索引
 *
 * @return Vector3 点的法线
 */

Vector3 MeshVertexData::GetMeshVertexNormal(int idx)const
{
	if( idx < 0 || idx >= m_meshVertexBuffer.size() )
	{
		throw "Vertex Index Invalid!";
	}

	return m_meshVertexBuffer[idx].normal;
}

/** @note 得到一个网格点的纹理
 *
 *@param idx   点的索引
 *
 * @return Vector2 点的纹理 
 */
Vector2 MeshVertexData::GetMeshVertexTexture(int idx)const
{
	if( idx < 0 || idx >= m_meshVertexBuffer.size() )
	{
		throw "Vertex Index Invalid!";
	}

	return m_meshVertexBuffer[idx].texture;
}


/** @note 设置一个网格点位置
 *
 *@param idx   点的索引
 *@param newPos 点的位置
 *
 * @return void  
 */  
void MeshVertexData::SetMeshVertexPos(int idx, Vector3 newPos)
{
	if( idx < 0 || idx >= m_meshVertexBuffer.size() )
	{
		throw "Vertex Index Invalid!";
	}

	m_meshVertexBuffer[idx].pos = newPos;
}

/** @note 设置一个网格点法线
 *
 *@param idx   点的索引
 *@param newNormal 点的法线
 *
 * @return void  
 */
void MeshVertexData::SetMeshVertexNormal(int idx, Vector3 newNormal)
{
	if( idx < 0 || idx >= m_meshVertexBuffer.size() )
	{
		throw "Vertex Index Invalid!";
	}

	m_meshVertexBuffer[idx].normal = newNormal;
}

/** @note 设置一个网格点纹理
 *
 *@param idx   点的索引
 *@param newTexture 点的纹理
 *
 * @return void  
 */
void MeshVertexData::SetMeshVertexTexture(int idx, Vector2 newTexture)
{
	if( idx < 0 || idx >= m_meshVertexBuffer.size() )
	{
		throw "Vertex Index Invalid!";
	}

	m_meshVertexBuffer[idx].texture = newTexture;
}


/** @note 设置一个网格点
 *
 *@param idx   点的索引
 *@param newMV 点的信息
 *
 * @return void  
 */
void MeshVertexData::SetMeshVertex(int idx, MeshVertex newMV)
{
	if( idx < 0 || idx >= m_meshVertexBuffer.size() )
	{
		throw "Vertex Index Invalid!";
	}

	m_meshVertexBuffer[idx] = newMV;
}

/** @note 设置网格点的类型
 *
 *@param type 点的类型
 *
 * @return void  
 */
void MeshVertexData::SetVertexType(VertexType type)
{
	m_type = type;
}


/** @note 得到网格点的类型
 * 
 *
 * @return VertexType  网格点的类型
 */
VertexType MeshVertexData::GetVertexType()const
{
	return m_type;
}


/** @note 为所有的点分配内存
 *
 *@param  nVertex 点的个数
 *
 * @return void  
 */
void MeshVertexData::AllocateBuffer(const int nVertex)
{
	m_meshVertexBuffer.resize(nVertex);
}


/** @note 得到一个网格点指针
 *
 *@param idx   点的索引
 *
 * @return MeshVertex * 网格点的指针
 */
MeshVertex* MeshVertexData::GetPMeshVertex(int idx)
{
	return &m_meshVertexBuffer[idx];
}