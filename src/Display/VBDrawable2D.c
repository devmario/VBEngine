#include "VBDrawable2D.h"
#include "../VBEngine.h"
#include "../VBConfig.h"
#include <string.h>
#include <stdlib.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#define _DEFAULT_STEPSIZE_ 100

VBDrawable2D* VBDrawable2DAlloc(void) {
	VBDrawable2D* _drawable = VBSystemCalloc(1, sizeof(VBDrawable2D));
	
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAlloc() - 메모리 할당에 실패하였습니다.");
#endif
    	
	return _drawable;
}

VBDrawable2D* VBDrawable2DInit(VBDrawable2D* _drawable) {
#ifdef _VB_DEBUG_
    if(_drawable == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBDrawable2DInit() - 초기화에 실패하였습니다.");
    
#endif
    
    _drawable->draw_type = VBDrawable2DType_None;
	_drawable->poly_len = 0;
	
	if(_drawable->color)
		VBSystemFree(_drawable->color);
	_drawable->color = VBNull;
	
	if(_drawable->vtx)
		VBSystemFree(_drawable->vtx);
	_drawable->vtx = VBNull;
	
	if(_drawable->txc)
		VBSystemFree(_drawable->txc);
	_drawable->txc = VBNull;
	
	_drawable->idx_len = 0;
	
	if(_drawable->idx)
		VBSystemFree(_drawable->idx);
	_drawable->idx = VBNull;
    
    _drawable->useStepSize = VBFalse;
    _drawable->poly_stepSize = 0;
    _drawable->idx_stepSize = 0;
	
    return _drawable;
}

VBDrawable2D* VBDrawable2DInitWithStepSize(VBDrawable2D* _drawable) {
#ifdef _VB_DEBUG_
    if(_drawable == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
                                         VBTrue, 
                                         "VBEngine Log: VBDrawable2DInit() - 초기화에 실패하였습니다.");
    
#endif
    
    _drawable->useStepSize = VBTrue;
    _drawable->poly_stepSize = _DEFAULT_STEPSIZE_;
    _drawable->idx_stepSize = _DEFAULT_STEPSIZE_;
    
    _drawable->draw_type = VBDrawable2DType_None;
	_drawable->poly_len = 0;
	
    
    if(_drawable->color) {
        VBSize _size = VBColorTypeGetSize(VBColorType_RGBA) * _drawable->poly_stepSize;
        _drawable->color = VBSystemRealloc(_drawable->color, _size);
    } else {
        VBSize _size = VBColorTypeGetSize(VBColorType_RGBA) * _drawable->poly_stepSize;
        _drawable->color = VBSystemMalloc(_size);
    }
	
    if(_drawable->vtx) {
		VBSize _size = sizeof(VBVector2D) * _drawable->poly_stepSize;
        _drawable->vtx = VBSystemRealloc(_drawable->vtx, _size);
    } else {
        VBSize _size = sizeof(VBVector2D) * _drawable->poly_stepSize;
        _drawable->vtx = VBSystemMalloc(_size);
    }
	
	if(_drawable->txc) {
        VBSize _size = sizeof(VBVector2D) * _drawable->poly_stepSize;
        _drawable->txc = VBSystemRealloc(_drawable->txc, _size);
    } else {
        VBSize _size = sizeof(VBVector2D) * _drawable->poly_stepSize;
        _drawable->txc = VBSystemMalloc(_size);
    }
	
	_drawable->idx_len = 0;
	
	if(_drawable->idx) {
        VBSize _size = sizeof(VBUShort) * _drawable->poly_stepSize;
        _drawable->idx = VBSystemRealloc(_drawable->idx, _size);
    } else {
        VBSize _size = sizeof(VBUShort) * _drawable->poly_stepSize;
        _drawable->idx = VBSystemMalloc(_size);
    }
	
    return _drawable;
}

VBDrawable2D* VBDrawable2DInitWithTexture(VBDrawable2D* _drawable, VBDrawable2DType _draw_type, VBTexture* _tex) {
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DInitWithTexture() - VBNull인 Draw요소는 초기화 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
#endif
    
    _drawable = VBDrawable2DInit(_drawable);
	_drawable->tex = _tex;
	_drawable->draw_type = _draw_type;
	
	return _drawable;
}

VBDrawable2D* VBDrawable2DInitWithData(VBDrawable2D* _drawable, VBDrawable2DType _draw_type,
									   VBTexture* _tex, 
									   VBUShort _poly_len, 
									   VBColorRGBA* _color, VBVector2D* _vtx, VBVector2D* _txc, 
									   VBUShort _idx_len, VBUShort* _idx) {
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DInitWithData() - VBNull인 Draw요소는 초기화 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DInitWithData() - 텍스쳐가 없는 Draw요소는 초기화 할수 없습니다.");
	
	if(_poly_len == 0)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DInitWithData() - 폴리곤이 없는 Draw요소는 초기화 할수 없습니다.");
	
	if(_color == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DInitWithData() - 칼라가 없는 Draw요소는 초기화 할수 없습니다.");
	
	if(_vtx == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DInitWithData() - 버텍스가 없는 Draw요소는 초기화 할수 없습니다.");
	
	if(_txc == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DInitWithData() - 텍스쳐좌표가 없는 Draw요소는 초기화 할수 없습니다.");
	
	if(_idx_len == 0)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DInitWithData() - 폴리곤인덱스가 없는 Draw요소는 초기화 할수 없습니다.");
	
	if(_idx == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DInitWithData() - 폴리곤인덱스가 없는 Draw요소는 초기화 할수 없습니다.");
#endif
	
	_drawable = VBDrawable2DInitWithTexture(_drawable, _draw_type, _tex);
    
	_drawable->poly_len = _poly_len;
	
	VBSize _size = VBColorTypeGetSize(VBColorType_RGBA) * _poly_len;
	_drawable->color = VBSystemMalloc(_size);
	memcpy(_drawable->color, _color, _size);
	
	_size = _poly_len * sizeof(VBVector2D);
	_drawable->vtx = VBSystemMalloc(_size);
	memcpy(_drawable->vtx, _vtx, _size);
	
	_size = _poly_len * sizeof(VBVector2D);
	_drawable->txc = VBSystemMalloc(_size);
	memcpy(_drawable->txc, _txc, _size);
	
	_drawable->idx_len = _idx_len;
	
	_size = _idx_len * sizeof(VBUShort);
	_drawable->idx = VBSystemMalloc(_size);
	memcpy(_drawable->idx, _idx, _size);
	
	return _drawable;
}


void VBDrawable2DSetData(VBDrawable2D* _drawable, VBDrawable2DType _draw_type,
                         VBTexture* _tex, VBUShort _poly_len, 
                         VBColorRGBA* _color, VBVector2D* _vtx, VBVector2D* _txc, 
                         VBUShort _idx_len, VBUShort* _idx) {
	_drawable->tex = _tex;
	_drawable->draw_type = _draw_type;
    
    if(_drawable->poly_len != _poly_len) {
        _drawable->poly_len = _poly_len;
        
        if(_drawable->vtx == NULL)
            _drawable->vtx = calloc(_poly_len, sizeof(VBVector2D));
        else
            _drawable->vtx = realloc(_drawable->vtx, _poly_len * sizeof(VBVector2D));
        
        if(_drawable->color == NULL)
            _drawable->color = calloc(_poly_len, VBColorTypeGetSize(VBColorType_RGBA));
        else
            _drawable->color = realloc(_drawable->color, _poly_len * VBColorTypeGetSize(VBColorType_RGBA));
        
        if(_drawable->txc == NULL)
            _drawable->txc = calloc(_poly_len, sizeof(VBVector2D));
        else
            _drawable->txc = realloc(_drawable->txc, _poly_len * sizeof(VBVector2D));
    }
    
    if(_drawable->idx_len != _idx_len) {
        _drawable->idx_len = _idx_len;
        if(_drawable->idx == NULL)
            _drawable->idx = calloc(_idx_len, sizeof(VBUShort));
        else
            _drawable->idx = realloc(_drawable->txc, _idx_len * sizeof(VBUShort));
    }
	memcpy(_drawable->color, _color, _poly_len * VBColorTypeGetSize(VBColorType_RGBA));
	memcpy(_drawable->vtx, _vtx, _poly_len * sizeof(VBVector2D));
	memcpy(_drawable->txc, _txc, _poly_len * sizeof(VBVector2D));
	memcpy(_drawable->idx, _idx, _idx_len * sizeof(VBUShort));
}

void VBDrawable2DFree(VBDrawable2D** _drawable) {
#ifdef _VB_DEBUG_
	if(*_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DFree() - VBNull인 Draw요소는 해제 할수 없습니다. VBDrawable2DAlloc()하지 않았거나 이미 VBDrawable2DFree()했을 수 있습니다.");
#endif
	
	VBDrawable2DInit(*_drawable);
	VBSystemFree(*_drawable);
	*_drawable = VBNull;
}

void VBDrawable2DAppend(VBDrawable2D* _drawable_1, VBDrawable2D* _drawable_2) {
#ifdef _VB_DEBUG_
    if(_drawable_1 == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAppend() - VBNull인 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc()하지 않았을 수 있습니다.");
    if(_drawable_2 == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAppend() - VBNull인 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc()하지 않았을 수 있습니다.");

    if(VBDrawable2DGetTexture(_drawable_2) == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAppend() - 텍스쳐가 없거나 다른 2개의 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc()하지 않았을 수 있습니다.");
        
#endif
    if(_drawable_1->tex == VBNull) {
//         VBDrawable2DInitWithData(_drawable_1, _drawable_2->draw_type, _drawable_2->tex, _drawable_2->poly_len, _drawable_2->color, _drawable_2->vtx, _drawable_2->txc, _drawable_2->idx_len, _drawable_2->idx);
//        return;
        _drawable_1->tex = _drawable_2->tex;
    }
        
    
#ifdef _VB_DEBUG_
	if(_drawable_1 == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAppend() - VBNull인 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(_drawable_2 == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAppend() - VBNull인 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetTexture(_drawable_1) != VBDrawable2DGetTexture(_drawable_2))
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAppend() - 텍스쳐가 없거나 다른 2개의 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetColor(_drawable_1) == VBNull || VBDrawable2DGetColor(_drawable_2) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAppend() - 칼라가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetVertex(_drawable_1) == VBNull || VBDrawable2DGetVertex(_drawable_2) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAppend() - 버텍스가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetTexcoord(_drawable_1) == VBNull || VBDrawable2DGetTexcoord(_drawable_2) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAppend() - 텍스쳐좌표가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetIndex(_drawable_1) == VBNull || VBDrawable2DGetIndex(_drawable_2) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAppend() - 인덱스가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
#endif
    
    VBSize _prev_poly_len = _drawable_1->poly_len;
    VBSize _next_poly_len = _drawable_2->poly_len;
    _drawable_1->poly_len += _drawable_2->poly_len;
    
    VBSize _prev_idx_len = _drawable_1->idx_len;
    VBSize _next_idx_len = _drawable_2->idx_len;
    _drawable_1->idx_len += _drawable_2->idx_len;
    
    if(_drawable_1->useStepSize) {
        if(_drawable_1->poly_len > _drawable_1->poly_stepSize) {
            _drawable_1->poly_stepSize += _DEFAULT_STEPSIZE_;
            VBSize _size;
            _size = VBColorTypeGetSize(VBColorType_RGBA) * _drawable_1->poly_stepSize;
            _drawable_1->color = VBSystemRealloc(_drawable_1->color, _size);
            
            _size = sizeof(VBVector2D) * _drawable_1->poly_stepSize;
            _drawable_1->vtx = VBSystemRealloc(_drawable_1->vtx, _size);
            
            _size = sizeof(VBVector2D) * _drawable_1->poly_stepSize;
            _drawable_1->txc = VBSystemRealloc(_drawable_1->txc, _size);
        }
        if(_drawable_1->idx_len > _drawable_1->idx_stepSize) {
            _drawable_1->idx_stepSize += _DEFAULT_STEPSIZE_;
            VBSize _size = sizeof(VBUShort) * _drawable_1->idx_stepSize;
            _drawable_1->idx = VBSystemRealloc(_drawable_1->idx, _size);
        }
    } else {
        VBSize _size;
        _size = VBColorTypeGetSize(VBColorType_RGBA) * _drawable_1->poly_len;
        _drawable_1->color = VBSystemRealloc(_drawable_1->color, _size);
        
        _size = sizeof(VBVector2D) * _drawable_1->poly_len;
        _drawable_1->vtx = VBSystemRealloc(_drawable_1->vtx, _size);
        
        _size = sizeof(VBVector2D) * _drawable_1->poly_len;
        _drawable_1->txc = VBSystemRealloc(_drawable_1->txc, _size);
        
        _size = sizeof(VBUShort) * _drawable_1->idx_len;
        _drawable_1->idx = VBSystemRealloc(_drawable_1->idx, _size);
    }
    
    VBColorRGBA* _color = _drawable_1->color + _prev_poly_len;
    memcpy(_color, _drawable_2->color, VBColorTypeGetSize(VBColorType_RGBA) * _next_poly_len);
    
    VBVector2D* _vtx = _drawable_1->vtx + _prev_poly_len;
    memcpy(_vtx, _drawable_2->vtx, sizeof(VBVector2D) * _next_poly_len);
    
    VBVector2D* _txc = _drawable_1->txc + _prev_poly_len;
    memcpy(_txc, _drawable_2->txc, sizeof(VBVector2D) * _next_poly_len);
        
    VBUShort* _idx = _drawable_1->idx + _prev_idx_len;
    memcpy(_idx, _drawable_2->idx, sizeof(VBUShort) * _next_idx_len);
    
    VBLong _i;
    for(_i = 0; _i < _next_idx_len; _i++)
        _idx[_i] += _prev_poly_len;
}

void VBDrawable2DBegin(VBDrawable2D* _drawable, VBColorRGBA _color, VBVector2D _vtx, VBVector2D _txc) {
    if(VBDrawable2DGetTexture(_drawable) == VBNull) 
        return;
    
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DBegin() - VBNull인 Draw요소는 설정 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetTexture(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DBegin() - 텍스쳐가 없는 Draw요소는 설정 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetColor(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DBegin() - 칼라가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetVertex(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DBegin() - 버텍스가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetTexcoord(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DBegin() - 텍스쳐좌표가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetIndex(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DBegin() - 인덱스가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
#endif
	
	VBSize _prev_poly_len = _drawable->poly_len;
	_drawable->poly_len += 1;
	VBSize _prev_idx_len = _drawable->idx_len;
	_drawable->idx_len += 3;
	
	VBSize _size = sizeof(VBColorRGBA) * _drawable->poly_len;
	_drawable->color = VBSystemRealloc(_drawable->color, _size);
	VBColorRGBA* _color_ptr = _drawable->color + _prev_poly_len;
	*_color_ptr = _color;
    	
	_size = sizeof(VBVector2D) * _drawable->poly_len;
	_drawable->vtx = VBSystemRealloc(_drawable->vtx, _size);
	VBVector2D* _vtx_ptr = _drawable->vtx + _prev_poly_len;
	*_vtx_ptr = _vtx;
	
	_size = sizeof(VBVector2D) * _drawable->poly_len;
	_drawable->txc = VBSystemRealloc(_drawable->txc, _size);
	VBVector2D* _txc_ptr = _drawable->txc + _prev_poly_len;
	*_txc_ptr = _txc;
	
	_size = sizeof(VBUShort) * _drawable->idx_len;
	_drawable->idx = VBSystemRealloc(_drawable->idx, _size);
	VBUShort* _idx_ptr = _drawable->idx + _prev_idx_len;
	*_idx_ptr = *(_idx_ptr - 1);
	_idx_ptr++;
	*_idx_ptr = _drawable->poly_len - 1;
	_idx_ptr++;
	*_idx_ptr = _drawable->poly_len - 1;
}

void VBDrawable2DAdd(VBDrawable2D* _drawable, VBColorRGBA _color, VBVector2D _vtx, VBVector2D _txc) {
    if(VBDrawable2DGetTexture(_drawable) == VBNull) 
        return;
    
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAdd() - VBNull인 Draw요소는 설정 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetTexture(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAdd() - 텍스쳐가 없는 Draw요소는 설정 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetColor(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAdd() - 칼라가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetVertex(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAdd() - 버텍스가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetTexcoord(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAdd() - 텍스쳐좌표가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetIndex(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DAdd() - 인덱스가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
#endif
	
	VBSize _prev_poly_len = _drawable->poly_len;
	_drawable->poly_len += 1;
	VBSize _prev_idx_len = _drawable->idx_len;
	_drawable->idx_len += 1;
	
	VBSize _prev_size = sizeof(VBColorRGBA) * _prev_poly_len;
	VBSize _size = sizeof(VBColorRGBA) * _drawable->poly_len;
	_drawable->color = VBSystemRealloc(_drawable->color, _size);
	VBColorRGBA* _color_ptr = _drawable->color + _prev_size;
	*_color_ptr = _color;
	
	_prev_size = sizeof(VBVector2D) * _prev_poly_len;
	_size = sizeof(VBVector2D) * _drawable->poly_len;
	_drawable->vtx = VBSystemRealloc(_drawable->vtx, _size);
	VBVector2D* _vtx_ptr = _drawable->vtx + _prev_size;
	*_vtx_ptr = _vtx;
	
	_prev_size = sizeof(VBVector2D) * _prev_poly_len;
	_size = sizeof(VBVector2D) * _drawable->poly_len;
	_drawable->txc = VBSystemRealloc(_drawable->txc, _size);
	VBVector2D* _txc_ptr = _drawable->txc + _prev_size;
	*_txc_ptr = _txc;
	
	_prev_size = sizeof(VBUShort) * _prev_idx_len;
	_size = sizeof(VBUShort) * _drawable->idx_len;
	_drawable->idx = VBSystemRealloc(_drawable->idx, _size);
	VBUShort* _idx_ptr = _drawable->idx + _prev_size;
	*_idx_ptr = _drawable->poly_len - 1;
}

void VBDrawable2DEnd(VBDrawable2D* _drawable, VBColorRGBA _color, VBVector2D _vtx, VBVector2D _txc) {
    if(VBDrawable2DGetTexture(_drawable) == VBNull) 
        return;
    
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DEnd() - VBNull인 Draw요소는 설정 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetTexture(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DEnd() - 텍스쳐가 없는 Draw요소는 설정 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetColor(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DEnd() - 칼라가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetVertex(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DEnd() - 버텍스가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetTexcoord(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DEnd() - 텍스쳐좌표가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
	
	if(VBDrawable2DGetIndex(_drawable) == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DEnd() - 인덱스가 없는 Draw요소는 연결 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
#endif
	
	VBSize _prev_poly_len = _drawable->poly_len;
	_drawable->poly_len += 1;
	VBSize _prev_idx_len = _drawable->idx_len;
	_drawable->idx_len += 1;
	
	VBSize _size = sizeof(VBColorRGBA) * _drawable->poly_len;
	_drawable->color = VBSystemRealloc(_drawable->color, _size);
	VBColorRGBA* _color_ptr = _drawable->color + _prev_poly_len;
	*_color_ptr = _color;
	
	_size = sizeof(VBVector2D) * _drawable->poly_len;
	_drawable->vtx = VBSystemRealloc(_drawable->vtx, _size);
	VBVector2D* _vtx_ptr = _drawable->vtx + _prev_poly_len;
	*_vtx_ptr = _vtx;
	
	_size = sizeof(VBVector2D) * _drawable->poly_len;
	_drawable->txc = VBSystemRealloc(_drawable->txc, _size);
	VBVector2D* _txc_ptr = _drawable->txc + _prev_poly_len;
	*_txc_ptr = _txc;
	
	_size = sizeof(VBUShort) * _drawable->idx_len;
	_drawable->idx = VBSystemRealloc(_drawable->idx, _size);
	VBUShort* _idx_ptr = _drawable->idx + _prev_idx_len;
	*_idx_ptr = _drawable->poly_len - 1;
}

void VBDrawable2DClear(VBDrawable2D* _drawable) {
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DClear() - VBNull인 Draw요소는 Clear 할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
#endif
	
	VBDrawable2DInitWithTexture(_drawable, _drawable->draw_type, _drawable->tex);
}

void VBDrawable2DDraw(VBDrawable2D* _drawable) {
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DDraw() - VBNull인 Draw요소는 그릴수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
#endif
	GLboolean _state;
    
	_state = glIsEnabled(GL_BLEND);
	if(!_state)
		glEnable(GL_BLEND);
    
    GLint _bendSRC, _bendDST;
    glGetIntegerv(GL_BLEND_SRC, &_bendSRC);
    glGetIntegerv(GL_BLEND_DST, &_bendDST);
    if(_bendSRC != GL_SRC_ALPHA || _bendDST != GL_ONE_MINUS_SRC_ALPHA)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	_state = glIsEnabled(GL_COLOR_MATERIAL);
	if(!_state)
		glEnable(GL_COLOR_MATERIAL);
	
	_state = glIsEnabled(GL_TEXTURE_2D);
	if(!_state)
		glEnable(GL_TEXTURE_2D);
    
    GLint _texID  = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &_texID);
    if(_texID != VBTextureGetID(VBDrawable2DGetTexture(_drawable))) {
        glBindTexture(GL_TEXTURE_2D, VBTextureGetID(VBDrawable2DGetTexture(_drawable)));
#ifdef _VB_UNITY_3D_
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
#endif
    }
	
    _state = glIsEnabled(GL_COLOR_ARRAY);
    if(_drawable->color) {
        if(_state == VBFalse)
            glEnableClientState(GL_COLOR_ARRAY); 
    } else {
        if(_state == VBTrue)
            glDisableClientState(GL_COLOR_ARRAY);
    }
    
    if(_drawable->color) {
        GLvoid* _glcolor = VBNull;
        glGetPointerv(GL_COLOR_ARRAY_POINTER, &_glcolor);
        if(_drawable->color != _glcolor) {
            glColorPointer(VBColorTypeGetSize(VBColorType_RGBA), GL_UNSIGNED_BYTE, 0, _drawable->color);
        }
    }
    
    _state = glIsEnabled(GL_VERTEX_ARRAY);
    if(_drawable->vtx) {
        if(_state == VBFalse)
            glEnableClientState(GL_VERTEX_ARRAY);
    } else {
        if(_state == VBTrue)
            glDisableClientState(GL_VERTEX_ARRAY);
    }
    
    if(_drawable->vtx) {
        GLvoid* _glvtx = VBNull;
        glGetPointerv(GL_COLOR_ARRAY_POINTER, &_glvtx);
        if(_drawable->vtx != _glvtx) {
            glVertexPointer(2, GL_FLOAT, 0, _drawable->vtx);
        }
    }
    
    _state = glIsEnabled(GL_TEXTURE_COORD_ARRAY);
    if(_drawable->color) {
        if(_state == VBFalse)
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    } else {
        if(_state == VBTrue)
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    
    if(_drawable->txc) {
        GLvoid* _gltxc = VBNull;
        glGetPointerv(GL_TEXTURE_COORD_ARRAY_POINTER, &_gltxc);
        if(_drawable->txc != _gltxc) {
            glTexCoordPointer(2, GL_FLOAT, 0, _drawable->txc);
        }
    }
    
#ifndef _VB_VISIBLE_VERTEX_LINE_
    glDrawElements(GL_TRIANGLES, _drawable->idx_len, GL_UNSIGNED_SHORT, _drawable->idx);
#endif
    
#ifdef _VB_VISIBLE_VERTEX_LINE_
    glDisable(GL_TEXTURE_2D);
    glDrawElements(GL_LINE_LOOP, _drawable->idx_len, GL_UNSIGNED_SHORT, _drawable->idx);
#endif
}

VBTexture* VBDrawable2DGetTexture(VBDrawable2D* _drawable) {
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DGetTexture() - VBNull인 Draw요소는 접근할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
#endif
	
	return _drawable->tex;
}

VBUShort VBDrawable2DGetPolygonLength(VBDrawable2D* _drawable) {
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DGetPolygonLength() - VBNull인 Draw요소는 접근할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
#endif
	
	return _drawable->poly_len;
}

VBColorRGBA* VBDrawable2DGetColor(VBDrawable2D* _drawable) {
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DGetColor() - VBNull인 Draw요소는 접근할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
#endif
	
	return _drawable->color;
}

VBVector2D* VBDrawable2DGetVertex(VBDrawable2D* _drawable) {
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DGetVertex() - VBNull인 Draw요소는 접근할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
#endif
	
	return _drawable->vtx;
}

VBVector2D* VBDrawable2DGetTexcoord(VBDrawable2D* _drawable) {
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DGetTexcoord() - VBNull인 Draw요소는 접근할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
#endif
	
	return _drawable->txc;
}

VBUShort VBDrawable2DGetIndexLength(VBDrawable2D* _drawable) {
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DGetIndexLength() - VBNull인 Draw요소는 접근할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
#endif
	
	return _drawable->idx_len;
}

VBUShort* VBDrawable2DGetIndex(VBDrawable2D* _drawable) {
#ifdef _VB_DEBUG_
	if(_drawable == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBDrawable2DGetIndex() - VBNull인 Draw요소는 접근할수 없습니다. VBDrawable2DAlloc하지 않았을 수 있습니다.");
#endif
	
	return _drawable->idx;
}
void VBDrawable2DSetTexture(VBDrawable2D* _drawable, VBTexture* _tex) {
    _drawable->tex = _tex;
}

VBDrawable2DType VBDrawable2DGetDrawType(VBDrawable2D* _drawable) {
    return _drawable->draw_type;
}

VBBool VBDrawable2DGetTriangle(VBDrawable2D* _drawable, VBUShort* _cur_step, VBTriangle2D* _tri) {
    VBDrawable2DType _type = VBDrawable2DGetDrawType(_drawable);
    VBVector2D* _vtx = VBDrawable2DGetVertex(_drawable);
    VBUShort _poly_len = VBDrawable2DGetPolygonLength(_drawable);
    if(_type == VBDrawable2DType_TriangleFan) {
        if(_poly_len <= *_cur_step + 2)
            return VBFalse;
        _tri->a = _vtx[0];
        _tri->b = _vtx[*_cur_step + 1];
        _tri->c = _vtx[*_cur_step + 2];
        *_cur_step += 1;
    }
    return VBTrue;
}

