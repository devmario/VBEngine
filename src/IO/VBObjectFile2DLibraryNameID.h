/**
 @file IO/VBObjectFile2DLibraryNameID.h
 @brief VBEngine의 VBObjectFile2DLibraryNameID 구조체타입과 여러 함수들.
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

#ifndef __VBObjectFile2DLibraryNameID_H__
#define __VBObjectFile2DLibraryNameID_H__

#include "../VBType.h"
#include "../Util/VBString.h"

#ifdef __cplusplus
extern "C" {
#endif
	
    /**
     @brief VBObjectFile2DLibraryNameID 관련 구조체 타입
     */
    typedef struct VBObjectFile2DLibraryNameID VBObjectFile2DLibraryNameID;
    
    /**
     @brief VBObjectFile2DLibraryNameID 관련 구조체
     */
    struct VBObjectFile2DLibraryNameID {
        /*!
         라이브러리 id
         */
        VBULong libraryID;
        /*!
         라이브러리 name
         */
        VBString* libraryName;
    };
    
    /**
     @brief VBObjectFile2DLibraryNameID의 메모리를 할당합니다. 
     @return 메모리가 할당된 VBObjectFile2DLibraryNameID를 반환합니다. 
     */
    VBObjectFile2DLibraryNameID* VBObjectFile2DLibraryNameIDAlloc(void);
    
    /**
     @brief VBObjectFile2DLibraryNameID의 메모리를 초기화합니다. 
     @param _name_id 메모리가 할당된 VBObjectFile2DLibraryNameID*
     @return
     */VBObjectFile2DLibraryNameID* VBObjectFile2DLibraryNameIDInit(VBObjectFile2DLibraryNameID* _name_id);
    
    /**
     @brief VBObjectFile2DLibraryNameID의 메모리를 이름과 함께 초기화합니다.  
     @param _name_id 메모리가 할당된 VBObjectFile2DLibraryNameID*     @return
     */VBObjectFile2DLibraryNameID* VBObjectFile2DLibraryNameIDInitWithIDAndName(VBObjectFile2DLibraryNameID* _name_id, VBULong _id, VBString* _name);
    
    /**
     @brief VBObjectFile2DLibraryNameID의 메모리를 해제합니다. 
     @param _name_id 메모리가 할당된 VBObjectFile2DLibraryNameID*
     @return 메모리가 할당된 VBObjectFile2DLibraryNameID*
     */void VBObjectFile2DLibraryNameIDFree(VBObjectFile2DLibraryNameID** _name_id);
    
    /**
     @brief VBObjectFile2DLibraryNameID의 라이브러리 id를 구합니다. 
     @param _name_id 메모리가 할당된 VBObjectFile2DLibraryNameID*
     @return _library_id 라이브러리 id를 반환합니다. 
     */VBULong VBObjectFile2DLibraryNameIDGetID(VBObjectFile2DLibraryNameID* _name_id);
    
    /**
     @brief VBObjectFile2DLibraryNameID의 라이브러리 name를 구합니다. 
     @param _name_id 메모리가 할당된 VBObjectFile2DLibraryNameID*
     @return _library_name 라이브러리 name을 반환합니다. 
     */VBString* VBObjectFile2DLibraryNameIDGetName(VBObjectFile2DLibraryNameID* _name_id);
    
#ifdef __cplusplus
}
#endif

#endif