/** @file
* @brief �ӵ�ռ䶨���ͷ�ļ�
* @author ����
* @date 2009/06/30
* @version 1.0
*
* ���ļ��������ӵ����ģ���е��ӵ�ռ䡣
*/

#ifndef VIEWDEFINITION_H
#define VIEWDEFINITION_H

#include <list>
#include <vector>
#include "..\\MathLib\Mathematics.h"

namespace Caca
{
	/** @brief �������� */
	 enum Neighborhood
	 {
		 NEGATIVE = -1,		///< ������
		 BOTH = 0,			///< ����������
		 POSITIVE = 1,		///< ������
	 };

	 /** @brief �ӵ�ṹ */
	 struct ViewPoint
	 {
		 int longitude;			///< ����
		 int latitude;			///< γ��
		 Neighborhood lonNb;	///< ��������
		 Neighborhood latNb;	///< γ������
		 bool isValid;			///< �Ƿ���Ч
	 };

	 /** @brief �ӵ��б� */
	 typedef std::list< ViewPoint > ViewPointList;

	 /** @brief �ӵ�ռ� */
	 typedef std::list< ViewPointList > KeyViewPoints;

	 class GLWidget;

	 /** @class ViewDefinition ViewDefinition.h "ViewDefinition.h"
	 * @brief �ӵ�ռ���Ķ��壬
	 * ���ඨ�����ӵ����ģ���еĹؼ��ӵ㶨�壬
	 * �Լ������ӵ��£��ؼ��ӵ�Ļ�ȡ��������ֵȨֵ���㷽���ȡ�
	 */
	 class ViewDefinition
	 {
	 public:
		 /** 
		 * @brief  ���캯��
		 */
		 ViewDefinition(void);

		 /** 
		 * @brief  ����Ĭ�Ϲؼ��ӵ�
		 */
		 void SetStandardDfn(void);

		 /** 
		 * @brief  ��ȡ�����ӵ���صĹؼ��ӵ�
		 */
		 ViewPointList* GetKeyViews(int lon, int lat) const; 

		 /** 
		 * @brief  ��ȡ���йؼ��ӵ���б�
		 */
		 ViewPointList* GetKeyViews( void ) const;

		 /** 
		 * @brief  �����ӵ���Ȩֵ
		 */
		 std::vector< double >* ComputeWeights( int lon, int lat, 
			 ViewPointList* keys) const;

		 /** 
		 * @brief  ���ӵ�ռ������ؼ��ӵ�
		 */
		 bool InsertKeyView(int lon, int lat, 
			 Neighborhood lonNb = BOTH, Neighborhood latNb = BOTH);

		 /** 
		 * @brief  ��������������͹ؽڷ�����㵱ǰ�ӵ�
		 */
		 static std::pair< int, int > ComputeViewPoint(const GLWidget* pW, 
			 const Quaternion& rot);

	 private:

		 KeyViewPoints m_keyViews;	///<�ӵ㶨��
	 };
}




#endif //VIEWDEFINITION_H
