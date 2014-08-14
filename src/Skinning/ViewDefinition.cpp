/** @file
* @brief 视点空间定义的实现文件
* @author 李响
* @date 2009/06/30
* @version 1.0
*
* 该文件实现了视点相关模型中的视点空间的相关方法。
*/
#include "ViewDefinition.h"
#include "..\\SceneManager\GLWidget.h"

using namespace Caca;

/**
* @note 构造函数
*/
ViewDefinition::ViewDefinition(void)
{
	InsertKeyView(0,-90);
	InsertKeyView(0,90);

	InsertKeyView(-90,0);
	InsertKeyView(0,0);
	InsertKeyView(90,0);
	InsertKeyView(180,0);
}

/**
* @note 设置默认关键视点
*/
void ViewDefinition::SetStandardDfn(void)
{
	InsertKeyView(-45,0);
	InsertKeyView(45,0);

	InsertKeyView(-90,-45);
	InsertKeyView(-45,-45);
	InsertKeyView(0,-45);
	InsertKeyView(45,-45);
	InsertKeyView(90,-45);
	InsertKeyView(180,-45);

	InsertKeyView(-90,45);
	InsertKeyView(-45,45);
	InsertKeyView(0,45);
	InsertKeyView(45,45);
	InsertKeyView(90,45);
	InsertKeyView(180,45);
}

/** 
* @param lon 经度
* @param lat 纬度
* @param lonNb 经度邻域
* @param latNb 纬度邻域
* @return 是否插入成功
* @note 在视点空间里插入参数指定的关键视点
*/
bool ViewDefinition::InsertKeyView(int lon, int lat, 
								   Neighborhood lonNb, Neighborhood latNb)
{
	if( lon<=-180 || lon>180 || lat<-90 || lat>90 )
		return false;

	ViewPoint vp;
	vp.longitude = lon;
	vp.latitude = lat;
	vp.lonNb = lonNb;
	vp.latNb = latNb;
	vp.isValid = false;

	//定义为空，直接插入新的纬线
	if( m_keyViews.empty() )
	{
		ViewPointList v;
		v.push_back(vp);
		m_keyViews.push_back(v);
		return true;
	}

	for( KeyViewPoints::iterator i = m_keyViews.begin(); 
		i != m_keyViews.end(); i++)
	{
		//北极和南极不允许插入重复点
		if( (i->begin()->latitude == -90 && lat == -90) ||
			(i->begin()->latitude == 90 && lat == 90) )
		{
			return false;
		}

		//如果不包含该点的纬线，则插入一条新的纬线
		else if( ( i->begin()->latitude > lat ) ||
			( i->begin()->latitude == lat && i->begin()->latNb > latNb ) )
		{
			ViewPointList v;
			v.push_back(vp);
			m_keyViews.insert(i,v);
			return true;
		}

		//已包含该点的纬线
		else if( i->begin()->latitude == lat && i->begin()->latNb == latNb )
		{
			for( ViewPointList::iterator iv = i->begin();
				iv != i->end(); iv++)
			{
				//不包含该视点，则插入
				if( ( iv->longitude > lon ) ||
					( iv->longitude == lon && iv->lonNb > lonNb ) )
				{
					i->insert(iv,vp);
					return true;
				}

				//不允许插入重复视点
				else if( iv->longitude == lon && iv->lonNb == lonNb )
				{
					return false;
				}
			}

			//大于原最大经度，直接插入该视点
			i->push_back(vp);
			return true;
		}
	}

	//大于原最大纬度，直接插入新的纬线
	ViewPointList v;
	v.push_back(vp);
	m_keyViews.push_back(v);
	return true;
}

/** 
* @param lon 经度
* @param lat 纬度
* @return 相关关键视点列表
* @note 获取视点(lon, lat)相关的关键视点
*/
ViewPointList* ViewDefinition::GetKeyViews(int lon, int lat) const
{
	if( lon<=-180 || lon>180 || lat<-90 || lat>90 || 
		m_keyViews.empty() )
	{
		return 0;
	}
	
	ViewPointList* vpl = new ViewPointList;


	//在南极点
	if(lat == -90)
	{
		vpl->push_back( m_keyViews.front().front() );
		return vpl;
	}

	//在北极点
	else if(lat == 90)
	{
		vpl->push_back( m_keyViews.back().front() );
		return vpl;
	}

	else
	{
		for( KeyViewPoints::const_iterator i = m_keyViews.begin(); 
			i != m_keyViews.end(); ++i)

		{
			//在纬线上
			if( i->begin()->latitude == lat && i->begin()->latNb == BOTH )
			{
				//小于最小的经度
				if( i->begin()->longitude > lon )
				{
					vpl->push_back( i->back() );
					vpl->push_back( i->front() );
					return vpl;
				}

				for( ViewPointList::const_iterator iv = i->begin();
					iv != i->end(); ++iv)
				{
					//在经纬线交点上
					if( iv->longitude == lon && iv->lonNb == BOTH )
					{
						vpl->push_back( *iv );
						return vpl;
					}

					//在纬线上（不包括交点）
					else if( iv->longitude > lon)
					{
						vpl->push_back( *iv );
						vpl->push_back( *(--iv) );
						return vpl;
					}
				}
			}

			//不在纬线上
			else if( i->begin()->latitude > lat )
			{
				--i;

				//在南极圈内
				if( i->begin()->latitude == -90)
				{
					vpl->push_back( i->front() );
				}

				else
				{
					for( ViewPointList::const_iterator iv = i->begin();
						iv != i->end(); iv++)
					{
						//在经线上，南关键视点
						if( iv->longitude == lon && iv->lonNb == BOTH )
						{
							vpl->push_back( *iv );
							break;
						}

						//不在经纬线上，南关键视点
						else if( iv->longitude > lon)
						{
							vpl->push_back( *iv );
							if( iv == i->begin() )
							{
								vpl->push_back( i->back() );
							}
							else
							{
								vpl->push_back( *(--iv) );
							}
							break;
						}
					}
				}

				++i;
				//在北极圈内
				if( i->begin()->latitude == 90)
				{
					vpl->push_back( i->front() );
					return vpl;
				}

				else
				{
					for( ViewPointList::const_iterator iv = i->begin();
						iv != i->end(); iv++)
					{
						//在经线上，北关键视点
						if( iv->longitude == lon && iv->lonNb == BOTH )
						{
							vpl->push_back( *iv );
							return vpl;
						}

						//不在经纬线上，北关键视点
						else if( iv->longitude > lon)
						{
							vpl->push_back( *iv );
							if( iv == i->begin() )
							{
								vpl->push_back( i->back() );
							}
							else
							{
								vpl->push_back( *(--iv) );
							}
							return vpl;
						}
					}
				}
			}
		}
	}

	return 0;
}



/** 
* @return 关键视点列表
* @note 获取所有关键视点的列表
*/
ViewPointList* ViewDefinition::GetKeyViews( void ) const
{
	ViewPointList* vpl = new ViewPointList;


	for( KeyViewPoints::const_iterator i = m_keyViews.begin(); 
		i != m_keyViews.end(); ++i)
	{
		for( ViewPointList::const_iterator iv = i->begin();
			iv != i->end(); ++iv)
		{
			vpl->push_back( *iv );
		}
	}

	return vpl;
}

/** 
* @param lon 经度
* @param lat 纬度
* @param 相关关键视点列表
* @return 相关混合权值列表
* @note 计算视点(lon, lat)相对于列表中各个关键视点的混合权值
*/
std::vector< double >* ViewDefinition::ComputeWeights( int lon, int lat, 
													  ViewPointList* keys) const
{
	std::vector<double>* weights = new std::vector<double>();
	switch(keys->size())
	{
	case 1:
		weights->push_back(1.0);
		break;
	
	case 2:
		if( keys->front().longitude == keys->back().longitude )
		{
			double dl = keys->back().latitude - keys->front().latitude;
			double dp = lat - keys->front().latitude;

			weights->push_back(1.0-dp/dl);
			weights->push_back(dp/dl);
		}
		else
		{
			double dl = keys->back().longitude - keys->front().longitude;
			double dp = lon - keys->front().longitude;

			weights->push_back(1.0-dp/dl);
			weights->push_back(dp/dl);
		}
		break;

	case 3:
		if( keys->front().latitude == -90)
		{
			ViewPointList::iterator i = keys->begin();
			i++;

			double dh = keys->back().longitude - i->longitude;
			double dv = keys->back().latitude - keys->front().latitude;
			double dx = lon - i->longitude;
			double dy = lat - keys->front().latitude;

			weights->push_back( 1.0-dy/dv );
			weights->push_back( (1.0-dx/dh) * (dy/dv) );
			weights->push_back( (dx/dh) * (dy/dv) );
		}
		else
		{
			ViewPointList::iterator i = keys->begin();
			i++;

			double dh = i->longitude - keys->front().longitude;
			double dv = keys->back().latitude - keys->front().latitude;
			double dx = lon - keys->front().longitude;
			double dy = lat - keys->front().latitude;

			weights->push_back( (1.0-dx/dh) * (1.0-dy/dv));
			weights->push_back( (dx/dh) * (1.0-dy/dv) );
			weights->push_back( dy/dv );
		}
		break;
		
	case 4:
		{
			double dh = keys->back().longitude - keys->front().longitude;
			double dv = keys->back().latitude - keys->front().latitude;
			double dx = lon - keys->front().longitude;
			double dy = lat - keys->front().latitude;

			weights->push_back( (1.0-dx/dh) * (1.0-dy/dv) );
			weights->push_back( (dx/dh) * (1.0-dy/dv) );
			weights->push_back( (1.0-dx/dh) * (dy/dv) );
			weights->push_back( (dx/dh) * (dy/dv) );
		}

		break;

	default:
		;
	}

	return weights;
}

/** 
* @param pW 模型显示窗口
* @param rot 关节朝向
* @return 当前视点
* @note 静态函数，根据模型显示窗口的摄像机参数和输入的关节方向，计算当前视点
*/
std::pair<int,int> ViewDefinition::ComputeViewPoint(const GLWidget* pW,
													const Quaternion& rot)
{
	Quaternion r(rot);

	r.Rotate(pW->m_xRot, pW->m_yRot, pW->m_zRot);
	r.Invert();

	Vector3 v = Vector3(pW->m_fCenterX - pW->m_fEyeX, 
		pW->m_fCenterY - pW->m_fEyeY, pW->m_fCenterZ - pW->m_fEyeZ );

	v = r * v;

	v.Normalize();

	int lat = ASinD( -v.y );
	int lon; 
	
	if( v.z <= 0 )
	{
		lon = ASinD( -v.x / CosD(lat) );
	}
	else if( v.x <= 0)
	{
		lon = 180 - ASinD( -v.x / CosD(lat) );
	}
	else
	{
		lon = -180 - ASinD( -v.x / CosD(lat) );
	}

	return std::pair<int,int>(lon, lat);
}
