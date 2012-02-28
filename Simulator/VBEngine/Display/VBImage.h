/**
 @file Display/VBImage.h
 @brief VBImage 타입들의 상수값 정의
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

#ifndef __VBImage_H__
#define __VBImage_H__

#include "../VBType.h"
#include "../Util/VBString.h"
#include "../Core/Color/VBColor.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 VBImage관련 구조체 타입.
	 */
	typedef struct VBImage VBImage;
	
	/**
	 VBImage관련 구조체.
	 
	 VBImage의 타입은 PNG와 JPEG(JPG)를 지원합니다.\n
	 파일 확장자에 따라 각각의 데이터(color 타입, color bit, 너비, 높이)를 구합니다.
	 */
	struct VBImage {
		/*!
		 Color Type(G, GA, RGB, RGBA)
		 */
		VBColorType color_type;
		/*!
		 VBImage의 bit
		 */
		VBUChar color_bit;
		/*!
		 VBImage의 너비
		 */
		VBULong width;
		/*!
		 VBImage의 길이
		 */
		VBULong height;
		/*!
		 VBImage의 데이터
		 */
		void* data;
        
        VBBool is_loaded;
	};
	
	/**
	 @brief VBImage의 메모리를 할당합니다.
	 @return _img 메모리가 할당된 VBImage를 반환합니다. 
	 */
	VBImage* VBImageAlloc(void);
		
	/**
	 @brief VBImage를 초기화 합니다.
     @param _img 메모리가 할당된 VBImage.
	 @return _img 초기화된 VBImage를 반환합니다.
	 */
	VBImage* VBImageInit(VBImage* _img);
	
	/**
	 @brief VBImage를 데이터(color 타입, color bit, 넓이, 길이, 크기)값을 대입하여 초기화 합니다.
	 @param _img VBImage.
	 @param _color_type color 타입.
	 @param _color_bit color bit.
	 @param _width 너비
	 @param _height 높이.
	 @param _data 사이즈.
     @return _img 초기화된 VBImage.
	 */
	VBImage* VBImageInitWithData(VBImage* _img, VBColorType _color_type, VBUChar _color_bit, VBULong _width, VBULong _height, void* _data);
	
	/**
	 @brief VBImage를 파일 위치와 함께 초기화 합니다.
	 @param _img VBImage.
	 @param _path 파일 위치.
     @return _img 초기화된 VBImage.
	 */
	VBImage* VBImageInitWithPath(VBImage* _img, VBString* _path);
	
	/**
	 @brief VBImage를 주어진 size로 초기화 시키고 생성된 data를 0으로 초기화합니다.
	 @param _img VBImage.
	 @param _color_type color 타입.
	 @param _color_bit color bit.
	 @param _width 너비
	 @param _height 높이.
     @return _img 초기화된 VBImage.
	 */
	VBImage* VBImageInitAndClear(VBImage* _img, VBColorType _color_type, VBUChar _color_bit, VBULong _width, VBULong _height);
	
	/**
	 @brief VBImage의 메모리를 해제합니다.
	 @param _img VBImage.
	 */
	void VBImageFree(VBImage** _img);
	
	/**
	 @brief VBImage를 copy 합니다.
	 @param _img VBImage.
	 @return copy된 VBImage를 반환합니다.
	 */
	VBImage* VBImageCopy(VBImage* _img);
	
	/**
	 @brief VBImage를 경로를 지정해 load합니다.
	 
	 VBImage의 타입은 PNG, JPEG와 JPG를 지원합니다.\n
	 파일 확장자에 따라 각각의 데이터(color 타입, color bit, 너비, 높이)를 구합니다.
	 
	 @param _path 파일이 저장되어 있는 경로.
	 */
	void VBImageLoad(VBImage* _img, VBString* _path);
	
	/**
	 @brief VBImage의 size를 구합니다.
	 @param _img VBimage.
     @return 반환된 이미지의 사이즈를 반환합니다.
	 */
	VBULong VBImageGetImageDataSize(VBImage* _img);
	
	/**
	 @brief VBImage의 데이터를 구합니다.
	 @param _img VBimage.
     @return 이미지 데이터를 반환합니다.
	 */
	void* VBImageGetImageData(VBImage* _img);
	
	/**
	 @brief VBImage의 color타입을 구합니다.
	 @param _img VBImage.
     @return 이지미의 타입을 반환합니다.
	 */
	VBColorType VBImageGetColorType(VBImage* _img);
	
	/**
	 @brief VBImage의 color bit을 구합니다.
	 @param _img VBImage.
     @return 이미지의 color bit을 반환합니다.
	 */
	VBUChar VBImageGetColorBit(VBImage* _img);
	
	/**
	 @brief VBImage의 너비를 구합니다.
	 @param _img VBImage.
     @return 이미지의 너비를 반환합니다.
	 */	
	VBULong VBImageGetWidth(VBImage* _img);
	
	/**
	 @brief VBImage의 길이을 구합니다.
	 @param _img VBImage.
     @return 이미지의 높이를 반환합니다.
	 */
	VBULong VBImageGetHeight(VBImage* _img);
	
	/**
	 @brief VBImage의 pixel color를 구합니다.
	 @param _img VBImage.
	 @param _x pixel의 가로축값.
	 @param _y pixel의 세로축값.
     @return 설정한 좌표의 픽셀 포인터
	 */
	void* VBImageGetPixelColor(VBImage* _img, VBULong _x, VBULong _y);
	
	/**
	 @brief VBImage의 pixel color를 설정합니다.
	 @param _img VBImage.
	 @param _x pixel의 가로축값.
	 @param _y pixel의 세로축값.
	 @param _color 설정하려는 color.
	 */
	void VBImageSetPixelColor(VBImage* _img, VBULong _x, VBULong _y, void* _color);
	
	/**
	 @brief VBImage의 pixel값을 Clear합니다.
	 @param _img VBImage.
	 */
	void VBImageClearPixel(VBImage* _img);
	
	/**
	 @brief VBImage의 pixel 데이터가 있는 곳의 데이터를 clear합니다.
	 @param _img VBImage.
	 @param _x pixel의 가로축값.
	 @param _y pixel의 세로축값.
	 @param _width 너비
	 @param _height 높이.
	 */
	void VBImageClearPixelAtBox(VBImage* _img, VBULong _x, VBULong _y, VBULong _width, VBULong _height);
    
    VBBool VBImageGetIsLoaded(VBImage* _img);
#ifdef __cplusplus
}
#endif

#endif