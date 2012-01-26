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

#include "../VBType.h"
#include "VBColorRGB.h"
#include "VBColorRGBA.h"
#include "VBColorHSV.h"
#include "VBColorAdvanced.h"

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
		VBColorType_HSV                 =	0x05,
		VBColorType_Advanced            =	0x06
	};
	typedef VBUChar VBColorType;
	
	/**
	 @brief 
	 @param _type VBColorType.
     @return 색상 타입의 크기
	 */
	VBLong VBColorTypeGetSize(VBColorType _type);
	
	/**
	 @brief RGB타입의 Color를 HSV타입 Color로 바꿉니다. 
	 
	 HSV Color Type 색 공간은 색을 표현하는 하나의 방법이자, 그 방법에 따라 색을 배치하는 방식이다.\n
	 색상(Hue), 채도(Saturation), 명도(Brightness, Value)의 좌표를 써서 특정한 색을 지정한다.\n
     
     RGB 색 공간은 색을 혼합하면 명도가 올라가는 가산 혼합 방식으로 색을 표현한다.\n
     RGB 가산혼합의 삼원색은 빨강(Red), 녹색(Green)[1], 파랑(Blue)을 뜻한다.
	 
	 @param _color RGB타입의 Color
     @return HSV타입의 Color
	 */
	VBColorHSV VBColorRGBToHSV(VBColorRGB _color);
	
	/**
	 @brief HSV타입 Color를 RGB타입의 Color로 바꿉니다. 
	 
	 HSV Color Type 색 공간은 색을 표현하는 하나의 방법이자, 그 방법에 따라 색을 배치하는 방식이다.\n
	 색상(Hue), 채도(Saturation), 명도(Brightness, Value)의 좌표를 써서 특정한 색을 지정한다.\n
     
     RGB 색 공간은 색을 혼합하면 명도가 올라가는 가산 혼합 방식으로 색을 표현한다.\n
     RGB 가산혼합의 삼원색은 빨강(Red), 녹색(Green)[1], 파랑(Blue)을 뜻한다.
	 
	 @param _color HSV타입의 Color
     @return RGB타입의 Color
	 */
	VBColorRGB VBColorHSVToRGB(VBColorHSV _color);
	
#ifdef __cplusplus
}
#endif

#endif