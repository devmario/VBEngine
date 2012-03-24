#include "VBModel.h"

int _VBModelDepthSort(const void* _a, const void* _b) {
    VBModelDepthSorter** _sorter_a = (VBModelDepthSorter**)_a;
    VBModelDepthSorter** _sorter_b = (VBModelDepthSorter**)_b;
    int sortNum = (*_sorter_a)->key->depth - (*_sorter_b)->key->depth;
    return sortNum;
}

void VBModel::Update(float _tick, bool _is_top) {
    if(frame) { //모델에 애니메이션 정보가 존재하는지 검사한다.
        if(is_play) { //모델의 애니메이션이 플레이 중인지 검사한다.
            //현재 프레임을 증가시킨다.
            if ( !update_frame ){
                cur_frame += _tick * frame_rate;
            }else{
                update_frame = VBFalse;
            }
            if(cur_frame > frame->total_frame - 1) { //모델의 현재 프레임이 전체 프레임 수 보다 큰지 검사한다.
                if(is_play_loop) { //모델의 애니메이션이 루핑되는지 검사한다.
                    //모델의 애니메이션이 루핑 된다면 초기 프레임으로 변경한다.
                    cur_frame = 0;
                } else {
                    //모델의 애니메이션이 루핑 되지 않으면 플레이 되지 않도록 설정한다.
                    is_play = VBFalse;
                    cur_frame = frame->total_frame - 1;
                }
            } else if(cur_frame < 0.0) {
                if(is_play_loop) { //모델의 애니메이션이 루핑되는지 검사한다.
                    //모델의 애니메이션이 루핑 된다면 마지막 프레임으로 변경한다.
                    cur_frame = frame->total_frame - 1;
                } else {
                    //모델의 애니메이션이 루핑 되지 않으면 플레이 되지 않도록 설정한다.
                    is_play = VBFalse;
                }
            }
            //모델의 애니메이션이 업데이트 되었음을 설정한다.
            is_animation_update = VBTrue;
        }else{
            if ( update_frame ){
                is_animation_update = VBTrue;
            }
        }
        update_frame = VBFalse;
        
        //애니메이션이 업데이트 되었을 경우 차일드 리스트에서 삭제하고 애니메이트 된다.
        if(frame_current_key_frame) {
            if(is_animation_update) {
                while(frame_current_key_frame->len) {
                    VBModelDepthSorter* _sorter = (VBModelDepthSorter*)VBArrayVectorRemoveBack(frame_current_key_frame);
                    removeChild(_sorter->child, false);
                    free(_sorter);
                }
                for(int i = 0; i < frame->key_frame->len; i++) {
                    VBObjectFile2DKeyFrame* _key_frame = (VBObjectFile2DKeyFrame*)frame->key_frame->data[i];
                    if((float)_key_frame->end_frame <=  cur_frame) {
                        continue;
                    }
                    if((float)_key_frame->begin_frame > cur_frame) {
                        break;
                    }
                    VBModelDepthSorter* _sorter = (VBModelDepthSorter*)calloc(1, sizeof(VBModelDepthSorter));
                    _sorter->key = _key_frame;
                    _sorter->child = (VBModel*)VBArrayVectorGetDataAt(frame_all_allocated_child_models, i);
                    VBArrayVectorAddBack(frame_current_key_frame, _sorter);
                }
                VBArrayVectorQuickSort(frame_current_key_frame, _VBModelDepthSort);
                
                if(is_real_time_animation) {
                    for(int i = 0; i < frame_current_key_frame->len; i++) {
                        VBModelDepthSorter* _sorter = (VBModelDepthSorter*)VBArrayVectorGetDataAt(frame_current_key_frame, i);
                        VBModel* child = (VBModel*)_sorter->child;
                        if(child->is_use_animation) {
                            VBObjectFile2DKeyFrame* _key_frame = _sorter->key;
                            VBULong _b = VBObjectFile2DKeyFrameGetBeginFrame(_key_frame);
                            VBULong _e = VBObjectFile2DKeyFrameGetEndFrame(_key_frame);
                            VBObjectFile2DKeyFrameElement* _element = VBObjectFile2DKeyFrameGetElement(_key_frame);
                            if(VBObjectFile2DKeyFrameElementType_Bitmap == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                VBObjectFile2DKeyFrameElementBitmap* _bitmap = (VBObjectFile2DKeyFrameElementBitmap*)VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                                VBMatrix2DWrapper mat = _bitmap->matrix;
                                child->setPosition(CCPoint(mat.position.x , -mat.position.y));
                                child->setAnchorPoint(CCPoint(mat.anchor.x, -mat.anchor.y));
                                child->setScaleX(mat.scale.x);
                                child->setScaleY(mat.scale.y);
                                if(isnan(mat.rotation)) {
                                    child->setSkewX(-mat.shear.x);
                                    child->setSkewY(-mat.shear.y);
                                    child->setRotation(NAN);
                                } else {
                                    child->setRotation(-mat.rotation);
                                }
                            } else if(VBObjectFile2DKeyFrameElementType_Graphic == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                VBMatrix2DWrapper mat;
                                VBObjectFile2DKeyFrameElementGraphic* _graphic = (VBObjectFile2DKeyFrameElementGraphic*)VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                                VBFloat t = (_e - _b) == 0.0f ? 0.0 : (cur_frame - _b) / (_e - _b);
                                if(t > 1.0)
                                    t = 1.0;
                                VBObjectFile2DKeyFrameElementGraphicGetTransitionProperties(_graphic, t, &mat, &child->color);
                                child->setPosition(CCPoint(mat.position.x, -mat.position.y));
                                child->setAnchorPoint(CCPoint(mat.anchor.x, -mat.anchor.y));
                                child->setScaleX(mat.scale.x);
                                child->setScaleY(mat.scale.y);
                                if(isnan(mat.rotation)) {
                                    child->setSkewX(-mat.shear.x);
                                    child->setSkewY(-mat.shear.y);
                                    child->setRotation(NAN);
                                } else {
                                    child->setRotation(-mat.rotation);
                                }
                            } else if(VBObjectFile2DKeyFrameElementType_MovieClip == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                VBMatrix2DWrapper mat;
                                VBObjectFile2DKeyFrameElementMovieClip* _movie_clip = (VBObjectFile2DKeyFrameElementMovieClip*)VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                                VBFloat t = (_e - _b) == 0.0f ? 0.0 : (cur_frame - _b) / (_e - _b);
                                if(t > 1.0)
                                    t = 1.0;
                                VBObjectFile2DKeyFrameElementMovieClipGetTransitionProperties(_movie_clip, t, &mat, &child->color); 
                                child->setPosition(CCPoint(mat.position.x, -mat.position.y));
                                child->setAnchorPoint(CCPoint(mat.anchor.x, -mat.anchor.y));
                                child->setScaleX(mat.scale.x);
                                child->setScaleY(mat.scale.y);
                                if(isnan(mat.rotation)) {
                                    child->setSkewX(-mat.shear.x);
                                    child->setSkewY(-mat.shear.y);
                                    child->setRotation(NAN);
                                } else {
                                    child->setRotation(-mat.rotation);
                                }
                            }
                        }
                        addChild(child);
                    }
                }
            }
            is_animation_update = VBFalse;
        }
    }
    
    if(_is_top) {
        mix_color = VBColorRGBAMultiply(color, VBColorRGBALoadIdentity());
    } else {
        VBModel* _parent = (VBModel*)getParent();
        if(_parent) {
            mix_color = VBColorRGBAMultiply(color, _parent->mix_color);
        } else {
            mix_color = VBColorRGBAMultiply(color, VBColorRGBALoadIdentity());
        }
    }
    
    if(is_bitmap) {
        ccColor3B _color3B;
        _color3B.r = mix_color.r;
        _color3B.g = mix_color.g;
        _color3B.b = mix_color.b;
        setColor(_color3B);
        setOpacity(mix_color.a);
    }
    
    if(getChildren()) {
        for(int i = 0; i < getChildren()->count(); i++) {
            VBModel* _child =  (VBModel*)getChildren()->objectAtIndex(i);
            _child->Update(_tick);
        }
    }
}
