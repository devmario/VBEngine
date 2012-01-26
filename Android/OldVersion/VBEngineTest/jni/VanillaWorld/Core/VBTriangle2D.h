/**
 @file Core/VBTriangle2D.h
 @brief VBEngine의 VBTriangle2D 구조체타입과 여러 함수들.
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

#ifndef __VBTriangle2D_H__
#define __VBTriangle2D_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "../VBType.h"
#include "VBString.h"
#include "VBVector2D.h"
	
	/**
	 @brief 2D관련 벡터 구조체타입.
	 */
	typedef struct VBTriangle2D VBTriangle2D;
	
	/**
	 @brief 2D관련 벡터 구조체.
	 
	 VBVector2D 구조체는 2D환경에서 2차원 좌표계에서의 위치를 나타냅니다.\n
	 여기서 x는 가로 축, y는 세로 축을 나타냅니다.\n
	 8바이트 구조체이며, 4바이트 VBFloat 2개(x, y)를 포함하고 있습니다.
	 */
	struct VBTriangle2D {
        /*!
         첫번째 점
         */
		VBVector2D a;
        /*!
         두번쨰 점
         */
        VBVector2D b;
        /*!
         세번째 점
         */
        VBVector2D c;
	};
	
    /**
     @brief VBTriangle2D을 생성합니다.
     @param _a 첫번쨰 점
     @param _b 두번쨰 점
     @param _c 세번쨰 점
     @return 생성된 VBTriangle2D를 반환합니다.
     */
	VBTriangle2D VBTriangle2DCreate(VBVector2D _a, VBVector2D _b, VBVector2D _c);
	
    /**
     @brief 점과 삼각형의 충돌체크를 합니다.
     @param _tri VBTriangle2D
     @param _pos 출동 체크할 점의 위치
     */
    VBBool VBTriangle2DCheckCollisionWithPoint(VBTriangle2D _tri, VBVector2D _pos);
	
#ifdef __cplusplus
}
#endif

#endif