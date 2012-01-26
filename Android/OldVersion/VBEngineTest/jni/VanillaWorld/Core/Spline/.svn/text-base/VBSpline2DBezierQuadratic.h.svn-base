/**
 @file Core/Spline/VBSpline2DBezierQuadratic.h
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

#ifndef __VBSpline2DBezierQuadratic_H__
#define __VBSpline2DBezierQuadratic_H__

#include "../../VBType.h"
#include "../VBVector2D.h"
#include "../VBLine2D.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @brief VBSpline2DBezierQuadratic 구조체의 타입 정의
     */
    typedef struct VBSpline2DBezierQuadratic VBSpline2DBezierQuadratic;
    
    /**
     @brief 2차 베지어 곡선 구조체
     
     3개의 점으로 2차 베지어 곡선을 생성합니다.
     */
    struct VBSpline2DBezierQuadratic {
        /**
         시작점
         */
        VBVector2D begin;
        /**
         조절점
         */
        VBVector2D control;
        /**
         끝점
         */
        VBVector2D end;
    };
    
    /**
     @brief VBSpline2DBezierQuadratic 구조체의 메모리를 할당합니다.
     @return 메모리가 할당된 VBSpline2DBezierQuadratic
     */
    VBSpline2DBezierQuadratic* VBSpline2DBezierQuadraticAlloc(void);
    
    /**
     @brief VBSpline2DBezierQuadratic 구조체를 초기화합니다.
     @param _bezier VBSpline2DBezierQuadratic
     @return 초기화된 VBSpline2DBezierQuadratic
     */
    VBSpline2DBezierQuadratic* VBSpline2DBezierQuadraticInit(VBSpline2DBezierQuadratic* _bezier);
    
    /**
     @brief 3개의 점으로 VBSpline2DBezierQuadratic 구조체를 초기화합니다.
     @param _bezier VBSpline2DBezierQuadratic
     @param _begin 시작점
     @param _control 조절점
     @param _end 끝점
     @return 초기화된 VBSpline2DBezierQuadratic
     */
    VBSpline2DBezierQuadratic* VBSpline2DBezierQuadraticInitWithVector(VBSpline2DBezierQuadratic* _bezier,
                                                                       VBVector2D _begin,
                                                                       VBVector2D _control,
                                                                       VBVector2D _end);
    
    /**
     @brief VBSpline2DBezierQuadratic를 메모리 해제합니다.
     @param _bezier VBSpline2DBezierQuadratic
     */
    void VBSpline2DBezierQuadraticFree(VBSpline2DBezierQuadratic** _bezier);
    
    /**
     @brief 2차 베지어 곡선 위의 한 점을 반환합니다.
     @param _bezier VBSpline2DBezierQuadratic
     @param _t 정점을 가져올 시점(0.0 ~ 1.0, 시작이 0, 끝이 1이라고 간주합니다.)
     @return 2차 베지어 곡선 위의 한 점
     */
    VBVector2D VBSpline2DBezierQuadraticGetVector2D(VBSpline2DBezierQuadratic* _bezier, VBFloat _t);
    
    /**
     @brief 2차 베지어 곡선과 선분의 충돌을 검출합니다.
     @param _bezier VBSpline2DBezierQuadratic
     @param _line VBLine2D
     @param _collision_vector 충돌 지점이 설정됩니다.
     @return VBTrue일 경우 충돌 발생, VBFalse일 경우 충돌 하지 않음.
     */
    VBBool VBSpline2DBezierQuadraticIsNearestCollisionLine2D(VBSpline2DBezierQuadratic* _bezier, VBLine2D _line, VBVector2D* _collision_vector);
	
#ifdef __cplusplus
}
#endif

#endif