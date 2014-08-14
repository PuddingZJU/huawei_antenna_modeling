#ifndef _SERIAL_TEXT_DATA_READER_H_INCLUDED_
#define _SERIAL_TEXT_DATA_READER_H_INCLUDED_

#include "DataRW.h"

namespace Caca

{
	class SerialTextDataReader : public TextDataReader
	{
	protected:
		/**
		 * Copy constructor, forbidden.
		 */
		SerialTextDataReader( const SerialTextDataReader& mdr)
		{
		}

		/**
		 * Copy constructor, forbidden.
		 */
		SerialTextDataReader operator= ( const SerialTextDataReader& )
		{

		}
		
		void fillBuf();


	public:
		/**
		 * Constructor.
		 */
		SerialTextDataReader( std::istream* pstream );

		SerialTextDataReader ();

		/**
		 * Cleans up.
		 */
		virtual ~SerialTextDataReader();
		

		int nextInt();
		
		double nextFloat();

		char nextChar();

		std::string nextWord();

		bool checkToken (std::string strToken);

		long getCurrentLineNo();

		void SetSkipWriteSpace(bool b);

	protected:
		std::istream* m_pstream;

		std::istringstream * m_pLine;

		std::string m_strLine; // temp. use

		long m_currentline;
		
	};
}
#endif //_SERIAL_TEXT_DATA_READER_H_INCLUDED_

