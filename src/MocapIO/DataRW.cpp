//#include "stdafx.h"

#include "DataRW.h"

using namespace Caca;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/* ============================================================== */
DataReader::DataReader()
{

}


DataReader::DataReader(const DataReader &other)
{

}


DataReader::~DataReader()
{

}

const DataReader& DataReader::operator = (const DataReader &other)
{
	return *this;
}

/* ============================================================== */
DataWriter::DataWriter()
{

}


DataWriter::DataWriter(const DataWriter &other)
{

}


DataWriter::~DataWriter()
{

}

const DataWriter& DataWriter::operator = (const DataWriter &other)
{
	return *this;
}

/* ============================================================== */
TextDataReader::TextDataReader()
{

}


TextDataReader::TextDataReader(const TextDataReader &other)
{

}


TextDataReader::~TextDataReader()
{

}

const TextDataReader& TextDataReader::operator = (const TextDataReader &other)
{
	return *this;
}

void TextDataReader::read()
{
	return;
}

/* ============================================================== */
TextDataWriter::TextDataWriter()
{

}

TextDataWriter::TextDataWriter( std::ostream * pstream )
	: m_pstream (pstream)
{

}

TextDataWriter::TextDataWriter(const TextDataWriter &other)
{

}


TextDataWriter::~TextDataWriter()
{
	if (m_pstream)
		delete m_pstream;
}

const TextDataWriter& TextDataWriter::operator = (const TextDataWriter &other)
{
	return *this;
}

void TextDataWriter::write()
{
	return;
}

/* ============================================================== */

