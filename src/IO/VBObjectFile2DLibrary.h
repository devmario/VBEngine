/**
 @file IO/VBObjectFile2DLibrary.h
 @brief VBEngine의 VBObjectFile2DLibrary 구조체타입과 여러 함수들.
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

#ifndef __VBObjectFile2DLibrary_H__
#define __VBObjectFile2DLibrary_H__

#include "../VBType.h"
#include "VBObjectFile2DLibraryNameID.h"
#include "VBObjectFile2DFrame.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @brief VBObjectFile2DLibrary의 구조체 타입
     */
    typedef struct VBObjectFile2DLibrary VBObjectFile2DLibrary;
    
    /**
     @enum VBObjectFile2DLibrary의 타입
     @brief VBObjectFile2DLibrary의 타입 열거
     */
    enum {
        VBObjectFile2DLibraryType_None          =   0x00,
        VBObjectFile2DLibraryType_Bitmap        =   0x01,
        VBObjectFile2DLibraryType_Graphic       =   0x02,
        VBObjectFile2DLibraryType_MovieClip     =   0x03
    };
    
    /**
     @brief VBObjectFile2DLibrary의 타입
     */
    typedef VBUChar VBObjectFile2DLibraryType;
    
    /**
     @brief VBObjectFile2DLibraryBitmap의 구조체 타입 
     */
    typedef struct VBObjectFile2DLibraryBitmap VBObjectFile2DLibraryBitmap;
    
    /**
     @brief VBObjectFile2DLibraryGraphic의 구조체 타입
     */
    typedef struct VBObjectFile2DLibraryGraphic VBObjectFile2DLibraryGraphic;
    
    /**
     @brief VBObjectFile2DLibraryMovieClip의 구조체 타입
     */
    typedef struct VBObjectFile2DLibraryMovieClip VBObjectFile2DLibraryMovieClip;
    
    /**
     @brief VBObjectFile2DLibrary의 구조체
     */
    struct VBObjectFile2DLibrary {
        /*!
         library name ID
         */
        VBObjectFile2DLibraryNameID* name_id;
        
        /*!
         library type
         */
        VBObjectFile2DLibraryType type;
        /*!
         library
         */
        void* library;
    };
    
    /**
     @brief VBObjectFile2DLibraryBitmap의 구조체
     */
    struct VBObjectFile2DLibraryBitmap {
        /*!
         uv파일 정보 길이
         */
        VBULong uv_info_length;
        /*!
         uv파일 정보
         */
        VBVector2D* uv_info;
    };
    
    /**
     @brief VBObjectFile2DLibraryGraphic의 구조체
     */
    struct VBObjectFile2DLibraryGraphic {
        /*!
         프레임
         */
        VBObjectFile2DFrame* frame;
    };
    
    /**
     @brief VBObjectFile2DLibraryMovieClip의 구조체
     */
    struct VBObjectFile2DLibraryMovieClip {
        /*!
         프레임
         */
        VBObjectFile2DFrame* frame;
    };
    
    /**
     @brief VBObjectFile2DLibrary의 메모리를 할당합니다. 
     */
    VBObjectFile2DLibrary* VBObjectFile2DLibraryAlloc(void);
    
    /**
     @brief VBObjectFile2DLibrary의 메모리를 초기화합니다. 
     @param _library 메로리가 할당된 VBObjectFile2DLibrary*
     @return 메모리가 초기화된 VBObjectFile2DLibrary를 반환합니다.   
     */
    VBObjectFile2DLibrary* VBObjectFile2DLibraryInit(VBObjectFile2DLibrary* _library);
    
    /**
     @brief VBObjectFile2DLibrary의 메모리를 데이터와 함께 초기화합니다. 
     @param _library 메로리가 할당된 VBObjectFile2DLibrary*  
     @param _name_id 라이브러리 이름 아이디
     @param _type 라이브러리 타입
     @param _library_base 라이브러리 
     @return 메모리가 초기화된 VBObjectFile2DLibrary를 반환합니다. 
     */
    VBObjectFile2DLibrary* VBObjectFile2DLibraryInitWithType(VBObjectFile2DLibrary* _library, VBObjectFile2DLibraryNameID* _name_id, VBObjectFile2DLibraryType _type, void* _library_base);
    
    /**
     @brief VBObjectFile2DLibrary의 메모리를 해제합니다. 
     @param _library 메로리가 할당된 VBObjectFile2DLibrary** 
     */
    void VBObjectFile2DLibraryFree(VBObjectFile2DLibrary** _library);
    
    /**
     @brief VBObjectFile2DLibraryBitmap의 메모리를 할당합니다. 
     @return 메모리가 할당된 VBObjectFile2DLibraryBitmap을 반환합니다.
     */
    VBObjectFile2DLibraryBitmap* VBObjectFile2DLibraryBitmapAlloc(void);
    
    /**
     @brief VBObjectFile2DLibraryBitmap의 메모리를 초기화합니다. 
     @param _bitmap 메모리가 할당된 VBObjectFile2DLibraryBitmap*
     @return 초기화된 VBObjectFile2DLibraryMovieClip를 반환합니다. 
     */
    VBObjectFile2DLibraryBitmap* VBObjectFile2DLibraryBitmapInit(VBObjectFile2DLibraryBitmap* _bitmap);
    
    /**
     @brief VBObjectFile2DLibraryMovieClip의 메모리를 데이터와 함께 초기화합니다. 
     @param _bitmap 메모리가 할당된 VBObjectFile2DLibraryBitmap*
     @param _uv_info_length textcoord 길이
     @param _uv_info textcoord
     @return 초기화된 VBObjectFile2DLibraryMovieClip를 반환합니다. 
     */
    VBObjectFile2DLibraryBitmap* VBObjectFile2DLibraryBitmapInitWithData(VBObjectFile2DLibraryBitmap* _bitmap, VBULong _uv_info_length, VBVector2D* _uv_info);
    
    /**
     @brief VBObjectFile2DLibraryBitmap의 uv파일 정보 길이를 구합니다.
     @param _bitmap 메모리가 할당된 VBObjectFile2DLibraryBitmap*
     @return uv파일 정보 길이를 반환합니다.
     */
    VBULong VBObjectFile2DLibraryBitmapGetUVInfoLength(VBObjectFile2DLibraryBitmap* _bitmap);
    
    /**
     @brief VBObjectFile2DLibraryBitmap의 uv파일 정보를 구합니다.
     @param _bitmap 메모리가 할당된 VBObjectFile2DLibraryBitmap*
     @return uv파일 정보를 반환합니다.
     */
    VBVector2D* VBObjectFile2DLibraryBitmapGetUVInfo(VBObjectFile2DLibraryBitmap* _bitmap);
    
    /**
     @brief VBObjectFile2DLibraryMovieClip의 메모리를 해제합니다. 
     @param _bitmap 메모리가 할당된 VBObjectFile2DLibraryBitmap**
     */
    void VBObjectFile2DLibraryBitmapFree(VBObjectFile2DLibraryBitmap** _bitmap);
    
    /**
     @brief VBObjectFile2DLibraryGraphic의 메모리를 할당합니다. 
     @return 메모리가 할당된 VBObjectFile2DLibraryGraphic를 반환합니다.
     */
    VBObjectFile2DLibraryGraphic* VBObjectFile2DLibraryGraphicAlloc(void);
    
    /**
     @brief VBObjectFile2DLibraryGraphic의 메모리를 초기화합니다. 
     @param _graphic 메모리가 할당된 VBObjectFile2DLibraryGraphic*
     @return 메모리가 초기화된 VBObjectFile2DLibraryGraphicInit를 반환합니다. 
     */
    VBObjectFile2DLibraryGraphic* VBObjectFile2DLibraryGraphicInit(VBObjectFile2DLibraryGraphic* _graphic);
    
    /**
     @brief VBObjectFile2DLibraryGraphic의 메모리를 데이터와 함께 초기화합니다.
     @param _graphic 메모리가 할당된 VBObjectFile2DLibraryGraphic*
     @param _frame frame
     @return 메모리가 초기화된 VBObjectFile2DLibraryGraphicInit를 반환합니다. 
     */
    VBObjectFile2DLibraryGraphic* VBObjectFile2DLibraryGraphicInitWithData(VBObjectFile2DLibraryGraphic* _graphic, VBObjectFile2DFrame* _frame);
    
    /**
     @brief VBObjectFile2DLibraryGraphic의 프레임을 구합니다.
     @param _graphic 메모리가 할당된 VBObjectFile2DLibraryGraphic*
     @return VBObjectFile2DLibraryGraphic의 프레임을 반환합니다.
     */
    VBObjectFile2DFrame* VBObjectFile2DLibraryGraphicGetFrame(VBObjectFile2DLibraryGraphic* _graphic);
    
    /**
     @brief VBObjectFile2DLibraryGraphic의 메모리르 해제합니다.
     @param _graphic 메모리가 할당된 VBObjectFile2DLibraryGraphic**
     */
    void VBObjectFile2DLibraryGraphicFree(VBObjectFile2DLibraryGraphic** _graphic);
    
    /**
     @brief VBObjectFile2DLibraryMovieClip의 메모리를 할당합니다. 
     @return 메모리가 할당된 VBObjectFile2DLibraryGraphic를 반환합니다.
     */
    VBObjectFile2DLibraryMovieClip* VBObjectFile2DLibraryMovieClipAlloc(void);
    
    /**
     @brief VBObjectFile2DLibraryMovieClip의 메모리를 초기화합니다. 
     @param _movie_clip 메모리가 할당된 VBObjectFile2DLibraryMovieClip*
     */
    VBObjectFile2DLibraryMovieClip* VBObjectFile2DLibraryMovieClipInit(VBObjectFile2DLibraryMovieClip* _movie_clip);
    
    /**
     @brief VBObjectFile2DLibraryMovieClip의 메모리를 데이터와 함께 초기화합니다. 
     @param _movie_clip 메모리가 할당된 VBObjectFile2DLibraryMovieClip*
     @param _frame frame
     @return 초기화된 VBObjectFile2DLibraryMovieClip를 반환합니다. 
     */
    VBObjectFile2DLibraryMovieClip* VBObjectFile2DLibraryMovieClipInitWithData(VBObjectFile2DLibraryMovieClip* _movie_clip,  VBObjectFile2DFrame* _frame);
    
    /**
     @brief VBObjectFile2DLibraryMovieClip의 프레임을 구합니다.
     @param _movie_clip 메모리가 할당된 VBObjectFile2DLibraryMovieClip*
     @return VBObjectFile2DLibraryMovieClip의 프레임을 반환합니다.
     */
    VBObjectFile2DFrame* VBObjectFile2DLibraryMovieClipGetFrame(VBObjectFile2DLibraryMovieClip* _movie_clip);
    
    /**
     @brief VBObjectFile2DLibraryMovieClip의 메모리를 해제합니다. 
     @param _movie_clip 메모리가 할당된 VBObjectFile2DLibraryMovieClip*
     */
    void VBObjectFile2DLibraryMovieClipFree(VBObjectFile2DLibraryMovieClip** _movie_clip);
    
    /**
     @brief VBObjectFile2DLibrary의 name_id를 구합니다.
     @param _library VBObjectFile2DLibrary*
     @return VBObjectFile2DLibrary의 name_id를 반환합니다. 
     */
    VBObjectFile2DLibraryNameID* VBObjectFile2DLibraryGetNameID(VBObjectFile2DLibrary* _library);
    
    /**
     @brief VBObjectFile2DLibrary의 타입을 구합니다.
     @param _library VBObjectFile2DLibrary*
     @return VBObjectFile2DLibrary의 타입을 반환합니다.
     */
    VBObjectFile2DLibraryType VBObjectFile2DLibraryGetType(VBObjectFile2DLibrary* _library);
    
    /**
     @brief VBObjectFile2DLibrary의 베이스를 구합니다.
     @param _library VBObjectFile2DLibrary*
     */
    void* VBObjectFile2DLibraryGetBase(VBObjectFile2DLibrary* _library);
    
#ifdef __cplusplus
}
#endif

#endif