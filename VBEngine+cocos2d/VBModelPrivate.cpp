#include "VBModel.h"

void VBModel::Init() {
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
    
    vb_tex = NULL;
    tex = NULL;
    
    model_parent = NULL;
    
    frame = NULL;
    
    frame_all_allocated_child_models = NULL;
    frame_willFree_child_models = NULL;
    frame_current_key_frame = NULL;
    
    setAnchorPoint(ccp(0,0));
}

void VBModel::InitWithLibName(VBObjectFile2D* _obj2D, VBTexture* _texture, VBObjectFile2DLibraryNameID* _library_name_id, bool _is_realtime_animation) {
    Init();
    
    is_use_animation = true;
    is_play_loop = true;
    is_play = true;
    is_real_time_animation = _is_realtime_animation;
    frame_rate = VBObjectFile2DGetFrameRate(_obj2D);
    
    VBObjectFile2DLibrary* _library = VBObjectFile2DGetLibraryByNameID(_obj2D, _library_name_id);
    void* _library_base = VBObjectFile2DLibraryGetBase(_library);
    if(VBObjectFile2DLibraryType_Bitmap == VBObjectFile2DLibraryGetType(_library)) {
        is_bitmap = true;
        VBObjectFile2DLibraryBitmap* _bitmap = (VBObjectFile2DLibraryBitmap*)_library_base;
        
        VBULong _poly_len = VBObjectFile2DLibraryBitmapGetUVInfoLength(_bitmap);
        
        VBVector2D _txc[_poly_len];
        VBVector2D* _uv = VBObjectFile2DLibraryBitmapGetUVInfo(_bitmap);
        
        VBVector2D* _txc_ptr = _txc;
        
        VBULong _i;
        
        for(_i = 0; _i < _poly_len; _i++) {
            _txc_ptr->x = _uv[_i].x;
            _txc_ptr->y = _uv[_i].y;
            _txc_ptr++;
        }
        vb_tex = _texture;
        tex = new cocos2d::CCTexture2D();
        
        tex->m_bPVRHaveAlphaPremultiplied = false;
        tex->m_bHasPremultipliedAlpha = false;
        if(_texture->color_type == VBColorType_RGBA)
            tex->m_ePixelFormat = kCCTexture2DPixelFormat_RGBA8888;
        tex->m_uName = _texture->tid;
        tex->m_fMaxS = 1.0;
        tex->m_fMaxT = 1.0;
        tex->m_uPixelsWide = _texture->width;
        tex->m_uPixelsHigh = _texture->height;
        tex->m_tContentSize.width = _texture->width;
        tex->m_tContentSize.height = _texture->height;
        setTexture(tex);
        
        setTextureRect( cocos2d::CCRectMake(_txc[0].x * tex->getPixelsWide() / CCDirector::sharedDirector()->getContentScaleFactor()
                                            ,_txc[0].y * tex->getPixelsHigh() / CCDirector::sharedDirector()->getContentScaleFactor()
                                            ,(_txc[2].x * tex->getPixelsWide() - _txc[0].x * tex->getPixelsWide()) / CCDirector::sharedDirector()->getContentScaleFactor()
                                            ,(_txc[2].y  * tex->getPixelsHigh() - _txc[0].y * tex->getPixelsHigh()) / CCDirector::sharedDirector()->getContentScaleFactor() ) );
        
    } else if(VBObjectFile2DLibraryType_Graphic == VBObjectFile2DLibraryGetType(_library) || VBObjectFile2DLibraryType_MovieClip == VBObjectFile2DLibraryGetType(_library)) {
        
        frame_all_allocated_child_models = VBArrayVectorInit(VBArrayVectorAlloc());
        frame_willFree_child_models = VBArrayVectorInit(VBArrayVectorAlloc());
        frame_current_key_frame = VBArrayVectorInit(VBArrayVectorAlloc());
        
        if(VBObjectFile2DLibraryType_Graphic == VBObjectFile2DLibraryGetType(_library)) {
            VBObjectFile2DLibraryGraphic* _graphic = (VBObjectFile2DLibraryGraphic*)_library_base;
            frame = VBObjectFile2DLibraryGraphicGetFrame(_graphic);
        } else if(VBObjectFile2DLibraryType_MovieClip == VBObjectFile2DLibraryGetType(_library)) {
            VBObjectFile2DLibraryMovieClip* _movie_clip = (VBObjectFile2DLibraryMovieClip*)_library_base;
            frame = VBObjectFile2DLibraryMovieClipGetFrame(_movie_clip);
        }
        
        is_play = VBTrue;
        is_play_loop = VBTrue;
        is_animation_update = VBTrue;
        
        while (frame_all_allocated_child_models->len < frame->key_frame->len) {
            VBArrayVectorAddBack(frame_all_allocated_child_models, NULL);
        }
        for(int i = 0; i < frame->key_frame->len; i++) {
            VBObjectFile2DKeyFrame* _key_frame = (VBObjectFile2DKeyFrame*)frame->key_frame->data[i];
            if(frame_all_allocated_child_models->data[i] == NULL) {
                VBModel* _child = new VBModel(_obj2D, _texture, _key_frame->library_id, _is_realtime_animation);
                frame_all_allocated_child_models->data[i] = _child;
                VBArrayVectorAddBack(frame_willFree_child_models, _child);
                LinkChildKeyFrames(i, _child, _key_frame);
            }
        }
    }
    Update(0.0f);
}

void VBModel::LinkChildKeyFrames(int _currentIdx, VBModel* _child, VBObjectFile2DKeyFrame* _key_frame) {
    int j;
    if(_key_frame->element->element_type == VBObjectFile2DKeyFrameElementType_Graphic) {
        VBObjectFile2DKeyFrameElementGraphic* _grap = (VBObjectFile2DKeyFrameElementGraphic*)_key_frame->element->element;
        if(VBObjectFile2DKeyFrameElementGraphicGetNext(_grap)) {
            for(j = _currentIdx; j < frame->key_frame->len; j++) {
                VBObjectFile2DKeyFrame* _key_frame_ot = (VBObjectFile2DKeyFrame*)frame->key_frame->data[j];
                if(_key_frame_ot->element->element_type == VBObjectFile2DKeyFrameElementType_Graphic) {
                    VBObjectFile2DKeyFrameElementGraphic* _grap_ot = (VBObjectFile2DKeyFrameElementGraphic*)_key_frame_ot->element->element;
                    if(VBObjectFile2DKeyFrameElementGraphicGetNext(_grap) == _grap_ot) {
                        frame_all_allocated_child_models->data[j] = _child;
                        if(j + 1 < frame->key_frame->len)
                            LinkChildKeyFrames(j + 1, _child, _key_frame_ot);
                        break;
                    }
                }
            }
        }
    }
    if(_key_frame->element->element_type == VBObjectFile2DKeyFrameElementType_MovieClip) {
        VBObjectFile2DKeyFrameElementMovieClip* _mc = (VBObjectFile2DKeyFrameElementMovieClip*)_key_frame->element->element;
        if(VBObjectFile2DKeyFrameElementMovieClipGetNext(_mc)) {
            for(j = _currentIdx; j < frame->key_frame->len; j++) {
                VBObjectFile2DKeyFrame* _key_frame_ot = (VBObjectFile2DKeyFrame*)frame->key_frame->data[j];
                if(_key_frame_ot->element->element_type == VBObjectFile2DKeyFrameElementType_MovieClip) {
                    VBObjectFile2DKeyFrameElementMovieClip* _mc_ot = (VBObjectFile2DKeyFrameElementMovieClip*)_key_frame_ot->element->element;
                    if(VBObjectFile2DKeyFrameElementMovieClipGetNext(_mc) == _mc_ot) {
                        frame_all_allocated_child_models->data[j] = _child;
                        if(j + 1 < frame->key_frame->len)
                            LinkChildKeyFrames(j + 1, _child, _key_frame_ot);
                        break;
                    }
                }
            }
        }
    }
}