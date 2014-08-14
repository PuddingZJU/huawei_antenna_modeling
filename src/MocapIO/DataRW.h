#ifndef DATA_READER_WRITER_H_INCLUDED
#define DATA_READER_WRITER_H_INCLUDED

#if _MSC_VER > 1000
// something that m$ c compiler ignored.
// we ignore the warning, too.
#pragma warning(disable: 4290) 

#endif //_MSC_VER > 1000

#include	<exception>
#include	<fstream>
#include	<sstream>
#include	<string>

#include "./MotionJoint.h"
#include "./MotionClip.h"

namespace Caca
{

	/*
	 * =====================================================================================
	 *        Class:  DataReader
	 *  Description:  
	 * =====================================================================================
	 */
	class DataReader
	{

	  public:

		/* ====================  LIFECYCLE   ========================================= */

		DataReader ();                  /* constructor      */
		DataReader ( const DataReader &other );  /* copy constructor */
		~DataReader ();                 /* destructor       */

		/* ====================  OPERATORS   ========================================= */

		const DataReader& operator = ( const DataReader &other );  /* assignment operator */

		/* ====================  OPERATIONS  ========================================= */
		
		virtual void read(void) = 0;
	    
		/* ====================  ACCESS      ========================================= */

		/* ====================  INQUIRY     ========================================= */

	  protected:

	  private:

	}; /* -----  end of class  DataReader  ----- */


	/*
	 * =====================================================================================
	 *        Class:  DataWriter
	 *  Description:  
	 * =====================================================================================
	 */
	class DataWriter
	{

	  public:

		/* ====================  LIFECYCLE   ========================================= */

		DataWriter ();                  /* constructor      */
		DataWriter ( const DataWriter &other );  /* copy constructor */
		~DataWriter ();                 /* destructor       */

		/* ====================  OPERATORS   ========================================= */

		const DataWriter& operator = ( const DataWriter &other );  /* assignment operator */

		/* ====================  OPERATIONS  ========================================= */

		virtual void write(void) = 0;

		/* ====================  ACCESS      ========================================= */

		/* ====================  INQUIRY     ========================================= */

	  protected:

	  private:

	}; /* -----  end of class  DataWriter  ----- */


	/*
	 * =====================================================================================
	 *        Class:  TextDataReader
	 *  Description:  
	 * =====================================================================================
	 */
	class TextDataReader : public DataReader
	{

	  public:

		/* ====================  LIFECYCLE   ========================================= */

		TextDataReader ();                  /* constructor      */
		TextDataReader ( const TextDataReader &other );  /* copy constructor */
		~TextDataReader ();                 /* destructor       */

		/* ====================  OPERATORS   ========================================= */

		const TextDataReader& operator = ( const TextDataReader &other );  /* assignment operator */

		/* ====================  OPERATIONS  ========================================= */

		virtual void read(void);

		/* ====================  ACCESS      ========================================= */

		/* ====================  INQUIRY     ========================================= */

	  protected:

	  private:

	}; /* -----  end of class  TextDataReader  ----- */


	/*
	 * =====================================================================================
	 *        Class:  TextDataWriter
	 *  Description:  
	 * =====================================================================================
	 */
	class TextDataWriter : public DataWriter
	{

	  public:

		/* ====================  LIFECYCLE   ========================================= */

		TextDataWriter ();                  /* constructor      */
		TextDataWriter ( std::ostream * pstream );

		TextDataWriter ( const TextDataWriter &other );  /* copy constructor */
		~TextDataWriter ();                 /* destructor       */

		/* ====================  OPERATORS   ========================================= */

		const TextDataWriter& operator = ( const TextDataWriter &other );  /* assignment operator */

		/* ====================  OPERATIONS  ========================================= */

		virtual void write(void);

		/* ====================  ACCESS      ========================================= */

		/* ====================  INQUIRY     ========================================= */

	  protected:
		std::ostream* m_pstream;

	  private:

	}; /* -----  end of class  TextDataWriter  ----- */



	/* ======================================================================== */

	class DataReaderError : public std::exception
	{
	public:
		DataReaderError(const std::string& str) : std::exception(str.c_str())
		{

		}

		DataReaderError(const char* pmsg) : std::exception(pmsg)
		{

		}

	};

	class DataWriterError : public std::exception
	{
	public:
		DataWriterError(const std::string& str) : std::exception(str.c_str())
		{

		}

		DataWriterError(const char* pmsg) : std::exception(pmsg)
		{

		}

	};



	class TextDataReaderError : public DataReaderError
	{
	public:
		TextDataReaderError(const std::string& str) : DataReaderError(str)
		{

		}

		TextDataReaderError(const char* pmsg) : DataReaderError(pmsg)
		{

		}

	};

	class TextDataWriterError : public DataWriterError
	{
	public:
		TextDataWriterError(const std::string& str) : DataWriterError(str)
		{

		}

		TextDataWriterError(const char* pmsg) : DataWriterError(pmsg)
		{

		}

	};
}
#endif //DATA_READER_WRITER_H_INCLUDED

