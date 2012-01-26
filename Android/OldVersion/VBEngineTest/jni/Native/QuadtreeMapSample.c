#include "QuadtreeMapSample.h"
#include "QuadtreeMapSample.h"
#include <stdio.h>
#include <pthread.h>

QuadtreeMapTouch* _QuadtreeMapTouchAllocAndInit(void* _id, QuadtreeMapTouchType _type, VBFloat _x, VBFloat _y) {
    QuadtreeMapTouch* _touch = VBSystemCalloc(1, sizeof(QuadtreeMapTouch));
    
    _touch->touch_id = _id;
    _touch->type = _type;
    _touch->postion = VBVector2DCreate(_x, _y);
    
    return _touch;
}

VBBool _QuadtreeSlice(VBQuadtree* _quad) {
    QuadtreeMapSample* _quadtree_map = _quad->reference;
    
    VBVector2D LT = VBVector2DCreate(_quad->x - 4096.0f, 
                                     _quad->y - 4096.0f);
    VBVector2D RB = VBVector2DCreate(_quad->x - 4096.0f + _quad->width, 
                                     _quad->y - 4096.0f + _quad->height);
    
    LT = VBMatrix2DMultiplyVBVector2D(_quadtree_map->camera, LT);
    RB = VBMatrix2DMultiplyVBVector2D(_quadtree_map->camera, RB);
    
    if(0.0 > RB.x)
        return VBFalse;
    if(_quadtree_map->screen_width < LT.x)
        return VBFalse;
    if(0.0 > RB.y)
        return VBFalse;
    if(_quadtree_map->screen_height < LT.y)
        return VBFalse;
    
    if(_quad->size * _quadtree_map->scale < 256)
        return VBFalse;
    
    return VBTrue;
}

void _QuadtreeApear(VBQuadtree* _quad, VBBool _is_apear) {
    QuadtreeMapSample* _quadtree_map = _quad->reference;
    
    if(_is_apear) {
        if(_quad->user_reference == VBNull) {
            VBFloat _per_pow = _quad->size / 256.0f * 2.0f;
            VBLong _depth = 0;
            while(_per_pow > 2.0f) {
                _per_pow *= 0.5;
                _depth++;
            }
            VBLong _x = (VBLong)(_quad->x / _quad->size);
            VBLong _y = (VBLong)(_quad->y / _quad->size);
            
            VBString* _path = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/beatles_%i_%i_%i.png", 
                                                            VBStringGetCString(_quadtree_map->resource_path), 
                                                            _depth, _x, _y);
            VBTexture* _texture = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _path);
            VBStringFree(&_path);
            
            VBModel2D* _model = VBModel2DInitWithTexture(VBModel2DAlloc(), _texture);
            VBModel2DSetPosition(_model, VBVector2DCreate(_quad->x - 4096.0f, _quad->y - 4096.0f));
            VBModel2DSetScale(_model, VBVector2DCreate(_quad->width / 256.0f, _quad->height / 256.0f));
            VBModel2DAddChildModel(_quadtree_map->map_model, _model);
            
            _quad->user_reference = _model;
        }
    } else {
        if(_quad->user_reference) {
            VBModel2D* _model = _quad->user_reference;
            
            VBTexture* _texture = VBDrawable2DGetTexture(VBModel2DGetOriginDrawable(_model));
            VBModel2DRemoveChildModel(_quadtree_map->map_model, _model);
            VBModel2DFree(&_model);
            
            VBTextureFree(&_texture);
            _quad->user_reference = VBNull;
        }
    }
}

QuadtreeMapSample* QuadtreeMapSampleAlloc() {
    return VBSystemCalloc(1, sizeof(QuadtreeMapSample));
}

QuadtreeMapSample* QuadtreeMapSampleInit(QuadtreeMapSample* _quadtree_map,
                                         const VBChar* _res_path, 
                                         VBUShort _w, VBUShort _h,
                                         VBColorRGBA _bg_color) {
    
    //리소스
    _quadtree_map->resource_path = VBStringInitWithCString(VBStringAlloc(), _res_path);
    
    //사이즈 설정
    _quadtree_map->screen_width = _w;
    _quadtree_map->screen_height = _h;
    
    //디스플레이 설정
    _quadtree_map->display2D = VBDisplay2DInitWithScreenSize(VBDisplay2DAlloc(), _w, _h);
    
    //맵 모델
    _quadtree_map->map_model = VBModel2DInit(VBModel2DAlloc());
    
    //카메라 매트릭스 및 위치 스케일
    _quadtree_map->slide = VBVector2DCreate(160.0f, 240.0f);
    _quadtree_map->camera = VBMatrix2DLoadIdentity();
    _quadtree_map->camera = VBMatrix2DTranslateV(_quadtree_map->camera, _quadtree_map->slide);
    _quadtree_map->scale = 320.0f / 8192.0f;
    _quadtree_map->camera = VBMatrix2DScale(_quadtree_map->camera, _quadtree_map->scale, _quadtree_map->scale);
    
    VBModel2DSetMatrix(_quadtree_map->map_model, _quadtree_map->camera);
    
    VBModel2DAddChildModel(VBDisplay2DGetTopModel(_quadtree_map->display2D), _quadtree_map->map_model);
    
    _quadtree_map->quadtree = VBQuadtreeInit(VBQuadtreeAlloc(), _QuadtreeSlice, _QuadtreeApear, _quadtree_map, 8192, 256);
    
    _quadtree_map->touch_list = VBArrayListInit(VBArrayListAlloc());
    
    return _quadtree_map;
}

void QuadtreeMapSampleFree(QuadtreeMapSample** _quadtree_map) {
    VBStringFree(&(*_quadtree_map)->resource_path);
    
    VBArrayListFree(&(*_quadtree_map)->touch_list);
    
    VBQuadtreeFree(&(*_quadtree_map)->quadtree);
    
    VBModel2DFree(&(*_quadtree_map)->map_model);
    
    //디스플레이 삭제
    VBDisplay2DFree(&(*_quadtree_map)->display2D);
    
    //해제
    VBSystemFree(*_quadtree_map);
    *_quadtree_map = VBNull;
}

void QuadtreeMapSampleDraw(QuadtreeMapSample* _quadtree_map) {
    _quadtree_map->slide = VBVector2DCreate(160.0f, 240.0f);
    _quadtree_map->camera = VBMatrix2DLoadIdentity();
    _quadtree_map->camera = VBMatrix2DTranslateV(_quadtree_map->camera, _quadtree_map->slide);
    if(_quadtree_map->scale < 1.0f) {
        _quadtree_map->scale *= 1.005;
    }
    if(_quadtree_map->scale > 1.0f){
        _quadtree_map->scale = 1.0f;
    }
    _quadtree_map->camera = VBMatrix2DScale(_quadtree_map->camera, _quadtree_map->scale, _quadtree_map->scale);
    VBModel2DSetMatrix(_quadtree_map->map_model, _quadtree_map->camera);
    
    VBArrayListNode* _node = VBArrayListGetNodeAt(_quadtree_map->touch_list, 0);
    while(_node) {
        QuadtreeMapTouch* _touch = VBArrayListNodeGetData(_node);
        VBSystemFree(_touch);
        _node = VBArrayListNodeGetNextNode(_node);
    }
    
    VBQuadtreeSlice(_quadtree_map->quadtree);
    
    //kTypoGraphyMotionSpeed의 시간으로 업데이트 하고 디스플레이 그림
    //VBDisplay2DDraw(_quadtree_map->display2D, kQuadtreeMapSpeed);
}

void QuadtreeMapSampleTouchBegin(QuadtreeMapSample* _quadtree_map, void* _id, VBFloat _x, VBFloat _y) {
    VBArrayListAddBack(_quadtree_map->touch_list, _QuadtreeMapTouchAllocAndInit(_id, QuadtreeMapTouchType_Begin, _x, _y));
}

void QuadtreeMapSampleTouchMove(QuadtreeMapSample* _quadtree_map, void* _id, VBFloat _x, VBFloat _y) {
    VBArrayListAddBack(_quadtree_map->touch_list, _QuadtreeMapTouchAllocAndInit(_id, QuadtreeMapTouchType_Move, _x, _y));
}

void QuadtreeMapSampleTouchEnd(QuadtreeMapSample* _quadtree_map, void* _id, VBFloat _x, VBFloat _y) {
    VBArrayListAddBack(_quadtree_map->touch_list, _QuadtreeMapTouchAllocAndInit(_id, QuadtreeMapTouchType_End, _x, _y));
}

void QuadtreeMapSampleTouchCancel(QuadtreeMapSample* _quadtree_map, void* _id, VBFloat _x, VBFloat _y) {
    VBArrayListAddBack(_quadtree_map->touch_list, _QuadtreeMapTouchAllocAndInit(_id, QuadtreeMapTouchType_Cancel, _x, _y));
}

