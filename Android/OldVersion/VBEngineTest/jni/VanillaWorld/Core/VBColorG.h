/**
 @file Core/VBColorG.h
 @brief VBEngine의 VBColorG 구조체타입과 여러 함수들.
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

#ifndef __VBColorG_H__
#define __VBColorG_H__

#include "../VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @brief VBColorG의 구조체 타입
     */
    typedef VBUChar VBColorG;
    
    /**
     @brief 두 개의 VBColocG의 값을 보간합니다.
     @param _color1 첫번쨰 VBColorG
     @param _color2 두번쨰 VBColorG
     @param _num    보간 수치(0.0 ~ 1.0)
     @return 보간된 두 컬러값을 반환합니다.
     */
    VBColorG VBColorGInterpolate(VBColorG _color1, VBColorG _color2, VBFloat _num);

#ifdef __cplusplus
}
#endif

#endif