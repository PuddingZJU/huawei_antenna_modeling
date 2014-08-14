/** @file
* @brief ��ģ������ͷ�ļ�
* @author ����
* @date 2009/06/29
* @version 1.0
*
* ���ļ��������ģ�ͽ�ģ����Ĳ���
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

	/** @brief �Ǽܲ��� */
	typedef std::vector< std::pair< std::string, std::string > > SkeletonParam;
	
	typedef std::pair< std::string, std::string > skeletonItem;

	/** @brief ��Χ������ */
	enum BOX_TYPE 
	{
		CUBOID,		///< ������
		SPHERE,		///< ����
		CYLINDER	///< Բ����
	};

	/** @brief ������Χ�нṹ */
	struct BoxParam
	{
		BOX_TYPE type;			///< ����
		std::string basePoint;	///< ������
		std::string refPoint;	///< �ο���
	};

	/** @brief ��Χ�в��� */
	typedef std::map< std::string, BoxParam > BoxesParam;

	/** @brief ��ż���˽ṹ���� */
	enum PUPPET_TOPOLOGY
	{
		CLOSE_SPHERE,		///< �������
		OPEN_RECTANGLE,		///< ������
		OPEN_HOUSE,			
		OPEN_CYLINDER,
		HALF_CYLINDER,
		HEMI_SPHERE,        ///< ����
		OPEN_ELLIPSE	        ///< ��Բ�� 
	};

	/** @brief ��żģ�ͳ�ʼ���Ƶ㶨�� */
	//typedef std::vector< DrawingAnalysis > MeshDef;

	/** @brief ��ż��λ�ṹ */
	struct PParam
	{
		PUPPET_TOPOLOGY type;	///< ��ż���˽ṹ
		std::string parentName;	///< ����ż��λ���ƣ�������������
		int initU;				///< u����ֱ���
		int initV;				///< v����ֱ���
		int subdivision;		///< ϸ�ִ���
		std::string basePoint;	///< �����ο���
		bool isCW;				///< ������Ƭ�Ƿ�˳ʱ��
		//MeshDef refPoint;		///< ��ģ�ο���
		bool isSilhouette;		///< �Ƿ���������
		QColor areaColor;		///< ������ɫ
		QColor slh1Color;		///< ����1��ɫ
		QColor slh2Color;		///< ����2��ɫ
		double slh1Width;		///< ����1���
		double slh2Width;		///< ����2���
		std::string texture;	///< ����������
		bool isStencil;			///< �Ƿ�Ӧ���ɰ�
		std::string stencil;	///< �ɰ�����
		bool isBulged;			///< �Ƿ�ͻ������
		bool isLitSphere;		///< �Ƿ�ʹ�ù�����
		bool isAdhere;          ///< �Ƿ���
		bool isVD;				///< �Ƿ��ӵ����
		bool isIterate;			///< �Ƿ����
		std::vector< std::string > pathVec; ///< �ʻ�·������
	};

	/** @brief ��żģ�Ͳ��� */
	typedef std::map< std::string, PParam > PuppetParam;

	/** @class ModelingParam ModelingParam.h "ModelingParam.h"
	* @brief ��ģ������Ķ��壬
	* ��������˽�ģ��������͡��Ǽܡ���Χ�к���żģ�Ͳ���
	*/
	class ModelingParam
	{
	public:
		std::string m_base;			///< �����ؽڵ�
		std::string m_ref;			///< �ο��ؽڵ�
		OBJECT_TYPE m_type;			///< ģ������
		SkeletonParam m_sklParam;	///< �Ǽܲ���
		BoxesParam  m_boxParam;		///< ��Χ�в���
		PuppetParam m_puppetParam;	///< ��ż����
		bool m_Template;
	};
}

#endif //MODELLINGPARAM_H