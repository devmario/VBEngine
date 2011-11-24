#include "VBModel2D.h"
#include "../VBEngine.h"
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#pragma mark - AABB처리로 속도를 빠르게 하기위해 VBDisplay2D에서 VBModel2D로 접근이 필요한 private한 재귀 method

//모델의 Vertex의 AABB를 설정합니다.(이메소드 호출시 하위의 모든 자식의 Vertex들도 AABB가 설정됨)
//child로 내려가며 재귀
void _VBModel2DSetVertexAABBTowardChildsRecursive(VBModel2D* _model) {
    if(_model->drawable->vtx)
        _model->vertex_aabb = VBAABBCreateWithVertex(_model->drawable->vtx, _model->drawable->poly_len);
    else
        _model->vertex_aabb = VBAABBLoadIndentity();
    _model->aabb = _model->vertex_aabb;
    
    VBArrayListNode* _node = VBArrayListGetFirstNode(_model->child);
    while(_node) {
        _VBModel2DSetVertexAABBTowardChildsRecursive(VBArrayListNodeGetData(_node));
        _node = VBArrayListNodeGetNextNode(_node);
    }
}

//모델의 AABB(모든 자식들의 AABB를 포함)를 설정합니다.(이메소드 호출시 모든 부모들의 AABB도 설정됨)
//parent로 타고 올라가며 재귀
void _VBModel2DSetAABBTowardParentsRecursive(VBModel2D* _model, VBAABB _child_aabb) {
    _model->aabb = VBAABBMerge(_model->aabb, _child_aabb);
    
    if(_model->parent)
        _VBModel2DSetAABBTowardParentsRecursive(_model->parent, _model->aabb);
}

//모델의 AABB와 화면의 AABB를 충돌검사해서 출력 플래그를 설정합니다.
//child로 내려가며 재귀
void _VBModel2DSetDrawFlagAsAABBTowardChildsRecursive(VBModel2D* _model, VBAABB _screen_aabb) {
    _model->is_aabb_draw = VBAABBHitTest(_model->aabb, _screen_aabb);
    _model->is_vertex_aabb_draw = VBAABBHitTest(_model->vertex_aabb, _screen_aabb);
    if(_model->is_aabb_draw) {
        VBArrayListNode* _node = VBArrayListGetFirstNode(_model->child);
        while(_node) {
            _VBModel2DSetDrawFlagAsAABBTowardChildsRecursive(VBArrayListNodeGetData(_node), _screen_aabb);
            _node = VBArrayListNodeGetNextNode(_node);
        }
    }
}

#pragma mark - VBModel2D의 drawable생성을 위한 업데이트 method

//모델의 칼라와 매트릭스를 두번째,세번째 인자로 넘긴 속성들과 혼합하고 Drawable을 만드는 private한 method
//자식들을 타고 내려가며 재귀 method
//5번째 인자로 넘긴 콜백은 재귀도는중 현재 모델이 모델트리의 가장 하위일때 호출된다.(자식이 없는 모델)
//이는 VBDisplay2D에서 모델을 Draw할때 AABB박스를 모델트리구조를 따르면서 병합하기 위해서이다.(빠른 렌더링 위해)
//4번째 인자로 넘긴 포인터는 5번째인자의 콜백 호출시 넘겨진다.
void _VBModel2DUpdateColorAndMatrixAndDrawableTowardChildsRecursive(VBModel2D* _model, VBColorRGBA _parent_color, VBMatrix2D _parent_mat, void* _user_reference, void _leaf_tree_child_func(void*,VBModel2D*)) {
    _model->multiply_color = VBColorRGBAMultiply(_model->color, _parent_color);
    _model->mat = VBMatrix2DWrapperUpdate(_model->mat);
    _model->multiply_matrix = VBMatrix2DMultiply(_parent_mat, VBMatrix2DWrapperGetMatrix(_model->mat));
    if(_model->origin_drawable->vtx) {
        VBColorRGBA _color[_model->origin_drawable->poly_len];
        VBVector2D vtx[_model->origin_drawable->poly_len];
        VBVector2D* origin_vtx = _model->origin_drawable->vtx;
        
        VBULong i;
        for(i = 0; i < _model->origin_drawable->poly_len; i++) {
            vtx[i] = VBMatrix2DMultiplyVBVector2D(_model->multiply_matrix, *origin_vtx);
            _color[i] = _model->multiply_color;
            origin_vtx++;
        }
        VBDrawable2DSetData(_model->drawable, _model->origin_drawable->draw_type,
                            _model->origin_drawable->tex, _model->origin_drawable->poly_len, _color, vtx, _model->origin_drawable->txc,
                            _model->origin_drawable->idx_len, _model->origin_drawable->idx);
    }
    if(VBModel2DGetChildNum(_model) == 0)
        _leaf_tree_child_func(_user_reference, _model);
    
    
    VBArrayListNode* _node = VBArrayListGetFirstNode(_model->child);
    while(_node) {
        _VBModel2DUpdateColorAndMatrixAndDrawableTowardChildsRecursive(VBArrayListNodeGetData(_node), _model->multiply_color, _model->multiply_matrix, _user_reference, _leaf_tree_child_func);
        _node = VBArrayListNodeGetNextNode(_node);
    }
}

#pragma mark - VBModel2D의 에니메이션 업데이트(private한 재귀 method)

typedef struct _key_sort _key_sort;

struct _key_sort {
    VBModel2D* _child;
    VBObjectFile2DKeyFrame* _key;
};

VBLong _key_sort_func(const void* _a, const void* _b) {
    _key_sort** _key_a = (_key_sort**)_a;
    _key_sort** _key_b = (_key_sort**)_b;
    if((*_key_a)->_key->depth > (*_key_b)->_key->depth) {
        return 1;
    }
    return 0;
}

//VBModel2D의 에니메이션 업데이트(private한 재귀 method)
//자식으로 내려가면서 모든 에니메이션을 업데이트
void _VBModel2DAnimationUpdateTowardChildsRecursive(VBModel2D* _model, VBFloat _tick, VBBool _is_update_child) {
    if(_model->frame) { //모델에 애니메이션 정보가 존재하는지 검사한다.
        if(_model->is_play) { //모델의 애니메이션이 플레이 중인지 검사한다.
            //현재 프레임을 증가시킨다.
            _model->cur_frame += _tick * _model->frame_rate;
            if(_model->cur_frame > _model->frame->total_frame - 1) { //모델의 현재 프레임이 전체 프레임 수 보다 큰지 검사한다.
                if(_model->is_play_loop) { //모델의 애니메이션이 루핑되는지 검사한다.
                    //모델의 애니메이션이 루핑 된다면 초기 프레임으로 변경한다.
                    _model->cur_frame = 0;
                } else {
                    //모델의 애니메이션이 루핑 되지 않으면 플레이 되지 않도록 설정한다.
                    _model->is_play = VBFalse;
                    _model->cur_frame = _model->frame->total_frame - 1;
                }
            } else if(_model->cur_frame < 0.0) {
                if(_model->is_play_loop) { //모델의 애니메이션이 루핑되는지 검사한다.
                    //모델의 애니메이션이 루핑 된다면 마지막 프레임으로 변경한다.
                    _model->cur_frame = _model->frame->total_frame - 1;
                } else {
                    //모델의 애니메이션이 루핑 되지 않으면 플레이 되지 않도록 설정한다.
                    _model->is_play = VBFalse;
                }
            }
            //모델의 애니메이션이 업데이트 되었음을 설정한다.
            _model->is_animation_update = VBTrue;
        }
        
        //애니메이션이 업데이트 되었을 경우 차일드 리스트에서 삭제하고 애니메이트 된다.
        if(_model->frame_current_key_frame) {
            if(_model->is_animation_update) {
                //printf("%i %f\n", _model->frame_current_key_frame->len, _model->cur_frame);
                while(_model->frame_current_key_frame->len) {
                    _key_sort* _key = VBArrayVectorRemoveBack(_model->frame_current_key_frame);
                    VBModel2DRemoveChildModel(_model, _key->_child);
                    VBSystemFree(_key);
                }
                for(int i = 0; i < _model->frame->key_frame->len; i++) {
                    VBObjectFile2DKeyFrame* _key_frame = _model->frame->key_frame->data[i];
                    if((float)_key_frame->end_frame <  floorf(_model->cur_frame)) {
                        continue;
                    }
                    if((float)_key_frame->begin_frame > floorf(_model->cur_frame)) {
                        break;
                    }
                    _key_sort* _key = VBSystemCalloc(1, sizeof(_key_sort));
                    _key->_key = _key_frame;
                    _key->_child = _model->frame_all_allocated_child_models->data[i];
                    VBArrayVectorAddBack(_model->frame_current_key_frame, _key);
                }
                VBArrayVectorQuickSort(_model->frame_current_key_frame, _key_sort_func);
                
                if(_model->is_real_time_animation) {
                    for(int i = 0; i < _model->frame_current_key_frame->len; i++) {
                        _key_sort* _key = _model->frame_current_key_frame->data[i];
                        VBModel2D* child = _key->_child;
                        if(_key->_child->is_use_animation) {
                            VBObjectFile2DKeyFrame* _key_frame = _key->_key;
                            VBULong _b = VBObjectFile2DKeyFrameGetBeginFrame(_key_frame);
                            VBULong _e = VBObjectFile2DKeyFrameGetEndFrame(_key_frame);
                            VBObjectFile2DKeyFrameElement* _element = VBObjectFile2DKeyFrameGetElement(_key_frame);
                            if(VBObjectFile2DKeyFrameElementType_Bitmap == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                VBObjectFile2DKeyFrameElementBitmap* _bitmap = VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                                VBModel2DSetMatrixWrapper(child, _bitmap->matrix);
                                child->color = VBColorRGBACreate(0xFF, 0xFF, 0xFF, 0xFF);
                            } else if(VBObjectFile2DKeyFrameElementType_Graphic == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                VBMatrix2DWrapper mat;
                                VBColorRGBA color;
                                VBObjectFile2DKeyFrameElementGraphic* _graphic = VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                                VBFloat t = (_e - _b) == 0.0f ? 0.0 : (_model->cur_frame - _b) / (_e - _b);
                                if(t > 1.0)
                                    t = 1.0;
                                VBObjectFile2DKeyFrameElementGraphicGetTransitionProperties(_graphic, t, &mat, &color);
                                VBModel2DSetMatrixWrapper(child, mat);
                                child->color = color;
                            } else if(VBObjectFile2DKeyFrameElementType_MovieClip == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                VBMatrix2DWrapper mat;
                                VBColorRGBA color;
                                VBObjectFile2DKeyFrameElementMovieClip* _movie_clip = VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                                VBFloat t = (_e - _b) == 0.0f ? 0.0 : (_model->cur_frame - _b) / (_e - _b);
                                if(t > 1.0)
                                    t = 1.0;
                                VBObjectFile2DKeyFrameElementMovieClipGetTransitionProperties(_movie_clip, t, &mat, &color);
                                VBModel2DSetMatrixWrapper(child, mat);
                                child->color = color;
                            }
                        }
                        VBModel2DAddChildModel(_model, child);
                    }
                } else {
                    for(int i = 0; i < _model->frame_current_key_frame->len; i++) {
                        _key_sort* _key = _model->frame_current_key_frame->data[i];
                        VBModel2D* child = _key->_child;
                        if(_key->_child->is_use_animation) {
                            VBObjectFile2DKeyFrame* _key_frame = _key->_key;
                            VBULong _b = VBObjectFile2DKeyFrameGetBeginFrame(_key_frame);
                            VBULong _e = VBObjectFile2DKeyFrameGetEndFrame(_key_frame);
                            VBULong _key_index = (_e - _b) == 0 ? 0 : (_model->cur_frame - _b);
                            VBObjectFile2DKeyFrameElement* _element = VBObjectFile2DKeyFrameGetElement(_key_frame);
                            if(VBObjectFile2DKeyFrameElementType_Bitmap == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                VBModel2DSetMatrixWrapper(child, *_key_frame->none_real_time_matrix);
                                child->color = *_key_frame->none_real_time_color;
                            } else if(VBObjectFile2DKeyFrameElementType_Graphic == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                if(VBObjectFile2DKeyFrameElementGraphicGetNext(_element->element) == VBNull) {
                                    _key_index = 0;
                                }
                                VBModel2DSetMatrixWrapper(child, _key_frame->none_real_time_matrix[_key_index]);
                                child->color = _key_frame->none_real_time_color[_key_index];
                            } else if(VBObjectFile2DKeyFrameElementType_MovieClip == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                if(VBObjectFile2DKeyFrameElementMovieClipGetNext(_element->element) == VBNull) {
                                    _key_index = 0;
                                }
                                VBModel2DSetMatrixWrapper(child, _key_frame->none_real_time_matrix[_key_index]);
                                child->color = _key_frame->none_real_time_color[_key_index];
                            }
                        }
                        VBModel2DAddChildModel(_model, child);
                    }
                }
            }
            _model->is_animation_update = VBFalse;
        }
    }
    if(_is_update_child) {
        VBArrayListNode* _node = VBArrayListGetFirstNode(_model->child);
        while(_node) {
            _VBModel2DAnimationUpdateTowardChildsRecursive(VBArrayListNodeGetData(_node), _tick, _is_update_child);
            _node = VBArrayListNodeGetNextNode(_node);
        }
    }
}

#pragma mark - VBModel2D 메모리 생성및 해제, 초기화 

VBModel2D* VBModel2DAlloc(void) {
    VBModel2D* _model = VBSystemCalloc(1, sizeof(VBModel2D));
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBModel2DAlloc() - 메모리 할당에 실패하였습니다.");
#endif
    
    _model->drawable = VBDrawable2DAlloc();
    _model->origin_drawable = VBDrawable2DAlloc();
    _model->frame_all_allocated_child_models = VBArrayVectorAlloc();
    _model->frame_current_key_frame = VBArrayVectorAlloc();
    _model->child = VBArrayListAlloc();
    
    return _model;
}

VBModel2D* VBModel2DInit(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DInit() - VBNull인 Model요소를 초기화 할수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    _model->mat = VBMatrix2DWrapperLoadIdentity();
    _model->drawable = VBDrawable2DInit(_model->drawable);
    _model->origin_drawable = VBDrawable2DInit(_model->origin_drawable);
    _model->cur_frame = 0;
    _model->frame_all_allocated_child_models = VBArrayVectorInit(_model->frame_all_allocated_child_models);
    _model->frame_current_key_frame = VBArrayVectorInit(_model->frame_current_key_frame);
    while(VBModel2DGetChildNum(_model)) {
        VBModel2DRemoveChildModelAt(_model, 0);
    }
    _model->child = VBArrayListInit(_model->child);
    _model->is_show = VBTrue;
    _model->is_tree_updated = VBTrue;
    if(_model->parent) {
        VBModel2DRemoveChildModel(_model->parent, _model);
    }
    _model->parent = VBNull;
    _model->color = VBColorRGBACreate(0xFF, 0xFF, 0xFF, 0xFF);
#ifdef MODEL_INFO
    
#endif
    return _model;
    
}

VBModel2D* VBModel2DInitWithTexture(VBModel2D* _model, VBTexture* _tex) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DInitWithTexture() - VBNull인 Model요소를 초기화 할수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
    if(_tex == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DInitWithTexture() - VBNull인 Texture요소를 초기화 할수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    _model = VBModel2DInit(_model);
    
    VBColorRGBA color[4] = {{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF}};
    VBVector2D vtx[4] = {{0,0}, {_tex->width, 0}, {0, _tex->height}, {_tex->width, _tex->height}};
    VBVector2D txc[4] = {{0,0}, {1,0}, {0,1}, {1,1}};
    VBUShort idx[6] = {0,1,2,1,2,3};
    _model->origin_drawable = VBDrawable2DInitWithData(_model->origin_drawable, VBDrawable2DType_TriangleStrip, _tex,
                                                4, color, vtx, txc,
                                                6, idx);
    
    return _model;
}

VBModel2D* VBModel2DInitWithLibraryNameAndTexture(VBModel2D* _model, VBObjectFile2D* _obj2D, VBString* _library_name, VBTexture* _texture, VBBool _is_realtime_animation) {
    VBObjectFile2DLibraryNameID* _library_name_id = VBObjectFile2DGetLibraryNameIDByName(_obj2D, _library_name);
    _model = VBModel2DInitWithLibraryNameIDAndTexture(_model, _obj2D, _library_name_id, _texture, _is_realtime_animation);
    
    return _model;
}

VBModel2D* VBModel2DInitWithLibraryIDAndTexture(VBModel2D* _model, VBObjectFile2D* _obj2D, VBULong _library_id, VBTexture* _texture, VBBool _is_realtime_animation) {
    VBObjectFile2DLibraryNameID* _library_name_id = VBObjectFile2DGetLibraryNameIDByID(_obj2D, _library_id);
    _model = VBModel2DInitWithLibraryNameIDAndTexture(_model, _obj2D, _library_name_id, _texture, _is_realtime_animation);
    
    return _model;
}

VBModel2D* VBModel2DInitWithLibraryNameIDAndTexture(VBModel2D* _model, VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _library_name_id, VBTexture* _texture, VBBool _is_realtime_animation) {
    _model = VBModel2DInit(_model);
    _model->is_real_time_animation = _is_realtime_animation;
    _model->frame_rate = VBObjectFile2DGetFrameRate(_obj2D);
    _model->is_use_animation = VBTrue;
    VBObjectFile2DLibrary* _library = VBObjectFile2DGetLibraryByNameID(_obj2D, _library_name_id);
    void* _library_base = VBObjectFile2DLibraryGetBase(_library);
    if(VBObjectFile2DLibraryType_Bitmap == VBObjectFile2DLibraryGetType(_library)) {
        VBObjectFile2DLibraryBitmap* _bitmap = _library_base;
        
        VBULong _poly_len = VBObjectFile2DLibraryBitmapGetUVInfoLength(_bitmap);
        VBULong _idx_len = (_poly_len - 2) * 3;
        
        VBColorRGBA _color[_poly_len];
        VBVector2D _vtx[_poly_len];
        VBVector2D _txc[_poly_len];
        VBUShort _idx[_idx_len];
        VBVector2D* _uv = VBObjectFile2DLibraryBitmapGetUVInfo(_bitmap);
        
        VBColorRGBA* _color_ptr = _color;
        VBVector2D* _vtx_ptr = _vtx;
        VBVector2D* _txc_ptr = _txc;
        VBUShort* _idx_ptr = _idx;
        
        VBULong _i;
        for(_i = 0; _i < _poly_len - 2; _i++) {
            *_idx_ptr = 0;
            _idx_ptr++;
            *_idx_ptr = _i + 1;
            _idx_ptr++;
            *_idx_ptr = _i + 2;
            _idx_ptr++;
        }
        
        VBVector2D _lt;
        _lt.x = __FLT_MAX__;
        _lt.y = __FLT_MAX__;
        for(_i = 0; _i < VBObjectFile2DLibraryBitmapGetUVInfoLength(_bitmap); _i++) {
            if(_uv[_i].x < _lt.x)
                _lt.x = _uv[_i].x;
            if(_uv[_i].y < _lt.y)
                _lt.y = _uv[_i].y;
        }
        for(_i = 0; _i < _poly_len; _i++) {
            _color_ptr->r = 0xFF;
            _color_ptr->g = 0xFF;
            _color_ptr->b = 0xFF;
            _color_ptr->a = 0xFF;
            _color_ptr++;
            
            _vtx_ptr->x = (_uv[_i].x - _lt.x) * _obj2D->uv_w;
            _vtx_ptr->y = (_uv[_i].y - _lt.y) * _obj2D->uv_h;
            _vtx_ptr++;
            
            _txc_ptr->x = _uv[_i].x;
            _txc_ptr->y = _uv[_i].y;
            _txc_ptr++;
        }
        
        _model->origin_drawable = VBDrawable2DInitWithData(_model->origin_drawable, VBDrawable2DType_TriangleFan, _texture,
                                                           _poly_len, _color, _vtx, _txc,
                                                           _idx_len, _idx);
    } else if(VBObjectFile2DLibraryType_Graphic == VBObjectFile2DLibraryGetType(_library) || VBObjectFile2DLibraryType_MovieClip == VBObjectFile2DLibraryGetType(_library)) {
        if(VBObjectFile2DLibraryType_Graphic == VBObjectFile2DLibraryGetType(_library)) {
            VBObjectFile2DLibraryGraphic* _graphic = _library_base;
            _model->frame = VBObjectFile2DLibraryGraphicGetFrame(_graphic);
        } else if(VBObjectFile2DLibraryType_MovieClip == VBObjectFile2DLibraryGetType(_library)) {
            VBObjectFile2DLibraryMovieClip* _movie_clip = _library_base;
            _model->frame = VBObjectFile2DLibraryMovieClipGetFrame(_movie_clip);
        }
        
        _model->is_play = VBTrue;
        _model->is_play_loop = VBTrue;
        _model->is_animation_update = VBTrue;
        
        for(int i = 0; i < _model->frame->key_frame->len; i++) {
            VBObjectFile2DKeyFrame* _key_frame = _model->frame->key_frame->data[i];
            VBModel2D* _child = VBModel2DInitWithLibraryNameIDAndTexture(VBModel2DAlloc(), _obj2D, _key_frame->library_id, _texture, _is_realtime_animation);
            VBArrayVectorAddBack(_model->frame_all_allocated_child_models, _child);
        }
    }    
    _VBModel2DAnimationUpdateTowardChildsRecursive(_model, 0.0, VBFalse);
    return _model;
}

void VBModel2DFree(VBModel2D** _model) {
#ifdef _VB_DEBUG_
    if(*_model == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DFree() - VBNull인 Model요소를 해제 할수 없습니다. VBModel2DAlloc하지 않았거나 이미 VBModel2DFree했을 수 있습니다.");
#endif
    
    int i;
    for(i = 0; i < VBArrayVectorGetLength((*_model)->frame_current_key_frame); i++) {
        VBSystemFree((*_model)->frame_all_allocated_child_models->data[i]);
    }
    for(i = 0; i < VBArrayVectorGetLength((*_model)->frame_all_allocated_child_models); i++) {
        VBModel2DFree((VBModel2D**)&(*_model)->frame_all_allocated_child_models->data[i]);
    }
    
    *_model = VBModel2DInit(*_model);
    VBArrayListFree(&(*_model)->child);
    VBArrayVectorFree(&(*_model)->frame_all_allocated_child_models);
    VBArrayVectorFree(&(*_model)->frame_current_key_frame);
    VBDrawable2DFree(&(*_model)->origin_drawable);
    VBDrawable2DFree(&(*_model)->drawable);
    VBSystemFree(*_model);
}

#pragma mark - VBModel2D 변환행렬

VBMatrix2DWrapper VBModel2DGetMatrixWrapper(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetMatrixWrapper() - VBNull인 Model요소의 Matrix Wrapper를 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return _model->mat;
}

void VBModel2DSetMatrixWrapper(VBModel2D* _model, VBMatrix2DWrapper _mat) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DSetMatrixWrapper() - VBNull인 Model요소의 Matrix Wrapper를 설정할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    _model->mat = _mat;
}

VBMatrix2D VBModel2DGetMatrix(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetMatrix() - VBNull인 Model요소의 Matrix 정보를 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return _model->mat.mat;
}

VBVector2D VBModel2DGetPosition(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetPosition() - VBNull인 Model요소의 Matrix Position 정보를 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return VBMatrix2DWrapperGetPosition(_model->mat);
}

void VBModel2DSetPosition(VBModel2D* _model, VBVector2D _position) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DSetPosition() - VBNull인 Model요소의 Matrix Position 정보를 설정할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    _model->mat = VBMatrix2DWrapperSetPosition(_model->mat, _position);
}

VBFloat VBModel2DGetX(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetX() - VBNull인 Model요소의 Matrix x 정보를 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return VBMatrix2DWrapperGetX(_model->mat);
}

void VBModel2DSetX(VBModel2D* _model, VBFloat _x) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DSetX() - VBNull인 Model요소의 Matrix x 정보를 설정할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    _model->mat = VBMatrix2DWrapperSetX(_model->mat, _x);
}

VBFloat VBModel2DGetY(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetY() - VBNull인 Model요소의 Matrix y 정보를 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return VBMatrix2DWrapperGetY(_model->mat);
}

void VBModel2DSetY(VBModel2D* _model, VBFloat _y) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DSetY() - VBNull인 Model요소의 Matrix y 정보를 설정할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    _model->mat = VBMatrix2DWrapperSetY(_model->mat, _y);
}

VBVector2D VBModel2DGetScale(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetScale() - VBNull인 Model요소의 Matrix Scale 정보를 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return VBMatrix2DWrapperGetScale(_model->mat);
}

void VBModel2DSetScale(VBModel2D* _model, VBVector2D _scale) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DSetScale() - VBNull인 Model요소의 Matrix Scale 정보를 설정할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    _model->mat = VBMatrix2DWrapperSetScale(_model->mat, _scale);
}

VBFloat VBModel2DGetScaleX(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetScaleX() - VBNull인 Model요소의 Matrix ScaleX 정보를 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return VBMatrix2DWrapperGetXScale(_model->mat);
}

void VBModel2DSetScaleX(VBModel2D* _model, VBFloat _sx) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DSetScaleX() - VBNull인 Model요소의 Matrix ScaleX 정보를 설정할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    _model->mat = VBMatrix2DWrapperSetXScale(_model->mat, _sx);
}

VBFloat VBModel2DGetScaleY(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetScaleY() - VBNull인 Model요소의 Matrix ScaleY의 정보를 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return VBMatrix2DWrapperGetYScale(_model->mat);
}

void VBModel2DSetScaleY(VBModel2D* _model, VBFloat _sy) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DSetScaleY() - VBNull인 Model요소의 Matrix ScaleY 정보를 설정할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    _model->mat = VBMatrix2DWrapperSetYScale(_model->mat, _sy);
}

VBVector2D VBModel2DGetShear(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetShear() - VBNull인 Model요소의 Matrix Shear 정보를 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return VBMatrix2DWrapperGetShear(_model->mat);
}

void VBModel2DSetShear(VBModel2D* _model, VBVector2D _shear) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DSetShear() - VBNull인 Model요소의 Matrix Shear 정보를 설정할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    _model->mat = VBMatrix2DWrapperSetShear(_model->mat, _shear);
}

VBFloat VBModel2DGetShearX(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetShearX() - VBNull인 Model요소의 Matrix ShearX 정보를 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return VBMatrix2DWrapperGetXShear(_model->mat);
}

void VBModel2DSetShearX(VBModel2D* _model, VBFloat _sx) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DSetShearX() - VBNull인 Model요소의 Matrix ShearX 정보를 설정할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    _model->mat = VBMatrix2DWrapperSetXShear(_model->mat, _sx);
}

VBFloat VBModel2DGetShearY(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetShearY() - VBNull인 Model요소의 Matrix ShearY 정보를 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return VBMatrix2DWrapperGetYShear(_model->mat);
}

void VBModel2DSetShearY(VBModel2D* _model, VBFloat _sy) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DSetShearY() - VBNull인 Model요소의 Matrix ShearX 정보를 설정할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    _model->mat = VBMatrix2DWrapperSetYShear(_model->mat, _sy);
}

VBFloat VBModel2DGetRotation(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetRotation() - VBNull인 Model요소의 Matrix Rotation 정보를 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return VBMatrix2DWrapperGetRotation(_model->mat);
}

void VBModel2DSetRotation(VBModel2D* _model, VBFloat _angle) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DSetRotation() - VBNull인 Model요소의 Matrix Rotation 정보를 설정할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    _model->mat = VBMatrix2DWrapperSetRotation(_model->mat, _angle);
}

VBVector2D  VBModel2DGetAnchor(VBModel2D* _model) {
    return VBMatrix2DWrapperGetAnchor(_model->mat);
}

void VBModel2DSetAnchor(VBModel2D* _model, VBVector2D _anchor) {
    _model->mat = VBMatrix2DWrapperSetAnchor(_model->mat, _anchor);
}

VBFloat VBModel2DGetAnchorX(VBModel2D* _model) {
    return VBMatrix2DWrapperGetAnchorX(_model->mat);
}

void VBModel2DSetAnchorX(VBModel2D* _model, VBFloat _ax) {
    _model->mat = VBMatrix2DWrapperSetAnchorX(_model->mat, _ax);
}

VBFloat VBModel2DGetAnchorY(VBModel2D* _model) {
    return VBMatrix2DWrapperGetAnchorY(_model->mat);
}

void VBModel2DSetAnchorY(VBModel2D* _model, VBFloat _ay) {
    _model->mat = VBMatrix2DWrapperSetAnchorY(_model->mat, _ay);
}

#pragma mark - VBModel2D 모델트리 조작

VBULong VBModel2DGetChildNum(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetChildNum() - VBNull인 Model요소의 ChildNum을 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return VBArrayListGetLength(_model->child);
}

VBModel2D* VBModel2DGetChildModelAt(VBModel2D* _model, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetChildModelAt() - VBNull인 Model요소의 특정 위치의 ChildNum을 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return VBArrayListDataAtIndex(_model->child, _at);
}

VBModel2D* VBModel2DGetChildModelByInstanceName(VBModel2D* _model, VBString* _instance_name) {
    int i;
    for(i = 0; i < _model->frame->key_frame->len; i++) {
        VBObjectFile2DKeyFrame* _k_frame = _model->frame->key_frame->data[i];
        if(_k_frame->element->element_type == VBObjectFile2DKeyFrameElementType_MovieClip) {
            VBObjectFile2DKeyFrameElementMovieClip* _mc = _k_frame->element->element;
            if(_mc->instance_name) {
                if(VBStringIsEqual(_mc->instance_name, _instance_name)) {
                    return _model->frame_all_allocated_child_models->data[i];
                }
            }
        }
    }
    return VBNull;
}

VBLongLong VBModel2DGetAtChildModel(VBModel2D* _model, VBModel2D* _child) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetAtChildModel() - VBNull인 Model요소의 Child Model을 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return VBArrayListIndexAtData(_model->child, _child);
}

void VBModel2DAddChildModel(VBModel2D* _model, VBModel2D* _child) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DAddChildModel() - VBNull인 Model요소에 ChildModel을 추가할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    if(_child->parent == VBNull) {
        VBArrayListAddBack(_model->child, _child);
        _child->parent = _model;
        _model->is_tree_updated = VBTrue;
    } else {
#ifdef _VB_DEBUG_
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBModel2DAddChildModel() - 이미 Add된 VBModel2D를 Add할수 없습니다.");
#endif
    }
}

void VBModel2DAddChildModelAt(VBModel2D* _model, VBModel2D* _child, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DAddChildModelAt() - VBNull인 Model요소의 특정 위치에 ChildModel을 추가할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    if(_child->parent == VBNull) {
        VBArrayListAddAt(_model->child, _child, _at);
        _child->parent = _model;
        _model->is_tree_updated = VBTrue;
    } else {
#ifdef _VB_DEBUG_
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBModel2DAddChildModelAt() - 이미 Add된 VBModel2D를 Add할수 없습니다.");
#endif
    }
}

void VBModel2DRemoveChildModel(VBModel2D* _model, VBModel2D* _child) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DRemoveChildModel() - VBNull인 Model요소에서 Child Model을 삭제할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    if(_child->parent) {
        VBArrayListRemove(_model->child, _child);
        _child->parent = VBNull;
        _model->is_tree_updated = VBTrue;
    } else {
#ifdef _VB_DEBUG_
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBModel2DRemoveChildModel() - Add가 되지않은 VBModel2D를 Remove할수 없습니다.");
#endif
    }
}

void VBModel2DRemoveChildModelAt(VBModel2D* _model, VBULong _at) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DRemoveChildModelAt() - VBNull인 Model요소의 특정 위치의 Child Model을 삭제할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    VBModel2D* _child = VBArrayListRemoveAt(_model->child, _at);
    if(_child) {
        _child->parent = VBNull;
        _model->is_tree_updated = VBTrue;
    } else {
#ifdef _VB_DEBUG_
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBModel2DRemoveChildModelAt() - 해당 index에 Add가 되어있는 VBModel2D이 없습니다.");
#endif
    }
}

void VBModel2DSwapChildModel(VBModel2D* _model, VBModel2D* _child_1, VBModel2D* _child_2) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DSwapChildModel() - VBNull인 Model요소의 두 개의 Child Model을 Swap할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
#ifdef _VB_DEBUG_
    if(_child_1->parent != _model)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBModel2DSwapChildModel() - 두번째 인자로 넘긴 child model은 첫번째 인자로 넘긴 모델에 Add가 되어있지 않습니다.");
    if(_child_2->parent != _model)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBModel2DSwapChildModel() - 세번째 인자로 넘긴 child model은 첫번째 인자로 넘긴 모델에 Add가 되어있지 않습니다.");
#endif
    VBArrayListSwapData(_model->child, _child_1, _child_2);
}

void VBModel2DSwapChildModelAt(VBModel2D* _model, VBULong _at_1, VBULong _at_2) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DSwapChildModelAt() - VBNull인 Model요소에서 두 특정 위치의 Child Model을 Swap할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    VBArrayListSwapAt(_model->child, _at_1, _at_2);
}

#pragma mark - VBModel2D Color Get Set

VBColorRGBA VBModel2DGetColor(VBModel2D* _model) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DGetColor() - VBNull인 Model요소의 Color 정보를 가져올 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    return _model->color;
}

void VBModel2DSetColor(VBModel2D* _model, VBColorRGBA _color) {
#ifdef _VB_DEBUG_
    if(_model == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBModel2DSetColor() - VBNull인 Model요소의 Color 정보를 설정할 수 없습니다. VBModel2DAlloc하지 않았을 수 있습니다.");
#endif
    
    _model->color = _color;
}

#pragma mark - VBModel2D Frame Get Set

VBULong VBModel2DGetTotalFrame(VBModel2D* _model) {
    if(_model->frame)
        return _model->frame->total_frame;
    else
        return 0;
}

void VBModel2DPlay(VBModel2D* _model) {
    _model->is_play = VBTrue;
    _model->is_animation_update = VBTrue;
}

void VBModel2DGoToAndPlay(VBModel2D* _model, VBFloat _frame) {
    _model->cur_frame = _frame;
    _model->is_play = VBTrue;
    _model->is_animation_update = VBTrue;
}

void VBModel2DStop(VBModel2D* _model) {
    _model->is_play = VBFalse;
    _model->is_animation_update = VBTrue;
}

void VBModel2DGoToAndStop(VBModel2D* _model, VBFloat _frame) {
    _model->is_play = VBFalse;
    _model->cur_frame = _frame;
    _model->is_animation_update = VBTrue;
}

VBBool VBModel2DGetIsPlay(VBModel2D* _model) {
    return _model->is_play;
}

VBBool VBModel2DGetIsLoop(VBModel2D* _model) {
    return _model->is_play_loop;
}

void VBModel2DSetIsLoop(VBModel2D* _model, VBBool _is_loop) {
    _model->is_play_loop = _is_loop;
}

VBBool VBModel2DGetIsUseAnimation(VBModel2D* _model) {
    return _model->is_use_animation;
}

void VBModel2DSetIsUseAnimation(VBModel2D* _model, VBBool _is_use_animation) {
    _model->is_use_animation = _is_use_animation;
}

#pragma mark - VBModel2D Texture Get Set

void VBModel2DSetTexture(VBModel2D* _model, VBTexture* _tex) {
    _model->origin_drawable->tex = _tex;
}

VBTexture* VBModel2DGetTexture(VBModel2D* _model) {
    return VBDrawable2DGetTexture(_model->origin_drawable);
}

#pragma mark - VBModel2D Vertex Get

VBFloat VBModel2DGetOriginWidth(VBModel2D* _model) {
    VBFloat _width = 0.0f;
    VBVector2D* _vtx = VBDrawable2DGetVertex(_model->origin_drawable);
    VBULong _len = VBDrawable2DGetPolygonLength(_model->origin_drawable);
    VBULong _i;
    VBFloat _max = __FLT_MIN__;
    VBFloat _min = __FLT_MAX__;
    if(_vtx) {
        for(_i = 0; _i < _len; _i++) {
            if(_max < _vtx[_i].x)
                _max = _vtx[_i].x;
            if(_min > _vtx[_i].x)
                _min = _vtx[_i].x;
        }
        _width = _max - _min;
    }
    return _width;
}

VBFloat VBModel2DGetOriginHeight(VBModel2D* _model) {
    VBFloat _height = 0.0f;
    VBVector2D* _vtx = VBDrawable2DGetVertex(_model->origin_drawable);
    VBULong _len = VBDrawable2DGetPolygonLength(_model->origin_drawable);
    VBULong _i;
    VBFloat _max = __FLT_MIN__;
    VBFloat _min = __FLT_MAX__;
    if(_vtx) {
        for(_i = 0; _i < _len; _i++) {
            if(_max < _vtx[_i].y)
                _max = _vtx[_i].y;
            if(_min > _vtx[_i].y)
                _min = _vtx[_i].y;
        }
        _height = _max - _min;
    }
    return _height;
}



