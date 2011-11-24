/**
 @file Display/VBModel2D.h
 @brief VBModel2D 타입들의 상수값 정의
 @author
 <table>
 <tr><th>Developer</th><th>Role</th><th>Email</th></tr>
 <tr><td>장원희</td><td>Main Programmer</td><td>mario@vanillabreeze.com</td></tr>
 <tr><td>김희동</td><td>Programmer</td><td>welivehere@vanillabreeze.com</td></tr>
 <tr><td>박두철</td><td>Programmer</td><td>encjf@vanillabreeze.com</td></tr>
 </table>
 @version 1.0
 @section License
 Copyright 2011 vanilla breeze. All rights reserved.
 */

#ifndef __VBModel2D_H__
#define __VBModel2D_H__

#include "../Core/Linear/VBMatrix2DWrapper.h"
#include "../Core/Linear/VBAABB.h"
#include "../Util/VBArrayList.h"
#include "../Util/VBArrayVector.h"
#include "VBTexture.h"
#include "VBDrawable2D.h"
#include "../IO/VBObjectFile2D.h"

#ifdef __cplusplus
extern "C" {
#endif
	
    /**
     @brief VBModel2D의 타입 정의
     */
	typedef struct VBModel2D VBModel2D;
	
    /**
     @brief 화면에 출력될 애니메이션 정보를 담고 있는 모델 구조체
     */
	struct VBModel2D {
        /**
         @brief 모델의 매트릭스 정보
         */
		VBMatrix2DWrapper mat;
        
        VBMatrix2D multiply_matrix;
		
        /**
         @brief 초기의 draw 정보
         */
		VBDrawable2D* origin_drawable;
		
        /**
         @brief 매트릭스및 색상값이 적용된 draw 정보
         */
		VBDrawable2D* drawable;
		
        /**
         @brief 현재 프레임
         */
		VBFloat cur_frame;
        
        /**
         @brief 모델의 리스트
         */
		VBArrayVector* frame_all_allocated_child_models;
        VBArrayVector* frame_current_key_frame;
        /**
         @brief 해당키프레임 포인터
         */
        VBObjectFile2DFrame* frame;
        
        VBFloat frame_rate;
        
        VBBool is_real_time_animation;
        
        /**
         @brief 애니메이션이 플레이중인지 플래그 정보
         */
        VBBool is_play;
        
        /**
         @brief 애니메이션이 계속해서 반복 되는지 플래그 정보
         */
        VBBool is_play_loop;
        
        /**
         @brief 현재 프레임 정보에 대해 그려야할 draw 정보가 업데이트 되었는지 플래그 정보
         */
        VBBool is_animation_update;
        
        VBBool is_use_animation;
		
        /**
         @brief 자식 모델에 대한 리스트
         */
		VBArrayList* child;
        
        /**
         @brief 부모 모델에 대한 포인터
         */
        VBModel2D* parent;
        
        /**
         @brief 자식의 바운딩 박스와 병합된 바운딩 박스 정보
         */
        VBAABB aabb;
        
        VBBool is_aabb_draw;
        
        /**
         @brief 자신의 바운딩 박스
         */
        VBAABB vertex_aabb;
        
        VBBool is_vertex_aabb_draw;
        
        /**
         @brief 모델의 색상 정보
         */
        VBColorRGBA color;
        VBColorRGBA multiply_color;

        /**
         @brief 
         */
		VBBool is_show;
        
        /**
         @brief 
         */
        VBBool is_tree_updated;
	};
    
#pragma mark - 메모리및 초기화
	
    /**
     @brief VBModel2D의 메모리를 할당합니다.
     @return 메모리가 할당된 VBModel2D.
     */
	VBModel2D* VBModel2DAlloc(void);
	
    /**
     @brief VBModel2D를 초기화 합니다.
     @param _model VBModel2D.
     @return 초기화된 VBModel2D.
     */
	VBModel2D* VBModel2DInit(VBModel2D* _model);
	
    /**
     @brief VBModel2D를 텍스쳐로 초기화 합니다.
     @param _model VBModel2D.
     @param _tex 텍스쳐.
     @return 초기화된 VBModel2D.
     */
    VBModel2D* VBModel2DInitWithTexture(VBModel2D* _model, VBTexture* _tex);
    
    /**
     @brief 라이브러리 이름과 텍스쳐로 VBModel2D를 초기화합니다.
     @param _model VBModel2D
     @param _obj2D 오브젝트 파일 구조체
     @param _library_name 라이브러리 이름
     @param _texture 텍스쳐
     @param _is_realtime_animation 
     @return 초기화된 VBModel2D
     */
    VBModel2D* VBModel2DInitWithLibraryNameAndTexture(VBModel2D* _model, VBObjectFile2D* _obj2D, VBString* _library_name, VBTexture* _texture, VBBool _is_realtime_animation);
    
    /**
     @brief 
     @param
     @param
     @param
     @param
     @param
     @return
     */
    VBModel2D* VBModel2DInitWithLibraryIDAndTexture(VBModel2D* _model, VBObjectFile2D* _obj2D, VBULong _library_id, VBTexture* _texture, VBBool _is_realtime_animation);
    
    /**
     @brief
     @param
     @param
     @param
     @param
     @param
     @return
     */
    VBModel2D* VBModel2DInitWithLibraryNameIDAndTexture(VBModel2D* _model, VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _library_name_id, VBTexture* _texture, VBBool _is_realtime_animation);
    
    void VBModel2DSetTexture(VBModel2D* _model, VBTexture* _tex);
    /**
     @brief VBModel2D를 메모리 해제합니다.
     @param _model VBModel2D.
     */
	void VBModel2DFree(VBModel2D** _model);
    
#pragma mark - 변환행렬 접근
	
    /**
     @brief 모델에서 매트릭스 정보를 반환합니다.
     @param _model VBModel2D.
     @return 매트릭스 정보
     */
	VBMatrix2DWrapper VBModel2DGetMatrixWrapper(VBModel2D* _model);
	
    /**
     @brief 모델에 매트릭스 정보를 설정합니다.
     @param _model VBModel2D.
     @param _mat 매트릭스 정보.
     */
	void VBModel2DSetMatrixWrapper(VBModel2D* _model, VBMatrix2DWrapper _mat);
	
    /**
     @brief 모델에서 매트릭스를 반환합니다.
     @param _model VBModel2D.
     @return 매트릭스
     */
	VBMatrix2D VBModel2DGetMatrix(VBModel2D* _model);
	
    /**
     @brief 모델의 위치를 반환합니다.
     @param _model VBModel2D.
     @return 모델의 위치 정보.
     */
	VBVector2D VBModel2DGetPosition(VBModel2D* _model);
	
    /**
     @brief 모델에 위치를 설정합니다.
     @param _model VBModel2D.
     @param _position 위치 정보.
     */
	void VBModel2DSetPosition(VBModel2D* _model, VBVector2D _position);
	
    /**
     @brief 모델의 x좌표 위치 정보를 반환합니다.
     @param _model VBModel2D.
     @return 모델의 x좌표.
     */
	VBFloat VBModel2DGetX(VBModel2D* _model);
	
    /**
     @brief 모델의 x좌표를 설정합니다.
     @param _model VBModel2D.
     @param _x x좌표.
     */
	void VBModel2DSetX(VBModel2D* _model, VBFloat _x);
	
    /**
     @brief 모델의 y좌표를 반환합니다.
     @param _model VBModel2D.
     @return 모델의 y좌표.
     */
	VBFloat VBModel2DGetY(VBModel2D* _model);
	
    /**
     @brief 모델의 y좌표를 설정합니다.
     @param _model VBModel2D.
     @param _y y좌표.
     */
	void VBModel2DSetY(VBModel2D* _model, VBFloat _y);
	
    /**
     @brief 모델의 스케일 정보를 반환합니다.
     @param _model VBModel2D.
     @return 스케일 정보.
     */
	VBVector2D VBModel2DGetScale(VBModel2D* _model);
	
    /**
     @brief 모델의 스케일 정보를 설정합니다.
     @param _model VBModel2D.
     @param _scale 스케일 정보.
     */
	void VBModel2DSetScale(VBModel2D* _model, VBVector2D _scale);
	
    /**
     @brief 모델의 스케일 정보 x값을 반환합니다.
     @param _model VBModel2D.
     @return 스케일 정보의 x값.
     */
	VBFloat VBModel2DGetScaleX(VBModel2D* _model);
	
    /**
     @brief 모델의 스케일 정보 x값을 설정합니다.
     @param _model VBModel2D.
     @param _sx 스케일 값.
     */
	void VBModel2DSetScaleX(VBModel2D* _model, VBFloat _sx);
	
    /**
     @brief 모델의 스케일 정보 y값을 반환합니다.
     @param _model VBModel2D.
     @return 스케일 정보 y값.
     */
	VBFloat VBModel2DGetScaleY(VBModel2D* _model);
	
    /**
     @brief 모델의 스케일 정보 y값을 설정합니다.
     @param _model VBModel2D.
     @param _sy 스케일 값.
     */
	void VBModel2DSetScaleY(VBModel2D* _model, VBFloat _sy);
	
    /**
     @brief 모델의 기울기 정보를 반환합니다.
     @param _model VBModel2D.
     @return 모델의 기울기 정보.
     */
	VBVector2D VBModel2DGetShear(VBModel2D* _model);
	
    /**
     @brief 모델의 기울기 정보를 설정합니다.
     @param _model VBModel2D.
     @param _shear 기울기 정보.
     */
	void VBModel2DSetShear(VBModel2D* _model, VBVector2D _shear);
	
    /**
     @brief 모델의 기울기 x값을 반환합니다.
     @param _model VBModel2D.
     @return 기울기 x값.
     */
	VBFloat VBModel2DGetShearX(VBModel2D* _model);
	
    /**
     @brief 모델의 기울기 x값을 설정합니다.
     @param _model VBModel2D.
     @param _sx 기울기 정보.
     */
	void VBModel2DSetShearX(VBModel2D* _model, VBFloat _sx);
	
    /**
     @brief 모델의 기울기 y값을 반환합니다.
     @param _model VBModel2D.
     @return 기울기 y값.
     */
	VBFloat VBModel2DGetShearY(VBModel2D* _model);
	
    /**
     @brief 모델의 기울기 y값을 설정합니다.
     @param _model VBModel2D.
     @param _sy 기울기 정보.
     */
	void VBModel2DSetShearY(VBModel2D* _model, VBFloat _sy);
	
    /**
     @brief 모델의 회전각도를 반환합니다.
     @param _model VBModel2D.
     @return 회전각도.
     */
	VBFloat VBModel2DGetRotation(VBModel2D* _model);
	
    /**
     @brief 모델의 회전각도를 설정합니다.
     @param _model VBModel2D.
     @param _angle 회전각도.
     */
	void VBModel2DSetRotation(VBModel2D* _model, VBFloat _angle);
    
    /**
     @brief
     @param
     @return
     */
    VBVector2D  VBModel2DGetAnchor(VBModel2D* _model);
    
    /**
     @brief
     @param
     @return
     */
    void VBModel2DSetAnchor(VBModel2D* _model, VBVector2D _anchor);
    
    /**
     @brief
     @param
     @return
     */
    VBFloat VBModel2DGetAnchorX(VBModel2D* _model);
    
    /**
     @brief
     @param
     @return
     */
    void VBModel2DSetAnchorX(VBModel2D* _model, VBFloat _ax);
    
    /**
     @brief
     @param
     @return
     */
    VBFloat VBModel2DGetAnchorY(VBModel2D* _model);
    
    /**
     @brief
     @param
     @return
     */
    void VBModel2DSetAnchorY(VBModel2D* _model, VBFloat _ay);
    
#pragma mark - 모델트리구조 접근
	
    /**
     @brief 모델의 자식 모델 개수를 반환합니다.
     @param _model VBModel2D.
     @return 모델의 자식 모델 개수.
     */
	VBULong VBModel2DGetChildNum(VBModel2D* _model);
	
    /**
     @brief 모델의 자식 모델 중 n번째 위치한 자식 모델을 반환합니다.
     @param _model VBModel2D.
     @param _at 자식 모델의 위치.
     @return 자식 모델.
     */
	VBModel2D* VBModel2DGetChildModelAt(VBModel2D* _model, VBULong _at);
    
    /**
     @brief
     @param
     @return
     */
    VBModel2D* VBModel2DGetChildModelByInstanceName(VBModel2D* _model, VBString* _instance_name);
	
    /**
     @brief 모델의 자식 모델의 위치를 반환합니다.
     @param _model VBModel2D.
     @param _child 자식 모델.
     @return 자식 모델의 위치.
     */
	VBLongLong VBModel2DGetAtChildModel(VBModel2D* _model, VBModel2D* _child);
	
    /**
     @brief 모델에 자식 모델을 추가합니다.
     @param _model VBModel2D.
     @param _child 추가할 모델.
     */
	void VBModel2DAddChildModel(VBModel2D* _model, VBModel2D* _child);
	
    /**
     @brief 모델의 n번째 위치에 자식 모델을 추가합니다.
     @param _model VBModel2D.
     @param _child 추가할 모델.
     @param _at 추가할 위치.
     */
	void VBModel2DAddChildModelAt(VBModel2D* _model, VBModel2D* _child, VBULong _at);
	
    /**
     @brief 모델의 자식 모델을 삭제합니다.
     @param _model VBModel2D.
     @param _child 자식 모델.
     */
	void VBModel2DRemoveChildModel(VBModel2D* _model, VBModel2D* _child);
	
    /**
     @brief 모델의 n번째 위치의 자식 모델을 삭제합니다.
     @param _model VBModel2D.
     @param _at 삭제할 위치.
     */
	void VBModel2DRemoveChildModelAt(VBModel2D* _model, VBULong _at);
	
    /**
     @brief 모델의 자식 모델들 간의 위치를 변경합니다.
     @param _model VBModel2D.
     @param _child_1 자식 모델1.
     @param _child_2 자식 모델2.
     */
	void VBModel2DSwapChildModel(VBModel2D* _model, VBModel2D* _child_1, VBModel2D* _child_2);
	
    /**
     @brief 모델의 자식 모델들 간의 위치를 변경합니다.
     @param _model VBModel2D.
     @param _at_1 첫번째 위치.
     @param _at_2 두번째 위치.
     */
	void VBModel2DSwapChildModelAt(VBModel2D* _model, VBULong _at_1, VBULong _at_2);
    
#pragma mark 색상 접근
    
    /**
     @brief 모델의 색 정보를 반환합니다.
     @param _model VBModel2D.
     @return 색 정보.
     */
    VBColorRGBA VBModel2DGetColor(VBModel2D* _model);
    
    /**
     @brief 모델의 색 정보를 설정합니다.
     @param _model VBModel2D.
     @param _color 색 정보.
     */
    void VBModel2DSetColor(VBModel2D* _model, VBColorRGBA _color);
    
#pragma - 에니메이션 접근
    
    /**
     @brief
     @param
     @return
     */
    void VBModel2DPlay(VBModel2D* _model);
    
    void VBModel2DGoToAndPlay(VBModel2D* _model, VBFloat _frame);
    
    /**
     @brief
     @param
     @return
     */
    void VBModel2DStop(VBModel2D* _model);
    
    void VBModel2DGoToAndStop(VBModel2D* _model, VBFloat _frame);
    
    /**
     @brief
     @param
     @return
     */
    VBBool VBModel2DGetIsPlay(VBModel2D* _model);
    
    /**
     @brief
     @param
     @return
     */
    VBBool VBModel2DGetIsLoop(VBModel2D* _model);
    
    /**
     @brief
     @param
     */
    void VBModel2DSetIsLoop(VBModel2D* _model, VBBool _is_loop);
    
    VBBool VBModel2DGetIsUseAnimation(VBModel2D* _model);
    
    void VBModel2DSetIsUseAnimation(VBModel2D* _model, VBBool _is_use_animation);
    
    VBULong VBModel2DGetTotalFrame(VBModel2D* _model);
    
#pragma mark - 버텍스 접근
    
    VBFloat VBModel2DGetOriginWidth(VBModel2D* _model);
    
    VBFloat VBModel2DGetOriginHeight(VBModel2D* _model);
    
    VBBool VBModel2DGetIsHitTestWithPoint(VBModel2D* _model, VBVector2D _point, VBVector2D* _hit_point);
    VBBool VBModel2DGetIsHitTestWithLine(VBModel2D* _model, VBLine2D _line, VBVector2D* _hit_point);
    VBBool VBModel2DGetIsHitTestWithTriangle(VBModel2D* _model, VBTriangle2D _triangle);
    VBBool VBModel2DGetIsHitTestWithModel(VBModel2D* _model1, VBModel2D* _model2);
	
#ifdef __cplusplus
}
#endif

#endif
