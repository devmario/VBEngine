/**
 @file VBType.h
 @brief VBEngine의 VBType 구조체타입과 여러 함수들.
 @author 
 <table>
 <tr><th>Developer</th><th>Role</th><th>Email</th></tr>
 <tr><td>장원희</td><td>Main Programmer</td><td>mario@vanillabreeze.com</td></tr>
 <tr><td>김희동</td><td>Programmer</td><td>welivehere@vanillabreeze.com</td></tr>
 <tr><td>박두철</td><td>Programmer</td><td>encjf@vanillabreeze.com</td></tr>
 </table>
 @version 1.0
 @section Lisence
 Copyright 2011 vanilla breeze. All rights reserved.
 */

#ifndef __VBType_H__
#define __VBType_H__

#include "VBConfig.h"
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
    
	/**
     @brief VBEngine은 다양한 환경안에서 작동시키기 위해 여러 데이터 타입을 명시하고 있습니다.\n
     */
	//!NULL
#define VBNull NULL
	
	//!true
#define VBFalse false
	//!false
#define VBTrue true
	//!bool형 타입
	/*!
	 1바이트 bool형 타입
	 */
	typedef bool VBBool;
	
	typedef size_t VBSize;
	
	//!byte형 타입
	/*!
	 1바이트 byte형 타입
	 */
	typedef unsigned char VBByte;
	
	//!signed char형 타입
	/*!
	 1바이트 signed char형 타입
	 */
	typedef char VBChar;
	
	//!unsigned char형 타입
	/*!
	 1바이트 unsigned char형 타입
	 */
	typedef unsigned char VBUChar;
	
	//!signed short형 타입
	/*!
	 2바이트 signed short형 타입
	 */
	typedef short VBShort;
	
	//!unsigned short형 타입
	/*!
	 2바이트 unsigned short형 타입
	 */
	typedef unsigned short VBUShort;
	
	//!signed long형 타입
	/*!
	 4바이트 signed long형 타입
	 */
	typedef long VBLong;
	
	//!unsigned long형 타입
	/*!
	 4바이트 unsigned long형 타입
	 */
	typedef unsigned long VBULong;
	
	//!signed long long형 타입
	/*!
	 8바이트 signed long long형 타입
	 */
	typedef long long VBLongLong;
	
	//!unsigned long long형 타입
	/*!
	 8바이트 unsigned long long형 타입
	 */
	typedef unsigned long long VBULongLong;
	
	//!float형 타입
	/*!
	 4바이트 float형 타입
	 */
	typedef float VBFloat;
    
	
	//!double형 타입
	/*!
	 8바이트 double형 타입
	 */
	typedef double VBDouble;
	
#ifdef __cplusplus
}
#endif

#endif