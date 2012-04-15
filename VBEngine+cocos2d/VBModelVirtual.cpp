#include "VBModel.h"

bool VBModel::init(void) {
	bool _ret = CCSprite::init();
	
	if(!_ret)
		return false;
	
    is_bitmap = false;
    
    color = mix_color = VBColorRGBALoadIdentity();
    
    is_real_time_animation = false;
    is_animation_update = false;
    is_use_animation = false;
    is_play_loop = false;
    is_play = false;
    frame_rate = 0.0f;
    update_frame = 0.0f;
    cur_frame = 0.0f;
    
    mat = VBMatrix2DWrapperLoadIdentity();
    
    model_parent = NULL;
    
    frame = NULL;
    
    frame_all_allocated_child_models = NULL;
    frame_willFree_child_models = NULL;
    frame_current_key_frame = NULL;
    
    is_exist_empty_frame = false;
    empty_frame = 0.0f;
    
    setAnchorPoint(ccp(0,0));
	
	return true;
}

CCAffineTransform VBModel::nodeToParentTransform(void) {
	if (m_bIsTransformDirty) {
        mat = VBMatrix2DWrapperLoadIdentity();
		
        mat = VBMatrix2DWrapperSetPosition(mat, VBVector2DCreate(m_tPosition.x, m_tPosition.y));
        mat = VBMatrix2DWrapperSetScale(mat, VBVector2DCreate(m_fScaleX, m_fScaleY));
        if(isnan(m_fRotation)) {
            mat = VBMatrix2DWrapperSetShear(mat, VBVector2DCreate(m_fSkewX, m_fSkewY));
            mat = VBMatrix2DWrapperSetRotation(mat, NAN);
        } else {
            mat = VBMatrix2DWrapperSetRotation(mat, m_fRotation);
        }
        mat = VBMatrix2DWrapperSetAnchor(mat, VBVector2DCreate(m_tAnchorPoint.x, m_tAnchorPoint.y));
        mat = VBMatrix2DWrapperUpdate(mat);
        
		m_tTransform = CCAffineTransformMake(mat.mat.m11, mat.mat.m21, mat.mat.m12, mat.mat.m22, mat.mat.m13, mat.mat.m23);
        
		m_bIsTransformDirty = false;
	}
    
	return m_tTransform;
}