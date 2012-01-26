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
#include "Display/VBModel2D.h"
#include "Core/VBMatrix3D.h"

#ifdef __cplusplus
extern "C" {
#endif
	
    /**
     @brief VBPinckingPointType 의 상수값 정의
     */
    enum {
        /**
         입력이 시작될때
         */
        VBPickingPointType_Begin          =   0x01 << 0x00,
        /**
         입력 중일때
         */
        VBPickingPointType_Move           =   0x01 << 0x01,
        /**
         입력이 종료 되었을때
         */
        VBPickingPointType_End            =   0x01 << 0x02,
    };
    
    /**
     @brief VBPickingPointType의 타입 정의
     */
    typedef unsigned char VBPickingPointType;
    
    /**
     @brief VBPickingPoint 구조체의 타입 정의
     */
    typedef struct VBPickingPoint VBPickingPoint;
    
    /**
     @brief 입력정보의 타입과 좌표
     */
	struct VBPickingPoint {
        /**
         입력정보의 타입
         */
        VBPickingPointType type;
        /**
         입력정보의 x좌표
         */
        VBFloat x;
        /**
         입력정보의 y좌표
         */
        VBFloat y;
    };
    
    /**
     @brief VBDisplay2D의 타입 정의
     */
	typedef struct VBDisplay2D VBDisplay2D;
	
    /**
     @brief 화면에 출력될 정보들을 관리하는 구조체
     */
	struct VBDisplay2D {
        /**
         출력될 모델들의 최상위 모델
         */
		VBModel2D* top;
        
        /**
         입력정보의 리스트
         */
        VBArrayList* picking_point;
		
        /**
         현재 프레임에 출력될 모델들의 drawable이 병합된 drawable 리스트.
         */
		VBArrayList* drawable_list;
        
        /**
         모델의 바운딩 박스 병합에 사용되는 리스트, 모델 트리에서 leaf 모델들의 리스트.
         */
        VBArrayList* leaf_list;
        
        /**
         모델들의 drawable이 병합되는 drawable.
         */
        VBDrawable2D* drawable;
        
        /**
         디스플레이의 가로 크기
         */
        VBUShort width;
        /**
         디스플레이의 세로 크기
         */
        VBUShort height;
        
        VBMatrix3D projection_matrix;
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
     @brief VBDisplay2D를 가로와 세로 크기로 초기화 합니다.
     @param _display VBDisplay2D.
     @param _w 가로 크기.
     @param _h 세로 크기.
     @return 초기화된 VBDisplay2D.
     */
	VBDisplay2D* VBDisplay2DInitWithScreenSize(VBDisplay2D* _display, VBUShort _w, VBUShort _h);
	
    /**
     @brief VBDisplay2D의 메모리를 해제합니다.
     @param _display VBDisplay2D.
     */
	void VBDisplay2DFree(VBDisplay2D** _display);
    
	void VBDisplay2DUpdate(VBDisplay2D* _display, VBFloat _tick);
    void VBDisplay2DDraw(VBDisplay2D* _display);
	
    /**
     @brief 디스플레이의 탑모델을 반환합니다.
     @param _display VBDislay2D.
     @return 디스플레이의 탑모델.
     */
	VBModel2D* VBDisplay2DGetTopModel(VBDisplay2D* _display);
    
    /**
     @brief 디스플레이의 리스트를 반환합니다.
     @return 디스플레이의 리스트.
     */
    VBArrayList* VBDisplay2DGetAllExistingVBDisplay2D(void);
    
    /**
     @brief 입력정보를 디스플레이의 추가합니다.
     @param _display VBDisplay2D.
     @param _picking 입력정보.
     */
    void VBDisplay2DPushPickingPoint(VBDisplay2D* _display, VBPickingPoint _picking);
    
    /**
     @brief 디스플레이에 속한 모델들의 바운딩 박스를 설정합니다.
     @param _display VBDisplay2D.
     */
    void VBDisplay2DSetModelBB(VBDisplay2D* _display);
    
    /**
     @brief 디스플레이에 속한 모델들의 화면 출력 여부를 결정합니다.
     @param _display VBDisplay2D.
     */
    void VBDisplay2DSetDrawFlag(VBDisplay2D* _display);
    
    /**
     @brief 디스플레이의 drawable 리스트를 clear합니다.
     @param _display VBDisplay2D.
     */
    void VBDisplay2DClearDrawableList(VBDisplay2D* _display);
    
    /**
     @brief 디스플레이의 drawable 리스트를 생성합니다.
     @param _display VBDisplay2D.
     @param _model drawable 리스트를 생성할 모델 트리의 최상위 모델.
     */
    void VBDisplay2DSetDrawableList(VBDisplay2D* _display, VBModel2D* _model);
    
    /**
     @brief 모델 트리의 leaf 리스트를 생성하고 현재 프레임의 매트릭스 정보를 업데이트 합니다.
     @param _display VBDisplay2D.
     @param _model 디스플레이 모델 트리의 최상위 모델.
     @param _parent_mat
     */
    void VBDisplay2DCreateLeafListAndUpdateMatrixAndColor(VBDisplay2D* _display, VBModel2D* _model, VBMatrix2D _parent_mat, VBColorAdvanced _parent_color);
	
#ifdef __cplusplus
}
#endif

#endif
