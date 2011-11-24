//
//  VBModel.h
//  VBEngineToCocos2d-x
//
//  Created by kim js on 11. 10. 14..
//  Copyright (c) 2011년 vanillabreeze. All rights reserved.
//

#ifndef VBEngineToCocos2d_x_VBModel_h
#define VBEngineToCocos2d_x_VBModel_h

#include "VBModel2D.h"
#include "cocos2d.h"

using namespace cocos2d;

class VBModel : cocos2d::CCSprite {
public:
    VBBool is_animation_update;
    VBBool is_use_animation;
    VBBool is_play_loop;
    VBBool is_play;
    VBBool is_real_time_animation;
    VBFloat frame_rate;
    VBObjectFile2DFrame* frame;
    VBArrayVector* frame_all_allocated_child_models;
    VBArrayVector* frame_current_key_frame;
    VBFloat cur_frame;
    VBMatrix2DWrapper mat;
    
    VBModel();
    VBModel(VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _library_name_id, CCTexture2D* _texture, VBBool _is_realtime_animation);
    virtual ~VBModel(void);
    
    void VBModelUpdate(float _tick);
    
    virtual void setTextureRectInPixels(CCRect rect, bool rotated, CCSize size);
	virtual void updateTextureCoords(CCRect rect);
    virtual CCAffineTransform nodeToParentTransform(void);
};

#endif
