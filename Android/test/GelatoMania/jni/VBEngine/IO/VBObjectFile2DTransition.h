/**
 @file IO/VBObjectFile2DTransition.h
 @brief VBEngine의 VBObjectFile2DTransition 구조체타입과 여러 함수들.
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

#ifndef __VBObjectFile2DTransition_H__
#define __VBObjectFile2DTransition_H__

#include "../VBType.h"
#include "../Core/Linear/VBVector2D.h"
#include "../Core/Linear/VBSpline2DBezierCubic.h"
#include "../Util/VBArrayVector.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @enum VBObjectFile2DTransition Type
     */
    enum {
        VBObjectFile2DTransitionType_None           =   0x00,
        VBObjectFile2DTransitionType_SingleBezier   =   0x01,
        VBObjectFile2DTransitionType_MultiBezier    =   0x02,
    };
    
    /**
     @brief VBObjectFile2DTransitionㅅType 타입
     */
    typedef VBUChar VBObjectFile2DTransitionType;
    
    /**
     @brief VBObjectFile2DTransition 구조체 타입
     */
    typedef struct VBObjectFile2DTransition VBObjectFile2DTransition;
    
    /**
     @brief VBObjectFile2DTransition 구조체
     */
    struct VBObjectFile2DTransition {
        /*!
         타입
         */
        VBObjectFile2DTransitionType type;
        /*!
         */
        VBArrayVector* single_transition_bezier;
        /*!
         */
        VBArrayVector* position_transition_bezier;
        /*!
         */
        VBArrayVector* rotation_transition_bezier;
        /*!
         */
        VBArrayVector* scale_transition_bezier;
        /*!
         */
        VBArrayVector* color_transition_bezier;
    };
    
    /**
     @brief VBObjectFile2DTransition의 메모리를 할당합니다.
     @return 메모리가 할당된 VBObjectFile2DTransition
     */
    VBObjectFile2DTransition* VBObjectFile2DTransitionAlloc(void);
    
    /**
     @brief VBObjectFile2DTransition을 초기화 합니다.
     @param _transition 
     @return 초기화된 VBObjectFile2DTransition를 반환합니다.
     */
    VBObjectFile2DTransition* VBObjectFile2DTransitionInit(VBObjectFile2DTransition* _transition);
    
    /**
     @brief VBObjectFile2DTransition을 멀티 데이터와 함께 초기화 합니다.
     @param _transition
     @param _position_bezier_vector_length
     @param _position_bezier_vector
     @param _rotation_bezier_vector_length
     @param _rotation_bezier_vector
     @param _scale_bezier_vector_length
     @param _scale_bezier_vector
     @param _color_bezier_vector_length
     @param _color_bezier_vector
     @return 초기화된 VBObjectFile2DTransition를 반환합니다.
     */
    VBObjectFile2DTransition* VBObjectFile2DTransitionInitWithMultiData(VBObjectFile2DTransition* _transition,
                                                                        VBULong _position_bezier_vector_length,
                                                                        VBVector2D* _position_bezier_vector,
                                                                        VBULong _rotation_bezier_vector_length,
                                                                        VBVector2D* _rotation_bezier_vector,
                                                                        VBULong _scale_bezier_vector_length,
                                                                        VBVector2D* _scale_bezier_vector,
                                                                        VBULong _color_bezier_vector_length,
                                                                        VBVector2D* _color_bezier_vector);
    
    /**
     @brief VBObjectFile2DTransition을 싱글 데이터와 함께 초기화 합니다.
     @param _transition
     @param _single_bezier_vector_length
     @param _single_bezier_vector
     @return 초기화된 VBObjectFile2DTransition를 반환합니다
     */
    VBObjectFile2DTransition* VBObjectFile2DTransitionInitWithSingleData(VBObjectFile2DTransition* _transition,
                                                                         VBULong _single_bezier_vector_length,
                                                                         VBVector2D* _single_bezier_vector);
    
    /**
     @brief VBObjectFile2DTransition의 메모리를 해제합니다.
     @param _transition VBObjectFile2DTransition
     */
    void VBObjectFile2DTransitionFree(VBObjectFile2DTransition** _transition);
    
    /**
     @brief VBObjectFile2DTransition의 타입을 구합니다
     @param _transition
     @return 타입을 반환합니다
     */
    VBObjectFile2DTransitionType VBObjectFile2DTransitionGetType(VBObjectFile2DTransition* _transition);
    
    /**
     @brief 
     @param _transition VBObjectFile2DTransition
     @param _time
     */
    VBFloat VBObjectFile2DTransitionGetSingleValue(VBObjectFile2DTransition* _transition, VBFloat _time);
    
    /**
     @brief
     @param _transition VBObjectFile2DTransition
     @param _time
     */
    VBFloat VBObjectFile2DTransitionGetPositionValue(VBObjectFile2DTransition* _transition, VBFloat _time);
    
    /**
     @brief
     @param _transition VBObjectFile2DTransition
     @param _time
     */
    VBFloat VBObjectFile2DTransitionGetRotationValue(VBObjectFile2DTransition* _transition, VBFloat _time);
    
    /**
     @brief
     @param _transition VBObjectFile2DTransition
     @param _time
     */
    VBFloat VBObjectFile2DTransitionGetScaleValue(VBObjectFile2DTransition* _transition, VBFloat _time);
    
    /**
     @brief
     @param _transition VBObjectFile2DTransition
     @param _time
     */
    VBFloat VBObjectFile2DTransitionGetColorValue(VBObjectFile2DTransition* _transition, VBFloat _time);
    
    /**
     @brief
     @param
     */
    void _VBObjectFile2DTransitionResetBezier(VBArrayVector* _bezier);
    
    /**
     @brief
     @param _transition VBObjectFile2DTransition
     */

    void _VBObjectFile2DTransitionSetBezier(VBArrayVector* _bezier, VBULong _bezier_vector_length, VBVector2D* _bezier_vector);
    
    /**
     @brief
     @param _transition VBObjectFile2DTransition
     */
    VBSpline2DBezierCubic* _VBObjectFile2DTransitionGetCurrentBezier(VBArrayVector* _bezier, VBFloat _time);
    
    /**
     @brief
     @param _transition VBObjectFile2DTransition
     */
    VBFloat _VBObjectFile2DTransitionGetValue(VBArrayVector* _bezier, VBFloat _time);
    
#ifdef __cplusplus
}
#endif

#endif
