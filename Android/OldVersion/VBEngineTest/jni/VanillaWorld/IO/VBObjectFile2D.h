/**
 @file IO/VBObjectFile2D.h
 @brief VBEngine의 VBObjectFile2D 구조체타입과 여러 함수들.
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

#ifndef __ObjectFile2D_H__
#define __ObjectFile2D_H__

#include "../VBType.h"
#include "VBSystem.h"
#include "../Core/VBString.h"
#include "../Core/VBArrayVector.h"
#include "../Core/VBArrayList.h"
#include "VBFile.h"
#include "VBObjectFile2DLibrary.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @brief VBOjbectFile2D관련 구조체 타입
     */
    typedef struct VBObjectFile2D VBObjectFile2D;
    
    /**
     @brief VBOjbectFile2D관련 구조체
     */
    struct VBObjectFile2D {
        /*!
         VBObject2D의 파일
         */
        VBFile* file;
        
        /*!
         라이브러리 이름 아이디 정보
         */
        VBArrayVector* library_name_id;
        /*!
         라이브러리 정보
         */
        VBArrayVector* library;
        VBArrayVector* library_bitmap;
        VBArrayList* library_graphic;
        VBArrayList* library_movie_clip;
        
        VBArrayList* frame;
        VBArrayList* key_frame;
        VBArrayList* element;
        VBArrayList* element_bitmap;
        VBArrayList* element_graphic;
        VBArrayList* element_movie_clip;
        
        VBArrayList* transition;
        
        VBFloat frame_rate;
        VBLong uv_w, uv_h, fl_w, fl_h;
    };
	
    /**
     @brief VBObjectFile2D의 메모리를 할당합니다. 
     @return _obj 메모리가 할당된 VBObjectFile2D를 반환합니다. 
     */
    VBObjectFile2D* VBObjectFile2DAlloc(void);
    
    /**
     @brief VBObjectFile2D를 초기화합니다. 
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @return 초기환된 VBObjectFile2D* 를 반환합니다.
     */
    VBObjectFile2D* VBObjectFile2DInit(VBObjectFile2D* _obj2D);
    VBObjectFile2D* VBObjectFile2DInitAndLoad(VBObjectFile2D* _obj2D, VBString* _path);
    
    /**
     @brief VBObjectFile2D의 메모리를 해제합니다. 
     
     기존에 존재하던 VBObjectFile2D의 각각의 요소들(file, library_name_id, library, bitmap)의\n
     메모리를 해제합니다. 
     
     @param _obj2D 메모리가 할당된 VBObjectFile2D**
     */
    void VBObjectFile2DFree(VBObjectFile2D** _obj2D);
    
    /**
     @brief VBObjectFile2D을 로드합니다. 
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _path VBObjectFile2D의 파일 경로
     */
    void VBObjectFile2DLoad(VBObjectFile2D* _obj2D, VBString* _path);
    
    /**
     @brief VBObjectFile2D의 library_name_id를 name을 이용하여 구합니다. 
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @return library_name_id를 반환합니다. 
     */
    VBObjectFile2DLibraryNameID* VBObjectFile2DGetLibraryNameIDByName(VBObjectFile2D* _obj2D, VBString* _name);
    
    /**
     @brief VBObjectFile2D의 library_name_id를 id를 이용하여 구합니다. 
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @return library_name_id를 반환합니다. 
     */
    VBObjectFile2DLibraryNameID* VBObjectFile2DGetLibraryNameIDByID(VBObjectFile2D* _obj2D, VBULong _id);
    
    /**
     @brief VBObjectFile2D의 library_name_id의 길이를 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @return library_name_id의 길이를 반환합니다.
     */
    VBULong VBObjectFile2DGetLibraryNameIDLength(VBObjectFile2D* _obj2D);
    
    /**
     @brief VBObjectFile2D의 _library_name의 위치를 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @return library_name의 위치를 반환합니다.
     */
    VBObjectFile2DLibraryNameID* VBObjectFile2DGetLibraryNameAt(VBObjectFile2D* _obj2D, VBULong _at);
    
    /**
     @brief VBObjectFile2D의 libraray의 길이를 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @return libraray의 길이를 반환합니다.
     */
    VBULong VBObjectFile2DGetLibraryLength(VBObjectFile2D* _obj2D);
    
    /**
     @brief VBObjectFile2D의 bitmap의 길이를 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @return library bitmap의 길이를 반환합니다.
     */
    VBULong VBObjectFile2DGetLibraryBitmapLength(VBObjectFile2D* _obj2D);
    
    /**
     @brief VBObjectFile2D의 graphic의 길이를 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @return library graphic의 길이를 반환합니다.
     */
    VBULong VBObjectFile2DGetLibraryGraphicLength(VBObjectFile2D* _obj2D);
    
    /**
     @brief VBObjectFile2D의 movieclip의 길이를 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @return movieclip의 길이를 반환합니다.
     */
    VBULong VBObjectFile2DGetLibraryMovieClipLength(VBObjectFile2D* _obj2D);
    
    /**
     @brief VBObjectFile2D의 library의 위치를 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _at 검색할 위치
     @return library의 위치를 반환합니다.
     */
    VBObjectFile2DLibrary* VBObjectFile2DGetLibraryAt(VBObjectFile2D* _obj2D, VBULong _at);
    
    /**
     @brief VBObjectFile2D의 bitmap의 위치를 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _at 검색할 위치
     @return bitmap의 위치를 반환합니다.
     */
    VBObjectFile2DLibraryBitmap* VBObjectFile2DGetLibraryBitmapAt(VBObjectFile2D* _obj2D, VBULong _at);
    
    /**
     @brief VBObjectFile2D의 graphic의 위치를 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _at 검색할 위치
     @return graphic의 위치를 반환합니다.
     */
    VBObjectFile2DLibraryGraphic* VBObjectFile2DGetLibraryGraphicAt(VBObjectFile2D* _obj2D, VBULong _at);
    
    /**
     @brief VBObjectFile2D의 movie clip의 위치를 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _at 검색할 위치     
     @return movie clip의 위치를 반환합니다.
     */
    VBObjectFile2DLibraryMovieClip* VBObjectFile2DGetLibraryMovieClipAt(VBObjectFile2D* _obj2D, VBULong _at);
    
    /**
     @brief VBObjectFile2D의 이름을 이용하여 library를 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _name 검색할 이름
     @return library를 반환합니다.
     */
    VBObjectFile2DLibrary* VBObjectFile2DGetLibraryByName(VBObjectFile2D* _obj2D, VBString* _name);
    
    /**
     @brief VBObjectFile2D의 이름을 이용하여 bitmap을 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _name 검색할 이름
     @return bitmap를 반환합니다.
     */
    VBObjectFile2DLibraryBitmap* VBObjectFile2DGetLibraryBitmapByName(VBObjectFile2D* _obj2D, VBString* _name);
    
    /**
     @brief VBObjectFile2D의 이름을 이용하여 graphic을 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _name 검색할 이름
     @return graphic를 반환합니다.
     */
    VBObjectFile2DLibraryGraphic* VBObjectFile2DGetLibraryGraphicByName(VBObjectFile2D* _obj2D, VBString* _name);
    
    /**
     @brief VBObjectFile2D의 이름을 이용하여 movie clip을 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _name 검색할 이름
     @return movie clip을 반환합니다.
     */
    VBObjectFile2DLibraryMovieClip* VBObjectFile2DGetLibraryMovieClipByName(VBObjectFile2D* _obj2D, VBString* _name);
    
    /**
     @brief VBObjectFile2D의 아이디를 이용하여 library을 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _name 검색할 아이디
     @return library를 반환합니다.
     */
    VBObjectFile2DLibrary* VBObjectFile2DGetLibraryByID(VBObjectFile2D* _obj2D, VBULong _id);
    
    /**
     @brief VBObjectFile2D의 아이디를 이용하여 bitmap을 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _name 검색할 아이디
     @return library를 반환합니다.
     */
    VBObjectFile2DLibraryBitmap* VBObjectFile2DGetLibraryBitmapByID(VBObjectFile2D* _obj2D, VBULong _id);
    
    /**
     @brief VBObjectFile2D의 아이디를 이용하여 grahpic을 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _name 검색할 아이디
     @return graphic를 반환합니다.
     */
    VBObjectFile2DLibraryGraphic* VBObjectFile2DGetLibraryGraphicByID(VBObjectFile2D* _obj2D, VBULong _id);
    
    /**
     @brief VBObjectFile2D의 아이디를 이용하여 movie clip을 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _name 검색할 아이디
     @return movie clip를 반환합니다.
     */
    VBObjectFile2DLibraryMovieClip* VBObjectFile2DGetLibraryMovieClipByID(VBObjectFile2D* _obj2D, VBULong _id);
    
    /**
     @brief VBObjectFile2D의 name_id를 이용하여 library을 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _name 검색할 name_id
     @return library를 반환합니다.
     */
    VBObjectFile2DLibrary* VBObjectFile2DGetLibraryByNameID(VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _name_id);
    
    /**
     @brief VBObjectFile2D의 name_id를 이용하여 bitmap을 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _name 검색할 name_id
     @return bitmap를 반환합니다.    
     */
    VBObjectFile2DLibraryBitmap* VBObjectFile2DGetLibraryBitmapByNameID(VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _name_id);
    
    /**
     @brief VBObjectFile2D의 name_id를 이용하여 graphic을 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _name 검색할 name_id
     @return graphic를 반환합니다.     
     */
    VBObjectFile2DLibraryGraphic* VBObjectFile2DGetLibraryGraphicByNameID(VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _name_id);
    
    /**
     @brief VBObjectFile2D의 name_id를 이용하여 movie clip을 구합니다.
     @param _obj2D 메모리가 할당된 VBObjectFile2D*
     @param _name 검색할 name_id     
     @return movie clip를 반환합니다.     
     */
    VBObjectFile2DLibraryMovieClip* VBObjectFile2DGetLibraryMovieClipByNameID(VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _name_id);
    
    VBFloat VBObjectFile2DGetFrameRate(VBObjectFile2D* _obj2D);
    
    VBLong VBObjectFile2DGetStageWidth(VBObjectFile2D* _obj2D);
    VBLong VBObjectFile2DGetStageHeight(VBObjectFile2D* _obj2D);
    
    VBLong VBObjectFile2DGetDefaultTextureWidth(VBObjectFile2D* _obj2D);
    VBLong VBObjectFile2DGetDefaultTextureHeight(VBObjectFile2D* _obj2D);
    
#ifdef __cplusplus
}
#endif

#endif