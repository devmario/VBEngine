/**
 @file Core/VBMath.h
 @brief VBEngine의 VBMath 구조체타입과 여러 함수들.
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

#ifndef __VBMath_H__
#define __VBMath_H__

#include "../VBType.h"
#include "VBArrayVector.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct VBFloatComplex VBFloatComplex;
    
    struct VBFloatComplex {
        VBFloat real;
        VBFloat imag;
    };
    
    typedef struct VBDoubleComplex VBDoubleComplex;
    
    struct VBDoubleComplex {
        VBDouble real;
        VBDouble imag;
    };

    typedef struct VBMathFxFloat VBMathFxFloat;
    
    /**
     @brief VBMathFxFloatSet의 타입정의
     */
    typedef struct VBMathFxFloatSet VBMathFxFloatSet;
    
    enum {
        VBMathFxFloatType_None           =   0x00,
        VBMathFxFloatType_NaN            =   0x01,
        VBMathFxFloatType_Infinity       =   0x02,
        VBMathFxFloatType_Deinfinity     =   0x03,
        VBMathFxFloatType_Real           =   0x04,
        VBMathFxFloatType_Imaginary      =   0x05,
        VBMathFxFloatType_Complex        =   0x06
    };
    /**
     @brief VBMathFxFloatType의 타입정의
     */
    typedef VBUChar VBMathFxFloatType;
    
    /**
     @brief VBMathFxFloat
     */
    struct VBMathFxFloat {
        /**
         */
        VBMathFxFloatType type;
        /**
         복소수
         */
        VBFloatComplex x;
    };
    
    /**
     @brief 
     */
    struct VBMathFxFloatSet {
        VBArrayVector* fx;
    };
    
    /**
     @brief VBMathFxFloatSet 구조체에 메모리를 할당합니다.
     @return 메모리가 할당된 VBMathFxFloatSet
     */
    VBMathFxFloatSet* VBMathFxFloatSetAlloc(void);
    
    /**
     @brief VBMathFxFloatSet 구조체를 초기화합니다.
     @param _fxs VBMathFxFloatSet
     @return 초기화된 VBMathFxFloatSet
     */
    VBMathFxFloatSet* VBMathFxFloatSetInit(VBMathFxFloatSet* _fxs);
    
    /**
     @brief VBMathFxFloatSet을 메모리 해제 합니다.
     @param _fxs VBMathFxFloatSet
     */
    void VBMathFxFloatSetFree(VBMathFxFloatSet** _fxs);
    
    /**
     @brief VBMathFxFloatSet의 길이를 반환합니다.
     @param _fxs VBMathFxFloatSet
     @return VBMathFxFloatSet의 길이
     */
    VBULong VBMathFxFloatSetGetLength(VBMathFxFloatSet* _fxs);
    
    /**
     @brief _at의 위치에 있는 VBMathFxFloat을 반환합니다.
     @param _fxs VBMathFxFloatSet
     @param _at 위치
     @return VBMathFxFloat
     */
    VBMathFxFloat* VBMathFxFloatSetGetFxAt(VBMathFxFloatSet* _fxs, VBULong _at);
    
    /**
     @brief VBMathFxFloat의 타입을 반환합니다.
     @param _fx VBMathFxFloat
     @return VBMathFxFloat의 타입
     */
    VBMathFxFloatType VBMathFxFloatGetType(VBMathFxFloat* _fx);
    
    /**
     @brief VBMathFxFloat의 실수를 반환합니다.
     @param _fx VBMathFxFloat
     @return 실수
     */
    VBFloat VBMathFxFloatGetFxReal(VBMathFxFloat* _fx);
    
    /**
     @brief VBMathFxFloat의 허수를 반환합니다.
     @param _fx VBMathFxFloat
     @return 허수
     */
    VBFloat VBMathFxFloatGetFxImagenary(VBMathFxFloat* _fx);
    
    /**
     @brief VBMathFxFloat에서 VBFloatComplex를 반환합니다.
     @param _fx VBMathFxFloat
     @return VBFloatComplex
     */
    VBFloatComplex VBMathFxFloatGetFxComplex(VBMathFxFloat* _fx);
    
    /**
     @brief 일차 방정식의 해를 계산합니다. 
     */
    void VBMathLinearEquationGetFx(VBFloat _a, VBFloat _b, VBMathFxFloatSet* _fxs);
    
    /**
     @brief 이차 방정식의 해를 계산합니다.
     */
    void VBMathQuadraticEquationGetFx(VBFloat _a, VBFloat _b, VBFloat _c, VBMathFxFloatSet* _fxs);
    
    /**
     @brief 삼차 방정식의 해를 계산합니다.
     */
    void VBMathCubicEquationGetFx(VBFloat _a, VBFloat _b, VBFloat _c, VBFloat _d, VBMathFxFloatSet* _fxs);
    
#ifdef __cplusplus
}
#endif

#endif