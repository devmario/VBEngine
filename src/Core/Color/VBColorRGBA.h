/**
 @file Core/VBColorRGBA.h
 @brief VBEngine의 VBColorRGBA 구조체타입과 여러 함수들.
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

#ifndef __VBColorRGBA_H__
#define __VBColorRGBA_H__

#include "../../VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 @brief VBColorRGBA 관련 구조체 타입.
	 */
	typedef struct VBColorRGBA VBColorRGBA;
	
	/**
	 @brief VBColorRGBA 관련 구조체.
	 
	 RGB 
	 R - 적색(Red)
	 G - 녹색(Green) 
	 B - 청색(Blue)
	 A - 알파(Alpha) 투명도 값
	 위의 4가지 값에 의해 색을 정의하는 색 모델, 또는 색 표시 방식. 
	 */
	struct VBColorRGBA {
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
		/*!
		 알파(Alpha)
		 */
		VBUChar a;
	};
    
    VBColorRGBA VBColorRGBALoadIdentity(void);
	
	/** 
	 @brief VBColorRGB타입 Color를 생성합니다. 
	 @param _r 적색(red)값.
	 @param _g 녹색(Green)값.
	 @param _b 청색(Blue)값.
	 @param _a 알파(Alpha)값.
     @return RGBA Color
	 */
	VBColorRGBA VBColorRGBACreate(VBUChar _r, VBUChar _g, VBUChar _b, VBUChar _a);
	
	/**
	 @brief VBColorRGBA타입 Color를 각각의 값(Red, Green, Blue, Alpha)에 값을 대입해 생성합니다.
	 @param _hex 16진수 값.
     @return RGBA Color
	 */
	VBColorRGBA VBColorRGBACreateWithColorCode(VBULong _hex);
	
	/**
	 @brief VBColorRGBA의 Color 코드를 반환합니다. 
	 @param _color VBColorRBGA.
     @return VBULong으로 변환된 색상값
	 */
	VBULong VBColorRGBAGetColorCode(VBColorRGBA _color);
	
	/**
	 @brief VBColorRGB에서 적색(Red)값을 반환합니다.
	 @param _color VBColorRBGA.
     @return 적색 색상값
	 */
	VBUChar VBColorRGBAGetR(VBColorRGBA _color);
	
	/**
	 @brief VBColorRGB에서 녹색(Green)값을 반환합니다.
	 @param _color VBColorRBGA.
     @return 녹색 색상값
	 */
	VBUChar VBColorRGBAGetG(VBColorRGBA _color);
	
	/**
	 @brief VBColorRGB에서 청색(Blue)값을 반환합니다.
	 @param _color VBColorRBGA.
     @return 청색 색상값
	 */
	VBUChar VBColorRGBAGetB(VBColorRGBA _color);
	
	/**
	 @brief VBColorRGB에서 알파(Alpha)값을 반환합니다.
	 @param _color VBColorRBGA.
     @return 알파 색상값
	 */
	VBUChar VBColorRGBAGetA(VBColorRGBA _color);
    
    /**
     @brief 두 개의 색상 정보를 보간합니다.
     @param _color1 첫번째 색상 정보
     @param _color2 두번째 색상 정보
     @param _num    보간 수치(0.0 ~ 1.0)
     @return 보간값을 반환합니다.
     */
    VBColorRGBA VBColorRGBAInterpolate(VBColorRGBA _color1, VBColorRGBA _color2, VBFloat _num);
    
    /**
     @brief 두 개의 색상 정보를 곱합니다.
     @param _color1 첫번째 색상 정보
     @param _color2 두번째 색상 정보
     @return 연산이 적용된 color를 반환합니다.
     */
    VBColorRGBA VBColorRGBAMultiply(VBColorRGBA _color1, VBColorRGBA _color2);
    
    
    
    VBColorRGBA VBColorRGBADraw_ONE_MINUS_SRC_ALPHA(VBColorRGBA _src, VBColorRGBA _dst);
    VBColorRGBA VBColorRGBADraw_SRC_ALPHA(VBColorRGBA _src, VBColorRGBA _dst);
    
    VBColorRGBA VBColorRGBADrawColor(VBColorRGBA _color1, int _hex, int _maxDark, int _minDark);
	
#ifdef __cplusplus
}
#endif

#endif