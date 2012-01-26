/**
 @file Display/VBBlendMode.h
 @brief VBBlendMode 타입들의 상수값 정의
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

#ifndef __VBBlendMode_H__
#define __VBBlendMode_H__

#include "../VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @enum 블렌딩 모드 타입들의 상수값 정의
     */
    enum {
        /*!
         보통 기준 색상과 상호 작용하지 않고 일반적으로 색상을 적용합니다.
         */
        VBBlendMode_Normal          =   0x00,
        /*!
         동영상 클립의 색상은 변경되지 않고 동영상 클립을 위로 쌓아올립니다.
         */
        VBBlendMode_Layer           =   0x01,
        /*!
         블렌드 색상보다 밝은 영역만 바꿉니다. 블렌드 색상보다 어두운 영역은 변경되지 않습니다.
         */
        VBBlendMode_Darken          =   0x02,
        /*!
         기준 색상에 블렌드 색상을 곱하여 색상을 어둡게 만듭니다.
         */
        VBBlendMode_Multiplay       =   0x03,
        /*!
         블렌드 색상보다 어두운 픽셀만 바꿉니다. 블렌드 색상보다 밝은 영역은 변경되지 않습니다.
         */
        VBBlendMode_Lighten         =   0x04,
        /*!
         반전된 블렌드 색상에 기준 색상을 곱하여 표백 효과를 냅니다.
         */
        VBBlendMode_Screen          =   0x05,
        /*!
         기준 색상에 따라 색상을 곱하거나 스크린합니다.
         */
        VBBlendMode_Overlay         =   0x06,
        /*!
         블렌드 모드 색상에 따라 색상을 곱하거나 스크린합니다. 이 효과는 객체에 스포트라이트를 비추는 것과 유사합니다.
         */
        VBBlendMode_HardLight       =   0x07,
        /*!
         두 이미지 사이에서 색상을 밝게 하는 디졸브 애니메이션 효과를 만드는 데 주로 사용됩니다.
         */
        VBBlendMode_Add             =   0x08,
        /*!
         두 이미지 사이에서 색상을 어둡게 하는 디졸브 애니메이션 효과를 만드는 데 주로 사용됩니다.
         */
        VBBlendMode_Subtract        =   0x09,
        /*!
         어느 쪽의 밝기 값이 더 큰지에 따라 기준 색상에서 블렌드 색상을 제거하거나 블렌드 색상에서 기준 색상을 제거합니다. 이 효과는 컬러 네거티브와 유사합니다.
         */
        VBBlendMode_Difference      =   0x0A,
        /*!
         기준 색상을 반전시킵니다.
         */
        VBBlendMode_Invert          =   0x0B,
        /*!
         알파 마스크를 적용합니다.
         */
        VBBlendMode_Alpha           =   0x0C,
        /*!
         배경 이미지에 있는 픽셀을 비롯하여 모든 기준 색상 픽셀을 제거합니다.
         */
        VBBlendMode_Erase           =   0x0D
    };
    typedef VBUChar VBBlendMode;
    
#ifdef __cplusplus
}
#endif

#endif