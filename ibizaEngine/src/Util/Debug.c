#include "Debug.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void DebugAbort(bool _isAbort) {
	if(_isAbort)
		abort();
}

void DebugPrintAbort(bool _isAbort, const char* _str, ...) {
	va_list args;
	va_start(args, _str);
	printf(_str, args);
	printf("\n");
	va_end(args);
	
	DebugAbort(_isAbort);
}

void DebugPrintLogFile(FILE* _logFile, const char* _str, ...) {
	if(_logFile) {
		va_list args;
		va_start(args, _str);
		if(!fprintf(_logFile, _str, args)) {
			DebugPrintAbort(true, "로그파일에 글을 쓰는데에 실패했습니다.");
		}
		if(!fprintf(_logFile, "\n")) {
			DebugPrintAbort(true, "로그파일에 줄넘김을 실패했습니다.");
		}
		va_end(args);
	} else {
		DebugPrintAbort(true, "로그파일이 없습니다.");
	}
}
