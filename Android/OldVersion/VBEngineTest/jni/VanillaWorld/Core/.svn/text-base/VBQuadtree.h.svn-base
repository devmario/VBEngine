#ifndef __VBQuadtree_H__
#define __VBQuadtree_H__

#include "../VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @brief VBQuadtree의 구조체 정의
     */
    typedef struct VBQuadtree VBQuadtree;
    
    /**
     @brief 쪼갤지 판단해주는 콜백
     */
    typedef VBBool (*VBQuadtreeIsSlice)(VBQuadtree* quadtree);

    /**
     @brief 쿼드트리 메모리 관리
     */
    typedef void (*VBQuadtreeIsApear)(VBQuadtree* quadtree, VBBool is_apear);
    
    //쿼드트리
    /**
     @brief 쿼드트리 구조체 
     */
    struct VBQuadtree {
        /*!
         쪼갤지 판단해주는 콜백
         */
        VBQuadtreeIsSlice is_slice;
        /*!
         쿼드트리 메모리 관리
         */
        VBQuadtreeIsApear is_apear;
        /*!
         유저포인터
         */
        void* reference;
        
        /*!
         쿼드트리 최대 사이즈
         */
        VBFloat max_size;
        /*!
         쿼드트리 최소 사이즈
         */
        VBFloat min_size;
        /*!
         현재 쿼드트리 사이즈
         */
        VBFloat size;
        /*!
         쿼드트리 위치
         L,T,W,H
         */
        VBFloat x, y, width, height;
        /*!
         x
         */
        VBFloat center_x;
        /*!
         y
         */
        VBFloat center_y;
        
        /*!
         쪼개진 하위 쿼드트리가 있는지 검사하는 flag
         */
        VBBool has_child;

        /*!
         하위 쿼드트리 포인터(4개배열)
         하위없으면 VBNull
         */
        VBQuadtree** child;
        
        void* user_reference;
    };
    
    /**
     @brief VBQuadtree의 메모리를 할당합니다.
     @return _quadtree 메모리가 할당된 VBQuadtree를 반환합니다.
     */
    VBQuadtree* VBQuadtreeAlloc(void);
    
    /**
     @brief VBQuadtree를 초기화합니다.
     @param _quadtree VBQuadtree
     @param _is_slice 쪼갤지 판단해주는 콜백
     @param _is_apear 쿼드트리 메모리 관리
     @param _reference 유저포인터
     @param _max_size 쿼드트리 최대 사이즈
     @param _min_size 쿼드트리 최소 사이즈
     @return 초기화된 VBQuadtree를 반환합니다.
     */
    VBQuadtree* VBQuadtreeInit(VBQuadtree* _quadtree, VBQuadtreeIsSlice _is_slice, VBQuadtreeIsApear _is_apear, 
                               void* _reference, VBFloat _max_size, VBFloat _min_size);
    
    /**
     @brief VBQuadtree를 실행합니다.
     @param _quadtree VBQuadtree
     */
    void VBQuadtreeSlice(VBQuadtree* _quadtree);
    
    /**
     @brief VBQuadtree의 메모리를 해제합니다.
     @param _quadtree VBQuadtree
     */
    void VBQuadtreeFree(VBQuadtree** _quadtree);
    
#ifdef __cplusplus
}
#endif

#endif