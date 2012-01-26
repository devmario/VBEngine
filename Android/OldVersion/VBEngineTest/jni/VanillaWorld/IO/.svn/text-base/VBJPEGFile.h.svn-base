/**
 @file IO/VBJPEGFile.h
 @brief VBEngine의 VBJPEGFile 구조체타입과 여러 함수들.
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

#ifndef __JPEGFile_H__
#define __JPEGFile_H__

#include "../VBType.h"
#include "../Core/VBString.h"
#include "../Core/VBColor.h"

#ifdef __cplusplus
extern "C" {
#endif
	
    /**
     @brief VBJPEGFile 관련 구조체 타입
     */
	typedef struct VBJPEGFile VBJPEGFile;
	
    /**
     @brief VBJPEGFile 관련 구조체
     */
	struct VBJPEGFile {
        /*!
         JPEG파일 로딩 확인 여부
         */
		VBBool loaded;
		/*!
         JPEG파일 저장 경로
         */
        VBString* path;
		/*!
         Color 타입
         @see VBColorType
         */
        VBColorType color_type;
		/*!
         Color bit
         */
        VBUChar color_bit;
		/*!
         JPEG파일의 넓이
         */
        VBULong width;
		/*!
         JPEG파일의 높이
         */
        VBULong height;
		/*!
         JPEG파일 사이즈
         */
        VBULong data_size;
		/*!
         JPEG파일 정보
         */
        void* data;
	};
	
    /**
     @brief VBJPEGFile의 메모리를 할당합니다.
     @return _jpeg 메로리가 할당된 VBJPEGFile을 반환합니다.
     */
	VBJPEGFile* VBJPEGFileAlloc(void);
	
    /**
     @brief VBJPEGFile를 초기화합니다.
     @param _jpeg 메모리가 할당된 VBJPEGFile*
     @return 초기화된 VBJPEGFile을 반환합니다.
     */
	VBJPEGFile* VBJPEGFileInit(VBJPEGFile* _jpeg);
	
    /**
     @brief VBJPEGFile을 파일경로와 함께 초기화합니다. 
     @param _jpeg 메모리가 할당된 VBJPEGFile*
     @param _path 파일 경로     
     @return 파일경로와 함께 초기화된 VBJPEGFile을 반환합니다. 
     */
	VBJPEGFile* VBJPEGFileInitWithFilePath(VBJPEGFile* _jpeg, VBString* _path);
	
    /**
     @brief VBJPEGFile의 메모리를 해제합니다.
     @param _jpeg 메모리가 할당된 VBJPEGFile**
     */
	void VBJPEGFileFree(VBJPEGFile** _jpeg);
	
    /**
     @brief VBJPEGFile을 로드합니다. 
     @param _jpeg 메모리가 할당된 VBJPEGFile*
     @param _path 파일 경로
     */
	void VBJPEGFileLoad(VBJPEGFile* _jpeg, VBString* _path);
	
    /**
     @brief VBJPEGFile을 unload 시킵니다. 
     @param _jpeg 메모리가 할당된 VBJPEGFile*
     */
	void VBJPEGFileUnload(VBJPEGFile* _jpeg);
	
    /**
     @brief VBJPEGFile의 로딩 여부를 구합니다.
     @param _jpeg 메모리가 할당된 VBJPEGFile*
     @return VBJPEGFile의 로딩 여부를 반환합니다.     
     */
	VBBool VBJPEGFileGetIsLoaded(VBJPEGFile* _jpeg);
	
    /**
     @brief VBJPEGFile의 파일 경로를 구합니다.
     @param _jpeg 메모리가 할당된 VBJPEGFile*
     @return VBJPEGFile의 파일 경로를 반환합니다.
     */
	VBString* VBJPEGFileGetPath(VBJPEGFile* _jpeg);
	
    /**
     @brief VBJPEGFile의 color type을 구합니다.
     @param _jpeg 메모리가 할당된 VBJPEGFile*
     @return VBJPEGFile의 color type를 반환합니다.
     */
	VBColorType VBJPEGFileGetColorType(VBJPEGFile* _jpeg);
	
    /**
     @brief VBJPEGFile의 color bit를 구합니다.
     @param _jpeg 메모리가 할당된 VBJPEGFile*
     @return VBJPEGFile의 color bit를 반환합니다.
     */
	VBUChar VBJPEGFileGetColorBit(VBJPEGFile* _jpeg);
	
    /**
     @brief VBJPEGFile의 넓이를 구합니다.
     @param _jpeg 메모리가 할당된 VBJPEGFile*
     @return VBJPEGFile의 넓이를 반환합니다.
     */
	VBUShort VBJPEGFileGetWidth(VBJPEGFile* _jpeg);
	
    /**
     @brief VBJPEGFile의 높이를 구합니다.
     @param _jpeg 메모리가 할당된 VBJPEGFile*
     @return VBJPEGFile의 높이를 반환합니다.
     */
	VBUShort VBJPEGFileGetHeight(VBJPEGFile* _jpeg);
	
    /**
     @brief VBJPEGFile의 데이터 사이즈를 구합니다. 
     @param _jpeg 메모리가 할당된 VBJPEGFile*
     @return VBJPEGFile의 데이터 사이즈를 반환합니다.
     */
	VBULong VBJPEGFileGetDataSize(VBJPEGFile* _jpeg);
	
    /**
     @brief VBJPEGFile의 데이터를 구합니다.
     @param _jpeg 메모리가 할당된 VBJPEGFile*
     @return VBJPEGFile의 데이터를 반환합니다.
     */
	void* VBJPEGFileGetData(VBJPEGFile* _jpeg);
	
#ifdef __cplusplus
}
#endif

#endif