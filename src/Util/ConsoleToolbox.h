#ifndef ConsoleToolbox_h__
#define ConsoleToolbox_h__
//#define NOMINMAX
//#include <Windows.h>
//#include <winbase.h>

void consoleSeprate(const char* s);

void consoleBackChar(int n) ;

void consoleRewriteChar(int n, const char* s);

void consolePauss();
//
//void startRedirectedProc(wchar_t *cmdline,const wchar_t* logFilePath);
//
//void consoleCall(const char* s, bool wait2end = true);

#endif // ConsoleToolbox_h__