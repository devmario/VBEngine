/**
 @file VBDisplay2D.h
 @brief VBEngine의 VBDisplay2D 구조체타입과 여러 함수들.
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

#ifndef __VBDisplay2D_H__
#define __VBDisplay2D_H__

#include "VBType.h"
#include "VBModel2D.h"
#include "../Core/Linear/VBMatrix2D.h"
#include "VBCamera2D.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @brief VBDisplay2D의 타입 정의
     */
	typedef struct VBDisplay2D VBDisplay2D;
	
    /**
     @brief 화면에 출력될 정보들을 관리하는 구조체
     */
	struct VBDisplay2D {
        /**
         디스플레이의 카메라
         */
        VBCamera2D* camera;
        
        /**
         출력될 모델들의 최상위 모델
         */
		VBModel2D* top;
        
        /**
         모델의 바운딩 박스 병합에 사용되는 리스트, 모델 트리에서 leaf 모델들의 리스트.
         */
        VBArrayList* leaf_list;
        
        /**
         모델들의 drawable이 병합되는 drawable.
         */
        VBDrawable2D* drawable;
		
        /**
         현재 프레임에 출력될 모델들의 drawable이 병합된 drawable 리스트.
         */
		VBArrayList* drawable_list;
	};
	
    /**
     @brief VBDisplay2D에 메모리를 할당합니다.
     @return 메모리가 할당된 VBDisplay2D.
     */
	VBDisplay2D* VBDisplay2DAlloc(void);
	
    /**
     @brief VBDisplay2D를 초기화합니다.
     @param _display VBDisplay2D.
     @return 초기화된 VBDisplay2D.
     */
	VBDisplay2D* VBDisplay2DInit(VBDisplay2D* _display);
	
    /**
     @brief VBDisplay2D의 메모리를 해제합니다.
     @param _display VBDisplay2D.
     */
	void VBDisplay2DFree(VBDisplay2D** _display);
    
	void VBDisplay2DUpdate(VBDisplay2D* _display, VBFloat _tick);
    
    void VBDisplay2DDraw(VBDisplay2D* _display);
    
    VBCamera2D* VBDisplay2DGetCamera(VBDisplay2D* _display);
	
    /**
     @brief 디스플레이의 탑모델을 반환합니다.
     @param _display VBDislay2D.
     @return 디스플레이의 탑모델.
     */
    //톱모델 접근 막아야 함
	VBModel2D* VBDisplay2DGetTopModel(VBDisplay2D* _display);
    
#ifdef __cplusplus
}
#endif

#endif
