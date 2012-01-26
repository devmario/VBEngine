/**
 @file Core/VBColorHSV.h
 @brief VBEngine의 VBColorHSV 구조체타입과 여러 함수들.
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

#ifndef __VBColorHSV_H__
#define __VBColorHSV_H__

#include "../VBType.h"
#include "VBColorRGB.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 @brief VBColorHSV 관련 구조체 타입.
	 */
	typedef struct VBColorHSV VBColorHSV;
	
	/**
	 @brief VBColorHSV 관련 구조체.
	 
	 HSV(HSB)
	 H - 색상(Hue)
	 S - 채도(Saturation)	 
	 V - 명도(Brightness, Value)
	 위의 3가지 값에 의해 색을 정의하는 색 모델, 또는 색 표시 방식. 
	 
	 */
	struct VBColorHSV {
		/*!
		 색상(Hue)
		 */
		VBFloat h;
		/*!
		 채도(Saturation)
		 */
		VBFloat s;
		/*!
		 명도(Brightness, Value)
		 */
		VBFloat v;
	};
	
	/**
	 @brief VBColorHS타입 Color를 생성합니다.
	 @param _h 색상(Hue)값.
	 @param _s 채도(Saturation)값.
	 @param _v 명도(Brightness, Value)값.
     @return HSV Color
	 */
	VBColorHSV VBColorHSVCreate(VBFloat _h, VBFloat _s, VBFloat _v);
	
	/**
	 @brief VBColorHSV타입 Color값에서 색상(Hue)값을 반환합니다.
	 @param _color VBColorHSV 색상(Hue)값을 반환합니다.
     @return Hue Value
	 */
	VBFloat VBColorHSVGetH(VBColorHSV _color);
	
	/**
	 @brief VBColorHSV타입 Color값에서 채도(Saturation)값을 반환합니다.
	 @param _color VBColorHSV 채도(Saturation)값을 반환합니다.
     @return Saturation Value
	 */
	VBFloat VBColorHSVGetS(VBColorHSV _color);
	
	/**
	 @brief VBColorHSV타입 Color값에서 밝기(Brightness, Value)값을 반환합니다.
	 @param _color VBColorHSV 밝기(Brightness, Value)값을 반환합니다.
     @return Brightness Value
	 */
	VBFloat VBColorHSVGetV(VBColorHSV _color);
    
    /**
     @brief VBColorHSV타입 2개의 Color값에서 각각의 값(hue, saturation, brightness value)을 보간한 값을 적용한 HSV color값을 반환합니다.
     @param _color1 첫번쨰 VBColorHSV
     @param _color2 두번쨰 VBColorHSV
     @param _num    보간 수치(0.0 ~ 1.0)
     @return 보간된 값에 적용된 HSV color값을 반환합니다.
     */
    VBColorHSV VBColorHSVInterpolate(VBColorHSV _color1, VBColorHSV _color2, VBFloat _num);
	
#ifdef __cplusplus
}
#endif

#endif