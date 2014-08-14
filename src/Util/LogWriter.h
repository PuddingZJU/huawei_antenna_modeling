#ifndef DEBUGOUT_H
#define DEBUGOUT_H

#include <QThread>
#include <QMutex>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "Singleton.h"

// message 输出内容
// moduleID 模块ID
#define WriteLog(message) LogWriter::Instance().writeDebugMsgLine(message)
#define WriteLogs(messageLst) LogWriter::Instance().writeDebugMsgLines(messageLst)
#define WriteError(message,moduleID) LogWriter::Instance().writeDebugMsgLine(message,true,moduleID)
#define AssertLog(exp) LogWriter::Instance().assertLog(#exp, exp)
#define EnableLog LogWriter::Instance().enableLog(true)
#define DisableLog LogWriter::Instance().enableLog(false)
#define EnableAssert LogWriter::Instance().enableAssert(true)
#define DisableAssert LogWriter::Instance().enableAssert(false)

class LogWriter : public QThread, public Ant::Singleton<LogWriter>
{	
		friend class Ant::Singleton<LogWriter>;
public:
	bool init(const char* logName);//初始化
	bool init();
	void run();
	bool reinit();
	QString getFileName() { return debugFile.fileName(); };

	void clearHistoryLogs(int validDayNum);

	// message 输出内容
	// isError 是否是错误
	// moduleID 模块ID
	// withTime 是否输出时间
	// newLine 是否换行
	void writeDebugMsgLine(const QString& message, bool isError = false, 
		int moduleID = 0, bool withTime = true, bool newLine = true);
	void writeDebugMsgLines(const QStringList& messageLst, bool isError = false,
		int moduleID = 0, bool withTime = true, bool newLine = true);

	void enableLog(bool val) { m_EnableLog = val; };
	bool enableLog() { return m_EnableLog; };
	bool enableAssert() const { return m_EnableAssert; }
	void enableAssert(bool val) { m_EnableAssert = val; }

	bool assertLog(QString exp, bool flag) {
		if(!m_EnableAssert) {
			return flag;
		}
		if(!flag) {
			WriteLog(QString("assert %1 failed").arg(exp));
			printf("press enter to continue...\n");
			getchar();
		}
		return flag;
	}

	int ValidHistoryDays() const { return m_ValidHistoryDays; }
	void ValidHistoryDays(int val) { m_ValidHistoryDays = val; }

protected:
	LogWriter();
	~LogWriter();

private:
	QFile debugFile;
	QTextStream debugStream;
	QMutex mutex;
	bool m_EnableLog;
	bool m_EnableAssert;
	int m_ValidHistoryDays;

private:
	bool newDebugLog(const char* filename);
};


//void WriteLog(const QString& message, bool isError = false, 
//			  int moduleID = 0, bool withTime = true, 
//			  bool newLine = true )
//{
//	LogWriter::Instance().writeDebugMsgLine(
//		message, isError, moduleID, withTime, newLine);
//};

#endif // DEBUGOUT_H


