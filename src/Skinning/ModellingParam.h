/** @file
* @brief 建模参数的头文件
* @author 李响
* @date 2009/06/29
* @version 1.0
*
* 该文件定义各层模型建模所需的参数
*/

#ifndef MODELLINGPARAM_H
#define MODELLINGPARAM_H

#include <map>
#include <list>
#include <string>
#include "..\src\gui\painting\qcolor.h"

//#include "../VDModel/DrawingAnalysis.h"

namespace Caca
{
	extern enum OBJECT_TYPE;

	/** @brief 骨架参数 */
	typedef std::vector< std::pair< std::string, std::string > > SkeletonParam;
	
	typedef std::pair< std::string, std::string > skeletonItem;

	/** @brief 包围盒类型 */
	enum BOX_TYPE 
	{
		CUBOID,		///< 长方体
		SPHERE,		///< 球体
		CYLINDER	///< 圆柱体
	};

	/** @brief 单个包围盒结构 */
	struct BoxParam
	{
		BOX_TYPE type;			///< 类型
		std::string basePoint;	///< 基本点
		std::string refPoint;	///< 参考点
	};

	/** @brief 包围盒参数 */
	typedef std::map< std::string, BoxParam > BoxesParam;

	/** @brief 人偶拓扑结构类型 */
	enum PUPPET_TOPOLOGY
	{
		CLOSE_SPHERE,		///< 封闭球体
		OPEN_RECTANGLE,		///< 开矩形
		OPEN_HOUSE,			
		OPEN_CYLINDER,
		HALF_CYLINDER,
		HEMI_SPHERE,        ///< 半球
		OPEN_ELLIPSE	        ///< 椭圆形 
	};

	/** @brief 人偶模型初始控制点定义 */
	//typedef std::vector< DrawingAnalysis > MeshDef;

	/** @brief 人偶部位结构 */
	struct PParam
	{
		PUPPET_TOPOLOGY type;	///< 人偶拓扑结构
		std::string parentName;	///< 父人偶部位名称，用于网格连接
		int initU;				///< u方向分辨率
		int initV;				///< v方向分辨率
		int subdivision;		///< 细分次数
		std::string basePoint;	///< 基本参考点
		bool isCW;				///< 三角面片是否顺时针
		//MeshDef refPoint;		///< 建模参考点
		bool isSilhouette;		///< 是否检测轮廓线
		QColor areaColor;		///< 区域颜色
		QColor slh1Color;		///< 轮廓1颜色
		QColor slh2Color;		///< 轮廓2颜色
		double slh1Width;		///< 轮廓1宽度
		double slh2Width;		///< 轮廓2宽度
		std::string texture;	///< 光照球纹理
		bool isStencil;			///< 是否应用蒙板
		std::string stencil;	///< 蒙板名称
		bool isBulged;			///< 是否突出法向
		bool isLitSphere;		///< 是否使用光照球
		bool isAdhere;          ///< 是否附着
		bool isVD;				///< 是否视点相关
		bool isIterate;			///< 是否迭代
		std::vector< std::string > pathVec; ///< 笔画路径索引
	};

	/** @brief 人偶模型参数 */
	typedef std::map< std::string, PParam > PuppetParam;

	/** @class ModelingParam ModelingParam.h "ModelingParam.h"
	* @brief 建模参数类的定义，
	* 该类包含了建模所需的类型、骨架、包围盒和人偶模型参数
	*/
	class ModelingParam
	{
	public:
		std::string m_base;			///< 基本关节点
		std::string m_ref;			///< 参考关节点
		OBJECT_TYPE m_type;			///< 模型类型
		SkeletonParam m_sklParam;	///< 骨架参数
		BoxesParam  m_boxParam;		///< 包围盒参数
		PuppetParam m_puppetParam;	///< 人偶参数
		bool m_Template;
	};
}

#endif //MODELLINGPARAM_H