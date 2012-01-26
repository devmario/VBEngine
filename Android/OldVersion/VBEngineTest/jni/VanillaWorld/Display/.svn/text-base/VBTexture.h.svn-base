/**
 @file Display/VBTexture.h
 @brief VBTexture 타입들의 상수값 정의
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

#ifndef __VBTexture_H__
#define __VBTexture_H__

#include "../VBType.h"
#include "../Core/VBString.h"
#include "VBImage.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 @brief VBTexture의 구조체 타입.
	 */
	typedef struct VBTexture VBTexture;

	/**
	 @brief VBTexture의 구조체.
	 */	
	struct VBTexture {
		/*!
		 color 타입
		 */
		VBColorType color_type;
		/*!
		 texture 인덱스
		 */
		VBUShort tid;
		/*!
		 넓이
		 */
		VBULong width;
		/*!
		 길이
		 */
		VBULong height;
	};
	
	/**
	 @brief VBTexture의 메모리를 할당합니다.
	 @return _tex 메모리 할당된 VBTexture를 반환합니다.
	 */
	VBTexture* VBTextureAlloc(void);

	/**
	 @brief VBTexture를 초기화 합니다.
	 @param _tex VBTexture.
	 @return _tex 초기화된 VBTexture를 반환합니다.
	 */
	VBTexture* VBTextureInit(VBTexture* _tex);

	/**
	 @brief VBTexture를 VBTexture로 사용될 이미지를 로드하고 초기화 합니다.
	 @param _tex VBTexture.
	 @param _img
	 */
	VBTexture* VBTextureInitAndLoadWithImage(VBTexture* _tex, VBImage* _img);

	/**
	 @brief VBTexture를 VBTexture로 사용될 이미지의 경로를 추가하고 초기화 합니다.
	 @param _tex VBTexture.
	 @param _path 파일이 저장되어 있는 경로.
	 */
	VBTexture* VBTextureInitAndLoadWithImagePath(VBTexture* _tex, VBString* _path);
	
	/**
	 @brief VBTexture의 메모리를 해제합니다.
	 @param _tex VBTexture.
	 */
	void VBTextureFree(VBTexture** _tex);
	
	/**
	 @brief VBTexture로 사용될 이미지를 load합니다. 
	 
	 Texture의 가로와 세로는 32pixel이상이어야 합니다.\n
	 Texture의 가로와 세로 길이는 2의 승수여야 합니다. \n
	 Texture로 사용될 이미지의 비트수는 8비트입니다. (현재 8비트만 지원)
	 
	 @param _tex VBTexture.
	 @param _img 사용될 Image.
	 */
	void VBTextureLoadImage(VBTexture* _tex, VBImage* _img);
	
	/**
	 @brief VBTexture로 사용될 이미지를 경로를 지정해 load합니다.
	 @param _tex VBTexture.
	 @param _path 파일이 저장되어 있는 경로.
	 */
	void VBTextureLoadImagePath(VBTexture* _tex, VBString* _path);
	
	/**
	 @brief 로드되어 있던 이미지를 Unload합니다. 
	 @param _tex VBTexture.
	 */
	void VBTextureUnload(VBTexture* _tex);
	
	/**
	 @brief VBTexture의 인덱스를 반환합니다. 
	 @param _tex VBTexture.
     @return 반환된 VBTexture의 인덱스.
	 */
	VBUShort VBTextureGetID(VBTexture* _tex);
	
	/**
	 @brief VBTexture의 너비를 반환합니다.
	 @param _tex VBTexture.
     @return 반환된 VBTexture의 넓이.
	 */
	VBULong VBTextureGetWidth(VBTexture* _tex);
	
	/**
	 @brief VBTexture의 높이를 반환합니다.
	 @param _tex VBTexture.
     @return 반환된 VBTexture의 높이.
	 */
	VBULong VBTextureGetHeight(VBTexture* _tex);
	
	/**
	 @brief VBtexture의 color타입을 반환합니다. 
	 @param _tex VBTexture.
     @return 반환된 VBTexture의  color타입.
	 */
	VBColorType VBTextureGetColorType(VBTexture* _tex);
	
#ifdef __cplusplus
}
#endif

#endif