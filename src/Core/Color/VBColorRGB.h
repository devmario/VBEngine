/**
 @file Core/VBColorRGB.h
 @brief VBEngine의 VBColorRGB 구조체타입과 여러 함수들.
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

#ifndef __VBColorRGB_H__
#define __VBColorRGB_H__

#include "../../VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 @brief VBColorRGB 관련 구조체 타입.
	 */
	typedef struct VBColorRGB VBColorRGB;
	
	/**
	 @brief VBColorRGB 관련 구조체.
	 
	 RGB 
	 R - 적색(Red)
	 G - 녹색(Green) 
	 B - 청(Blue)
	 위의 3가지 값에 의해 색을 정의하는 색 모델, 또는 색 표시 방식. 
	 */
	struct VBColorRGB {
		/*!
		 적색(Red)
		 */
		VBUChar r;
		/*!
		 녹색(Green)
		 */
		VBUChar g;
		/*!
		 청색(Blue)
		 */
		VBUChar b;
	};
	
	/** 
	 @brief VBColorRGB타입 Color를 생성합니다. 
	 @param _r 적색(red)값.
	 @param _g 녹색(Green)값.
	 @param _b  청색(Blue)값.
     @return RGB Color
	 */
	VBColorRGB VBColorRGBCreate(VBUChar _r, VBUChar _g, VBUChar _b);
	
	/**
	 @brief VBColorRGB타입 Color를 각각의 값(Red, Green, Blue)에 값을 대입해 생성합니다.
	 @param _hex 16진수 값.
     @return RGB Color
	 */
	VBColorRGB VBColorRGBCreateWithColorCode(VBULong _hex);
	
	/**
	 @brief VBColorRGB의 Color 코드를 반환합니다. 
	 @param _color
     @return VBULong으로 변환된 색상값 
	 */
	VBULong VBColorRGBGetColorCode(VBColorRGB _color);
	
	/**
	 @brief VBColorRGB에서 적색(Red)값을 반환합니다.
	 @param _color
     @return 적색 색상값
	 */
	VBUChar VBColorRGBGetR(VBColorRGB _color);
	
	/**
	 @brief VBColorRGB에서 녹색(Green)값을 반환합니다.
	 @param _color
     @return 녹색 색상값
	 */ 
	VBUChar VBColorRGBGetG(VBColorRGB _color);
	
	/**
	 @brief VBColorRGB에서 청색(Blue)값을 반환합니다.
	 @param _color
     @return 청색 색상값
	 */
	VBUChar VBColorRGBGetB(VBColorRGB _color);
    
    /**
     @brief 색상 정보를 보간합니다.
     @param _color1 첫번째 색상 정보
     @param _color2 두번째 색상 정보
     @param _num    보간 수치(0.0 ~ 1.0)
     @return VBColorRGB
     */
    VBColorRGB VBColorRGBInterpolate(VBColorRGB _color1, VBColorRGB _color2, VBFloat _num);
	
#ifdef __cplusplus
}
#endif

#endif