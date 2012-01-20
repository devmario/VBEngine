/**
 @file Core/VBColor.h
 @brief VBEngine의 VBColor 구조체타입과 여러 함수들.
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

#ifndef __VBColor_H__
#define __VBColor_H__

#include "../../VBType.h"
#include "VBColorRGB.h"
#include "VBColorRGBA.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 @brief VBEngine에서 사용되는 Color 타입.
	 
	 ColorType_G Grey Color.\n
	 ColorType_GA Grey Color + Alpha값.\n
	 ColorType_RGB RGB(적·녹·청)에 의해 색을 정의하는 색 모델, 또는 색 표시 방식.\n
	 ColorType_RGBA RGB방식에 투명도를 추가하는 방식.
	 */
	enum {
		VBColorType_None				=	0x00,
		VBColorType_G					=	0x01,
		VBColorType_GA					=	0x02,
		VBColorType_RGB					=	0x03,
		VBColorType_RGBA				=	0x04,
	};
	typedef VBUChar VBColorType;
	
	/**
	 @brief 
	 @param _type VBColorType.
     @return 색상 타입의 크기
	 */
	VBLong VBColorTypeGetSize(VBColorType _type);
	
#ifdef __cplusplus
}
#endif

#endif