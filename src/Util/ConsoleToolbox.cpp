#include "consoletoolbox.h"
#include <stdio.h>
#include <string.h>


#include "LogWriter.h"
void consoleBackChar( int n )
{
	if(n < 0) {
		n = 79;
	}
	for(int i = 0; i < n; i++) {
		printf("\b");
	}
	for(int i = 0; i < n; i++) {
		printf(" ");
	}	
	for(int i = 0; i < n; i++) {
		printf("\b");
	}
}

void consoleRewriteChar( int n, const char* s )
{
	consoleBackChar(n);
	printf("%s", s);
}

void consolePauss()
{
	printf("press enter to continue\n");
	getchar();
}

void consoleSeprate(const char* s)
{
	int nameLen = strlen(s);	
	int consoleWidth = 80;
	int leftw = consoleWidth/2 - nameLen/2;
	int rightw = consoleWidth - leftw - nameLen;
	for(int i = 0; i < leftw; i++) {
		printf("-");
	}
	printf("%s", s);
	for(int i = 0; i < rightw; i++) {
		printf("-");
	}
}
// 
// void startRedirectedProc(wchar_t *cmdline,const wchar_t* logFilePath)
// {
// 
// 	SECURITY_ATTRIBUTES sa={sizeof ( sa ),NULL,TRUE};
// 	SECURITY_ATTRIBUTES *psa=NULL;
// 	DWORD dwShareMode=FILE_SHARE_READ|FILE_SHARE_WRITE;
// 	OSVERSIONINFO osVersion={0};
// 	osVersion.dwOSVersionInfoSize =sizeof ( osVersion );
// 	if ( GetVersionEx ( &osVersion ) )
// 	{
// 		if ( osVersion.dwPlatformId ==VER_PLATFORM_WIN32_NT )
// 		{
// 			psa=&sa;
// 			dwShareMode|=FILE_SHARE_DELETE;
// 		}
// 	}
// 	//根据版本设置共享模式和安全属性
// 	HANDLE hConsoleRedirect=CreateFileW(
// 		logFilePath,
// 		GENERIC_WRITE,
// 		dwShareMode,
// 		psa,
// 		OPEN_ALWAYS,
// 		FILE_ATTRIBUTE_NORMAL,
// 		NULL );
// 	AssertLog(hConsoleRedirect != INVALID_HANDLE_VALUE);
// 
// 	STARTUPINFO s={sizeof ( s ) };
// 	s.dwFlags =STARTF_USESTDHANDLES;
// 	//使用标准柄和显示窗口
// 	s.hStdOutput =hConsoleRedirect;//将文件作为标准输出句柄
// 	//s.wShowWindow =SW_HIDE;//隐藏控制台窗口
// 	PROCESS_INFORMATION pi={0};
// 
// 	DWORD creationFlags = HIGH_PRIORITY_CLASS;
// 
// 	if ( CreateProcess( NULL,(LPWSTR)cmdline,NULL,NULL,TRUE,creationFlags,NULL,NULL,&s,&pi ) )
// 	{		
// 		WaitForSingleObject ( pi.hProcess ,INFINITE );		
// 		CloseHandle ( pi.hProcess );
// 		CloseHandle ( pi.hThread );		
// 	}
// 
// 	CloseHandle ( hConsoleRedirect );
// }

void consoleCall( const char* s, bool wait2end /*= true*/ )
{
	WinExec(s, SW_NORMAL);
}