/* by Wei Yang */
/* Last Modified: 2006/09/11 16:17:21 .*/

#pragma once

#ifndef  _MOTION_KEY_FRAME_SERIES_H_INCLUDED_
#define  _MOTION_KEY_FRAME_SERIES_H_INCLUDED_

#include <map>
#include "Curve.h"


namespace Caca
{
	class MotionKeyframe
	{

		public:

			/* ====================  LIFECYCLE   ========================== */

			MotionKeyframe ();                  /* constructor      */
			MotionKeyframe ( const MotionKeyframe &other );  /* copy constructor */
			~MotionKeyframe ();                 /* destructor       */

			/* ====================  OPERATORS   ========================== */

			const MotionKeyframe& operator = ( const MotionKeyframe &other );  /* assignment operator */

			/* ====================  OPERATIONS  ========================== */

			int getFrameNumber(void) const;

			void setFrameNumber(int fn);

			void clear(void);

		public:			
		
			ComplexCurve Curve;

		protected:

			int m_nFrameNumber;




	}; /* -----  end of class  MotionKeyframe  ----- */


	///* Functor  used to sort MotionKeyframes. */
	//class smallerFrameNumber
	//	: public std::binary_function<MotionKeyframe, MotionKeyframe, bool>
	//{
	//public:

	//	bool operator() (const MotionKeyframe& kf1, const MotionKeyframe& kf2) const
	//	{
	//		return (kf1.getFrameNumber() < kf2.getFrameNumber());
	//	}
	//}; /* end of functor smallerFrameNumber */

	class MotionKeyframeSeries 
		: public std::map <int, MotionKeyframe>
	{

		public:

			/* ====================  LIFECYCLE   ========================== */

			MotionKeyframeSeries ();                  /* constructor      */
			MotionKeyframeSeries ( const MotionKeyframeSeries &other );  /* copy constructor */
			virtual ~MotionKeyframeSeries ();                 /* destructor       */

			/* ====================  OPERATORS   ========================== */

			const MotionKeyframeSeries& operator = ( const MotionKeyframeSeries &other );  /* assignment operator */

			/* ====================  OPERATIONS  ========================== */
		public:

			void SetKey (const MotionKeyframe& kf);

			void DeleteKey (int nFrameNo);

			bool IsKeyframeExist (int nFrameNo);

		
		protected:

		protected:
			/* We want to disable something here. */

			inline std::map<int, MotionKeyframe>::iterator
				erase(std::map<int, MotionKeyframe>::iterator _Where)
			{
				return std::map<int, MotionKeyframe>::erase (_Where);
			}

			inline std::map<int, MotionKeyframe>::iterator
				erase (
				std::map<int, MotionKeyframe>::iterator _First,
				std::map<int, MotionKeyframe>::iterator _Last
				)
			{
				return std::map<int, MotionKeyframe>::erase (_First, _Last);
			}

			inline size_t erase ( const int& _Keyval )
			{
				return std::map<int, MotionKeyframe>::erase( _Keyval ); 
			}

		/*	inline void erase (
					const int* _First, const int* _Last
					)
			{
				return std::map<int, MotionKeyframe>::erase (
						_First, _Last
						);
			}*/

			inline std::map<int, MotionKeyframe>::iterator insert (
					std::map<int, MotionKeyframe>::iterator _Where, 
					const std::pair<int, MotionKeyframe>& _Val
					)
			{
				return std::map<int, MotionKeyframe>::insert (_Where, _Val);
			}

			inline std::pair< std::map<int, MotionKeyframe>::iterator, bool >
				insert (const std::pair<int, MotionKeyframe>& _Val)
				{
					return std::map<int,MotionKeyframe>::insert ( _Val );
				}

			inline void insert (
					std::map<int, MotionKeyframe>::iterator _First,
					std::map<int, MotionKeyframe>::iterator _Last
					)
			{
				return std::map<int, MotionKeyframe>::insert (
						_First, _Last
						);
			}	



	}; /* -----  end of class  MotionKeyframeSeries  ----- */


}

#endif   /* ----- #ifndef _MOTION_KEY_FRAME_SERIES_H_INCLUDED_  ----- */
