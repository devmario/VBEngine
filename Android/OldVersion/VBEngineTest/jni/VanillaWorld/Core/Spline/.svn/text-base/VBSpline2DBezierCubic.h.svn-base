/**
 @file Core/Spline/VBSpline2DBezierCubic.h
 @brief 스플라인 2D 2차 베지어 곡선 구조체 및 함수들
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

#ifndef __VBSpline2DBezierCubic_H__
#define __VBSpline2DBezierCubic_H__

#include "../../VBType.h"
#include "../VBVector2D.h"
#include "../VBLine2D.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @brief VBSpline2DBezierCubic의 타입 정의
     */
    typedef struct VBSpline2DBezierCubic VBSpline2DBezierCubic;
    
    /**
     @brief 3차 베지어 곡선 구조체
     
     4개의 점으로 3차 베지어 곡선을 생성합니다.
     */
    struct VBSpline2DBezierCubic {
        /**
         시작점
         */
        VBVector2D begin;
        /**
         시작점의 조절점
         */
        VBVector2D begin_control;
        /**
         끝점의 조절점
         */
        VBVector2D end_control;
        /**
         끝점
         */
        VBVector2D end;
    };
    
    /**
     @brief VBSpline2DBezierCubic 구조체에 메모리를 할당합니다.
     @return 메모리가 할당된 VBSpline2DBezierCubic
     */
    VBSpline2DBezierCubic* VBSpline2DBezierCubicAlloc(void);
    
    /**
     @brief VBSpline2DBezierCubic 구조체를 초기화 합니다.
     @param _bezier VBSpline2DBezierCubic
     @return 초기화된 VBSpline2DBezierCubic
     */
    VBSpline2DBezierCubic* VBSpline2DBezierCubicInit(VBSpline2DBezierCubic* _bezier);
    
    /**
     @brief VBSpline2DBezierCubic 구조체를 정점들로 초기화 합니다.
     @param _bezier VBSpline2DBezierCubic
     @param _begin 시작점
     @param _begin_control 시작점의 조절점
     @param _end_control 끝점의 조절점
     @param _end 끝점
     @return 초기화된 VBSpline2DBezierCubic
     */
    VBSpline2DBezierCubic* VBSpline2DBezierCubicInitWithVector(VBSpline2DBezierCubic* _bezier,
                                                               VBVector2D _begin,
                                                               VBVector2D _begin_control,
                                                               VBVector2D _end_control,
                                                               VBVector2D _end);
    
    /**
     @brief VBSpline2DBezierCubic 구조체를 메모리 해제 합니다.
     @param _bezier VBSpline2DBezierCubic
     */
    void VBSpline2DBezierCubicFree(VBSpline2DBezierCubic** _bezier);
    
    /**
     @brief 베지어 곡선 위의 한 정점을 반환합니다.
     @param _bezier VBSpline2DBezierCubic
     @param _t 정점을 가져올 시점(0.0 ~ 1.0, 시작이 0, 끝이 1이라고 간주합니다.)
     @return 베지어 곡선 위의 한 정점
     */
    VBVector2D VBSpline2DBezierCubicGetVector2D(VBSpline2DBezierCubic* _bezier, VBFloat _t);
    
    /**
     @brief 베지어 곡선과 한 선분의 충돌을 검출합니다.
     @param _bezier VBSpline2DBezierCubic
     @param _line VBLine2D
     @param _collision_vector 충돌 지점
     @return VBTrue일 경우 충돌 발생, VBFalse일 경우 충돌하지 않음.
     */
    VBBool VBSpline2DBezierCubicIsNearestCollisionLine2D(VBSpline2DBezierCubic* _bezier, VBLine2D _line, VBVector2D* _collision_vector);
    
    /**
     @brief 베지어 곡선의 x축만 가지고 있는 B(tx)를 이용하여 정점(t)를 구합니다.
     @param _bezier VBSpline2DBezierCubic
     @param _btx x축만 가지고 있는 베지어 곡선
     @return t의 값을 반환합니다.
     */
    VBFloat VBSpline2DBezierCubicGetTByBtx(VBSpline2DBezierCubic* _bezier, VBFloat _btx);
    
    /**
     @brief 정점(t)를 이용하여 베지어 곡선의 y값을 구합니다.
     @param _bezier VBSpline2DBezierCubic
     @param _t 정점을 가져올 시점(0.0 ~ 1.0, 시작이 0, 끝이 1이라고 간주합니다.)
     @return 베지어 곡선의 y값을 반환합니다.
     */
    VBFloat VBSpline2DBezierCubicGetBtyByT(VBSpline2DBezierCubic* _bezier, VBFloat _t);
	
#ifdef __cplusplus
}
#endif

#endif