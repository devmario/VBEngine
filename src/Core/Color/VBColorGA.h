/**
 @file Core/VBColorGA.h
 @brief VBEngine의 VBColorGA 구조체타입과 여러 함수들.
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

#ifndef __VBColorGA_H__
#define __VBColorGA_H__

#include "../../VBType.h"
#include "VBColorG.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @brief VBColorGA의 구조체 타입
     */
    typedef struct VBColorGA VBColorGA;
    
    /**
     @brief VBColorGA의 구조체
     */
    struct VBColorGA {
        /*!
         gray 값
         */
        VBUChar g;
        /*!
         alpha 값
         */
        VBUChar a;
    };
    
    /**
     @brief VBColorGA를 생성합니다.
     @param _g gray값
     @param _a alpha값
     */
    VBColorGA VBColorGACreate(VBUChar _g, VBUChar _a);
    
    /**
     @brief VBColorGA에서 gray값을 구합니다.
     @param _color VBColorGA
     @return gray값을 반환합니다.
     */
    VBUChar VBColorGAGetG(VBColorGA _color);
    
    /**
     @brief VBColorGA에서 alpha값을 구합니다.
     @param _color VBColorGA
     @return alpha값을 반환합니다.
     */
    VBUChar VBColorGAGetA(VBColorGA _color);
    
    /**
     @brief VBColorGA에서 gray값을 설정합니다.
     @param _color VBColorGA
     @param _g gray값
     @return gray값이 설정된 VBColorGA를 반환합니다.
     */
    VBColorGA VBColorGASetG(VBColorGA _color, VBUChar _g);
    
    /**
     @brief VBColorGA에서 alpha값을 설정합니다.
     @param _color VBColorGA
     @param _a alpha값
     @return alpha값이 설정된 VBColorGA를 반환합니다.
     */
    VBColorGA VBColorGASetA(VBColorGA _color, VBUChar _a);
    
    /**
     @brief 두 개의 VBColorGA을 보간합니다.
     @param _color1 첫번쨰 VBColorGA
     @param _color2 두번째 VBColorGA
     @param _num 보간 수치(0.0 ~ 1.0)
     @return 보간값을 반환합니다.
     */
    VBColorGA VBColorGAInterpolate(VBColorGA _color1, VBColorGA _color2, VBFloat _num);
    
#ifdef __cplusplus
}
#endif

#endif