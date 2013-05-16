/**
 @file IO/VBObjectFile2DFrame.h
 @brief VBEngine의 VBObjectFile2DFrame 구조체타입과 여러 함수들.
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

#ifndef __VBObjectFile2DFrame_H__
#define __VBObjectFile2DFrame_H__

#include "../VBType.h"
#include "VBObjectFile2DKeyFrame.h"
#include "../Util/VBArrayVector.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @brief VBObjectFile2DFrame 관련 구조체 타입
     */
    typedef struct VBObjectFile2DFrame VBObjectFile2DFrame;
    
    /**
     @brief @brief VBObjectFile2DFrame 관련 구조체

     */
    struct VBObjectFile2DFrame {
        
        VBULong total_frame;
        /*!
         element 정보
         */
        VBArrayVector* key_frame;
    };
    
    /**
     @brief VBObjectFile2DFrame의 메모리를 할당합니다. 
     @return _frame 메모리가 할당된 VBObjectFile2DFrame을 반환합니다. 
     */
    VBObjectFile2DFrame* VBObjectFile2DFrameAlloc(void);
    
    /**
     @brief VBObjectFile2DFrame의 메모리를 초기화합니다.
     @param _frame 메모리가 할당된 VBObjectFile2DFrame*
     @return _frame 메모리가 초기화된 VBObjectFile2DFrame를 반환합니다. 
     */
    VBObjectFile2DFrame* VBObjectFile2DFrameInit(VBObjectFile2DFrame* _frame);
    
    /**
     @brief VBObjectFile2DFrame의 메모리를 해제합니다. 
     @param _frame 메모리가 할당된 VBObjectFile2DFrame**
     */
    void VBObjectFile2DFrameFree(VBObjectFile2DFrame** _frame);
    
    VBULong VBObjectFile2DFrameGetTotalFrame(VBObjectFile2DFrame* _frame);
    
    VBArrayVector* VBObjectFile2DFrameGetKeyFrames(VBObjectFile2DFrame* _frame);

#ifdef __cplusplus
}
#endif

#endif