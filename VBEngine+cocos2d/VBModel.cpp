#include <iostream>
#include "VBModel.h"
#include "cocos2d.h"
#include <string.h>

typedef struct _key_sort {
    VBModel* _child;
    VBObjectFile2DKeyFrame* _key;
} _key_sort;

VBLong _key_sort_func(const void* _a, const void* _b) {
    _key_sort** _key_a = (_key_sort**)_a;
    _key_sort** _key_b = (_key_sort**)_b;
    if((*_key_a)->_key->depth > (*_key_b)->_key->depth) {
        return 1;
    }
    return 0;
}

using namespace cocos2d;

VBModel::VBModel() {
    init();
    this->setAnchorPoint(ccp(0,0));
    is_animation_update = 0;
    is_use_animation = 0;
    is_play_loop = 0;
    is_play = 0;
    is_real_time_animation = 0;
    frame_rate = 0;
    frame = NULL;
    frame_all_allocated_child_models = NULL;
    frame_current_key_frame = NULL;
    cur_frame = 0;
    this->frame_all_allocated_child_models = VBArrayVectorInit(VBArrayVectorAlloc());
    this->frame_current_key_frame = VBArrayVectorInit(VBArrayVectorAlloc());
}

VBModel::VBModel(VBObjectFile2D* _obj2D, VBObjectFile2DLibraryNameID* _library_name_id, CCTexture2D* _texture, VBBool _is_realtime_animation) {
    init();
    this->setAnchorPoint(ccp(0,0));
    is_animation_update = 0;
    is_use_animation = true;
    is_play_loop = true;
    is_play = true;
    is_real_time_animation = _is_realtime_animation;
    frame = NULL;
    frame_all_allocated_child_models = NULL;
    frame_current_key_frame = NULL;
    cur_frame = 0.0;
    this->frame_all_allocated_child_models = VBArrayVectorInit(VBArrayVectorAlloc());
    this->frame_current_key_frame = VBArrayVectorInit(VBArrayVectorAlloc());
    
    this->is_real_time_animation = _is_realtime_animation;
    this->frame_rate = VBObjectFile2DGetFrameRate(_obj2D);
    this->is_use_animation = VBTrue;
    
    VBObjectFile2DLibrary* _library = VBObjectFile2DGetLibraryByNameID(_obj2D, _library_name_id);
    void* _library_base = VBObjectFile2DLibraryGetBase(_library);
    if(VBObjectFile2DLibraryType_Bitmap == VBObjectFile2DLibraryGetType(_library)) {
        VBObjectFile2DLibraryBitmap* _bitmap = (VBObjectFile2DLibraryBitmap*)_library_base;
        
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
        this->setTexture(_texture);
        this->setTextureRect( cocos2d::CCRectMake(_txc[0].x * _texture->getPixelsWide()
                                                  ,_txc[0].y * _texture->getPixelsHigh()
                                                  ,_txc[2].x * _texture->getPixelsWide() - _txc[0].x * _texture->getPixelsWide()
                                                  ,_txc[2].y  * _texture->getPixelsHigh() - _txc[0].y * _texture->getPixelsHigh() ) );
        
    } else if(VBObjectFile2DLibraryType_Graphic == VBObjectFile2DLibraryGetType(_library) || VBObjectFile2DLibraryType_MovieClip == VBObjectFile2DLibraryGetType(_library)) {
        if(VBObjectFile2DLibraryType_Graphic == VBObjectFile2DLibraryGetType(_library)) {
            VBObjectFile2DLibraryGraphic* _graphic = (VBObjectFile2DLibraryGraphic*)_library_base;
            this->frame = VBObjectFile2DLibraryGraphicGetFrame(_graphic);
        } else if(VBObjectFile2DLibraryType_MovieClip == VBObjectFile2DLibraryGetType(_library)) {
            VBObjectFile2DLibraryMovieClip* _movie_clip = (VBObjectFile2DLibraryMovieClip*)_library_base;
            this->frame = VBObjectFile2DLibraryMovieClipGetFrame(_movie_clip);
        }
        
        this->is_play = VBTrue;
        this->is_play_loop = VBTrue;
        this->is_animation_update = VBTrue;
        
        for(int i = 0; i < this->frame->key_frame->len; i++) {
            VBObjectFile2DKeyFrame* _key_frame = (VBObjectFile2DKeyFrame*)this->frame->key_frame->data[i];
            VBModel* _child = new VBModel(_obj2D, _key_frame->library_id, _texture, _is_realtime_animation);
            VBArrayVectorAddBack(this->frame_all_allocated_child_models, _child);
        }
    }
    VBModelUpdate(0.0f);
}

VBModel::~VBModel(void) {
    int i;
    for(i = 0; i < VBArrayVectorGetLength(this->frame_current_key_frame); i++) {
        VBSystemFree(this->frame_all_allocated_child_models->data[i]);
    }
    for(i = 0; i < VBArrayVectorGetLength(this->frame_all_allocated_child_models); i++) {
        delete (VBModel*)this->frame_all_allocated_child_models->data[i];
    }
    
    VBArrayVectorFree(&this->frame_all_allocated_child_models);
    VBArrayVectorFree(&this->frame_current_key_frame);
    
    this->cleanup();
}

void VBModel::VBModelUpdate(float _tick) {
    if(this->frame) { //모델에 애니메이션 정보가 존재하는지 검사한다.
        if(this->is_play) { //모델의 애니메이션이 플레이 중인지 검사한다.
            //현재 프레임을 증가시킨다.
            this->cur_frame += _tick * this->frame_rate;
            if(this->cur_frame > this->frame->total_frame - 1) { //모델의 현재 프레임이 전체 프레임 수 보다 큰지 검사한다.
                //printf("animation 1 cur frame %f total frame %ld\n", _model->cur_frame, _model->frame->total_frame);
                if(this->is_play_loop) { //모델의 애니메이션이 루핑되는지 검사한다.
                    //모델의 애니메이션이 루핑 된다면 초기 프레임으로 변경한다.
                    this->cur_frame = 0;
                } else {
                    //모델의 애니메이션이 루핑 되지 않으면 플레이 되지 않도록 설정한다.
                    this->is_play = VBFalse;
                    this->cur_frame = this->frame->total_frame - 1;
                }
            } else if(this->cur_frame < 0.0) {
                //printf("animation 2 cur frame %f total frame %ld\n", _model->cur_frame, _model->frame->total_frame);
                if(this->is_play_loop) { //모델의 애니메이션이 루핑되는지 검사한다.
                    //모델의 애니메이션이 루핑 된다면 마지막 프레임으로 변경한다.
                    this->cur_frame = this->frame->total_frame - 1;
                } else {
                    //모델의 애니메이션이 루핑 되지 않으면 플레이 되지 않도록 설정한다.
                    this->is_play = VBFalse;
                }
            }
            //모델의 애니메이션이 업데이트 되었음을 설정한다.
            this->is_animation_update = VBTrue;
        }
        
        //애니메이션이 업데이트 되었을 경우 차일드 리스트에서 삭제하고 애니메이트 된다.
        if(this->frame_current_key_frame) {
            if(this->is_animation_update) {
                while(this->frame_current_key_frame->len) {
                    _key_sort* _key = (_key_sort*)VBArrayVectorRemoveBack(this->frame_current_key_frame);
                    this->removeChild(_key->_child, false);
                    VBSystemFree(_key);
                }
                for(int i = 0; i < this->frame->key_frame->len; i++) {
                    VBObjectFile2DKeyFrame* _key_frame = (VBObjectFile2DKeyFrame*)this->frame->key_frame->data[i];
                    if((float)_key_frame->end_frame <  floorf(this->cur_frame)) {
                        continue;
                    }
                    if((float)_key_frame->begin_frame > floorf(this->cur_frame)) {
                        break;
                    }
                    _key_sort* _key = (_key_sort*)VBSystemCalloc(1, sizeof(_key_sort));
                    _key->_key = _key_frame;
                    _key->_child = (VBModel*)this->frame_all_allocated_child_models->data[i];
                    VBArrayVectorAddBack(this->frame_current_key_frame, _key);
                }
                VBArrayVectorQuickSort(this->frame_current_key_frame, _key_sort_func);
                
                if(this->is_real_time_animation) {
                    for(int i = 0; i < this->frame_current_key_frame->len; i++) {
                        _key_sort* _key = (_key_sort*)this->frame_current_key_frame->data[i];
                        VBModel* child = (VBModel*)_key->_child;
                        if(_key->_child->is_use_animation) {
                            VBObjectFile2DKeyFrame* _key_frame = _key->_key;
                            VBULong _b = VBObjectFile2DKeyFrameGetBeginFrame(_key_frame);
                            VBULong _e = VBObjectFile2DKeyFrameGetEndFrame(_key_frame);
                            VBObjectFile2DKeyFrameElement* _element = VBObjectFile2DKeyFrameGetElement(_key_frame);
                            if(VBObjectFile2DKeyFrameElementType_Bitmap == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                VBObjectFile2DKeyFrameElementBitmap* _bitmap = (VBObjectFile2DKeyFrameElementBitmap*)VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                                VBMatrix2DWrapper mat = _bitmap->matrix; 
                                child->setPosition(CCPoint(mat.position.x, mat.position.y));
                                child->setAnchorPoint(CCPoint(mat.anchor.x, mat.anchor.y));
                                child->setScaleX(mat.scale.x);
                                child->setScaleY(mat.scale.y);
                                child->setSkewX(mat.shear.x);
                                child->setSkewY(mat.shear.y);
                                child->setRotation(mat.rotation);
                            } else if(VBObjectFile2DKeyFrameElementType_Graphic == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                VBMatrix2DWrapper mat;
                                VBColorRGBA color;
                                VBObjectFile2DKeyFrameElementGraphic* _graphic = (VBObjectFile2DKeyFrameElementGraphic*)VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                                VBFloat t = (_e - _b) == 0.0f ? 0.0 : (this->cur_frame - _b) / (_e - _b);
                                if(t > 1.0)
                                    t = 1.0;
                                VBObjectFile2DKeyFrameElementGraphicGetTransitionProperties(_graphic, t, &mat, &color); 
                                child->setPosition(CCPoint(mat.position.x, mat.position.y));
                                child->setAnchorPoint(CCPoint(mat.anchor.x, mat.anchor.y));
                                child->setScaleX(mat.scale.x);
                                child->setScaleY(mat.scale.y);
                                child->setSkewX(mat.shear.x);
                                child->setSkewY(mat.shear.y);
                                child->setRotation(mat.rotation);
                                ccColor3B _color3B;
                                _color3B.r = color.r;
                                _color3B.g = color.g;
                                _color3B.b = color.b;
                                child->setColor(_color3B);
                                child->setOpacity(color.a);
                            } else if(VBObjectFile2DKeyFrameElementType_MovieClip == VBObjectFile2DKeyFrameElementGetType(_element)) {
                                VBMatrix2DWrapper mat;
                                VBColorRGBA color;
                                VBObjectFile2DKeyFrameElementMovieClip* _movie_clip = (VBObjectFile2DKeyFrameElementMovieClip*)VBObjectFile2DKeyFrameElementGetBaseElement(_element);
                                VBFloat t = (_e - _b) == 0.0f ? 0.0 : (this->cur_frame - _b) / (_e - _b);
                                if(t > 1.0)
                                    t = 1.0;
                                VBObjectFile2DKeyFrameElementMovieClipGetTransitionProperties(_movie_clip, t, &mat, &color); 
                                child->setPosition(CCPoint(mat.position.x, mat.position.y));
                                child->setAnchorPoint(CCPoint(mat.anchor.x, mat.anchor.y));
                                child->setScaleX(mat.scale.x);
                                child->setScaleY(mat.scale.y);
                                child->setSkewX(mat.shear.x);
                                child->setSkewY(mat.shear.y);
                                child->setRotation(mat.rotation);
                                ccColor3B _color3B;
                                _color3B.r = color.r;
                                _color3B.g = color.g;
                                _color3B.b = color.b;
                                child->setColor(_color3B);
                                child->setOpacity(color.a);
                            }
                        }
                        this->addChild(child);
                    }
                }
            }
            this->is_animation_update = VBFalse;
        }
    }
    if(this->getChildren()) {
        for(int i = 0; i < this->getChildren()->count(); i++) {
            VBModel* _child =  (VBModel*)this->getChildren()->objectAtIndex(i);
            _child->VBModelUpdate(_tick);
        }
    }
}


void VBModel::setTextureRectInPixels(CCRect rect, bool rotated, CCSize size) {
    m_obRectInPixels = rect;
	m_obRect = CC_RECT_PIXELS_TO_POINTS(rect);
	m_bRectRotated = rotated;
    
	setContentSizeInPixels(size);
	updateTextureCoords(m_obRectInPixels);
    
	CCPoint relativeOffsetInPixels = m_obUnflippedOffsetPositionFromCenter;
    
	if (m_bFlipX)
	{
		relativeOffsetInPixels.x = -relativeOffsetInPixels.x;
	}
	if (m_bFlipY)
	{
		relativeOffsetInPixels.y = -relativeOffsetInPixels.y;
	}
    
	m_obOffsetPositionInPixels.x = relativeOffsetInPixels.x + (m_tContentSizeInPixels.width - m_obRectInPixels.size.width) / 2;
	m_obOffsetPositionInPixels.y = relativeOffsetInPixels.y + (m_tContentSizeInPixels.height - m_obRectInPixels.size.height) / 2;
    
	if (m_bUsesBatchNode)
	{
		m_bDirty = true;
	}
	else
	{
		m_sQuad.bl.vertices = vertex3(0, 0, 0);
		m_sQuad.br.vertices = vertex3(m_obRectInPixels.size.width, 0, 0);
		m_sQuad.tl.vertices = vertex3(0, -m_obRectInPixels.size.height, 0);
		m_sQuad.tr.vertices = vertex3(m_obRectInPixels.size.width, -m_obRectInPixels.size.height, 0);
	}
}

void VBModel::updateTextureCoords(CCRect rect) {
    CCTexture2D *tex = m_bUsesBatchNode ? m_pobTextureAtlas->getTexture() : m_pobTexture;
	if (! tex)
	{
		return;
	}
    
	float atlasWidth = (float)tex->getPixelsWide();
	float atlasHeight = (float)tex->getPixelsHigh();
    
	float left, right, top, bottom;
    
    left	= rect.origin.x/atlasWidth;
    right	= left + rect.size.width/atlasWidth;
    top		= rect.origin.y/atlasHeight;
    bottom	= top + rect.size.height/atlasHeight;
    
    m_sQuad.bl.texCoords.u = left;
    m_sQuad.bl.texCoords.v = top;
    m_sQuad.br.texCoords.u = right;
    m_sQuad.br.texCoords.v = top;
    m_sQuad.tl.texCoords.u = left;
    m_sQuad.tl.texCoords.v = bottom;
    m_sQuad.tr.texCoords.u = right;
    m_sQuad.tr.texCoords.v = bottom;
    
}

CCAffineTransform VBModel::nodeToParentTransform(void) {
	if (m_bIsTransformDirty) {
        mat = VBMatrix2DWrapperLoadIdentity();
		
        mat = VBMatrix2DWrapperSetPosition(mat, VBVector2DCreate(m_tPosition.x, -m_tPosition.y));
        mat = VBMatrix2DWrapperSetScale(mat, VBVector2DCreate(m_fScaleX, m_fScaleY));
        mat = VBMatrix2DWrapperSetShear(mat, VBVector2DCreate(m_fSkewX, -m_fSkewY));
        mat = VBMatrix2DWrapperSetRotation(mat, -m_fRotation);
        mat = VBMatrix2DWrapperSetAnchor(mat, VBVector2DCreate(m_tAnchorPoint.x, -m_tAnchorPoint.y));
        mat = VBMatrix2DWrapperUpdate(mat);
        
		m_tTransform = CCAffineTransformMake(mat.mat.m11, mat.mat.m21, mat.mat.m12, mat.mat.m22, mat.mat.m13, mat.mat.m23);
        
		m_bIsTransformDirty = false;
	}
    
	return m_tTransform;
}
