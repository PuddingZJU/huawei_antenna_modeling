//Motion clip implement file by YangWei
/* Last Modified: 2007/03/31 21:50:50 . */
//#include "stdafx.h"
 
#ifdef _DEBUG
#include <assert.h>
#include <iostream>
#endif // _DEBUG

//#include "stdafx.h"
#include "MotionClip.h"
#include "MotionJoint.h"

#include <exception>

using namespace Caca;

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



MotionClip::MotionClip() 
	: m_currentFrame (0), m_nNextIndex (0), m_bLocked (false), m_nJointCount(0), m_pKeyframeSeries(0)
	, m_fFrameTime(0.0333333)
{
}


MotionClip::~MotionClip()
{
	// delete all the joints in this motion clip.
	if (! m_JointsIndexMap.empty() )
	{
		for (std::map<int, MotionJoint*>::iterator i = m_JointsIndexMap.begin();
			i != m_JointsIndexMap.end(); i++)
		{
			if ( (*i).second )
			{
				delete ( (*i).second );
			}
		}
	}

	if (! m_JointsNameMap.empty() )
	{
		m_JointsNameMap.clear();
	}

	if (m_pKeyframeSeries)
	{
		delete m_pKeyframeSeries;
	}

	// assert (m_pRoot == NULL);

	
}

MotionClip* MotionClip::CloneAll()
{
	MotionClip* pmc=new MotionClip();

	pmc->m_bLocked = this->m_bLocked;
	pmc->m_currentFrame = 0;
	pmc->m_fFrameTime = this->m_fFrameTime;
	pmc->m_nFrameCount = this->m_nFrameCount;
	pmc->m_nJointCount = this->m_nJointCount;
	pmc->m_nNextIndex = this->m_nNextIndex;
	pmc->m_strFileName = this->m_strFileName;

	this->CloneAllRecursively( pmc, this->m_pRoot, NULL );
	
	updateIndex();

	if (this->m_pKeyframeSeries)
	{
		pmc->copyKeyframeSeries( *(this->m_pKeyframeSeries) );
	}
	else
	{
		pmc->m_pKeyframeSeries = NULL;
	}
	
	return pmc;
}

MotionClip* MotionClip::CloneSkeleton()
{
	MotionClip * pmc = new MotionClip();

	pmc->m_bLocked = this->m_bLocked;
	pmc->m_currentFrame = 0;
	pmc->m_fFrameTime = this->m_fFrameTime;
	pmc->m_nFrameCount = 0;
	pmc->m_nJointCount = this->m_nJointCount;
	pmc->m_nNextIndex = this->m_nNextIndex;
	pmc->m_strFileName = this->m_strFileName;

	this->CloneSkeletonRecursively( pmc, this->m_pRoot, NULL );

	updateIndex();

	if (this->m_pKeyframeSeries)
	{
		pmc->copyKeyframeSeries( *(this->m_pKeyframeSeries) );
	}
	else
	{
		pmc->m_pKeyframeSeries = NULL;
	}

	return pmc;
}

MotionClip* MotionClip::ClonePart( int start, int end )
{
	MotionClip* pmc=new MotionClip();

	if( start < 0 )
	{
		start = 0;
	}

	if( end >= m_nFrameCount )
	{
		end = m_nFrameCount - 1;
	}

	if( start > end )
	{
		return pmc;
	}

	pmc->m_bLocked = this->m_bLocked;
	pmc->m_currentFrame = 0;
	pmc->m_fFrameTime = this->m_fFrameTime;
	pmc->m_nFrameCount = end - start + 1;
	pmc->m_nJointCount = this->m_nJointCount;
	pmc->m_nNextIndex = this->m_nNextIndex;
	pmc->m_strFileName = this->m_strFileName;

	this->ClonePartRecursively( pmc, this->m_pRoot, NULL, start, end );

	updateIndex();

	//if (this->m_pKeyframeSeries)
	//{
	//	pmc->copyKeyframeSeries( *(this->m_pKeyframeSeries) );
	//}
	//else
	//{
		pmc->m_pKeyframeSeries = NULL;
	//}

	return pmc;
}

void MotionClip::ClonePartRecursively( MotionClip* pmc, MotionJoint* pmj, 
									  MotionJoint* pParentJoint, 
									  int start, int end )
{
	MotionJoint* pmjnew = pmj->ClonePart(start, end);

	if (pParentJoint) 
	{
		pParentJoint->m_pChildren.push_back(pmjnew);
	}
	else
	{
		pmc->m_pRoot = pmjnew;
	}

	pmjnew->m_pParent = pParentJoint;

	pmc->m_JointsIndexMap.insert( 
		std::pair<int, MotionJoint*> (pmjnew->m_nIndex, pmjnew));
	pmc->m_JointsNameMap.insert ( 
		std::pair<std::string, MotionJoint*> (pmjnew->m_strName, pmjnew));

	int c = static_cast<int>(pmj->m_pChildren.size());
	for (int i = 0; i < c; i++)
	{
		ClonePartRecursively( pmc, pmj->m_pChildren[i], pmjnew, start, end);
	}
}

void MotionClip::CloneAllRecursively(MotionClip* pmc, MotionJoint* pmj, 
									 MotionJoint* pParentJoint)
{
	MotionJoint* pmjnew = pmj->CloneAll();

	if (pParentJoint) 
	{
		pParentJoint->m_pChildren.push_back(pmjnew);
	}
	else
	{
		pmc->m_pRoot = pmjnew;
	}

	pmjnew->m_pParent = pParentJoint;

	pmc->m_JointsIndexMap.insert( 
		std::pair<int, MotionJoint*> (pmjnew->m_nIndex, pmjnew));
	pmc->m_JointsNameMap.insert ( 
		std::pair<std::string, MotionJoint*> (pmjnew->m_strName, pmjnew));

	int c = static_cast<int>(pmj->m_pChildren.size());
	for (int i = 0; i < c; i++)
	{
		CloneAllRecursively( pmc, pmj->m_pChildren[i], pmjnew);
	}
}

void MotionClip::CloneSkeletonRecursively(MotionClip* pmc, MotionJoint* pmj, 
										  MotionJoint* pParentJoint)
{
	MotionJoint* pmjnew = pmj->CloneSketelon();

	if (pParentJoint)
	{
		pParentJoint->m_pChildren.push_back(pmjnew);
	}
	else
	{
		pmc->m_pRoot = pmjnew;
	}

	pmjnew->m_pParent = pParentJoint;

	pmc->m_JointsIndexMap.insert( 
		std::pair<int, MotionJoint*> (pmjnew->m_nIndex, pmjnew));
	pmc->m_JointsNameMap.insert ( 
		std::pair<std::string, MotionJoint*> (pmjnew->m_strName, pmjnew));

	int c = static_cast<int>(pmj->m_pChildren.size());
	for (int i = 0; i < c; i++)
	{
		CloneSkeletonRecursively( pmc, pmj->m_pChildren[i], pmjnew);
	}

}

double MotionClip::getFrameTime() const
{
	return m_fFrameTime;
}


void MotionClip::setFrameTime(double fTime)
{
	m_fFrameTime = fTime;
}


int MotionClip::getFrameCount() const
{
	return m_nFrameCount;
}


void MotionClip::setFrameCount(int nCount)
{
	m_nFrameCount = nCount;
}


int MotionClip::getJointCount() const
{
	return m_nJointCount;
}


void MotionClip::setJointCount(int nCount)
{
	m_nJointCount = nCount;
}


std::string MotionClip::getFileName() const
{
	return m_strFileName;
}


void MotionClip::setFileName(std::string name)
{
	m_strFileName = name;
}


int MotionClip::clearAll()
{
	this->m_bLocked = false;
	this->m_currentFrame = 0;
	this->m_fFrameTime = 0;
	this->m_nFrameCount = 0;
	this->m_nJointCount = 0;
	this->m_nNextIndex = 0;
	this->m_strFileName = "";
	this->m_JointsIndexMap.clear();
	this->m_JointsNameMap.clear();

	return 0; 
}

int MotionClip::setJointName(std::string name , MotionJoint* pJoint)
{
	std::map<std::string, MotionJoint*>::iterator 
		it = this->m_JointsNameMap.find( pJoint->getName() );
	if ( it == this->m_JointsNameMap.end())
	{
		// not found in the map, insert it
		this->m_JointsNameMap.insert(std::pair<std::string, MotionJoint*> (name, pJoint));
	}
	else if ( name != it->second->getName() )
	{
		// rename
		this->m_JointsNameMap.erase (it);
		this->m_JointsNameMap.insert(std::pair<std::string, MotionJoint*> (name, pJoint));

	}

	pJoint->setName(name);
	return 0;
}

MotionJoint* MotionClip::addJoint()
{
	MotionJoint* p = new MotionJoint;

	p->m_nIndex = this->m_nNextIndex++;
	this->m_JointsIndexMap.insert( std::pair<int, MotionJoint*> ( p->m_nIndex, p));
	this->m_nJointCount ++;

	return p;
}

MotionJoint* MotionClip::addJoint(std::string name, Vector3 off, MotionJoint* parent)
{
	MotionJoint* p = new MotionJoint;

	p->m_nIndex = this->m_nNextIndex++;
	this->m_JointsIndexMap.insert( std::pair<int, MotionJoint*> ( p->m_nIndex, p));
	this->m_JointsNameMap.insert(make_pair(name, p));
	this->m_nJointCount++;

	p->setName(name);
	p->setXYZOffset(off);
	p->m_pParent = parent;

	if(!p->m_pParent) {
		p->m_JointType = MotionJoint::ROOT_JOINT;
		setRoot(p);	
	}

	return p;    
}

MotionJoint* MotionClip::addJoint(std::string name, double xoff, double yoff, double zoff, MotionJoint* parent)
{
	MotionJoint* p = new MotionJoint;

	p->m_nIndex = this->m_nNextIndex++;
	this->m_JointsIndexMap.insert( std::pair<int, MotionJoint*> (p->m_nIndex, p));
	this->m_nJointCount++;

	p->setName(name);
	p->setXOffset(xoff);
	p->setYOffset(yoff);
	p->setZOffset(zoff);
	p->m_pParent = parent;

	return p;    
}

int MotionClip::deleteJoint(MotionJoint* pJoint)
{
	//TODO: !!! change jointtype if root is deleted???

	// attach its children to its parent
	MotionJoint * pj;
	pj = getParent(pJoint);
	int c = getChildrenCount(pJoint);
	for (int i=0; i < c ; i++)
	{
		setParent( getChild(pJoint, i), pj );
	}

	deleteChild(pJoint, pj);

	delete pJoint;

	this->m_nJointCount--;
	this->updateIndex();

	return 0;
}

void MotionClip::updateIndex()
{
	this->m_nNextIndex =0;
	this->m_JointsIndexMap.clear();

	this->updateIndexRecursively( this->m_pRoot );
}

void MotionClip::updateIndexRecursively(MotionJoint* pmj)
{
	pmj->m_nIndex = this->m_nNextIndex ++;

	this->m_JointsIndexMap.insert( std::pair<int, MotionJoint*> ( pmj->m_nIndex, pmj ));

	int c = static_cast<int>(pmj->m_pChildren.size());
	for ( int i =0; i < c; i++)
	{
		this->updateIndexRecursively( pmj->m_pChildren[i] );
	}
}

void MotionClip::setParent(MotionJoint* pJoint, MotionJoint* pParent)
{
	if (pJoint && pParent)
	{
		pJoint->m_pParent = pParent;
		pParent->m_pChildren.push_back(pJoint);
	}
	else
	{
		throw std::runtime_error("Null Pointer Error in MotionClip::setParent");
	}
}

MotionJoint* MotionClip::getRoot(void)
{
	return m_pRoot;
}


MotionJoint* MotionClip::getRoot(int frameno)
{
	setCurrentFrame(frameno);

	return m_pRoot;
}

int MotionClip::setRoot(MotionJoint * root)
{
	root->m_JointType = MotionJoint::ROOT_JOINT;
	m_pRoot = root;
	return 0;
}

int MotionClip::setCurrentFrame(int frameno)
{
	if (this->m_currentFrame != frameno)
	{
		setCurrentFrameRecursively(this->m_pRoot, frameno);
		this ->m_currentFrame = frameno;
	}
	return 0;
}

int MotionClip::getCurrentFrame()
{
	return m_currentFrame;
}

void MotionClip::setCurrentFrameRecursively(MotionJoint* pj, int frameno)
{
	if(frameno >= getFrameCount()) {
		frameno = getFrameCount() - 1;
	}
	pj->setCurrentFrame(frameno);

	int c = this ->getChildrenCount(pj);
	for (int i =0 ; i<c; i++)
	{
		setCurrentFrameRecursively(this->getChild(pj,i), frameno);
	}
}

MotionJoint* MotionClip::findJoint(std::string name)
{
	std::map<std::string, MotionJoint*>::iterator i = m_JointsNameMap.find(name);
	if (i != this->m_JointsNameMap.end())
		return i->second;
	else
		return NULL;
}

MotionJoint* MotionClip::findJoint(std::string name, int frameno)
{
	setCurrentFrame(frameno);
	std::map<std::string, MotionJoint*>::iterator i = m_JointsNameMap.find(name);
	if (i != this->m_JointsNameMap.end())
		return i->second;
	else
		return NULL;
}

MotionJoint* MotionClip::findJoint(int index)
{
	std::map<int, MotionJoint*>::iterator i = m_JointsIndexMap.find(index);
	if (i != this->m_JointsIndexMap.end())
		return i->second;
	else
		return NULL;

}
MotionJoint* MotionClip::findJoint(int index, int frameno)
{
	setCurrentFrame(frameno);
	std::map<int, MotionJoint*>::iterator i = m_JointsIndexMap.find(index);
	if (i != this->m_JointsIndexMap.end())
		return i->second;
	else
		return NULL;
}

MotionJoint* MotionClip::getParent(MotionJoint* pJoint)
{
	return pJoint->m_pParent;
}

MotionJoint* MotionClip::getParent(int index)
{
	return getParent( findJoint (index));
}

int MotionClip::getParentIndex(MotionJoint* pJoint)
{
	//2008.05.20�����޸�
	return pJoint->m_pParent ? pJoint->m_pParent->m_nIndex : -1; 
}

int MotionClip::getParentIndex(int index)
{
	return getParentIndex(findJoint(index)); 
}

int MotionClip::getJointIndex(MotionJoint* pJoint)
{
	return pJoint->m_nIndex;
}

int MotionClip::getJointIndexByName(std::string name)
{
	return getJointIndex( findJoint(name) );
}

int MotionClip::getChildrenCount(MotionJoint* pJoint)
{
	return static_cast<int> (pJoint->m_pChildren.size());
}

int MotionClip::getChildrenCount(int index)
{
	return getChildrenCount(findJoint(index)); 
}

MotionJoint* MotionClip::getChild(MotionJoint* pJoint, int childno)
{
	return ( pJoint->m_pChildren[childno]);    
}

MotionJoint* MotionClip::getChild(int index, int childno)
{
	return getChild(findJoint(index), childno);
}


int MotionClip::deleteChild(MotionJoint *pj ,MotionJoint* pParent)
{
	for (std::vector<MotionJoint*>::iterator i = pParent->m_pChildren.begin();
		i != pParent->m_pChildren.end(); i++)
	{
		if (pj == *i)
		{
			pParent->m_pChildren.erase(i);
			break;
		}
	}

	return 0;
}

int MotionClip::insertFrame(int beforewhich, int count)
{	
	this->m_pRoot->m_pPositionData->insert(
		this->m_pRoot->m_pPositionData->begin() + beforewhich,
		count, Vector3::ZERO
		);

	MotionJoint* pmj;

	for ( std::map<int, MotionJoint*>::iterator i = this->m_JointsIndexMap.begin();
		i != this->m_JointsIndexMap.end(); i++)
	{
		pmj = (*i).second;
		if (pmj->m_pRotationData)
		{
			pmj-> m_pRotationData->insert(
				pmj->m_pRotationData->begin() + beforewhich,
				count, Vector3::ZERO
				);
		}
		if (pmj->m_pQuaternionData)
		{
			pmj-> m_pQuaternionData->insert(
				pmj->m_pQuaternionData->begin() + beforewhich,
				count, Quaternion::IDENTITY
				);
		}
		if (pmj->m_pScaleData)
		{
			pmj->m_pScaleData->insert(
				pmj->m_pScaleData->begin() + beforewhich,
				count, Vector3::UNIT_SCALE
				);
		}
	}

	this->m_nFrameCount += count;

	return (this->m_nFrameCount);
}

int MotionClip::insertFrameBehind(int behindwhich, int count)
{
	this->m_pRoot->m_pPositionData->insert(
		this->m_pRoot->m_pPositionData->begin() + behindwhich + 1,
		count, Vector3::ZERO
		);

	MotionJoint* pmj;

	for ( std::map<int, MotionJoint*>::iterator i = this->m_JointsIndexMap.begin();
		i != this->m_JointsIndexMap.end(); i++)
	{
		pmj = (*i).second;
		if (pmj->m_pRotationData)
		{
			pmj->m_pRotationData->insert(
				pmj->m_pRotationData->begin() + behindwhich + 1,
				count, Vector3::ZERO
				);
		}
		if (pmj->m_pQuaternionData)
		{
			pmj->m_pQuaternionData->insert(
				pmj->m_pQuaternionData->begin() + behindwhich + 1,
				count, Quaternion::IDENTITY
				);
		}
		if (pmj->m_pScaleData)
		{
			pmj->m_pScaleData->insert(
				pmj->m_pScaleData->begin() + behindwhich + 1,
				count, Vector3::UNIT_SCALE
				);
		}

	}

	this->m_nFrameCount += count;

	return (this->m_nFrameCount);
}

void MotionClip::deleteFrame ( int start, int count)
{
	this->m_pRoot->m_pPositionData->erase( 
		this->m_pRoot->m_pPositionData->begin() + start,
		this->m_pRoot->m_pPositionData->begin() + start + count
		);

	MotionJoint* pmj;
	for ( std::map<int, MotionJoint*>::iterator i = this->m_JointsIndexMap.begin();
		i != this->m_JointsIndexMap.end(); i++)
	{
		pmj = (*i).second;
		if (pmj->m_pRotationData)
		{
			pmj->m_pRotationData->erase(
				pmj->m_pRotationData->begin() + start,
				pmj->m_pRotationData->begin() + start + count
				);
		}
		if (pmj->m_pQuaternionData)
		{
			pmj->m_pQuaternionData->erase(
				pmj->m_pQuaternionData->begin() + start,
				pmj->m_pQuaternionData->begin() + start + count
				);
		}
		if (pmj->m_pScaleData)
		{
			pmj->m_pScaleData->erase(
				pmj->m_pScaleData->begin() + start,
				pmj->m_pScaleData->begin() + start + count
				);
		}
	}

	this->m_nFrameCount -= count;
}

int MotionClip::GetIndexCount()
{
	return static_cast<int>(m_JointsIndexMap.size());
}

bool MotionClip::compareSkeleton(MotionClip* pmc, MotionClip* pmc2/* = NULL */)
{
	if (pmc2 == NULL)
	{
		pmc2 = this;
	}

	if (pmc == pmc2)
		return true;
	else
	{
		return compareSkeletonRecursively(pmc, pmc2, pmc->getRoot(0), pmc2->getRoot(0));
	}
}

bool MotionClip::compareSkeletonRecursively(MotionClip* pmc, MotionClip* pmc2, MotionJoint* pmj, MotionJoint* pmj2)
{
	Vector3 v1, v2;
	// TODO: need to compare bone length?
	v1 = pmj->getXYZOffset();
	v2 = pmj2->getXYZOffset();
	if ((v1.x - v2.x > M_TOLERANCE) && (v1.y - v2.y > M_TOLERANCE) && (v1.z - v2.z > M_TOLERANCE))
		return false;

	int c1, c2;
	c1 = pmc->getChildrenCount(pmj);
	c2 = pmc2->getChildrenCount(pmj2);
	if (c1 != c2)
		return false;

	for (int i = 0; i < c1; i++)
	{
		if (!(compareSkeletonRecursively(pmc, pmc2, pmc->getChild(pmj,i), pmc2->getChild(pmj2,i))))
		{
			return false;
		}
	}
	return true;
}

MotionKeyframeSeries * MotionClip::getKeyframeSeries(void) const
{
	return this->m_pKeyframeSeries;
}

MotionKeyframeSeries * MotionClip::initKeyframeSeries(void)
{
	if (this->m_pKeyframeSeries)
	{
		delete this->m_pKeyframeSeries;
	}
	this->m_pKeyframeSeries = new MotionKeyframeSeries;

	return this->m_pKeyframeSeries;
}

void MotionClip::copyKeyframeSeries (MotionKeyframeSeries & kfs)
{
	if (this->m_pKeyframeSeries)
	{
		delete this->m_pKeyframeSeries;
	}
	this->m_pKeyframeSeries = new MotionKeyframeSeries ( kfs );
}

void MotionClip::AdjustToGround(double height, bool isscale)
{

	double btm;		//��͸߶�
	Vector3 pc;		//�Ӵ�λ��
	int nc = -1;			//�Ӵ��ؽ�

	std::vector<Vector3>* vPD = m_pRoot->getPositionDataPointer();

	double scale;

	for( int k = 0; k < vPD->size(); k++ )
	{
		//Ѱ�Ҹ�֡��͵ĵ�
		btm = 10000.0 + height;

		int nt;
		Vector3 pt;

		for( std::map<int, MotionJoint*>::iterator i = m_JointsIndexMap.begin();
			i != m_JointsIndexMap.end(); i++)
		{
			Vector3 jp = i->second->getAbsolutePosition(k);

			if( btm > jp.y )
			{
				nt = i->first;
				pt = jp;
				btm = jp.y;
			}
		}

		if(isscale)
		{
			if(k == 0)
			{
				scale = 1.5 * ((*vPD)[k].y - btm)/(*vPD)[k].y;
			}

			(*vPD)[k].x *= scale;
			//(*vPD)[k].y *= scale;
			(*vPD)[k].z *= scale;
		}

		(*vPD)[k].y -= btm - height;

	}

	m_pRoot->NeedUpdate();
}

void MotionClip::AdjustToFeet(double height, bool isscale)
{

	double btm;		//��͸߶�
	Vector3 pc;		//�Ӵ�λ��
	int nc = -1;			//�Ӵ��ؽ�

	std::vector<Vector3>* vPD = m_pRoot->getPositionDataPointer();

	double scale;

	for( int k = 0; k < vPD->size(); k++ )
	{
		//Ѱ�Ҹ�֡��͵ĵ�
		btm = 10000.0 + height;

		int nt;
		Vector3 pt;

		for( std::map<int, MotionJoint*>::iterator i = m_JointsIndexMap.begin();
			i != m_JointsIndexMap.end(); i++)
		{
			Vector3 jp = i->second->getAbsolutePosition(k);

			if( btm > jp.y )
			{
				nt = i->first;
				pt = jp;
				btm = jp.y;
			}
		}

		if( -1 == nc )
		{
			nc = nt;
			pc = Vector3(pt.x, height, pt.y);
		}
		else if( nt != nc  )
		{
			Vector3 pp = m_JointsIndexMap[nc]->getAbsolutePosition(k);
			nc = nt;
			pc += pt - pp; 
			pc.y = height;
		}

		(*vPD)[k] += pc - pt;
	}

	m_pRoot->NeedUpdate();
}


/* ********** debug code starts here ********** */

#ifdef _DEBUG
void MotionClip::dumpJoint(MotionJoint* pj)
{
	std::vector<Vector3>* pvec;
	std::vector<Quaternion>* pvecq;
	Vector3 v;

	if (!pj) return;

	std::cout << pj->getName() << "{"<<std::endl;
	if (pj->m_JointType == MotionJoint::ROOT_JOINT)
	{
		std::cout<< "Position: ";
		pvec = pj -> getPositionDataPointer();
		for (std::vector<Vector3>::iterator i = pvec->begin(); i != pvec->end(); i++)
		{
			std::cout << *i << "|";
		}
		std::cout << std::endl;

		std::cout << "Rotation: ";
		pvec = pj -> getRotationDataPointer();
		for (std::vector<Vector3>::iterator i = pvec->begin(); i != pvec->end(); i++)
		{
			std::cout << *i << "|";
		}
		std::cout << std::endl;

		std::cout << "Quaternion: ";
		pvecq = pj -> getQuaternionDataPointer();
		for (std::vector<Quaternion>::iterator i = pvecq->begin();
			i != pvecq->end(); ++i)
		{
			std::cout << *i << "|";
		}
		std::cout << std::endl;

		std::cout << "Relative Position: ";
		int c = this->m_nFrameCount;
		for (int i = 0; i < c; i++)
		{
			v = pj->getRelativePosition(i);
			std::cout << v << "|";
		}
		std::cout << std::endl;

		std::cout << "Ab Position: ";
		for (int i = 0; i < c; i++)
		{
			v = pj->getAbsolutePosition(i);
			std::cout << v << "|";
		}
		std::cout << std::endl;

	}
	else if (pj -> m_JointType == MotionJoint::NORMAL_JOINT)
	{
		//std::cout << "Offset: "<< pj->getXYZOffset() << std::endl;
		std::cout << "Offset: ("<< pj->getXOffset() << ", " << pj->getYOffset() 
			<< ", " << pj->getZOffset() << ")" << std::endl;

		std::cout << "Rotation: ";
		pvec = pj -> getRotationDataPointer();
		for (std::vector<Vector3>::iterator i = pvec->begin(); i != pvec->end(); i++)
		{
			std::cout << *i << "|";
		}
		std::cout << std::endl;

		std::cout << "Quaternion: ";
		pvecq = pj -> getQuaternionDataPointer();
		for (std::vector<Quaternion>::iterator i = pvecq->begin();
			i != pvecq->end(); ++i)
		{
			std::cout << *i << "|";
		}
		std::cout << std::endl;


		std::cout << "Relative Position: ";
		int c = this->m_nFrameCount;
		for (int i = 0; i < c; i++)
		{
			v = pj->getRelativePosition(i);
			std::cout << v << "|";
		}
		std::cout << std::endl;

		std::cout << "Ab Position: ";
		for (int i = 0; i < c; i++)
		{
			v = pj->getAbsolutePosition(i);
			std::cout << v << "|";
		}
		std::cout << std::endl;
	}

	else if (pj -> m_JointType == MotionJoint::END_SITE)
	{
		std::cout << "Offset: ("<< pj->getXOffset() << ", " << pj->getYOffset() 
			<< ", " << pj->getZOffset() << ")" << std::endl;
	}

	int c = this->getChildrenCount(pj);
	for (int i=0; i<c; i++)
	{
		dumpJoint(this->getChild(pj, i));
	}
	std::cout<< "}" << std::endl;

}

void MotionClip::dump()
{
	MotionJoint* pj;
	pj = this->getRoot(0);
	std::cout << "Dumping MotionClip: " << std::endl;

	dumpJoint (pj);

}
#endif // _DEBUG
