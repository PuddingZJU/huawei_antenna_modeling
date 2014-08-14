/** @file 
* @ brief ����㶨���ʵ���ļ�.
* @author ������
* @date 2008-10-27
* @version 0.1
*
* ���ļ��ж�������㼯�ϣ��Լ���صĲ���
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


/** @note ���һ�������
 *
 *@param mv  Ҫ��ӵĵ�
 *
 * @return void 
 */
void MeshVertexData::AddMeshVertex(MeshVertex mv)
{
	m_meshVertexBuffer.push_back(mv);
}

/** @note �õ������ĸ���
 *
 *
 * @return int ��ĸ��� 
 */
int MeshVertexData::GetVertexCount()const
{
	return (int)m_meshVertexBuffer.size();
}

/** @note �õ�һ�������
 *
 *@param idx   �������
 *
 * @return MeshVertex 
 */
MeshVertex MeshVertexData::GetMeshVertex(int idx) const
{
	return m_meshVertexBuffer[idx];
}

/** @note �õ�һ�������λ��
 *
 *@param idx   �������
 *
 * @return Vector3 ���λ�� 
 */
Vector3 MeshVertexData::GetMeshVertexPos(int idx)const
{
	if( idx < 0 || idx >= m_meshVertexBuffer.size() )
	{
		throw "Vertex Index Invalid!";
	}

	return m_meshVertexBuffer[idx].pos;
}

/** @note �õ�һ�������ķ���
 *
 *@param idx   �������
 *
 * @return Vector3 ��ķ���
 */

Vector3 MeshVertexData::GetMeshVertexNormal(int idx)const
{
	if( idx < 0 || idx >= m_meshVertexBuffer.size() )
	{
		throw "Vertex Index Invalid!";
	}

	return m_meshVertexBuffer[idx].normal;
}

/** @note �õ�һ������������
 *
 *@param idx   �������
 *
 * @return Vector2 ������� 
 */
Vector2 MeshVertexData::GetMeshVertexTexture(int idx)const
{
	if( idx < 0 || idx >= m_meshVertexBuffer.size() )
	{
		throw "Vertex Index Invalid!";
	}

	return m_meshVertexBuffer[idx].texture;
}


/** @note ����һ�������λ��
 *
 *@param idx   �������
 *@param newPos ���λ��
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

/** @note ����һ������㷨��
 *
 *@param idx   �������
 *@param newNormal ��ķ���
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

/** @note ����һ�����������
 *
 *@param idx   �������
 *@param newTexture �������
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


/** @note ����һ�������
 *
 *@param idx   �������
 *@param newMV �����Ϣ
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

/** @note ��������������
 *
 *@param type �������
 *
 * @return void  
 */
void MeshVertexData::SetVertexType(VertexType type)
{
	m_type = type;
}


/** @note �õ�����������
 * 
 *
 * @return VertexType  ����������
 */
VertexType MeshVertexData::GetVertexType()const
{
	return m_type;
}


/** @note Ϊ���еĵ�����ڴ�
 *
 *@param  nVertex ��ĸ���
 *
 * @return void  
 */
void MeshVertexData::AllocateBuffer(const int nVertex)
{
	m_meshVertexBuffer.resize(nVertex);
}


/** @note �õ�һ�������ָ��
 *
 *@param idx   �������
 *
 * @return MeshVertex * ������ָ��
 */
MeshVertex* MeshVertexData::GetPMeshVertex(int idx)
{
	return &m_meshVertexBuffer[idx];
}