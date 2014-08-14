/* by Wei Yang */
/* Last Modified: 2006/09/14 01:33:29 .*/

//#include "stdafx.h"
#include "MotionKeyframeSeries.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace Caca
{

	/* ----- Implement of class MotionKeyframe. ----- */

	MotionKeyframe::MotionKeyframe ()
	{
	}

	MotionKeyframe::MotionKeyframe ( const MotionKeyframe &other )
	{
	}

	MotionKeyframe::~MotionKeyframe ()
	{
	}

	const MotionKeyframe&
	MotionKeyframe::operator = ( const MotionKeyframe &other )
	{
		if(this!=&other)
		{
			this->m_nFrameNumber = other.m_nFrameNumber;
			this->Curve = other.Curve;
		}
		return *this;
	}  

	int MotionKeyframe::getFrameNumber (void) const
	{
		return m_nFrameNumber;
	}

	void MotionKeyframe::setFrameNumber (int fn)
	{
		m_nFrameNumber = fn;
	}

	void MotionKeyframe::clear(void)
	{
		this->m_nFrameNumber = -1;
		this->Curve.clear();
	}


	/* ----- end of implement of class MotionKeyframe. ----- */

	/* ----- Implement of class MotionKeyframeSeries. ----- */

	MotionKeyframeSeries::MotionKeyframeSeries ()
	{
	}  

	MotionKeyframeSeries::MotionKeyframeSeries ( const MotionKeyframeSeries &other )
	{
		std::map<int, MotionKeyframe>::operator = (other);
	}

	MotionKeyframeSeries::~MotionKeyframeSeries ()
	{
	}

	const MotionKeyframeSeries&
	MotionKeyframeSeries::operator = ( const MotionKeyframeSeries &other )
	{
		if(this!=&other)
		{
			this->std::map<int, MotionKeyframe>::operator = (other);
		}
		return *this;
	}

	void MotionKeyframeSeries::SetKey (const MotionKeyframe& kf)
	{
		(*this)[kf.getFrameNumber()] = kf;
	}

	void MotionKeyframeSeries::DeleteKey (int nFrameNo)
	{
		MotionKeyframeSeries::iterator it = this->find(nFrameNo);
		if ( it != this->end() )
		{
			// key exists.
			this->erase(it);
		}
	}

	bool MotionKeyframeSeries::IsKeyframeExist(int nFrameNo)
	{
		return ( this->find(nFrameNo) != this->end() );
	}


	/* ----- end of implement of class MotionKeyframeSeries. ----- */

}



