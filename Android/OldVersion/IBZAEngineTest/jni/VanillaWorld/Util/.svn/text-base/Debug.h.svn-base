#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>
#include <stdbool.h>

//_isAbort가 true이면 에러를 발생시키고 에러중단점으로 이동
void DebugAbort(bool _isAbort);

//해당 메세지를 출력하고 _isAbort가 true이면 에러를 발생시키고 에러중단점으로 이동
void DebugPrintAbort(bool _isAbort, const char* _str, ...);

//로그파일에 로그를 적는다.
void DebugPrintLogFile(FILE* _logFile, const char* _str, ...);

#endif