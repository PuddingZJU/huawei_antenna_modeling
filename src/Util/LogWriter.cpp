#include "LogWriter.h"
#include "qstringlist.h"
#include "qdatetime.h"
#include "qdir.h"
#include "qcoreapplication.h"
#include "qfileinfo.h"

LogWriter::LogWriter()
: QThread(0)
, m_EnableLog(true)
, m_EnableAssert(true)
, m_ValidHistoryDays(3)
{

}

LogWriter::~LogWriter()
{
	if(debugFile.isOpen ())
	{
		//关闭文件
		debugFile.close();
	}
}

bool LogWriter::init(const char* logName)
{
	return newDebugLog(logName);
}

bool LogWriter::init()
{
	QString dataTimeStr = QString("%1_%2").arg(
		QDate::currentDate().toString("yyyy-MM-dd")).arg(
		QTime::currentTime().toString("hh-mm-ss"));
	return newDebugLog(QString("%1_%2.txt").arg(
		QCoreApplication::applicationName()).arg(
		dataTimeStr).toStdString().data());
}

void LogWriter::run()
{
	exec();
}
bool LogWriter::reinit()
{
	return true;
}
bool LogWriter::newDebugLog(const char* filename)
{
	debugFile.setFileName(filename);

	if(!debugFile.open(QIODevice::WriteOnly|QIODevice::Text))
	{
		return false;//无法建立日志文件
	}

	debugStream.setDevice(&debugFile);
	debugStream<<"This file record the log of the programm"<<endl;
	writeDebugMsgLine("log start",false);

	m_EnableLog = true;

	clearHistoryLogs(m_ValidHistoryDays);

	return true;
}

void LogWriter::writeDebugMsgLine(const QString& msg, bool errorMsg, 
								  int moduleID, bool withTime /* =true */,
								  bool newLine /* =true */ )
{
	if(!debugFile.isOpen())
		return;

	if(!m_EnableLog) {
		return;
	}

	mutex.lock();

	if(newLine)
	{
		debugStream<<endl;
	}

	if(withTime)
	{
		//记录时间		
		QString currentTime = QDateTime::currentDateTime().toString("yy-M-d h:mm:ss");
		debugStream<<currentTime<<": ";
	}

	if(errorMsg){
		debugStream<<"!ERROR: ";
	}

	switch(moduleID){
		case 0:break;
		case 1:debugStream<<"<"<<"Kernel"<<">";break;
		case 2:debugStream<<"<"<<"Canvas"<<">";break;
		case 3:debugStream<<"<"<<"Model"<<">";break;
		case 4:debugStream<<"<"<<"Face"<<">";break;
		case 5:debugStream<<"<"<<"Hair"<<">";break;
		case 6:debugStream<<"<"<<"Body"<<">";break;
		case 7:debugStream<<"<"<<"Clothes"<<">";break;
		case 8:debugStream<<"<"<<"Render"<<">";break;
		case 9:debugStream<<"<"<<"GUI"<<">";break;
		case 10:debugStream<<"<"<<"Camera"<<">";break;
		case 11:debugStream<<"<"<<"LitSphere"<<">";break;
		case 12:debugStream<<"<"<<"BVH"<<">";break;
		case 13:debugStream<<"<"<<"Skin"<<">";break;
		default:break;
	}
	debugStream<<msg;
	debugStream.flush();
	mutex.unlock();

	printf("%s\n", msg.toStdString().data());
}

void LogWriter::writeDebugMsgLines( const QStringList& messageLst,
								   bool isError /*= false*/,
								   int moduleID /*= 0*/, 
								   bool withTime /*= true*/, 
								   bool newLine /*= true*/ )
{
	foreach(QString str, messageLst) {
		writeDebugMsgLine(str, isError, moduleID, withTime, newLine);
	}
}

void LogWriter::clearHistoryLogs( int validDayNum )
{
	QDir dir(QDir::current());
	QStringList fileFilter;
	fileFilter << QString("%1_*.txt").arg(QCoreApplication::applicationName());
	QFileInfoList fioLst = dir.entryInfoList(fileFilter);

	foreach(QFileInfo fio, fioLst) {
		QDateTime modifiedTime = fio.lastModified();
		if(modifiedTime.daysTo(QDateTime::currentDateTime()) > 3) {
			WriteLog(tr("remove old log file %1").arg(fio.filePath()));
			QFile::remove(fio.filePath());
		}
	}
}
