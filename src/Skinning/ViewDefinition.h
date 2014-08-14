/** @file
* @brief 视点空间定义的头文件
* @author 李响
* @date 2009/06/30
* @version 1.0
*
* 该文件定义了视点相关模型中的视点空间。
*/

#ifndef VIEWDEFINITION_H
#define VIEWDEFINITION_H

#include <list>
#include <vector>
#include "..\\MathLib\Mathematics.h"

namespace Caca
{
	/** @brief 邻域类型 */
	 enum Neighborhood
	 {
		 NEGATIVE = -1,		///< 负方向
		 BOTH = 0,			///< 正、负方向
		 POSITIVE = 1,		///< 正方向
	 };

	 /** @brief 视点结构 */
	 struct ViewPoint
	 {
		 int longitude;			///< 经度
		 int latitude;			///< 纬度
		 Neighborhood lonNb;	///< 经度邻域
		 Neighborhood latNb;	///< 纬度邻域
		 bool isValid;			///< 是否有效
	 };

	 /** @brief 视点列表 */
	 typedef std::list< ViewPoint > ViewPointList;

	 /** @brief 视点空间 */
	 typedef std::list< ViewPointList > KeyViewPoints;

	 class GLWidget;

	 /** @class ViewDefinition ViewDefinition.h "ViewDefinition.h"
	 * @brief 视点空间类的定义，
	 * 该类定义了视点相关模型中的关键视点定义，
	 * 以及任意视点下，关键视点的获取方法，插值权值计算方法等。
	 */
	 class ViewDefinition
	 {
	 public:
		 /** 
		 * @brief  构造函数
		 */
		 ViewDefinition(void);

		 /** 
		 * @brief  设置默认关键视点
		 */
		 void SetStandardDfn(void);

		 /** 
		 * @brief  获取任意视点相关的关键视点
		 */
		 ViewPointList* GetKeyViews(int lon, int lat) const; 

		 /** 
		 * @brief  获取所有关键视点的列表
		 */
		 ViewPointList* GetKeyViews( void ) const;

		 /** 
		 * @brief  计算视点混合权值
		 */
		 std::vector< double >* ComputeWeights( int lon, int lat, 
			 ViewPointList* keys) const;

		 /** 
		 * @brief  在视点空间里插入关键视点
		 */
		 bool InsertKeyView(int lon, int lat, 
			 Neighborhood lonNb = BOTH, Neighborhood latNb = BOTH);

		 /** 
		 * @brief  根据摄像机参数和关节方向计算当前视点
		 */
		 static std::pair< int, int > ComputeViewPoint(const GLWidget* pW, 
			 const Quaternion& rot);

	 private:

		 KeyViewPoints m_keyViews;	///<视点定义
	 };
}




#endif //VIEWDEFINITION_H
