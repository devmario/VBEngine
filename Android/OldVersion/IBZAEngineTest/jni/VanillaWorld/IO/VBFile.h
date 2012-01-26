/**
 @file IO/VBFile.h
 @brief VBEngine의 VBFile 구조체타입과 여러 함수들.
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

#ifndef __VBFile_H__
#define __VBFile_H__

#include "../VBConfig.h"
#include "../VBType.h"
#include "VBSystem.h"
#include "../Util/VBString.h"

#ifdef _VB_ANDROID_
#include "../VBEngineFileInfo.h"
#endif
#ifdef __cplusplus
extern "C" {
#endif
	
    /**
     @brief File read/write 관련 구조체 타입.
     */
	typedef struct VBFile VBFile;
	
    /**
     @enum 
     @brief VBFile의 모드 타입 열거
     
     VBFileMode_Read - 읽기만 가능
     VBFileMode_Write - 쓰기만 가능
     VBFileMode_ReadWrite - 읽기 쓰기 모두 가능
     
     */
	enum {
		VBFileMode_None			=	0x00,
		VBFileMode_Read			=	0x01,
		VBFileMode_Write		=	0x02,
		VBFileMode_ReadWrite	=	0x03
	};
	typedef VBUChar VBFileMode;
	
    /**
     @brief VBFile 구조체
     */
	struct VBFile {
        /*!
         파일 모드
         */
		VBFileMode mode;
		/*!
         시스템 endian
         */
        VBSystemEndian endian;
		/*!
         파일
         */
        void* file;
		/*!
         파일 사이즈
         */
        VBUShort size;
		/*!
         파일 offset
         */
        VBUShort offset;
	};
	
    /**
     @brief VBFile의 메모리를 할당합니다.
     @return _file 메모리가 할당된 VBFile을 반환합니다.
     */
	VBFile* VBFileAlloc(void);
	
    /**
     @brief VBFile를 초기화 합니다. 
     
     기존에 존대하는 file의 모드을 VBFileMode_Node와 endian을 VBSystemEndian_Node으로 초기화하고 \n
     파일의 사이즈와 Offset를 0으로 초기화합니다. 
     
     @param _file 메모리가 할당된 VBFile*
     @return 초기화된 VBFile* 를 반환합니다. 
     */
	VBFile* VBFileInit(VBFile* _file);
	
    /**
     @brief File을 열고 VBFile을 초기화합니다.  
     @param _file 메모리가 할당된 VBFile*
     @parma _path 지정된 파일 경로
     @param _mode VBFile 모드
     @return 초기화된 VBFile* 를 반환합니다. 
     */
	VBFile* VBFileInitWithOpen(VBFile* _file, VBString* _path, VBFileMode _mode);
	
    /**
     @brief VBFile의 메모리를 해제합니다.
     @return 메로리가 할당된 VBFile**
     */
	void VBFileFree(VBFile** _file);
	
    /**
     @brief VBFile을 엽니다. 
     @param _file 메모리가 할당된 VBFile*
     @param _path 지정된 파일 경로
     @param _mode VBFile 모드
     @see VBFileMode
     */
	void VBFileOpen(VBFile* _file, VBString* _path, VBFileMode _mode);
	
    /**
     @brief VBFile을 닫습니다.
     @param _file 메모리가 할당된 VBFile*
     */
	void VBFileClose(VBFile* _file);
	
    /**
     @brief VBFile의 Open여부를 구합니다. 
     @param _file 메모리가 할당된 VBFile*
     @return file이 열려있을 경우 VBTrue, 그렇지 않을 경우 VBFalse를 반환합니다. 
     */
	VBBool VBFileGetIsOpen(VBFile* _file);
	
    /**
     @brief VBFile의 모드를 구합니다. 
     @param _file 메모리가 할당된 VBFile*
     @return 설정되어 있는 VBFileMode를 반환합니다. 
     */
	VBFileMode VBFileGetMode(VBFile* _file);
	
    /**
     @brief VBFile에 Endian을 설정합니다. 
     @param _file 메모리가 할당된 VBFile*
     @param _endian 설정하려고하는 Endian
     @see VBSystemEndian
     */
	void VBFileSetEndian(VBFile* _file, VBSystemEndian _endian);
	
    /**
     @brief VBFile에 설정된 Endian을 구합니다. 
     @param _file 메모리가 할당된 VBFile*
     @return Endian을 반환합니다.
     */
	VBSystemEndian VBFileGetEndian(VBFile* _file);
	
    /**
     @brief VBFile에 offset을 설정합니다.
     @param _file 메모리가 할당된 VBFile*
     @param _pffset 설정하려는 Offset
     */
	void VBFileSetOffset(VBFile* _file, VBUShort _offset);
	
    /**
     @brief VBFile에 설정되어 있는 offset를 구합니다.
     @param _file 메모리가 할당된 VBFile*
     @return offset을 반환합니다. 
     */
	VBUShort VBFileGetOffset(VBFile* _file);
	
    /**
     @brief VBFile의 크기를 구합니다. 
     @param _file 메모리가 할당된 VBFile*
     @return 파일의 크기를 반환합니다.  
     */
	VBUShort VBFileGetSize(VBFile* _file);
	
    /**
     @brief VBFile에 씁니다. 
     
     VBFile의 mode가 VBFileMode_Write와 VBFileMode_ReadWrite여야 합니다.
     
     @param _file 메모리가 할당된 VBFile*
     @param _ptr VBFile에 write할 내용
     @param _size 항목의 크기
     @param _len 항목의 길이
     @return _w_size wirte한 데이터의 사이즈
     */
	VBUShort VBFileWrite(VBFile* _file, void* _ptr, VBUShort _size, VBUShort _len);
	
    /**
     @brief VBFile에서 읽습니다.
     
     VBFile의 mode가 VBFileMode_Read와 VBFileMode_ReadWrite여야 합니다. 
     
     @param _file 메모리가 할당된 VBFile*
     @param _ptr VBFile에서 read할 내용
     @param _size 항목의 크기
     @param _len 항목의 길이
     @return _r_size read한 데이터의 사이즈 
     */
	VBUShort VBFileRead(VBFile* _file, void* _ptr, VBUShort _size, VBUShort _len);
	
	/**
     @brief File Copy 할때 씁니다.
    
     @param _src source file -> 원시파일 VBFileMode_Read 로 파일을 엽니다.
     @param _des destination -> 목적파일 VBFileMode_ReadWrite 로 파일을 엽니다.
     */
	void VBFileCopy(VBString* _src, VBString* _des);
	
	/**
     @brief File 을 Memory에 Copy 할때 씁니다.

     @param _src source file -> 원시파일 VBFileMode_Read 로 파일을 엽니다.
     @param _buffer memorybuffer void* 를 넘겨주면  malloc 하고 file read한 data를 memory에 write하여  리턴합니다.
     */
	VBSize VBFileCopyToMemory(VBString* _src, void** _buffer);
	
    /**
     @brief VBFile에 1 VBByte를 씁니다.
     @param _file 메모리가 할당된 VBFile*
     @param _byte 쓰려고하는 1 VBByte
     @return wirte한 데이터의 사이즈
     */
	VBUShort VBFileWriteByte(VBFile* _file, VBByte _byte);
	
    /**
     @brief  VBFile에서 1 VBByte*를 읽습니다.
     @param _file 메모리가 할당된 VBFile*
     @param _byte 읽으려고 하는 1 VBByte*
     @return read한 데이터의 사이즈 
     */
	VBUShort VBFileReadByte(VBFile* _file, VBByte* _byte);
	
    /**
     @brief VBFile에 VBByte의 길이만큼 씁니다.
     @param _file 메모리가 할당된 VBFile*
     @param _len 쓰려고 하는 VBByte의 길이
     @return wirte한 데이터의 사이즈
     */
	VBUShort VBFileWriteBytes(VBFile* _file, VBByte* _bytes, VBUShort _len);
	
    /**
     @brief VBFile에서 VBByte*의 길이만큼 읽습니다.
     @param _file 메모리가 할당된 VBFile*
     @param _len 읽으려고 하는 VBByte*의 길이
     @return read한 데이터의 사이즈 
     */
	VBUShort VBFileReadBytes(VBFile* _file, VBByte* _bytes, VBUShort _len);
	
    /**
     @brief VBFile에 VBChar형 데이터를 씁니다. 
     @param _file 메모리가 할당된 VBFile*
     @param _char 쓰려고하는 VBChar형 데이터
     @return wirte한 데이터의 사이즈
     */
	VBUShort VBFileWriteChar(VBFile* _file, VBChar _char);
	
    /**
     @brief VBFile에서 VBChar형 데이터를 읽습니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 읽으려고 하는 VBChar형 데이터
     @return read한 데이터의 사이즈 
     */
	VBUShort VBFileReadChar(VBFile* _file, VBChar* _char);
	
    /**
     @brief VBFile에 VBUChar형 데이터를 씁니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 쓰려고하는 VBUChar형 데이터
     @return wirte한 데이터의 사이즈
     */
	VBUShort VBFileWriteUChar(VBFile* _file, VBUChar _char);
	
    /**
     @brief VBFile에서 VBUChar*형 데이터를 읽습니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 읽으려고 하는 VBUChar*형 데이터
     @return read한 데이터의 사이즈 
     */
	VBUShort VBFileReadUChar(VBFile* _file, VBUChar* _char);
	
    /**
     @brief VBFile에 VBShort형 데이터를 씁니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 쓰려고하는 VBShort형 데이터
     @return wirte한 데이터의 사이즈
     */
	VBUShort VBFileWriteShort(VBFile* _file, VBShort _short);
	
    /**
     @brief VBFile에서 VBShort*형 데이터를 읽습니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 읽으려고 하는 VBShort*형 데이터
     @return read한 데이터의 사이즈 
     */
	VBUShort VBFileReadShort(VBFile* _file, VBShort* _short);
	
    /**
     @brief VBFile에 VBUShort형 데이터를 씁니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 쓰려고하는 VBUShort형 데이터
     @return wirte한 데이터의 사이즈
     */
	VBUShort VBFileWriteUShort(VBFile* _file, VBUShort _short);
	
    /**
     @brief VBFile에서 VBUShort*형 데이터를 읽습니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 읽으려고 하는 VBUShort*형 데이터
     @return read한 데이터의 사이즈 
     */
	VBUShort VBFileReadUShort(VBFile* _file, VBUShort* _short);
	
    /**
     @brief VBFile에 VBLong형 데이터를 씁니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 쓰려고하는 VBLong형 데이터
     @return wirte한 데이터의 사이즈
     */
	VBUShort VBFileWriteLong(VBFile* _file, VBLong _long);
	
    /**
     @brief VBFile에서 VBLong*형 데이터를 읽습니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 읽으려고 하는 VBLong*형 데이터
     @return read한 데이터의 사이즈 
     */
	VBUShort VBFileReadLong(VBFile* _file, VBLong* _long);
	
    /**
     @brief VBFile에 VBULong형 데이터를 씁니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 쓰려고하는 VBULong형 데이터
     @return wirte한 데이터의 사이즈
     */
	VBUShort VBFileWriteULong(VBFile* _file, VBULong _long);
	
    /**
     @brief VBFile에서 VBULong*형 데이터를 읽습니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 읽으려고 하는 VBULong*형 데이터
     @return read한 데이터의 사이즈 
     */
	VBUShort VBFileReadULong(VBFile* _file, VBULong* _long);
	
    /**
     @brief VBFile에 VBLongLong형 데이터를 씁니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 쓰려고하는 VBLongLong형 데이터
     @return wirte한 데이터의 사이즈
     */
	VBUShort VBFileWriteLongLong(VBFile* _file, VBLongLong _longlong);
	
    /**
     @brief VBFile에서 VBLongLong*형 데이터를 읽습니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 읽으려고 하는 VBLongLong*형 데이터
     @return read한 데이터의 사이즈 
     */
	VBUShort VBFileReadLongLong(VBFile* _file, VBLongLong* _longlong);
	
    /**
     @brief VBFile에 VBULongLong형 데이터를 씁니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 쓰려고하는 VBULongLong형 데이터
     @return wirte한 데이터의 사이즈
     */
	VBUShort VBFileWriteULongLong(VBFile* _file, VBULongLong _longlong);
	
    /**
     @brief VBFile에서 VBULongLong*형 데이터를 읽습니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 읽으려고 하는 VBULongLong*형 데이터
     @return read한 데이터의 사이즈 
     */
	VBUShort VBFileReadULongLong(VBFile* _file, VBULongLong* _longlong);
    
    /**
     @brief VBFile에서 VBFloat*형 데이터를 읽습니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 읽으려고 하는 VBFloat*형 데이터
     @return read한 데이터의 사이즈 
     */
    VBUShort VBFileReadFloat(VBFile* _file, VBFloat* _float);
	
    /**
     @brief VBFile에서 VBDouble*형 데이터를 읽습니다.
     @param _file 메모리가 할당된 VBFile*
     @param _char 읽으려고 하는 VBDouble*형 데이터
     @return read한 데이터의 사이즈 
     */
    VBUShort VBFileReadDouble(VBFile* _file, VBDouble* _float);

#ifdef __cplusplus
}
#endif

#endif