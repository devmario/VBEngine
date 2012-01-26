/**
 @file IO/VBObjectFile2DTexcoord.h
 @brief VBEngine의 VBObjectFile2DTexcoord 구조체타입과 여러 함수들.
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

#ifndef __VBObjectFile2DTexcoord_H__
#define __VBObjectFile2DTexcoord_H__

#include "../VBType.h"
#include "VBObjectFile2DLibraryNameID.h"
#include "../Core/VBVector2D.h"

#ifdef __cplusplus
extern "C" {
#endif
	

    /**
     @brief VBObjectFile2DTexcoord 관련 구조체 타입
     */
    typedef struct VBObjectFile2DTexcoord VBObjectFile2DTexcoord;
    
    /**
     @brief VBObjectFile2DTexcoord 관련 구조체
     */
    struct VBObjectFile2DTexcoord {
        /*!
         libraryNameID
         */
        VBObjectFile2DLibraryNameID* libraryNameID;
        /*!
         texcoord_length
         */
        VBULong texcoord_length;
        /*!
         texcoord
         */
        VBVector2D* texcoord;
    };
    
    /**
     @brief VBObjectFile2DTexcoord의 메모리를 할당합니다. 
     @return 메모리가 할당된 VBObjectFile2DTexcoord를 반환합니다. 
     */
    VBObjectFile2DTexcoord* VBObjectFile2DTexcoordAlloc(void);
    
    /**
     @brief VBObjectFile2DTexcoord의 메모리를 초기화 합니다. 
     @param _texcoord 메모리가 할당된 VBObjectFile2DTexcoord*
     @return 메모리가 초기화된 VBObjectFile2DTexcoord를 반환합니다. 
     */
    VBObjectFile2DTexcoord* VBObjectFile2DTexcoordInit(VBObjectFile2DTexcoord* _texcoord);
    
    /**
     @brief VBObjectFile2DTexcoord의 메모리를 name id와 texcoor vector와 함께 초기화합니다. 
     @param _texcoord 메모리가 할당된 VBObjectFile2DTexcoord*
     @param _name_id
     @param _texcoord_vector_length
     @parma _texcoord_vector
     @return 
     */
    VBObjectFile2DTexcoord* VBObjectFile2DTexcoordInitWithNameIDAndTexcoordVector(VBObjectFile2DTexcoord* _texcoord,
                                                                                  VBObjectFile2DLibraryNameID* _name_id,
                                                                                  VBULong _texcoord_vector_length,
                                                                                  VBVector2D* _texcoord_vector);
    /**
     @brief VBObjectFile2DTexcoord의 메모리를 해제합니다. 
     @param _texcoord 메모리가 할당된 VBObjectFile2DTexcoord**
     */
    void VBObjectFile2DTexcoordFree(VBObjectFile2DTexcoord** _texcoord);
    
#ifdef __cplusplus
}
#endif

#endif