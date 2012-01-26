/**
 @file Core/VBLine2D.h
 @brief VBEngine의 VBLine2D 구조체타입과 여러 함수들.
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

#ifndef __VBLine2D_H__
#define __VBLine2D_H__

#include "../VBType.h"
#include "VBVector2D.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
	 @brief VBLine2D 구조체타입.
	 */
    typedef struct VBLine2D VBLine2D;
    
    /**
	 @brief VBLine2D 구조체.
	 */
    struct VBLine2D {
        /*!
         라인의 시작점
         */
        VBVector2D begin;
        /*!
         라인의 끝점
         */
        VBVector2D end;
    };
    
    /**
     @brief 시작점과 끝점으로 라인을 생성합니다.
     @param _beginX 시작점의 x좌표
     @param _beginY 시작점의 y좌표
     @param _endX 끝점의 x좌표
     @param _endY 끝점의 y좌표
     @return 생성된 라인을 반환
     */
    VBLine2D VBLine2DCreate(VBFloat _beginX, VBFloat _beginY, VBFloat _endX, VBFloat _endY);
    
    /**
     @brief 시작점과 끝점으로 라인을 생성합니다.
     @param _begin 시작점의 벡터
     @param _end 끝점의 벡터
     @return 생성된 라인을 반환
     */
    VBLine2D VBLine2DCreateV(VBVector2D _begin, VBVector2D _end);
    
    /**
     @brief 두 선분의 충돌 지점을 검출합니다.
     @param _line1 첫번째 라인
     @param _line2 두번째 라인
     @param _intersection_vector 반환되는 충돌지점 벡터
     @return VBTrue이면 두 선분이 충돌됨, VBFalse이면 충돌하지 않음.
     */
    VBBool VBLine2DIsCollisionLine2D(VBLine2D _line1, VBLine2D _line2, VBVector2D* _intersection_vector);
    
    /**
     @brief 
        A+(B-A)*T
     @param 
     @param _t 0.0~1.0의 값
     @return 
     */
    VBVector2D VBLine2DGetVector2D(VBLine2D _line, VBFloat _t);


#ifdef __cplusplus
}
#endif

#endif