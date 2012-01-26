/**
 @file IO/VBPNGFile.h
 @brief VBEngine의 VBPNGFile 구조체타입과 여러 함수들.
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

#ifndef __VBPNGFile_H__
#define __VBPNGFile_H__

#include "../VBType.h"
#include "../Core/VBString.h"
#include "../Core/VBColor.h"

#ifdef __cplusplus
extern "C" {
#endif
	
    /**
     @brief VBPNGFile 관련 구조체 타입 
     */
	typedef struct VBPNGFile VBPNGFile;
	
    /**
     @brief VBPNGFile 관련 구조체 
     */
	struct VBPNGFile {
        /*!
         로딩 여부
         */
		VBBool loaded;
		/*!
         파일 위치
         */
        VBString* path;
		/*!
         컬러 타입
         */
        VBColorType color_type;
		/*!
         color_bit
         */
        VBUChar color_bit;
		/*!
         넓이
         */
        VBULong width;
		/*!
         길이
         */
        VBULong height;
		/*!
         데이터 사이즈
         */
        VBULong data_size;
		/*!
         데이터
         */
        void* data;
	};
	
    /**
     @brief VBPNGFile의 메모리를 할당합니다.
     @return 메모리가 할당된 VBPNGFile를 반환합니다. 
     */
	VBPNGFile* VBPNGFileAlloc(void);
	
    /** 
     @brief VBPNGFile의 메모리를 초기화 합니다. 
     @param _png 메모리가 할당된 VBPNGFile*
     @return 메모리가 초기화된 VBPNGFile를 반환합니다. 
     */
	VBPNGFile* VBPNGFileInit(VBPNGFile* _png);
	
    /**
     @brief VBPNGFile의 메모리를 파일 경로와 함께 초기화 합니다. 
     @param _png 메모리가 할당된 VBPNGFile*
     @param _path VBPNGFile의 파일 경로
     @return 
     */
	VBPNGFile* VBPNGFileInitWithFilePath(VBPNGFile* _png, VBString* _path);
	
    /**
     @brief VBPNGFile의 메모리를 해제합니다. 
     @param _png 메모리가 할당된 VBPNGFile**
     */
	void VBPNGFileFree(VBPNGFile** _png);
	
    /**
     @brief VBPNGFile을 로드합니다.
     @param _png 메모리가 할당된 VBPNGFile*
     */
	void VBPNGFileLoad(VBPNGFile* _png, VBString* _path);
	
    /**
     @brief VBPNGFile을 unload합니다. 
     @param _png 메모리가 할당된 VBPNGFile*
     */
	void VBPNGFileUnload(VBPNGFile* _png);
	
    /**
     @brief VBPNGFile의 로딩 여부를 구합니다.
     @param _png 메모리가 할당된 VBPNGFile*
     @return VBPNGFile이 로드됐을 경우 VBTrue, 그렇지 않을 경우 VGFalse를 반환합니다. 
     */
	VBBool VBPNGFilgGetIsLoaded(VBPNGFile* _png);
	
    /**
     @brief VBPNGFile의 파일 경로를 구합니다. 
     @param _png 메모리가 할당된 VBPNGFile*
     @return VBPNGFile의 파일 경로를 반환합니다. 
     */
	VBString* VBPNGFileGetPath(VBPNGFile* _png);
	
    /**
     @brief VBPNGFile의 color type을 구합니다.
     @param _png 메모리가 할당된 VBPNGFile*
     @return VBPNGFile의 color type을 반환합니다. 
     @see VBColorType
     */
	VBColorType VBPNGFileGetColorType(VBPNGFile* _png);
	
    /**
     @brief VBPNGFile의 color bit을 구합니다.
     @param _png 메모리가 할당된 VBPNGFile*
     @return VBPNGFile의 color bit을 반환합니다.
     */
	VBUChar VBPNGFileGetColorBit(VBPNGFile* _png);
	
    /**
     @brief VBPNGFile의 넓이를 구합니다.
     @param _png 메모리가 할당된 VBPNGFile*
     @return VBPNGFile의 넓이를 반환합니다. 
     */
	VBUShort VBPNGFileGetWidth(VBPNGFile* _png);
	
    /**
     @brief VBPNGFile의 높이를 구합니다.
     @param _png 메모리가 할당된 VBPNGFile*
     @return VBPNGFile의 높이를 반환합니다.
     */
	VBUShort VBPNGFileGetHeight(VBPNGFile* _png);
	
    /**
     @brief VBPNGFile의 데이터 사이즈를 구합니다.
     @param _png 메모리가 할당된 VBPNGFile*
     @return VBPNGFile의 데이터 사이즈를 반환합니다.
     */
	VBULong VBPNGFileGetDataSize(VBPNGFile* _png);
	
    /**
     @brief VBPNGFile의 데이터를 구합니다.
     @param _png 메모리가 할당된 VBPNGFile*
     @return VBPNGFile의 데이터를 반환합니다. 
     */
	void* VBPNGFileGetData(VBPNGFile* _png);
	
#ifdef __cplusplus
}
#endif

#endif