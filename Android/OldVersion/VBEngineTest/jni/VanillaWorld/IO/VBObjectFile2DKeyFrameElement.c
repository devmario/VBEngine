#include "VBObjectFile2DKeyFrameElement.h"
#include "VBSystem.h"
#include "../VBEngine.h"

VBObjectFile2DKeyFrameElement* VBObjectFile2DKeyFrameElementAlloc(void) {
    VBObjectFile2DKeyFrameElement* _element = VBSystemCalloc(1, sizeof(VBObjectFile2DKeyFrameElement));
#ifdef _VB_DEBUG_
    if(_element == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementAlloc() - 메모리 할당에 실패하였습니다.");
#endif
    return _element;
}

VBObjectFile2DKeyFrameElement* VBObjectFile2DKeyFrameElementInit(VBObjectFile2DKeyFrameElement* _element) {
#ifdef _VB_DEBUG_
    if(_element == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementInit() - VBNull인 element는 초기화할 수 없습니다. VBObjectFile2DKeyFrameElementAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
    _element->element_type = VBObjectFile2DKeyFrameElementType_None;
    _element->element = VBNull;
    return _element;
}

VBObjectFile2DKeyFrameElement* VBObjectFile2DKeyFrameElementInitWithType(VBObjectFile2DKeyFrameElement* _element, VBObjectFile2DKeyFrameElementType _type, void* _element_base) {
#ifdef _VB_DEBUG_
    if(_element == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementInitWithType() - VBnull인 element는 초기화할 수 없습니다. VBObjectFile2DKeyFrameElementAlloc()하지 않은 파일을 사용했을 수 있습니다.");
    if(_element_base == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementInitWithType() - VBNull인 element_base는 초기화할 수 없습니다.");
#endif
    
    _element = VBObjectFile2DKeyFrameElementInit(_element);
    _element->element_type = _type;
    _element->element = _element_base;
    return _element;
}

void VBObjectFile2DKeyFrameElementFree(VBObjectFile2DKeyFrameElement** _element) {
#ifdef _VB_DEBUG_
    if(*_element == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementFree() - VBNull인 element의 메모리는 해제할 수 없습니다. 이미 VBObjectFile2DKeyFrameElementFree()하였거나 VBObjectFile2DKeyFrameElementAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
    
    *_element = VBObjectFile2DKeyFrameElementInit(*_element);
    VBSystemFree(*_element);
    *_element = VBNull;
}

VBObjectFile2DKeyFrameElementType VBObjectFile2DKeyFrameElementGetType(VBObjectFile2DKeyFrameElement* _element) {
#ifdef _VB_DEBUG_
    if(_element == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementGetType() - VBNull인 element로는 element의 타입을 구할 수 없습니다.");
#endif
    
    return _element->element_type;
}

void* VBObjectFile2DKeyFrameElementGetBaseElement(VBObjectFile2DKeyFrameElement* _element) {
#ifdef _VB_DEBUG_
    if(_element == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementGetBaseElement() - VBNull인 element로는 base element를 구할 수 없습니다.");
#endif
    
    return _element->element;
}

VBObjectFile2DKeyFrameElementBitmap* VBObjectFile2DKeyFrameElementBitmapAlloc(void) {
    VBObjectFile2DKeyFrameElementBitmap* _bitmap = VBSystemCalloc(1, sizeof(VBObjectFile2DKeyFrameElementBitmap));
#ifdef _VB_DEBUG_
    if(_bitmap == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementBitmapAlloc() - 메모리 할당에 실패하였습니다.");
#endif
    
    return _bitmap;
}

VBObjectFile2DKeyFrameElementBitmap* VBObjectFile2DKeyFrameElementBitmapInit(VBObjectFile2DKeyFrameElementBitmap* _bitmap) {
#ifdef _VB_DEBUG_
    if(_bitmap == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementBitmapInit() - VBNull인 bitmap는 초기화할 수 없습니다. VBObjectFile2DKeyFrameElementBitmapInit()하지 않은 파일을 사용했을 수 있습니다.");
#endif
    
    _bitmap->matrix = VBMatrix2DWrapperLoadIdentity();
    return _bitmap;
}

VBObjectFile2DKeyFrameElementBitmap* VBObjectFile2DKeyFrameElementBitmapInitWithData(VBObjectFile2DKeyFrameElementBitmap* _bitmap, VBMatrix2DWrapper _matrix) {
#ifdef _VB_DEBUG_
    if(_bitmap == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementBitmapInitWithData() - VBNull인 bitmap는 초기화할 수 없습니다. VBObjectFile2DKeyFrameElementBitmapInit()하지 않은 파일을 사용했을 수 있습니다.");
        
#endif
    
    _bitmap = VBObjectFile2DKeyFrameElementBitmapInit(_bitmap);
    _bitmap->matrix = _matrix;
    return _bitmap;
}

void VBObjectFile2DKeyFrameElementBitmapFree(VBObjectFile2DKeyFrameElementBitmap** _bitmap) {
#ifdef _VB_DEBUG_
    if(*_bitmap == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementBitmapFree() - VBNull인 bitmap의 메모리를 해제할 수 없습니다. 이미 VBObjectFile2DKeyFrameElementBitmapFree()했거나 VBObjectFile2DKeyFrameElementBitmapInit()하지 않은 파일을 사용했을 수 있습니다.");
#endif
    
    *_bitmap = VBObjectFile2DKeyFrameElementBitmapInit(*_bitmap);
    VBSystemFree(*_bitmap);
    *_bitmap = VBNull;
}

VBObjectFile2DKeyFrameElementGraphic* VBObjectFile2DKeyFrameElementGraphicAlloc(void) {
    VBObjectFile2DKeyFrameElementGraphic* _graphic = VBSystemCalloc(1, sizeof(VBObjectFile2DKeyFrameElementGraphic));
#ifdef _VB_DEBUG_
    if(_graphic == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementGraphicAlloc() - 메모리를 할당할 수 없습니다.");
#endif
    
    return _graphic;
}

VBObjectFile2DKeyFrameElementGraphic* VBObjectFile2DKeyFrameElementGraphicInit(VBObjectFile2DKeyFrameElementGraphic* _graphic) {
#ifdef _VB_DEBUG_
    if(_graphic == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementGraphicInit() - VBNull인 graphic는 초기화할 수 없습니다. VBObjectFile2DKeyFrameElementBitmapInit()하지 않은 파일을 사용했을 수 있습니다.");
#endif
    
    _graphic->blend_mode = VBBlendMode_Normal;
    _graphic->color = VBColorAdvancedCreate(0, 0, 0, 0, 0, 0, 0, 0);
    _graphic->matrix = VBMatrix2DWrapperLoadIdentity();
    _graphic->transition = VBNull;
    return _graphic;
}

VBObjectFile2DKeyFrameElementGraphic* VBObjectFile2DKeyFrameElementGraphicInitWithData(VBObjectFile2DKeyFrameElementGraphic* _graphic, VBBlendMode _blend_mode, VBObjectFile2DTransition* _transition, VBMatrix2DWrapper _matrix, VBColorAdvanced _color) {
#ifdef _VB_DEBUG_
    if(_graphic == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementGraphicInitWithData() - VBNull인 bitmap는 초기화할 수 없습니다. VBObjectFile2DKeyFrameElementBitmapInit()하지 않은 파일을 사용했을 수 있습니다.");
    if(_transition == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementGraphicInitWithData() - VBNull인 transition은 초기활 할 수 없습니다.");
    
#endif
    
    _graphic = VBObjectFile2DKeyFrameElementGraphicInit(_graphic);
    _graphic->blend_mode = _blend_mode;
    _graphic->color = _color;
    _graphic->matrix = _matrix;
    _graphic->transition = _transition;
    _graphic->next = VBNull;
    return _graphic;
}

VBMatrix2DWrapper VBObjectFile2DKeyFrameElementGraphicGetMatrixWrapper(VBObjectFile2DKeyFrameElementGraphic* _graphic) {
#ifdef _VB_DEBUG_
    if(_graphic == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementGraphicGetMatrixWrapper() - VBNull인 graphic으로는 MatrixWrapper를 구할 수 없습니다.");
#endif
    
    return _graphic->matrix;
}

VBColorAdvanced VBObjectFile2DKeyFrameElementGraphicGetColor(VBObjectFile2DKeyFrameElementGraphic* _graphic) {
#ifdef _VB_DEBUG_
    if(_graphic == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: - VBObjectFile2DKeyFrameElementGraphicGetColor() - VBNull인 graphic으로는 Color를 구할 수 없습니다.");
#endif
    
    return _graphic->color;
}

void VBObjectFile2DKeyFrameElementGraphicGetTransitionProperties(VBObjectFile2DKeyFrameElementGraphic* _graphic, VBFloat _t, VBMatrix2DWrapper* _matrix, VBColorAdvanced* _color) {
#ifdef _VB_DEBUG_
    if(_graphic == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementGraphicGetTransitionProperties() - VBNull인 graphic으로는 transition properties를 구할 수 없습니다.");
    if(_matrix == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementGraphicGetTransitionProperties() = VBNull인 matrix로는 transition properties를 구할 수 없습니다.");
    if(_color == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementGraphicGetTransitionProperties() - VBNull인 color로는 transition properties를 구할 수 없습니다.");
#endif
    
    VBObjectFile2DTransition* _transition = VBObjectFile2DKeyFrameElementGraphicGetTransition(_graphic);
    VBMatrix2DWrapper _origin_matrix = VBObjectFile2DKeyFrameElementGraphicGetMatrixWrapper(_graphic);
    VBColorAdvanced _origin_color = VBObjectFile2DKeyFrameElementGraphicGetColor(_graphic);
    if(_transition) {
        VBFloat _value;
        VBObjectFile2DKeyFrameElementGraphic* _next = VBObjectFile2DKeyFrameElementGraphicGetNext(_graphic);
        VBMatrix2DWrapper _next_matrix = VBObjectFile2DKeyFrameElementGraphicGetMatrixWrapper(_next);
        VBColorAdvanced _next_color = VBObjectFile2DKeyFrameElementGraphicGetColor(_next);
        *_matrix = VBMatrix2DWrapperLoadIdentity();
        if(VBObjectFile2DTransitionGetType(_transition) == VBObjectFile2DTransitionType_SingleBezier) {
            _value = VBObjectFile2DTransitionGetSingleValue(_transition, _t);
            *_matrix = VBMatrix2DWrapperInterpolate(_origin_matrix, _next_matrix, _value);
            *_color = VBColorAdvancedInterpolate(_origin_color, _next_color, _value);
        } else if(VBObjectFile2DTransitionGetType(_transition) == VBObjectFile2DTransitionType_MultiBezier) {
            _value = VBObjectFile2DTransitionGetPositionValue(_transition, _t);
            *_matrix = VBMatrix2DWrapperSetPosition(*_matrix, VBVector2DInterpolate(VBMatrix2DWrapperGetPosition(_origin_matrix), VBMatrix2DWrapperGetPosition(_next_matrix), _value));
            
            if(_t >= 1.0) {
                _matrix->anchor = _next_matrix.anchor;
            } else {
                _matrix->anchor = _origin_matrix.anchor;
            }
           
            _value = VBObjectFile2DTransitionGetScaleValue(_transition, _t);
            *_matrix = VBMatrix2DWrapperSetScale(*_matrix, VBVector2DInterpolate(VBMatrix2DWrapperGetScale(_origin_matrix), VBMatrix2DWrapperGetScale(_next_matrix), _value));
            
            _value = VBObjectFile2DTransitionGetRotationValue(_transition, _t);
            *_matrix = VBMatrix2DWrapperSetShear(*_matrix, VBVector2DInterpolate(VBMatrix2DWrapperGetShear(_origin_matrix), VBMatrix2DWrapperGetShear(_next_matrix), _value));
            
            *_matrix = VBMatrix2DWrapperUpdate(*_matrix);
            
            _value = VBObjectFile2DTransitionGetColorValue(_transition, _t);
            *_color = VBColorAdvancedInterpolate(_origin_color, _next_color, _value);
        }
    } else {
        *_matrix = _origin_matrix;
        *_color = _origin_color;
    }
}

void VBObjectFile2DKeyFrameElementGraphicFree(VBObjectFile2DKeyFrameElementGraphic** _graphic) {
#ifdef _VB_DEBUG_
    if(*_graphic == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: - VBNull인 그래픽의 메모리를 해제할 수 없습니다. 이미 VBObjectFile2DKeyFrameElementGraphicFree()하였거나 VBObjectFile2DKeyFrameElementGraphicAlloc()하지 않았을 수 있습니다.");
#endif
    
    *_graphic = VBObjectFile2DKeyFrameElementGraphicInit(*_graphic);
    VBSystemFree(*_graphic);
    *_graphic = VBNull;
}

VBObjectFile2DKeyFrameElementMovieClip* VBObjectFile2DKeyFrameElementMovieClipAlloc(void) {
    VBObjectFile2DKeyFrameElementMovieClip* _movie_clip = VBSystemCalloc(1, sizeof(VBObjectFile2DKeyFrameElementMovieClip));
#ifdef _VB_DEBUG_
    if(_movie_clip == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementMovieClipAlloc() - 메모리를 할당 할 수 없습니다.");
#endif
    
    _movie_clip->instance_name = VBStringAlloc();
    return _movie_clip;
}

VBObjectFile2DKeyFrameElementMovieClip* VBObjectFile2DKeyFrameElementMovieClipInit(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip) {
#ifdef _VB_DEBUG_
    if(_movie_clip == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementMovieClipInit() - VBNull인 무비클립을 초기화 할 수 없습니다. VBObjectFile2DKeyFrameElementMovieClipAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
    
    _movie_clip->blend_mode = VBBlendMode_Normal;
    _movie_clip->color = VBColorAdvancedCreate(0, 0, 0, 0, 0, 0, 0, 0);
    _movie_clip->instance_name = VBStringInit(_movie_clip->instance_name);
    _movie_clip->matrix = VBMatrix2DWrapperLoadIdentity();
    _movie_clip->transition = VBNull;
    _movie_clip->next = VBNull;
    return _movie_clip;
}

VBObjectFile2DKeyFrameElementMovieClip* VBObjectFile2DKeyFrameElementMovieClipInitWithData(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip, VBString* _instance_name, VBBlendMode _blend_mode, VBObjectFile2DTransition* _transition, VBMatrix2DWrapper _matrix, VBColorAdvanced _color) {
#ifdef _VB_DEBUG_
    if(_movie_clip == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementMovieClipInitWithData() - VBNull인 무비클립을 초기화 할 수 없습니다. VBObjectFile2DKeyFrameElementMovieClipAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
    
    _movie_clip = VBObjectFile2DKeyFrameElementMovieClipInit(_movie_clip);
    _movie_clip->blend_mode = _blend_mode;
    _movie_clip->color = _color;
    _movie_clip->instance_name = VBStringInitWithCString(_movie_clip->instance_name, VBStringGetCString(_instance_name));
    _movie_clip->matrix = _matrix;
    _movie_clip->transition = _transition;
    return _movie_clip;
}

VBString* VBObjectFile2DKeyFrameElementMovieClipGetInstanceName(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip) {
#ifdef _VB_DEBUG_
    if(_movie_clip == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementMovieClipGetInstanceName() - VBNull인 무비클립으로는 instance_name을 구할 수 없습니다.");
#endif
    
    return _movie_clip->instance_name;
}

VBMatrix2DWrapper VBObjectFile2DKeyFrameElementMovieClipGetMatrixWrapper(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip) {
#ifdef _VB_DEBUG_
    if(_movie_clip == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: - VBNull인 무비클립으로는 MatrixWrapper를 구할 수 없습니다.");
#endif

    return _movie_clip->matrix;
}

VBColorAdvanced VBObjectFile2DKeyFrameElementMovieClipGetColor(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip) {
#ifdef _VB_DEBUG_
    if(_movie_clip == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementMovieClipGetColor() - VBNull인 무비클립으로는 color를 구할 수 없습니다.");
#endif

    return _movie_clip->color;
}

void VBObjectFile2DKeyFrameElementMovieClipGetTransitionProperties(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip, VBFloat _t, VBMatrix2DWrapper* _matrix, VBColorAdvanced* _color) {
#ifdef _VB_DEBUG_
    if(_movie_clip == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementMovieClipGetTransitionProperties() - VBNull인 무비클립으로는 transition_properties를 구할 수 없습니다.");
    if(_matrix == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementMovieClipGetTransitionProperties() - VBNull인 matrix으로는 transition_properties를 구할 수 없습니다.");
#endif

    VBObjectFile2DTransition* _transition = VBObjectFile2DKeyFrameElementMovieClipGetTransition(_movie_clip);
    VBMatrix2DWrapper _origin_matrix = VBObjectFile2DKeyFrameElementMovieClipGetMatrixWrapper(_movie_clip);
    VBColorAdvanced _origin_color = VBObjectFile2DKeyFrameElementMovieClipGetColor(_movie_clip);
    if(_transition) {
        VBFloat _value;
        VBObjectFile2DKeyFrameElementMovieClip* _next = VBObjectFile2DKeyFrameElementMovieClipGetNext(_movie_clip);
        VBMatrix2DWrapper _next_matrix = VBObjectFile2DKeyFrameElementMovieClipGetMatrixWrapper(_next);
        VBColorAdvanced _next_color = VBObjectFile2DKeyFrameElementMovieClipGetColor(_next);
        *_matrix = VBMatrix2DWrapperLoadIdentity();
        if(VBObjectFile2DTransitionGetType(_transition) == VBObjectFile2DTransitionType_SingleBezier) {
            _value = VBObjectFile2DTransitionGetSingleValue(_transition, _t);
            *_matrix = VBMatrix2DWrapperInterpolate(_origin_matrix, _next_matrix, _value);
            *_color = VBColorAdvancedInterpolate(_origin_color, _next_color, _value);
        } else if(VBObjectFile2DTransitionGetType(_transition) == VBObjectFile2DTransitionType_MultiBezier) {
            _value = VBObjectFile2DTransitionGetPositionValue(_transition, _t);
            *_matrix = VBMatrix2DWrapperSetPosition(*_matrix, VBVector2DInterpolate(VBMatrix2DWrapperGetPosition(_origin_matrix), VBMatrix2DWrapperGetPosition(_next_matrix), _value));
            
            if(_t >= 1.0) {
                _matrix->anchor = _next_matrix.anchor;
            } else {
                _matrix->anchor = _origin_matrix.anchor;
            }
            
            _value = VBObjectFile2DTransitionGetScaleValue(_transition, _t);
            *_matrix = VBMatrix2DWrapperSetScale(*_matrix, VBVector2DInterpolate(VBMatrix2DWrapperGetScale(_origin_matrix), VBMatrix2DWrapperGetScale(_next_matrix), _value));
            
            _value = VBObjectFile2DTransitionGetRotationValue(_transition, _t);
            *_matrix = VBMatrix2DWrapperSetShear(*_matrix, VBVector2DInterpolate(VBMatrix2DWrapperGetShear(_origin_matrix), VBMatrix2DWrapperGetShear(_next_matrix), _value));
            
            *_matrix = VBMatrix2DWrapperUpdate(*_matrix);
            
            _value = VBObjectFile2DTransitionGetColorValue(_transition, _t);
            *_color = VBColorAdvancedInterpolate(_origin_color, _next_color, _value);
        }
    } else {
        *_matrix = _origin_matrix;
        *_color = _origin_color;
    }
}

void VBObjectFile2DKeyFrameElementMovieClipFree(VBObjectFile2DKeyFrameElementMovieClip** _movie_clip) {
#ifdef _VB_DEBUG_
    if(*_movie_clip == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementMovieClipFree() - VBNull인 무비클립의 메모리를 해제할 수 없습니다. 이미 VBObjectFile2DKeyFrameElementMovieClipFree()하였거나 VBObjectFile2DKeyFrameElementMovieClipAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif

    *_movie_clip = VBObjectFile2DKeyFrameElementMovieClipInit(*_movie_clip);
    VBStringFree(&(*_movie_clip)->instance_name);
    VBSystemFree(*_movie_clip);
    *_movie_clip = VBNull;
}

VBObjectFile2DKeyFrameElementGraphic* VBObjectFile2DKeyFrameElementGraphicGetNext(VBObjectFile2DKeyFrameElementGraphic* _graphic) {
#ifdef _VB_DEBUG_
    if(_graphic == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementGraphicGetNext() - VBNull인 그래픽으로 다음 그래픽을 구할 수 없습니다.");
#endif

    return _graphic->next;
}

VBObjectFile2DKeyFrameElementMovieClip* VBObjectFile2DKeyFrameElementMovieClipGetNext(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip) {
#ifdef _VB_DEBUG_
    if(_movie_clip == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log:VBObjectFile2DKeyFrameElementMovieClipGetNext() - VBNull인 무비클립으로 다음 무비클립을 구할 수 없습니다.");
#endif

    return _movie_clip->next;
}

void VBObjectFile2DKeyFrameElementGraphicSetNext(VBObjectFile2DKeyFrameElementGraphic* _graphic, VBObjectFile2DKeyFrameElementGraphic* _next) {
#ifdef _VB_DEBUG_
    if(_graphic == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementGraphicSetNext() - VBNull인 그래픽으로 다음 그래픽을 설정할 수 없습니다.");
#endif

    _graphic->next = _next;
}

void VBObjectFile2DKeyFrameElementMovieClipSetNext(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip, VBObjectFile2DKeyFrameElementMovieClip* _next) {
#ifdef _VB_DEBUG_
    if(_movie_clip == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementMovieClipSetNext() - VBNull인 무비클립으로 다음 무비클립을 설정할 수 없습니다.");
#endif

    _movie_clip->next = _next;
}

VBObjectFile2DTransition* VBObjectFile2DKeyFrameElementGraphicGetTransition(VBObjectFile2DKeyFrameElementGraphic* _graphic) {
#ifdef _VB_DEBUG_
    if(_graphic == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementGraphicGetTransition() - VBNull인 그래픽으로 그래픽의 트랜지션을 구할 수 없습니다.");
#endif

    return _graphic->transition;
}

VBObjectFile2DTransition* VBObjectFile2DKeyFrameElementMovieClipGetTransition(VBObjectFile2DKeyFrameElementMovieClip* _movie_clip) {
#ifdef _VB_DEBUG_
    if(_movie_clip == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameElementMovieClipGetTransition() - VBNull인 무비클립으로 무비클립의 트랜지션을 구할 수 없습니다.");
#endif
    
    return _movie_clip->transition;
}
