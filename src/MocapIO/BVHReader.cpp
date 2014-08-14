//#include "stdafx.h"

#include "BVHReader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <iostream>
using namespace Caca;

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BVHReader::BVHReader(std::string filepathname) 
: m_filepathname(filepathname)
{
	this->m_pmc = NULL;
}

BVHReader::BVHReader()
{
	this->m_pmc = NULL;
}

BVHReader::~BVHReader()
{
	this->m_pstream = NULL;
}

void BVHReader::setStream(std::istream& is)
{
	this->m_pstream = &is;
}

//void BVHReader::setStream2(std::ifstream ifs)
//{
//	//this->m_pstream = &ifs;
//}


void BVHReader::open() throw (std::exception)
{
	this->m_ifstream.open(this->m_filepathname.c_str() , std::ios::in);

	if (m_ifstream.fail())
	{
		throw std::runtime_error("CANNOT open file \"" + this->m_filepathname + "\" for reading.");
	}
	else
	{
		this->m_pstream = &m_ifstream;
	}
}

void BVHReader::close() throw (std::exception)
{
	this->m_ifstream.close();
}

void BVHReader::setFilePathName(std::string filepathname)
{
	this->m_filepathname = filepathname;
}

void BVHReader::exceptToken(std::string strToken) throw (TextDataReaderError, std::exception)
{
	if (! checkToken(strToken))
	{
		std::ostringstream ost;
		ost << this->getCurrentLineNo();
		throw TextDataReaderError("Excepted token \"" + strToken + "\" no found at line " + ost.str()
			+ " in file \"" + this->m_filepathname + "\" .");
	}
}

void BVHReader::exceptDataF(double f)
{
	double ff = nextFloat();
	if (! ( (f-ff) < M_TOLERANCE || (ff-f) < M_TOLERANCE ) )
	{
		std::ostringstream ost;
		ost << f;
		std::string str ("Excepted data ");
		str += ost.str();
		str += " no found at line ";
		ost.clear();
		ost << this->getCurrentLineNo();
		str += ost.str();
		str = str + " in file \""+ this->m_filepathname + "\" .";

		throw TextDataReaderError(str);
	}
}

void BVHReader::exceptDataI(int i)
{
	int ii = nextInt();
	
	if ( i != ii )
	{
		std::ostringstream ost;
		ost << i;
		std::string str ("Excepted data ");
		str += ost.str();
		str += " no found at line ";
		ost.clear();
		ost << this->getCurrentLineNo();
		str += ost.str();
		str = str + " in file \""+ this->m_filepathname + "\" .";
		throw TextDataReaderError(str);
	}
}

void BVHReader::readSkeleton()
{	
	fillBuf();
	m_tempEndSiteIndex =0;
	// hierarchy
	exceptToken("HIERARCHY");
	readSkeletonRelatively();
}

MotionJoint* BVHReader::readSkeletonRelatively()
{
	
	std::string strTemp = this->nextWord();

	if ( 0 == strTemp.compare("ROOT"))
	{
		// root joint
		m_pmc->setRoot(m_pmc->addJoint()); 
		m_pmc->getRoot(0)->m_JointType = MotionJoint::ROOT_JOINT;
		// root name
		m_pmc->setJointName(this->nextWord(), m_pmc->getRoot(0));

		// "{"
		exceptToken("{");

		// offset data of root joint
		exceptToken("OFFSET");
		m_pmc->getRoot(0)->setXOffset(nextFloat());
		m_pmc->getRoot(0)->setYOffset(nextFloat());
		m_pmc->getRoot(0)->setZOffset(nextFloat());

		// channels
		exceptToken("CHANNELS");
		exceptDataI(6);
		exceptToken("Xposition");
		exceptToken("Yposition");
		exceptToken("Zposition");
//		exceptToken("Zrotation");
//		exceptToken("Xrotation");
//		exceptToken("Yrotation");
		std::string s1;
		s1 = nextWord();
		// a bit crack here...  need to improve this some day.
		// check out: ZXY or XYZ ?
		if ( 0 == s1.compare("Zrotation") )
		{
			// ZXY
			exceptToken("Xrotation");
			exceptToken("Yrotation");

			m_EulerAngleSeq = SEQ_ZXY;
			m_pmc->getRoot(0)->setEulerAnglesSequence(SEQ_ZXY);
		}
		else if ( 0 == s1.compare("Xrotation") )
		{
			// XYZ
			exceptToken("Yrotation");
			exceptToken("Zrotation");

			m_EulerAngleSeq = SEQ_XYZ;
			m_pmc->getRoot(0)->setEulerAnglesSequence(SEQ_XYZ);
		}
		else
		{
			// error. at lease for now.
			m_EulerAngleSeq = SEQ_ERROR;

			std::ostringstream ost;
			std::string str ("Excepted Euler Angle Sequence ZXY or XYZ ");
			str += " no found at line ";
			ost.clear();
			ost << this->getCurrentLineNo();
			str += ost.str();
			str = str + " in file \""+ this->m_filepathname + "\" .";
			throw TextDataReaderError(str);
		}


		// setup data storage
		m_pmc->getRoot(0)->setPositionDataPointer(new std::vector<Vector3>);
		m_pmc->getRoot(0)->setRotationDataPointer(new std::vector<Vector3>);
		m_pmc->getRoot(0)->setQuaternionDataPointer(new std::vector<Quaternion>);

		// deal with children
		MotionJoint* pmjChild;
		while (pmjChild = readSkeletonRelatively())
		{
			m_pmc->setParent(pmjChild, m_pmc->getRoot(0));
		}
		
		return m_pmc->getRoot(0);

	}
	else if ( 0 == strTemp.compare("JOINT"))
	{
		// normal joint
		MotionJoint* pmj = m_pmc->addJoint();
		pmj->m_JointType = MotionJoint::NORMAL_JOINT;

		// joint name
		m_pmc->setJointName(this->nextWord(), pmj);

		// "{"
		exceptToken("{");

		// offset data of this normal joint
		exceptToken("OFFSET");
		pmj->setXOffset(nextFloat());
		pmj->setYOffset(nextFloat());
		pmj->setZOffset(nextFloat());

		// channels
		exceptToken("CHANNELS");
		exceptDataI(3);

		if ( m_EulerAngleSeq == SEQ_ZXY )
		{
			exceptToken("Zrotation");
			exceptToken("Xrotation");
			exceptToken("Yrotation");
			pmj->setEulerAnglesSequence(SEQ_ZXY);
		}
		else if ( m_EulerAngleSeq == SEQ_XYZ )
		{
			exceptToken("Xrotation");
			exceptToken("Yrotation");
			exceptToken("Zrotation");
			pmj->setEulerAnglesSequence(SEQ_XYZ);
		}
		else
		{
			std::ostringstream ost;
			std::string str ("Euler Angle Sequence should be ZXY or XYZ ");
			str = str + " in file \""+ this->m_filepathname + "\" .";
			throw TextDataReaderError(str);
		}

		// setup data storage
		pmj->setRotationDataPointer(new std::vector<Vector3>);
		pmj->setQuaternionDataPointer(new std::vector<Quaternion>);

		// deal with children
		MotionJoint* pmjChild;
		while (pmjChild = readSkeletonRelatively())
		{
			m_pmc->setParent(pmjChild, pmj);
		}

		return pmj;

	}
	else if ( 0 == strTemp.compare("End"))
	{
		// end site
		MotionJoint* pmj = m_pmc->addJoint();
		pmj->m_JointType = MotionJoint::END_SITE;

		// "Site"
		exceptToken("Site");

		// joint name
		std::ostringstream ost;
		std::string str ("EndSite_");
		ost << ++m_tempEndSiteIndex;
		str += ost.str();
		m_pmc->setJointName(str, pmj);

		// "{"
		exceptToken("{");

		// "OFFSET"
		exceptToken("OFFSET");
		pmj->setXOffset(nextFloat());
		pmj->setYOffset(nextFloat());
		pmj->setZOffset(nextFloat());

		// complete reading a "End Site" joint
		// "}" 
		exceptToken("}");

		return pmj;

	}
	else if ( 0 == strTemp.compare("}"))
	{
		return NULL;
	}
	else
	{
		// error
		std::ostringstream ost;
		ost << this->getCurrentLineNo();
		std::string str;
		str = "Unknown token \""+ strTemp +"\" at line " + ost.str() + 
			" in file \"" + this->m_filepathname + "\" .";
		throw TextDataReaderError(str);
	}

	return NULL;
}
void BVHReader::readData()
{
	// motion
	exceptToken("MOTION");

	// "Frames:"
	exceptToken("Frames:");
	m_pmc->setFrameCount(nextInt());

	// "Frame Time:"
	exceptToken("Frame");
	exceptToken("Time:");
	m_pmc->setFrameTime(nextFloat());

	// empty vector "channels"
	m_channels.clear();
	m_channels.reserve(m_pmc->getJointCount()+1);

	// enlarge the vectors in joints to get better performance
	reserveDataSpace(m_pmc->getFrameCount());

	// read raw data now
	int countRow = m_pmc->getFrameCount();
	int countCol = static_cast<int>(m_channels.size());
	double t1, t2, t3;
	
	for (int i = 0; i < countRow; i++)
	{
		for (int j = 0; j < countCol; j++)
		{
			t1 = nextFloat();
			t2 = nextFloat();
			t3 = nextFloat();

			Vector3 vec;

			if (j == 0)
			{
				// root position
				vec.x = t1;
				vec.y = t2;
				vec.z = t3;
			}
			else
			{
				// rotation
				if (m_EulerAngleSeq == SEQ_ZXY)
				{
					vec.z = t1;
					vec.x = t2;
					vec.y = t3;
				}
				else
				{
					// XYZ
					vec.x = t1;
					vec.y = t2;
					vec.z = t3;
				}
				
			}
			m_channels[j]->push_back(vec);
		}
	}


}

void BVHReader::read() throw(TextDataReaderError, std::exception)
{
	if (m_pstream == NULL)
	{
		if ( 0 == this->m_filepathname.length() )
		{
			throw TextDataReaderError("No filename given.");
		}

		this->open();
	}

	this->m_pmc = new MotionClip;
	m_pmc->setFileName(m_filepathname);

	try
	{
		this->readSkeleton();

		this->readData();

		this->updateData();
	}
	catch (...)
	{
		throw;
	}

	this->close();

	return;
	 
}

MotionClip* BVHReader::result()
{
	return this->m_pmc;
}

void BVHReader::reserveDataSpace(const int count)
{
	reserveDataSpaceRecursively(m_pmc->getRoot(0), count);
}

void BVHReader::reserveDataSpaceRecursively(MotionJoint* pmj, const int count)
{
	if (pmj->m_JointType == MotionJoint::ROOT_JOINT)
	{
		pmj->getPositionDataPointer()->reserve(count);
		pmj->getRotationDataPointer()->reserve(count);

		pmj->getQuaternionDataPointer()->reserve(count);

		m_channels.push_back(pmj->getPositionDataPointer());
		m_channels.push_back(pmj->getRotationDataPointer());
	}
	else if (pmj->m_JointType == MotionJoint::NORMAL_JOINT)
	{
		pmj->getRotationDataPointer()->reserve(count);

		pmj->getQuaternionDataPointer()->reserve(count);

		m_channels.push_back(pmj->getRotationDataPointer());
	}

	for (int i = 0; i < m_pmc->getChildrenCount(pmj); i++)
	{
		reserveDataSpaceRecursively(m_pmc->getChild(pmj, i), count);
	}
}

void BVHReader::updateData()
{
	updateDataRecursively(m_pmc->getRoot(0));
}

void BVHReader::updateDataRecursively(MotionJoint * pmj)
{
	if (pmj->m_JointType != MotionJoint::END_SITE)
	{
		pmj->updateEulerAngleToQuaternion();

		int c = m_pmc->getChildrenCount(pmj);
		for (int i = 0; i < c; i++)
		{
			updateDataRecursively(m_pmc->getChild(pmj, i));
		}
	}
}

