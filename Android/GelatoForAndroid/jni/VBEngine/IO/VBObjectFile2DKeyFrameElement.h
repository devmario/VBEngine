/**
 @file IO/VBObjectFile2DKeyFrameElement.h
 @brief VBEngine의 VBObjectFile2DKeyFrameElement 구조체타입과 여러 함수들.
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

#ifndef __VBObjectFile2DKeyFrameElement_H__
#define __VBObjectFile2DKeyFrameElement_H__

#include "../VBType.h"
#include "../Core/Linear/VBVector2D.h"
#include "../Core/Color/VBColorRGBA.h"
#include "../Core/Linear/VBMatrix2DWrapper.h"
#include "VBObjectFile2DTransition.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @enum 프레임 요소 타입 열거형
     */
    enum {
        VBObjectFile2DKeyFrameElementType_None         =   0x00,
        VBObjectFile2DKeyFrameElementType_Bitmap       =   0x01,
        VBObjectFile2DKeyFrameElementType_Graphic      =   0x02,
        VBObjectFile2DKeyFrameElementType_MovieClip    =   0x04
    };
    
    /**
     @brief VBObjectFile2DKeyFrameElementType의 타입
     */
    typedef VBUChar VBObjectFile2DKeyFrameElementType;
    /**
     @brief VBObjectFile2DKeyFrameElementType의 구조체 타입
     */
    typedef struct VBObjectFile2DKeyFrameElement VBObjectFile2DKeyFrameElement; 
    /**
     @brief VBObjectFile2DKeyFrameElementBitmap의 구조체 타입
     */
    typedef struct VBObjectFile2DKeyFrameElementBitmap VBObjectFile2DKeyFrameElementBitmap;
    /**
     @brief VBObjectFile2DKeyFrameElementGraphic의 구조체 타입
     */
    typedef struct VBObjectFile2DKeyFrameElementGraphic VBObjectFile2DKeyFrameElementGraphic;
    /**
     @brief VBObjectFile2DKeyFrameElementMovieClip의 구조체 타입
     */
    typedef struct VBObjectFile2DKeyFrameElementMovieClip VBObjectFile2DKeyFrameElementMovieClip;
   
    /**
     @brief VBObjectFile2DKeyFrameElement의 구조체
     */
    struct VBObjectFile2DKeyFrameElement {
        /*!
         프레임 element 타입
         */
        VBObjectFile2DKeyFrameElementType element_type;
        /*!
         element
         */
        void* element;
    };
    
    /**
     @brief VBObjectFile2DKeyFrameElementBitmap의 구조체
     */
    struct VBObjectFile2DKeyFrameElementBitmap {
        /*!
         매트릭스 wrapper
         */
        VBMatrix2DWrapper matrix;
    };
    /**
     @brief VBObjectFile2DKeyFrameElementGraphic의 구조체
     */
    struct VBObjectFile2DKeyFrameElementGraphic {
        /*!
         obj 파일 변형 정보
         */
        VBObjectFile2DTransition* transition;
        /*!
         그래픽 element
         */
        VBObjectFile2DKeyFrameElementGraphic* next;
        
        /*!
         매트릭스 wrapper
         */
        VBMatrix2DWrapper matrix;
        
        /*!
         컬러
         */
        VBColorRGBA color;
    };
    
    /**
     @brief VBObjectFile2DKeyFrameElementMovieClip의 구조체
     */
    struct VBObjectFile2DKeyFrameElementMovieClip {
        /*!
         인스턴스 이름
         */
        VBString* instance_name;
        
        /*!
         obj파일 변형 정보
         */
        VBObjectFile2DTransition* transition;
        /*!
         무비클립 
         */
        VBObjectFile2DKeyFrameElementMovieClip* next;
        
        /*!
         매트릭스 wrapper
         */
        VBMatrix2DWrapper matrix;
        
        /*!
         컬러
         */
        VBColorRGBA color;
    };
    
    /**
     @brief VBObjectFile2DKeyFrameElement의 메모리를 할당합니다.
     @return 메모리가 할당된 VBObjectFile2DKeyFrameElement를 반환합니다.
     */
    VBObjectFile2DKeyFrameElement* VBObjectFile2DKeyFrameElementAlloc(void);
    
    /**
     @brief VBObjectFile2DKeyFrameElement의 메모리를 초기화합니다.
     @param _element 메모리가 할당된 VBObjectFile2DKeyFrameElement*
     @return 초기화된 VBObjectFile2DKeyFrameElement를 반환합니다.
     */
    VBObjectFile2DKeyFrameElement* VBObjectFile2DKeyFrameElementInit(VBObjectFile2DKeyFrameElement* _element);
    
    /**
     @brief VBObjectFile2DKeyFrameElement의 메모리를 타입 데이터와 함께 초기화합니다.
     @param _element 메모리가 할당된 VBObjectFile2DKeyFrameElement*
     @param _type 프레임 element타입 
     @param _element_base 
     @return 초기화된 VBObjectFile2DKeyFrameElement를 반환합니다. 
     */
    VBObjectFile2DKeyFrameElement* VBObjectFile2DKeyFrameElementInitWithType(VBObjectFile2DKeyFrameElement* _element, VBObjectFile2DKeyFrameElementType _type, void* _element_base);
    
    /**
     @brief VBObjectFile2DKeyFrameElement의 메모리를 해제합니다.
     @param _element 메모리가 할당된 VBObjectFile2DKeyFrameElement**
     */
    void VBObjectFile2DKeyFrameElementFree(VBObjectFile2DKeyFrameElement** _element);
    
    /**
     @brief VBObjectFile2DKeyFrameElement의 타입을 구합니다.
     @param _element 메모리가 할당된 VBObjectFile2DKeyFrameElement*
     @return 타입을 반환합니다.
     */
    VBObjectFile2DKeyFrameElementType VBObjectFile2DKeyFrameElementGetType(VBObjectFile2DKeyFrameElement* _element);
    
    /**
     @brief VBObjectFile2DKeyFrameElement의 기본 element를 구합니다.
     @param _element 메모리가 할당된 VBObjectFile2DKeyFrameElement*
     @return 기본 element를 반환합니다.
     */
    void* VBObjectFile2DKeyFrameElementGetBaseElement(VBObjectFile2DKeyFrameElement* _element);
    
    /**
     @brief VBObjectFile2DKeyFrameElementBitmap의 메모리를 할당합니다.
     @return 메모리가 할당된 VBObjectFile2DKeyFrameElementBitmap를 반환합니다.
     */
    VBObjectFile2DKeyFrameElementBitmap* VBObjectFile2DKeyFrameElementBitmapAlloc(void);
    
    /**
     @brief VBObjectFile2DKeyFrameElementBitmap의 메모리를 초기화 합니다.
     @param _bitmap 메모리가 할당된 VBObjectFile2DKeyFrameElementBitmap*
     @return 초기화된 VBObjectFile2DKeyFrameElementBitmap를 반환합니다.
     */
    VBObjectFile2DKeyFrameElementBitmap* VBObjectFile2DKeyFrameElementBitmapInit(VBObjectFile2DKeyFrameElementBitmap* _bitmap);
    
    /**
     @brief VBObjectFile2DKeyFrameElementBitmap의 메모리를 데이터와 함께 초기화 합니다.
     @param _bitmap 메모리가 할당된 VBObjectFile2DKeyFrameElementBitmap*
     @parma _matrix 매트릭스 wrapper
     @return 초기화된 VBObjectFile2DKeyFrameElementBitmap를 반환합니다.
     */
    VBObjectFile2DKeyFrameElementBitmap* VBObjectFile2DKeyFrameElementBitmapInitWithData(VBObjectFile2DKeyFrameElementBitmap* 
                                                                                         _bitmap, VBMatrix2DWrapper _matrix);
    
    /**
     @brief VBObjectFile2DKeyFrameElementBitmap의 메모리를 해제합니다.
     @param _bitmap 메모리가 할당된 VBObjectFile2DKeyFrameElementBitmap**
     */
    void VBObjectFile2DKeyFrameElementBitmapFree(VBObjectFile2DKeyFrameElementBitmap** _bitmap);
    
    /**
     @brief VBObjectFile2DKeyFrameElementGraphic의 메모리를 할당합니다.
     @return 메모리가 할당된 VBObjectFile2DKeyFrameElementGraphic를 반환합니다.
     */
    VBObjectFile2DKeyFrameElementGraphic* VBObjectFile2DKeyFrameElementGraphicAlloc(void);
    
    /**
     @brief VBObjectFile2DKeyFrameElementGraphic의 메모리를 초기화합니다.
     @param _graphic 메모리가 할당된 VBObjectFile2DKeyFrameElementGraphic*
     @return 초기화된 VBObjectFile2DKeyFrameElementGraphic를 반환합니다.
     */
    VBObjectFile2DKeyFrameElementGraphic* VBObjectFile2DKeyFrameElementGraphicInit(VBObjectFile2DKeyFrameElementGraphic* _graphic);
    
    /**
     @brief VBObjectFile2DKeyFrameElementGraphic의 메모리를 데이터와 함께 초기화합니다.
     @param _graphic 메모리가 할당된 VBObjectFile2DKeyFrameElementGraphic*
     @param _blend_mode 블랜딩 모드
     @param _transition transition
     @param _matrix 매트릭스 wrapper
     @param _color 컬러
     @return 초기화된 VBObjectFile2DKeyFrameElementGraphic를 반환합니다.
     */
    VBObjectFile2DKeyFrameElementGraphic* VBObjectFile2DKeyFrameElementGraphicInitWithData(VBObjectFile2DKeyFrameElementGraphic* _graphic, VBObjectFile2DTransition* _transition, VBMatrix2DWrapper _matrix, VBColorRGBA _color);
    
    /**
     @brief VBObjectFile2DKeyFrameElementGraphic의 매트릭스 wrapper를 구합니다.
     @param _graphic 메모리가 할당된 VBObjectFile2DKeyFrameElementGraphic*
     @return 매트릭스 wrapper를 반환합니다.
     */
    VBMatrix2DWrapper VBObjectFile2DKeyFrameElementGraphicGetMatrixWrapper(VBObjectFile2DKeyFrameElementGraphic* _graphic);
    
    /**
     @brief VBObjectFile2DKeyFrameElementGraphic의 컬러를 구합니다.
     @param _graphic 메모리가 할당된 VBObjectFile2DKeyFrameElementGraphic*
     @return 컬러를 반환합니다.
     */
    VBColorRGBA VBObjectFile2DKeyFrameElementGraphicGetColor(VBObjectFile2DKeyFrameElementGraphic* _graphic);
    
    /**
     @brief VBObjectFile2DKeyFrameElementGraphic의 transitio properties를 구합니다.
     @param _graphic 메모리가 할당된 VBObjectFile2DKeyFrameElementGraphic*
     @return transitio properties를 반환합니다.
     */
    void VBObjectFile2DKeyFrameElementGraphicGetTransitionProperties(VBObjectFile2DKeyFrameElementGraphic* _graphic, VBFloat _t, VBMatrix2DWrapper* _matrix, VBColorRGBA* _color);
    
    /**
     @brief VBObjectFile2DKeyFrameElementGraphic의 메모리를 해제합니다.
     @param _graphic 메모리가 할당된 VBObjectFile2DKeyFrameElementGraphic**
     */
    void VBObjectFile2DKeyFrameElementGraphicFree(VBObjectFile2DKeyFrameElementGraphic** _graphic);
    
    /**
     @brief VBObjectFile2DKeyFrameElementMovieClip의 메모리를 할당합니다.
     @return 메모리가 할당된 VBObjectFile2DKeyFrameElementMovieClip를 반환합니다.
     */
    VBObjectFile2DKeyFrameElementMovieClip* VBObjectFile2DKeyFrameElementMovieClipAlloc(void);
    
    /**
     @brief VBObjectFile2DKeyFrameElementMovieClip의 메모리를 초기화합니다.
     @param _movie_clip 메모리가 할당된 VBObjectFile2DKeyFrameElementMovieClip*
     @return 초기화된 VBObjectFile2DKeyFrameElementMovieClip를 반환합니다.
     */
    VBObjectFile2DKeyFrameElementMovieClip* VBObjectFile2DKeyFrameElementMovieClipInit(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip);
    
    /**
     @brief VBObjectFile2DKeyFrameElementMovieClip의 메모리를 데이터와 함께 초기화합니다.
     @param _movie_clip 메모리가 할당된 VBObjectFile2DKeyFrameElementMovieClip*
     @param _blend_mode 블랜딩 모드
     @param _transition transition*
     @param _matrix 매트릭스 wrapper
     @param _color 컬러
     @return 초기화된 VBObjectFile2DKeyFrameElementMovieClipfmf 반환합니다. 
     */
    VBObjectFile2DKeyFrameElementMovieClip* VBObjectFile2DKeyFrameElementMovieClipInitWithData(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip, VBString* _instance_name, VBObjectFile2DTransition* _transition, VBMatrix2DWrapper _matrix, VBColorRGBA _color);
    
    /**
     @brief VBObjectFile2DKeyFrameElementMovieClip의 인스턴스 이름을 구합니다.
     @param _movie_clip 메모리가 할당된 VBObjectFile2DKeyFrameElementMovieClip*
     @return 인스턴스 이름을 반환합니다.
     */
    VBString* VBObjectFile2DKeyFrameElementMovieClipGetInstanceName(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip);
    
    /**
     @brief VBObjectFile2DKeyFrameElementMovieClip의 매트릭스 wrapper를 구합니다.
     @param _movie_clip 메모리가 할당된 VBObjectFile2DKeyFrameElementMovieClip*
     @return 매트릭스 wrapper를 반환합니다.
     */
    VBMatrix2DWrapper VBObjectFile2DKeyFrameElementMovieClipGetMatrixWrapper(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip);
    
    /**
     @brief VBObjectFile2DKeyFrameElementMovieClip의 컬러를 구합니다.
     @param _movie_clip 메모리가 할당된 VBObjectFile2DKeyFrameElementMovieClip*
     @return 컬러를 반환합니다.
     */
    VBColorRGBA VBObjectFile2DKeyFrameElementMovieClipGetColor(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip);
    
    /**
     @brief VBObjectFile2DKeyFrameElementMovieClip의 transition properties를 구합니다.
     @param _movie_clip 메모리가 할당된 VBObjectFile2DKeyFrameElementMovieClip*
     @param _t 
     @param _matrix 매트릭스 wapper
     @param _color 컬러
     @return transition properties를 반환합니다. 
     */
    void VBObjectFile2DKeyFrameElementMovieClipGetTransitionProperties(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip, VBFloat _t, VBMatrix2DWrapper* _matrix, VBColorRGBA* _color);
    
    /**
     @brief VBObjectFile2DKeyFrameElementMovieClip의 메모리를 해제합니다.
     @param _movie_clip 메모리가 할당된 VBObjectFile2DKeyFrameElementMovieClip*
     */
    void VBObjectFile2DKeyFrameElementMovieClipFree(VBObjectFile2DKeyFrameElementMovieClip** _movie_clip);
    
    /**
     @brief VBObjectFile2DKeyFrameElementGraphic의 다음 그래픽을 구합니다.
     @param _graphic 메모리가 할당된 VBObjectFile2DKeyFrameElementGraphic*
     @return 다음 그래픽을 반환합니다.
     */
    VBObjectFile2DKeyFrameElementGraphic* VBObjectFile2DKeyFrameElementGraphicGetNext(VBObjectFile2DKeyFrameElementGraphic* _graphic);
    
    /**
     @brief VBObjectFile2DKeyFrameElementMovieClip의 다음 무비클립을 구합니다.
     @param _movie_clip 메모리가 할당된 VBObjectFile2DKeyFrameElementMovieClip*
     @return 다음 무비클립을 반환합니다.
     */
    VBObjectFile2DKeyFrameElementMovieClip* VBObjectFile2DKeyFrameElementMovieClipGetNext(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip);
    
    /**
     @brief VBObjectFile2DKeyFrameElementGraphic의 다음 그래픽을 설정합니다.
     @param _graphic 메모리가 할당된 VBObjectFile2DKeyFrameElementGraphic*
     */
    void VBObjectFile2DKeyFrameElementGraphicSetNext(VBObjectFile2DKeyFrameElementGraphic* _graphic, VBObjectFile2DKeyFrameElementGraphic* _next);
    
    /**
     @brief VBObjectFile2DKeyFrameElementMovieClip의 다음 무비 클립을 설정합니다.
     @param _movie_clip 메모리가 할당된 VBObjectFile2DKeyFrameElementMovieClip*
     */
    void VBObjectFile2DKeyFrameElementMovieClipSetNext(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip, VBObjectFile2DKeyFrameElementMovieClip* _next);
    
    /**
     @brief VBObjectFile2DKeyFrameElementGraphic의 transition을 구합니다. 
     @param _graphic 메모리가 할당된 VBObjectFile2DKeyFrameElementGraphic*
     @return transition을 반환합니다.
     */
    VBObjectFile2DTransition* VBObjectFile2DKeyFrameElementGraphicGetTransition(VBObjectFile2DKeyFrameElementGraphic* _graphic);
    
    /**
     @brief VBObjectFile2DKeyFrameElementMovieClip의 transition을 구합니다.
     @param _movie_clip 메모리가 할당된 VBObjectFile2DKeyFrameElementMovieClip*
     @return transition을 반환합니다.
     */
    VBObjectFile2DTransition* VBObjectFile2DKeyFrameElementMovieClipGetTransition(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip);

#ifdef __cplusplus
}
#endif

#endif
