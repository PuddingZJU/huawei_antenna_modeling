/** @file
* @brief �ӵ�ռ䶨���ʵ���ļ�
* @author ����
* @date 2009/06/30
* @version 1.0
*
* ���ļ�ʵ�����ӵ����ģ���е��ӵ�ռ����ط�����
*/
#include "ViewDefinition.h"
#include "..\\SceneManager\GLWidget.h"

using namespace Caca;

/**
* @note ���캯��
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
* @note ����Ĭ�Ϲؼ��ӵ�
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
* @param lon ����
* @param lat γ��
* @param lonNb ��������
* @param latNb γ������
* @return �Ƿ����ɹ�
* @note ���ӵ�ռ���������ָ���Ĺؼ��ӵ�
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

	//����Ϊ�գ�ֱ�Ӳ����µ�γ��
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
		//�������ϼ�����������ظ���
		if( (i->begin()->latitude == -90 && lat == -90) ||
			(i->begin()->latitude == 90 && lat == 90) )
		{
			return false;
		}

		//����������õ��γ�ߣ������һ���µ�γ��
		else if( ( i->begin()->latitude > lat ) ||
			( i->begin()->latitude == lat && i->begin()->latNb > latNb ) )
		{
			ViewPointList v;
			v.push_back(vp);
			m_keyViews.insert(i,v);
			return true;
		}

		//�Ѱ����õ��γ��
		else if( i->begin()->latitude == lat && i->begin()->latNb == latNb )
		{
			for( ViewPointList::iterator iv = i->begin();
				iv != i->end(); iv++)
			{
				//���������ӵ㣬�����
				if( ( iv->longitude > lon ) ||
					( iv->longitude == lon && iv->lonNb > lonNb ) )
				{
					i->insert(iv,vp);
					return true;
				}

				//����������ظ��ӵ�
				else if( iv->longitude == lon && iv->lonNb == lonNb )
				{
					return false;
				}
			}

			//����ԭ��󾭶ȣ�ֱ�Ӳ�����ӵ�
			i->push_back(vp);
			return true;
		}
	}

	//����ԭ���γ�ȣ�ֱ�Ӳ����µ�γ��
	ViewPointList v;
	v.push_back(vp);
	m_keyViews.push_back(v);
	return true;
}

/** 
* @param lon ����
* @param lat γ��
* @return ��عؼ��ӵ��б�
* @note ��ȡ�ӵ�(lon, lat)��صĹؼ��ӵ�
*/
ViewPointList* ViewDefinition::GetKeyViews(int lon, int lat) const
{
	if( lon<=-180 || lon>180 || lat<-90 || lat>90 || 
		m_keyViews.empty() )
	{
		return 0;
	}
	
	ViewPointList* vpl = new ViewPointList;


	//���ϼ���
	if(lat == -90)
	{
		vpl->push_back( m_keyViews.front().front() );
		return vpl;
	}

	//�ڱ�����
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
			//��γ����
			if( i->begin()->latitude == lat && i->begin()->latNb == BOTH )
			{
				//С����С�ľ���
				if( i->begin()->longitude > lon )
				{
					vpl->push_back( i->back() );
					vpl->push_back( i->front() );
					return vpl;
				}

				for( ViewPointList::const_iterator iv = i->begin();
					iv != i->end(); ++iv)
				{
					//�ھ�γ�߽�����
					if( iv->longitude == lon && iv->lonNb == BOTH )
					{
						vpl->push_back( *iv );
						return vpl;
					}

					//��γ���ϣ����������㣩
					else if( iv->longitude > lon)
					{
						vpl->push_back( *iv );
						vpl->push_back( *(--iv) );
						return vpl;
					}
				}
			}

			//����γ����
			else if( i->begin()->latitude > lat )
			{
				--i;

				//���ϼ�Ȧ��
				if( i->begin()->latitude == -90)
				{
					vpl->push_back( i->front() );
				}

				else
				{
					for( ViewPointList::const_iterator iv = i->begin();
						iv != i->end(); iv++)
					{
						//�ھ����ϣ��Ϲؼ��ӵ�
						if( iv->longitude == lon && iv->lonNb == BOTH )
						{
							vpl->push_back( *iv );
							break;
						}

						//���ھ�γ���ϣ��Ϲؼ��ӵ�
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
				//�ڱ���Ȧ��
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
						//�ھ����ϣ����ؼ��ӵ�
						if( iv->longitude == lon && iv->lonNb == BOTH )
						{
							vpl->push_back( *iv );
							return vpl;
						}

						//���ھ�γ���ϣ����ؼ��ӵ�
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
* @return �ؼ��ӵ��б�
* @note ��ȡ���йؼ��ӵ���б�
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
* @param lon ����
* @param lat γ��
* @param ��عؼ��ӵ��б�
* @return ��ػ��Ȩֵ�б�
* @note �����ӵ�(lon, lat)������б��и����ؼ��ӵ�Ļ��Ȩֵ
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
* @param pW ģ����ʾ����
* @param rot �ؽڳ���
* @return ��ǰ�ӵ�
* @note ��̬����������ģ����ʾ���ڵ����������������Ĺؽڷ��򣬼��㵱ǰ�ӵ�
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
