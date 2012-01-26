/**
 @file Util/VBDebug.h
 @brief 디버깅 유틸 함수들
 @author
 <table>
 <tr><th>Developer</th><th>Role</th><th>Email</th></tr>
 <tr><td>장원희</td><td>Main Programmer</td><td>mario@vanillabreeze.com</td></tr>
 <tr><td>김희동</td><td>Programmer</td><td>welivehere@vanillabreeze.com</td></tr>
 <tr><td>박두철</td><td>Programmer</td><td>encjf@vanillabreeze.com</td></tr>
 </table>
 @version 1.0
 @section License
 Copyright 2011 vanilla breeze. All rights reserved.
 */

#ifndef __VBDebug_H__
#define __VBDebug_H__

#include "../VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
	
    /**
     @brief VBDebug 구조체 타입 정의
     */
	typedef struct VBDebug VBDebug;
	
    /**
     @brief 디버그 정보 구조체
     */
	struct VBDebug {
        /**
         디버그 파일의 경로/이름
         */
		VBChar* path;
        /**
         디버그 파일 포인터
         */
		void* file;
	};
	
    /**
     @brief VBDebug를 메모리 할당합니다.
     @return 메모리 할당된 VBDebug.
     */
	VBDebug* VBDebugAlloc(void);
	
    /**
     @brief VBDebug를 초기화합니다.
     @param _debug VBDebug.
     @param _log_file_path 로그 파일의 경로.
     @return 초기화된 VBDebug.
     */
	VBDebug* VBDebugInit(VBDebug* _debug, const VBChar* _log_file_path);
	
    /**
     @brief VBDebug를 메모리 해제합니다.
     @param _debug VBDebug.
     */
	void VBDebugFree(VBDebug** _debug);
	
    /**
     @brief 프로그램을 중단합니다.
     @param _debug VBDebug.
     @param _isAbort 중단 플래그, VBTrue이면 중단, VBFalse이면 중단하지 않음.
     */
	void VBDebugAbort(VBDebug* _debug, VBBool _isAbort);
	
    /**
     @brief IDE의 로그패널에 로그를 출력합니다.
     @param _debug VBDebug.
     @param _str 포맷화된 문자열.
     */
	void VBDebugPrint(VBDebug* _debug, const VBChar* _str, ...);
	
    /**
     @brief 로그를 출력하고 프로그램을 중단합니다.
     @param _debug VBDebug.
     @param _isAbort 중단 플래그, VBTrue이면 중단, VBFalse이면 중단하지 않음.
     @param _str 포맷화된 문자열.
     */
	void VBDebugPrintAbort(VBDebug* _debug, VBBool _isAbort, const VBChar* _str, ...);
	
    /**
     @brief 로그 파일의 내용을 초기화 합니다.
     @param _debug VBDebug.
     */
	void VBDebugLogFileClear(VBDebug* _debug);
	
    /**
     @brief 로그 파일에 로그를 출력합니다.
     @param _debug VBDebug.
     @param _str 포맷화된 문자열.
     */
	void VBDebugPrintLogFile(VBDebug* _debug, const VBChar* _str, ...);
	
    /**
     @brief 로그 파일에 로그를 출력하고 프로세스를 종료합니다.
     @param _debug VBDebug.
     @param _isAbort 중단 플래그, VBTrue이면 중단, VBFalse이면 중단하지 않음.
     @param _str 포맷화된 문자열.
     */
	void VBDebugPrintLogFileAbort(VBDebug* _debug, VBBool _isAbort, const VBChar* _str, ...);
	
    /**
     @brief 로그를 디버그 패널에 출력하고 로그 파일에 출력합니다.
     @param _debug VBDebug.
     @param _str 포맷화된 문자열.
     */
	void VBDebugPrintAndPrintLogFile(VBDebug* _debug, const VBChar* _str, ...);
	
    /**
     @brief 로그를 디버그 패널과 로그 파일에 출력하고 프로세스를 종료합니다.
     @param _debug VBDebug.
     @param _isAbort 중단 플래그, VBTrue이면 중단, VBFalse이면 중단하지 않음.
     @param _str 포맷화된 문자열.
     */
	void VBDebugPrintAndPrintLogFileAbort(VBDebug* _debug, VBBool _isAbort, const VBChar* _str, ...);
	
#ifdef __cplusplus
}
#endif

#endif