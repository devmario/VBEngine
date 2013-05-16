/**
 @file IO/VBSystem.h
 @brief VBEngine의 VBSystem 구조체타입과 여러 함수들.
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

#ifndef __VBSystem_H__
#define __VBSystem_H__

#include "../VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @brief 시스템의 엔디안 타입들의 정의.
     */
	enum {
        /**
         정의되지 않은 엔디안 타입
         */
		VBSystemEndian_None		=	0x00,
        /**
         리틀 엔디안
         */
		VBSystemEndian_Little	=	0x01,
        /**
         빅 엔디안
         */
		VBSystemEndian_Big		=	0x02
	};
    /**
     @brief 시스템 엔디안 타입 정의.
     */
	typedef VBUChar VBSystemEndian;
	
    /**
     @brief 시스템의 엔디안 정보를 반환합니다.
     @return 시스템의 엔디안 정보.
     */
	VBSystemEndian VBSystemGetEndian(void);
	
    /**
     @brief 주어진 파라메터의 엔디안을 변환합니다.
     @param _ptr 엔디안을 변환할 메모리 포인터.
     @param _byte_size 메모리 포인터의 사이즈.
     */
	void VBSystemEndianSwap(void* _ptr, VBUShort _byte_size);
	
    /**
     @brief 메모리를 주어진 크기만큼 할당합니다.
     @param _size 타입의 사이즈
     @param _count 타입의 길이
     @return 할당된 메모리
     */
	void* VBSystemCalloc(VBSize _size, VBSize _count);
	
    /**
     @brief 메모리를 주어진 크기만큼 할당합니다.
     @param _size 할당할 메모리의 크기
     @return 할당된 메모리
     */
	void* VBSystemMalloc(VBSize _size);
	
    /**
     @brief 할당된 메모리를 새로운 크기로 재할당 합니다.
     @param _re_ptr 재할당할 메모리의 포인터.
     @param _size 재할당할 크기
     @return 할당된 메모리
     */
	void* VBSystemRealloc(void* _re_ptr, VBSize _size);
	
    void* VBSystemMemorySet(void* _ptr, VBLong _hex, VBSize _set_size);
    VBLong VBSystemUSleep(VBULong _m_sec);
    /**
     @brief 대상 포인터에 원본 포인터의 데이터를 복사합니다.
     @param _dest_ptr 대상 포인터
     @param _src_ptr 원본 포인터
     @param _copy_size 원본 포인터로부터 복사할 크기
     @return 대상 포인터
     */
    void* VBSystemMemoryCopy(void* _dest_ptr, const void* _src_ptr, VBSize _copy_size);
    
    /**
     @brief 포인터의 메모리를 해제합니다.
     @param _ptr 메모리를 해제할 포인터
     */
	void VBSystemFree(void* _ptr);
	
#ifdef __cplusplus
}
#endif

#endif