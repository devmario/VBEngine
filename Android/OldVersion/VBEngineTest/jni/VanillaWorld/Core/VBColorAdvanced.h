/**
 @file Core/VBColorAdvanced.h
 @brief VBEngine의 VBColorAdvanced 구조체타입과 여러 함수들.
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

#ifndef __VBColorAdvanced_H__
#define __VBColorAdvanced_H__

#include "../VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
	 @brief 이미지의 색상을 변환 시킬 색상 변환 정보
     
     red_percent, green_percent, blue_percent, alpha_percent는 원본 이미지의 색상을 어느정도 비율로 사용할 것인가를 나타내는 수치입니다.
     red_amount, green_amount, blue_amount, alpha_amount는 원본 색상값에서 추가되거나 감소될 색상값을 나타냅니다.
	 */
    typedef struct VBColorAdvanced VBColorAdvanced;
    
    struct VBColorAdvanced {
        /*!
         빨간색 비율(-100% - 100%)
         */
        VBChar red_percent;
        /*!
         녹색 비율(-100% - 100%)
         */
        VBChar green_percent;
        /*!
         파란색 비율(-100% - 100%)
         */
        VBChar blue_percent;
        /*!
         알파 비율(-100% - 100%)
         */
        VBChar alpha_percent;
        
        /*!
         빨간색 증감 색상값(-255 - 255)
         */
        VBShort red_amount;
        /*!
          녹색 증감 색상값(-255 - 255)
         */
        VBShort green_amount;
        /*!
         파란색 증감 색상값(-255 - 255)
         */
        VBShort blue_amount;
        /*!
         알파 증감 색상값(-255 - 255)
         */
        VBShort alpha_amount;
    };
    
    VBColorAdvanced VBColorAdvancedLoadIdentity();
    
    /**
     @brief 색상 변환 정보를 생성합니다.
     @param _red_percent    빨간색 비율(-100% - 100%)
     @param _green_percent  녹색 비율(-100% - 100%)
     @param _blue_percent   파란색 비율(-100% - 100%)
     @param _alpha_percent  알파 비율(-100% - 100%)
     @param _red_amount     빨간색 증감 색상값(-255 - 255)
     @param _green_amount   녹색 증감 색상값(-255 - 255)
     @param _blue_amount    파란색 증감 색상값(-255 - 255)
     @param _alpha_amount   알파 증감 색상값(-255 - 255)
     @return VBColorAdvanced
     */
    VBColorAdvanced VBColorAdvancedCreate(VBChar _red_percent, VBChar _green_percent, VBChar _blue_percent, VBChar _alpha_percent, VBShort _red_amount, VBShort _green_amount, VBShort _blue_amount, VBShort _alpha_amount);
    
    /**
     @brief 색상 변환 정보를 보간합니다.
     @param _color1 첫번째 색상 정보
     @param _color2 두번째 색상 정보
     @param _num    보간 수치(0.0 ~ 1.0)
     @return VBColorAdvanced
     */
    VBColorAdvanced VBColorAdvancedInterpolate(VBColorAdvanced _color1, VBColorAdvanced _color2, VBFloat _num);
    
    /**
     @brief 생상 변환 정보를 곱합니다.
     @param _color1 첫번째 색상 정보
     @param _color2 두번째 색상 정보
     @return 연산이 적용된 color를 반환합니다.
     */
    VBColorAdvanced VBColorAdvancedMultiply(VBColorAdvanced _color1, VBColorAdvanced _color2);
#ifdef __cplusplus
}
#endif

#endif