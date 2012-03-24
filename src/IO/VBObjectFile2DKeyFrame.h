/**
 @file IO/VBObjectFile2DKeyFrame.h
 @brief VBEngine의 VBObjectFile2DKeyFrame 구조체타입과 여러 함수들.
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

#ifndef __VBObjectFile2DKeyFrame_H__
#define __VBObjectFile2DKeyFrame_H__

#include "../VBType.h"
#include "VBObjectFile2DKeyFrameElement.h"
#include "VBObjectFile2DLibraryNameID.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @brief VBObjectFile2DKeyFrame의 구조체 타입
     */
    typedef struct VBObjectFile2DKeyFrame VBObjectFile2DKeyFrame;
    
    /**
     @brief VBObjectFile2DKeyFrame의 구조체
     */
    struct VBObjectFile2DKeyFrame {
        /*!
         library id
         */
        VBObjectFile2DLibraryNameID* library_id;
        /*!
         depth
         */
        VBULong depth;
        /*!
         시작 프레임
         */
        VBULong begin_frame;
        /*!
         끝 프레임
         */
        VBULong end_frame;
        
        VBMatrix2DWrapper* none_real_time_matrix;
        VBColorRGBA* none_real_time_color;
        /*!
         element(bitmap, graphic, movie clip)
         */
        VBObjectFile2DKeyFrameElement* element;
    };
    
    VBObjectFile2DLibraryNameID* VBObjectFile2DKeyFrameGetLibraryNameID(VBObjectFile2DKeyFrame* _key_frame);
    
    /**
     @brief VBObjectFile2DKeyFrame의 메모리를 할당합니다.
     @return 메모리가 할당된 VBObjectFile2DKeyFrame를 반환합니다.
     */
    VBObjectFile2DKeyFrame* VBObjectFile2DKeyFrameAlloc(void);
    
    /**
     @brief VBObjectFile2DKeyFrame의 메모리를 초기화 합니다.
     @param _key_frame 메모리가 할당된 VBObjectFile2DKeyFrame
     @return 메모리가 초기화된 VBObjectFile2DKeyFrame를 반환합니다.
     */
    VBObjectFile2DKeyFrame* VBObjectFile2DKeyFrameInit(VBObjectFile2DKeyFrame* _key_frame);
    
    /**
     @brief VBObjectFile2DKeyFrame의 메모리를 데이터와 함께 초기화 합니다.
     @param _key_frame 메모리가 할당된 VBObjectFile2DKeyFrame
     @param _library_id 라이브러리 아이디
     @param _begin_frame 시작 프레임
     @param _end_frame 끝 프레임
     @param _element element(bitmap, graphic, movie clip)
     @return 메모리가 초기화된 VBObjectFile2DKeyFrame를 반환합니다.
     */
    VBObjectFile2DKeyFrame* VBObjectFile2DKeyFrameInitWithData(VBObjectFile2DKeyFrame* _key_frame, VBObjectFile2DLibraryNameID* _library_id, VBULong _begin_frame, VBULong _end_frame, VBObjectFile2DKeyFrameElement* _element);
    
    /**
     @brief VBObjectFile2DKeyFrame의 메모리를 해제합니다.
     @param _key_frame 메모리가 할당된 VBObjectFile2DKeyFrame
     */
    void VBObjectFile2DKeyFrameFree(VBObjectFile2DKeyFrame** _key_frame);
    
    /**
     @brief VBObjectFile2DKeyFrame의 시작 프레임을 구합니다.
     @param _key_frame 메모리가 할당된 VBObjectFile2DKeyFrame
     @return 시작 프레임을 반환합니다.
     */
    VBULong VBObjectFile2DKeyFrameGetBeginFrame(VBObjectFile2DKeyFrame* _key_frame);
    
    /**
     @brief VBObjectFile2DKeyFrame의 끝 프레임을 구합니다.
     @param _key_frame 메모리가 할당된 VBObjectFile2DKeyFrame
     @return 끝 프레임을 반환합니다.
     */
    VBULong VBObjectFile2DKeyFrameGetEndFrame(VBObjectFile2DKeyFrame* _key_frame);
    
    /**
     @brief VBObjectFile2DKeyFrame의 element을 구합니다.
     @param _key_frame
     @return element를 반환합니다.
     */
    VBObjectFile2DKeyFrameElement* VBObjectFile2DKeyFrameGetElement(VBObjectFile2DKeyFrame* _key_frame);

#ifdef __cplusplus
}
#endif

#endif