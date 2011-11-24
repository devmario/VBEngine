/**
 @file Display/VBDrawable2D.h
 @brief VBDrawable2D 타입들의 상수값 정의
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

#ifndef __VBDrawable2D_H__
#define __VBDrawable2D_H__

#include "../VBType.h"
#include "VBTexture.h"
#include "../Core/Linear/VBVector2D.h"
#include "../Core/Linear/VBMatrix2D.h"
#include "../Core/Linear/VBTriangle2D.h"
#include "../Core/Color/VBColor.h"

#ifdef __cplusplus
extern "C" {
#endif 
	
	/**
	 @brief VBEngine에서 사용되는 타입.
	 
     <b>Triangle Type Image</b><br>
     -<i>Triangle Strip</i><br>
     -<i>Triangle Fan</i>
     <table>
     <tr>
     <td>
     <img src="/Users/welivehere/Desktop/img/triangle.jpg" alt="triangle_type">
     </td>
     </tr>
     </table>
	 */
	enum {
		VBDrawable2DType_None				=	0x00,
		VBDrawable2DType_TriangleStrip		=	0x01,
		VBDrawable2DType_TriangleFan		=	0x02
	};
	
	/**
	 @brief VBDrawable2DType의 구조체 타입.
	 */
	typedef VBUChar VBDrawable2DType;
	
	/**
	 @brief VBDrawable2D의 구조체 타입.
	 */
	typedef struct VBDrawable2D VBDrawable2D;
	
	/**
	 @brief VBDrawable2d의 구조체.
	 */
	struct VBDrawable2D {
		/*!
		 VBTexture
		 */
		VBTexture* tex;
		
		/*!
		 draw 타입
		 */
		VBDrawable2DType draw_type;
		
		/*!
		 폴리곤의 길이
		 */
		VBUShort poly_len;
        
        /*!
         폴리 스텝 사이즈
         */
        VBUShort poly_stepSize;
        
        /*!
         인덱스 스텝 사이즈
         */
        VBUShort idx_stepSize;
        
        /*!
         스텝 사이즈 사용 여부
         */
        VBBool useStepSize;
		
		/*!
		 RBGA 컬러값
		 */
		VBColorRGBA* color;
        
		/*!
		 버텍스
		 */
		VBVector2D* vtx;
		/*!
		 VBTexture 좌표
		 */
		VBVector2D* txc;
		/*!
		 폴리곤 인덱스의 길이
		 */
		VBUShort idx_len;
		/*!
		 인덱스
		 */
		VBUShort* idx;
	};
	
	/**
	 @brief VBDrawable2D의 메모리를 할당합니다.
	 @return _drawable 메모리가 할당된 VBDrawable2D를 반환합니다.
	 */
	VBDrawable2D* VBDrawable2DAlloc(void);
    
    /**
     @brief VBDrawable2D를 초기화 합니다.
     @param _drawable 메모리가 할당된 VBDrawable2D
     @return 초기화된 VBDrawable2D
     */
    VBDrawable2D* VBDrawable2DInit(VBDrawable2D* _drawable);
    
    /**
     @brief VBDrawable2D를 초기화 하고 필요한 메모리를 미리 확보해 놓습니다.
     @param _drawable 메모리가 할당된 VBDrawable2D
     @return 초기화된 VBDrawable2D
     */
    VBDrawable2D* VBDrawable2DInitWithStepSize(VBDrawable2D* _drawable);
	
	/**
	 @brief VBDrawable2D를 텍스쳐와 함께 초기화 합니다.
     
     VBDrawayble2DType의 타입 (VBDrawable2DType_TriangleStrip, VBDrawable2DType_TriangleFan)을 설정해야 합니다. 
	 
     @param _drawable VBDrawable2D.
     @param _draw_type draw 타입.
     @param _tex VBTexture.
     @return 초기화된 VBDrawable2D를 반환합니다.
	 */
	VBDrawable2D* VBDrawable2DInitWithTexture(VBDrawable2D* _drawable, VBDrawable2DType _draw_type, VBTexture* _tex);
	
	/**
	 @brief VBDrawable2D를 여러가지 data와 함께 초기화 합니다.
     
     VBDrawable2D의 메모리를 할당하지 않았을 경우 혹은 각각의 요소들 \n
     (VBTexture, VBUShort, VBColorRGBA, VBVector2D, VBVector2D, VBUShort, VBUShort) \n
     이 없을 경우에는 VBDrawable2D 초기화되지 않습니다. 
     
     @param _drawable VBDrawable2D.
     @param _draw_type draw 타입.
     @param _tex VBTexture.
     @param _poly_len 폴리곤의 길이.
     @param _color 컬러.
     @param _vtx 버텍스.
     @param _txc VBTexture 좌표.
     @param _idx_len 인덱스의 길이.
     @param _idx 인덱스.
     @return 초기화된 VBDrawable2D를 반환합니다.
	 */
	VBDrawable2D* VBDrawable2DInitWithData(VBDrawable2D* _drawable, VBDrawable2DType _draw_type,
										   VBTexture* _tex, VBUShort _poly_len, 
										   VBColorRGBA* _color, VBVector2D* _vtx, VBVector2D* _txc, 
										   VBUShort _idx_len, VBUShort* _idx);
	
	/**
	 @brief VBDrawable2D의 메모리를 해제합니다.
	 @param _drawable VBDrawable2D.
	 */
	void VBDrawable2DFree(VBDrawable2D** _drawable);
	
	/**
	 @brief 첫번째 VBDrawable2D에 두번째 VBDrawable2D을 더합니다.
	 @param _drawable_1 첫번째 VBDrawable2D
     @param _drawable_2 두번째 VBDrawable2D
	 */
	void VBDrawable2DAppend(VBDrawable2D* _drawable_1, VBDrawable2D* _drawable_2);
	
	/**
	 @brief 
	 @param
	 */
	void VBDrawable2DBegin(VBDrawable2D* _drawable, VBColorRGBA _color, VBVector2D _vtx, VBVector2D _txc);
	
	/**
	 @brief
	 @param
	 */
	void VBDrawable2DAdd(VBDrawable2D* _drawable, VBColorRGBA _color, VBVector2D _vtx, VBVector2D _txc);
	
	/**
	 @brief
	 @param
	 */
	void VBDrawable2DEnd(VBDrawable2D* _drawable, VBColorRGBA _color, VBVector2D _vtx, VBVector2D _txc);
	
	/**
	 @brief VBDrawable2D을 클리어 합니다.
	 @param _drawable VBDrawabel2D.
	 */
	void VBDrawable2DClear(VBDrawable2D* _drawable);
	
	/**
	 @brief VBDrawable2D의 데이터를 화면에 출력합니다.
	 @param _drawable VBDrawabel2D.
	 */
	void VBDrawable2DDraw(VBDrawable2D* _drawable);
	
	/**
	 @brief VBDrawable2D의 텍스쳐를 구합니다.
	 @param _drawable VBDrawabel2D.
     @return VBDrawable2D의 텍스쳐를 반환합니다.
	 */
	VBTexture* VBDrawable2DGetTexture(VBDrawable2D* _drawable);
	
	/**
	 @brief VBDrawable2D의 폴리곤의 길이를 구합니다.
	 @param _drawable VBDrawabel2D.
     @return VBDrawable2D의 폴리곤의 길이를 반환합니다.
	 */
	VBUShort VBDrawable2DGetPolygonLength(VBDrawable2D* _drawable);
	
	/**
	 @brief VBDrawable2D의 VBTexture Color를 구합니다.
	 @param _drawable VBDrawabel2D.
     @return VBDrawable2D의 VBTexture Color를 반환합니다.
	 */
	VBColorRGBA* VBDrawable2DGetColor(VBDrawable2D* _drawable);
	
	/**
	 @brief VBDrawable2D의 VBTexture 버텍스를 구합니다.
	 @param _drawable VBDrawabel2D.
     @return VBDrawable2D의 VBTexture 좌표를 반환합니다.
	 */
	VBVector2D* VBDrawable2DGetVertex(VBDrawable2D* _drawable);
	
	/**
	 @brief VBDrawable2D의 VBTexture 좌표를 구합니다.
	 @param _drawable VBDrawabel2D.
     @return VBDrawable2D의 VBTexture 좌표를 반환합니다.
	 */
	VBVector2D* VBDrawable2DGetTexcoord(VBDrawable2D* _drawable);
	
	/**
	 @brief VBDrawable2D의 인덱스의 길이를 구합니다.
	 @param _drawable VBDrawabel2D.
     @return VBDrawable2D의 인덱스의 길이를 반환합니다.
	 */
	VBUShort VBDrawable2DGetIndexLength(VBDrawable2D* _drawable);
	
	/**
	 @brief VBDrawable2D의 인덱스를 구합니다.
	 @param _drawable VBDrawable2D.
     @return VBDrawable2D의 인덱스를 반환합니다.
	 */
	VBUShort* VBDrawable2DGetIndex(VBDrawable2D* _drawable);
    
    void VBDrawable2DSetTexture(VBDrawable2D* _drawable, VBTexture* _tex);
    
    VBDrawable2DType VBDrawable2DGetDrawType(VBDrawable2D* _drawable);
    
    VBBool VBDrawable2DGetTriangle(VBDrawable2D* _drawable, VBUShort* _cur_step, VBTriangle2D* _tri);
    
#ifdef __cplusplus
}
#endif

#endif
