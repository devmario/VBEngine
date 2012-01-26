/**
 @file Display/VBGraphic2D.h
 @brief VBGraphic2D 타입들의 상수값 정의
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

#ifndef __VBGraphic2D_H__
#define __VBGraphic2D_H__

#include "VBDrawable2D.h"

#ifdef __cplusplus
extern "C" {
#endif
	
    /**
	 @brief VBGraphic2D 관련 구조체타입.
	 */
	typedef struct VBGraphic2D VBGraphic2D;
	
    /**
	 @brief VBGraphic2D 관련 구조체.
	 */
	struct VBGraphic2D {
        /*!
         선
         */
		VBDrawable2D* line_drawable;
        /*!
         
         */
		VBDrawable2D* fill_drawable;
		
        /*!
         선의 넓이
         */
		VBFloat line_width;
		/*!
         선의 컬러
         */
        VBColorRGBA line_color;
		
        /*!
         
         */
		VBBool is_fill;
		/*!
         
         */
        VBColorRGBA fill_color;
		
        /*!
         */
		VBVector2D last_position;
	};
	
    /**
     @brief VBGraphic2D의 메모리를 할당합니다.
     @return 메모리가 할당된 VBGraphic2D를 반환합니다. 
     */
	VBGraphic2D* VBGraphic2DAlloc(void);
	
    /**
     @brief VBGraphic2D를 초기화합니다. 
     @param _grap VBGraphic2D.
     @return 초기화된 VBGraphic2D를 반환합니다. 
     */
	VBGraphic2D* VBGraphic2DInit(VBGraphic2D* _grap);
	
    /**
     @brief VBGraphic2D의 메모리를 해제합니다.
     @param _grap VBGraphic2D.
     */
	void VBGraphic2DFree(VBGraphic2D** _grap);
	
    /**
     @brief VBGraphic2D를 이용하여 생성된 것을 clear하고 다시 초기화 합니다.
     @param _grap VBGraphic2D.
     */
	void VBGraphic2DClear(VBGraphic2D* _grap);
	
    /**
     @brief 라인을 그릴 시작 위치
     @param _grap VBGraphic2D
     @param _x x좌표
     @param _y y좌표     
     */
	void VBGraphic2DMoveTo(VBGraphic2D* _grap, VBFloat _x, VBFloat _y);
	
    /**
     @brief 라인을 그릴 마지막 위치
     @param _grap VBGraphic2D
     @param _x x좌표
     @param _y y좌표
     */
	void VBGraphic2DLineTo(VBGraphic2D* _grap, VBFloat _x, VBFloat _y);
	
    /**
     @brief  
     @param _grap
     @param _ctrX
     @param _ctrY
     @param _x
     @param _y
     @param _detail
     */
	void VBGraphic2DQuadBezierCurveTo(VBGraphic2D* _grap, VBFloat _ctrX, VBFloat _ctrY, VBFloat _x, VBFloat _y, VBULong _detail);
	
    /**
     @brief
     @param _grap
     @param _ctrX
     @param _ctrY
     @param _x
     @param _y
     @param _detail
     */
    void VBGraphic2DCubicBezierCurveTo(VBGraphic2D* _grap, VBFloat _ctrX1, VBFloat _ctrY1, VBFloat _ctrX2, VBFloat _ctrY2, VBFloat _x, VBFloat _y, VBULong _detail);
	
    /**
     @brief 라인의 색상 지정
     @param _grap VBGraphic2D
     @param _color 색상
     */
	void VBGraphic2DSetLineColor(VBGraphic2D* _grap, VBColorRGBA _color);
	
    /**
     @brief 라인의 굵기 지정
     @param _grap VBGraphic2D
     @param _width 굵기
     */
	void VBGraphic2DSetLineWidth(VBGraphic2D* _grap, VBFloat _width);
	
    /**
     @brief
     @param
     */
	void VBGraphic2DBeginFill(VBGraphic2D* _grap);
	
    /**
     @brief
     @param
     */
	void VBGraphic2DEndFill(VBGraphic2D* _grap);
	
    /**
     @brief
     @param
     */
	void VBGraphic2DSetFillColor(VBGraphic2D* _grap, VBColorRGBA _color);
	
    /**
     @brief
     @param
     */
	void VBGraphic2DDrawCircle(VBGraphic2D* _grap, VBFloat _x, VBFloat _y, VBFloat _radius);
	
    /**
     @brief
     @param
     */
	void VBGraphic2DDrawEllepse(VBGraphic2D* _grap, VBFloat _x, VBFloat _y, VBFloat _width, VBFloat _height);
	
    /**
     @brief 
     @param
     */
	void VBGraphic2DDrawRect(VBGraphic2D* _grap, VBFloat _x, VBFloat _y, VBFloat _width, VBFloat _height);

#ifdef __cplusplus
}
#endif

#endif