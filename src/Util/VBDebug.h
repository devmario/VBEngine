/**
 @file Util/VBDebug.h
 
 @brief 디버깅 유틸 구조체와 이를 다룰수 있는 함수들
 
 VBDebug는 디버깅 관련 중단점 및 로그출력, 로그파일출력을 위해 만들어진 소스 입니다.\n
 VBDebug를 이용하여 로그출력, 파일에 로그 쓰기, 중단점 설정을 해주세요.
 
 @author
 <table>
 <tr><th>Developer</th><th>Role</th><th>Email</th><th>Mobile Phone</th></tr>
 <tr><td>장원희</td><td>Main Programmer</td><td>mario@vanillabreeze.com</td><td>82-(0)10-4443-0711</td></tr>
 <tr><td>김희동</td><td>Programmer</td><td>welivehere@vanillabreeze.com</td><td>82-(0)10-2624-6873</td></tr>
 <tr><td>박두철</td><td>Programmer</td><td>encjf@vanillabreeze.com</td><td>82-(0)10-6825-3221</td></tr>
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
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBDebug 메모리 할당</i> \n\n
     VBDebug *debug = VBDebugAlloc();
     </td>
     </tr>
	 </table>
     
     @return 메모리 할당된 VBDebug.
     */
	VBDebug* VBDebugAlloc(void);
	
    /**
     @brief VBDebug를 초기화합니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBDebug 메모리 할당후 초기화</i> \n\n
     VBString *logFilePath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/log.txt", VBEngineGetDocumentPath());\n
     VBDebug *debug = VBDebugInitWithLogFilePath(VBDebugAlloc(), VBStringGetCString(logFilePath));\n
     VBStringFree(&logFilePath);
     </td>
     </tr>
	 </table>
     
     @param _debug VBDebug.
     @param _log_file_path 로그 파일의 경로.(VBDebugLog는 엔진의 예약된 경로이므로 사용하지마세요.)
     @return 초기화된 VBDebug.
     */
	VBDebug* VBDebugInitWithLogFilePath(VBDebug* _debug, const VBChar* _log_file_path);
	
    /**
     @brief VBDebug를 메모리 해제합니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>VBDebug 메모리 할당후 초기화하고 메모리 해제</i> \n\n
     VBString *logFilePath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/log.txt", VBEngineGetDocumentPath());\n
     VBDebug *debug = VBDebugInitWithLogFilePath(VBDebugAlloc(), VBStringGetCString(logFilePath));\n
     VBStringFree(&logFilePath);\n
     \n
     VBDebugFree(&debug);
     </td>
     </tr>
	 </table>
     
     @param _debug VBDebug.
     */
	void VBDebugFree(VBDebug** _debug);
	
    /**
     @brief 프로그램을 중단합니다.\n
     또한 이함수는 VBDebug(함수의 첫번째 인자)가 VBNull이어도 실행됩니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>프로그램을 중단</i> \n\n
     VBString *logFilePath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/log.txt", VBEngineGetDocumentPath());\n
     VBDebug *debug = VBDebugInitWithLogFilePath(VBDebugAlloc(), VBStringGetCString(logFilePath));\n
     VBStringFree(&logFilePath);\n
     \n
     VBDebugAbort(debug, VBTrue);\n
     \n
     VBDebugFree(&debug);
     </td>
     </tr>
	 </table>
     
     @param _debug VBDebug.
     @param _isAbort 중단 플래그, VBTrue이면 중단, VBFalse이면 중단하지 않음.
     */
	void VBDebugAbort(VBDebug* _debug, VBBool _isAbort);
	
    /**
     @brief IDE의 로그패널에 로그를 출력합니다.\n
     또한 이함수는 VBDebug(함수의 첫번째 인자)가 VBNull이어도 실행됩니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>IDE의 로그패널에 로그 "hello world!"를 출력</i> \n\n
     VBString *logFilePath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/log.txt", VBEngineGetDocumentPath());\n
     VBDebug *debug = VBDebugInitWithLogFilePath(VBDebugAlloc(), VBStringGetCString(logFilePath));\n
     VBStringFree(&logFilePath);\n
     \n
     VBDebugPrint(debug, "%s world!", "hello");\n
     \n
     VBDebugFree(&debug);
     </td>
     </tr>
	 </table>
     
     @param _debug VBDebug.
     @param _str 포맷화된 문자열.
     */
	void VBDebugPrint(VBDebug* _debug, const VBChar* _str, ...);
	
    /**
     @brief 로그를 출력하고 프로그램을 중단합니다.\n
     또한 이함수는 VBDebug(함수의 첫번째 인자)가 VBNull이어도 실행됩니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>IDE의 로그패널에 로그 "hello world!"를 출력하고 프로그램 중단</i> \n\n
     VBString *logFilePath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/log.txt", VBEngineGetDocumentPath());\n
     VBDebug *debug = VBDebugInitWithLogFilePath(VBDebugAlloc(), VBStringGetCString(logFilePath));\n
     VBStringFree(&logFilePath);\n
     \n
     VBDebugPrintAbort(debug, VBTrue, "%s world!", "hello");\n
     \n
     VBDebugFree(&debug);
     </td>
     </tr>
	 </table>
     
     @param _debug VBDebug.
     @param _isAbort 중단 플래그, VBTrue이면 중단, VBFalse이면 중단하지 않음.
     @param _str 포맷화된 문자열.
     */
	void VBDebugPrintAbort(VBDebug* _debug, VBBool _isAbort, const VBChar* _str, ...);
	
    /**
     @brief 로그 파일의 내용을 초기화 합니다.\n
     로그파일 관련 디버거 함수 사용시 이 함수로 파일내용을 초기화 하지 않으면 로그파일스트림의 마지막에 로그들이 지속적으로 기록됩니다.\n
     디버거가 종료하고 같은 로그파일로 디버거를 다시 초기화 하였을때 로그파일을 초기화 하고 싶으면 이함수를 호출하세요.\n
     이함수는 VBNull포인터로 할당된 VBDebug에는 사용할 수 없습니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>로그 파일(log.txt)의 내용을 초기화</i> \n\n
     VBString *logFilePath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/log.txt", VBEngineGetDocumentPath());\n
     VBDebug *debug = VBDebugInitWithLogFilePath(VBDebugAlloc(), VBStringGetCString(logFilePath));\n
     VBStringFree(&logFilePath);\n
     \n
     VBDebugPrintLogFile(debug, "%s world!", "hello");\n
     VBDebugLogFileClear(debug);\n
     \n
     VBDebugFree(&debug);
     </td>
     </tr>
	 </table>
     
     @param _debug VBDebug.
     */
	void VBDebugLogFileClear(VBDebug* _debug);
	
    /**
     @brief 로그 파일에 로그를 출력합니다.\n
     이함수는 VBNull포인터로 할당된 VBDebug에는 사용할 수 없습니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>로그 파일(log.txt)스트림 마지막에 "hello world!"을 기록.</i> \n\n
     VBString *logFilePath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/log.txt", VBEngineGetDocumentPath());\n
     VBDebug *debug = VBDebugInitWithLogFilePath(VBDebugAlloc(), VBStringGetCString(logFilePath));\n
     VBStringFree(&logFilePath);\n
     \n
     VBDebugPrintLogFile(debug, "%s world!", "hello");\n
     \n
     VBDebugFree(&debug);
     </td>
     </tr>
	 </table>
     
     @param _debug VBDebug.
     @param _str 포맷화된 문자열.
     */
	void VBDebugPrintLogFile(VBDebug* _debug, const VBChar* _str, ...);
	
    /**
     @brief 로그 파일에 로그를 출력하고 프로세스를 중단합니다.\n
     이함수는 VBNull포인터로 할당된 VBDebug에는 사용할 수 없습니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>로그 파일(log.txt)스트림 마지막에 "hello world!"를 기록하고 프로그램 중단.</i> \n\n
     VBString *logFilePath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/log.txt", VBEngineGetDocumentPath());\n
     VBDebug *debug = VBDebugInitWithLogFilePath(VBDebugAlloc(), VBStringGetCString(logFilePath));\n
     VBStringFree(&logFilePath);\n
     \n
     VBDebugPrintLogFileAbort(debug, VBTrue, "%s world!", "hello");\n
     \n
     VBDebugFree(&debug);
     </td>
     </tr>
	 </table>
     
     @param _debug VBDebug.
     @param _isAbort 중단 플래그, VBTrue이면 중단, VBFalse이면 중단하지 않음.
     @param _str 포맷화된 문자열.
     */
	void VBDebugPrintLogFileAbort(VBDebug* _debug, VBBool _isAbort, const VBChar* _str, ...);
	
    /**
     @brief 로그를 디버그 패널에 출력하고 로그 파일에 출력합니다.\n
     이함수는 VBNull포인터로 할당된 VBDebug에는 사용할 수 없습니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>로그 파일(log.txt)스트림 마지막에 "hello world!"를 기록하고 로그패널에 "hellow world!"를 출력.</i> \n\n
     VBString *logFilePath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/log.txt", VBEngineGetDocumentPath());\n
     VBDebug *debug = VBDebugInitWithLogFilePath(VBDebugAlloc(), VBStringGetCString(logFilePath));\n
     VBStringFree(&logFilePath);\n
     \n
     VBDebugPrintAndPrintLogFile(debug, "%s world!", "hello");\n
     \n
     VBDebugFree(&debug);
     </td>
     </tr>
	 </table>
     
     @param _debug VBDebug.
     @param _str 포맷화된 문자열.
     */
	void VBDebugPrintAndPrintLogFile(VBDebug* _debug, const VBChar* _str, ...);
	
    /**
     @brief 로그를 디버그 패널과 로그 파일에 출력하고 프로세스를 중단합니다.\n
     이함수는 VBNull포인터로 할당된 VBDebug에는 사용할 수 없습니다.
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>로그 파일(log.txt)스트림 마지막에 "hello world!"를 기록하고 로그패널에 "hellow world!"를 출력하며 프로그램을 중단.</i> \n\n
     VBString *logFilePath = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/log.txt", VBEngineGetDocumentPath());\n
     VBDebug *debug = VBDebugInitWithLogFilePath(VBDebugAlloc(), VBStringGetCString(logFilePath));\n
     VBStringFree(&logFilePath);\n
     \n
     VBDebugPrintAndPrintLogFileAbort(debug, VBTrue, "%s world!", "hello");\n
     \n
     VBDebugFree(&debug);
     </td>
     </tr>
	 </table>
     
     @param _debug VBDebug.
     @param _isAbort 중단 플래그, VBTrue이면 중단, VBFalse이면 중단하지 않음.
     @param _str 포맷화된 문자열.
     */
	void VBDebugPrintAndPrintLogFileAbort(VBDebug* _debug, VBBool _isAbort, const VBChar* _str, ...);
    
    /**
     @brief 로그를 디버그패널에 출력.\n
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>로그패널에 "hellow world!"를 출력.</i> \n\n
     VBLog("hellow %s!", "world");
     </td>
     </tr>
	 </table>
     
     @param _str 포맷화된 문자열.
     */
#define VBLog(_str, ...) VBDebugPrint(VBNull, _str, __VA_ARGS__)
    
    /**
     @brief 로그를 디버그패널에 출력하고 프로그램중단.\n
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>로그패널에 "hellow world!"를 출력하고 프로그램중단.</i> \n\n
     VBLogAbort(VBTrue, "hellow %s!", "world");
     </td>
     </tr>
	 </table>
     
     @param _isAbort 중단 플래그, VBTrue이면 중단, VBFalse이면 중단하지 않음.
     @param _str 포맷화된 문자열.
     */
#define VBLogAbort(_isAbort, _str, ...) VBDebugPrintAbort(VBNull, _isAbort, _str, __VA_ARGS__)
    
    /**
     @brief 프로그램중단.\n
     
     <b>Example</b>
	 <table bgcolor="#DDDDDD">
     <tr>
     <td>
     <i>프로그램중단.</i> \n\n
     VBAbort(VBTrue);
     </td>
     </tr>
	 </table>
     
     @param _isAbort 중단 플래그, VBTrue이면 중단, VBFalse이면 중단하지 않음.
     */
#define VBAbort(_isAbort) VBDebugAbort(VBNull, _isAbort)
	
#ifdef __cplusplus
}
#endif

#endif