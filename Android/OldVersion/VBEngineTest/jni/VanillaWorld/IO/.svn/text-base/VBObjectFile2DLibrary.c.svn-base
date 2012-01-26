#include "VBObjectFile2DLibrary.h"
#include "VBSystem.h"
#include "../VBEngine.h"

VBObjectFile2DLibrary* VBObjectFile2DLibraryAlloc(void) {
    VBObjectFile2DLibrary* _library = VBSystemCalloc(1, sizeof(VBObjectFile2DLibrary));
#ifdef _VB_DEBUG_
    if(_library == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryAlloc() - 메모리 할당에 실패하였습니다.");
#endif
    
    return _library;
}

VBObjectFile2DLibrary* VBObjectFile2DLibraryInit(VBObjectFile2DLibrary* _library) {
#ifdef _VB_DEBUG_
    if(_library == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryInit() - VBNull인 library을 초기화 하려고 합니다. VBObjectFile2DLibraryAlloc()하지 않은 파일을 사용했을 수 도 있습니다.");
#endif
    
    _library->name_id = 0;
    _library->type = VBObjectFile2DLibraryType_None;
    _library->library = VBNull;
    return _library;
}

VBObjectFile2DLibrary* VBObjectFile2DLibraryInitWithType(VBObjectFile2DLibrary* _library, VBObjectFile2DLibraryNameID* _name_id, VBObjectFile2DLibraryType _type, void* _library_base) {
#ifdef _VB_DEBUG_
    if(_library == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryInitWithType() - VBNull인 library을 초기화하려고 합니다. VBObjectFile2DLibraryAlloc()하지 않은 파일을 사용했을 수 도 있습니다.");
    if(_name_id == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryInitWithType() - VBNull인 _name_id를 사용했을 수 있습니다.");
    if(_library_base == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryInitWithType() - VBNull인 _library_base를 사용했을 수 있습니다.");   
#endif
    if(_library) {
        _library = VBObjectFile2DLibraryInit(_library);
        
        _library->name_id = _name_id;
        _library->type = _type;
        _library->library = _library_base;
    } else {
        
#ifdef _VB_DEBUG_
        if(_library == VBNull) 
            VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                             "VBEngine Log: VBObjectFile2DLibraryInitWithType() - VBNull인 _library을 초기화 하려고 합니다. VBObjectFile2DLibraryAlloc()하지 않은 파일을 사용했을 수 도 있습니다.");
#endif
    }
    return _library;
}

void VBObjectFile2DLibraryFree(VBObjectFile2DLibrary** _library) {
#ifdef _VB_DEBUG_
    if(*_library == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryFree() - VBNull인 _library를 free하려고 합니다. 이미 VBObjectFile2DLibraryFree()하였거나 VBObjectFile2DLibraryAlloc()하지 않은 파일을 사용했을 수 도 있습니다.");
#endif 
    *_library = VBObjectFile2DLibraryInit(*_library);
    VBSystemFree(*_library);
    *_library = VBNull;
}

VBObjectFile2DLibraryBitmap* VBObjectFile2DLibraryBitmapAlloc(void) {
    VBObjectFile2DLibraryBitmap* _bitmap = VBSystemCalloc(1, sizeof(VBObjectFile2DLibraryBitmap));
#ifdef _VB_DEBUG_
    if(_bitmap == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryBitmapAlloc() - 메모리 할당에 실패하였습니다.");
#endif
    
    return _bitmap;
}

VBObjectFile2DLibraryBitmap* VBObjectFile2DLibraryBitmapInit(VBObjectFile2DLibraryBitmap* _bitmap) {
#ifdef _VB_DEBUG_
    if(_bitmap == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryBitmapInit() - VBNull인 _bitmap을 초기화 하려고 합니다. VBObjectFile2DLibraryBitmapAlloc()하지 않은 파일을 사용했을 수 도 있습니다.");
#endif
    
    _bitmap->uv_info_length = 0;
    if(_bitmap->uv_info) {
        VBSystemFree(_bitmap->uv_info);
        _bitmap->uv_info
        = VBNull;
    }
    
    return _bitmap;
}

VBObjectFile2DLibraryBitmap* VBObjectFile2DLibraryBitmapInitWithData(VBObjectFile2DLibraryBitmap* _bitmap, VBULong _uv_info_length, VBVector2D* _uv_info) {
#ifdef _VB_DEBUG_
    if(_bitmap == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryBitmapInitWithData() - VBNull인 _bitmap을 초기화 하려고 합니다. VBObjectFile2DLibraryBitmapAlloc()하지 않은 파일을 사용했을 수 도 있습니다.");
#endif
    
    _bitmap = VBObjectFile2DLibraryBitmapInit(_bitmap);
    
    _bitmap->uv_info_length = _uv_info_length;
    VBSize _size = _bitmap->uv_info_length * sizeof(VBVector2D);
    _bitmap->uv_info = VBSystemMalloc(_size);
    VBSystemMemoryCopy(_bitmap->uv_info, _uv_info, _size);
    
    return _bitmap;
}

VBULong VBObjectFile2DLibraryBitmapGetUVInfoLength(VBObjectFile2DLibraryBitmap* _bitmap) {
    return _bitmap->uv_info_length;
}

VBVector2D* VBObjectFile2DLibraryBitmapGetUVInfo(VBObjectFile2DLibraryBitmap* _bitmap) {
    return _bitmap->uv_info;
}

void VBObjectFile2DLibraryBitmapFree(VBObjectFile2DLibraryBitmap** _bitmap) {
#ifdef _VB_DEBUG_
    if(*_bitmap == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryBitmapFree() - VBNull인 _bitmap를 free하려고 합니다. 이미 VBObjectFile2DLibraryBitmapFree()하였거나 VBObjectFile2DLibraryBitmapAlloc()하지 않은 파일을 사용했을 수 도 있습니다.");
#endif
    *_bitmap = VBObjectFile2DLibraryBitmapInit(*_bitmap);
    VBSystemFree(*_bitmap);
    *_bitmap = VBNull;
}

VBObjectFile2DLibraryGraphic* VBObjectFile2DLibraryGraphicAlloc(void) {
    VBObjectFile2DLibraryGraphic* _graphic = VBSystemCalloc(1, sizeof(VBObjectFile2DLibraryGraphic));
#ifdef _VB_DEBUG_
    if(_graphic == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryGraphicAlloc() - 메모리 할당에 실패하였습니다.");
#endif
    
    return _graphic;
}

VBObjectFile2DLibraryGraphic* VBObjectFile2DLibraryGraphicInit(VBObjectFile2DLibraryGraphic* _graphic) {
#ifdef _VB_DEBUG_
    if(_graphic == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryGraphicInit() - VBNull인 graphic을 초기화 하려고 합니다. VBObjectFile2DLibraryGraphicAlloc()하지 않은 파일을 사용했을 수 도 있습니다.");
#endif
    
    _graphic->frame = VBNull;
    return _graphic;
}

VBObjectFile2DLibraryGraphic* VBObjectFile2DLibraryGraphicInitWithData(VBObjectFile2DLibraryGraphic* _graphic , VBObjectFile2DFrame* _frame) {
#ifdef _VB_DEBUG_
    if(_graphic == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryGraphicInitWithData() - VBNull인 graphic을 초기화 하려고 합니다. VBObjectFile2DLibraryGraphicAlloc()하지 않은 파일을 사용했을 수 도 있습니다.");
    if(_frame == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryGraphicInitWithData() - VBNull인 fraem을 초기화 하려고 합니다. VBObjectFile2DLibraryGraphicAlloc()하지 않은 파일을 사용했을 수 도 있습니다.");
#endif
    
    _graphic = VBObjectFile2DLibraryGraphicInit(_graphic);
    
    _graphic->frame = _frame;
    
    return _graphic;
}

VBObjectFile2DFrame* VBObjectFile2DLibraryGraphicGetFrame(VBObjectFile2DLibraryGraphic* _graphic) {
    return _graphic->frame;
}

void VBObjectFile2DLibraryGraphicFree(VBObjectFile2DLibraryGraphic** _graphic) {
#ifdef _VB_DEBUG_
    if(*_graphic == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryGraphicFree() - VBNull인 _graphic를 free하려고 합니다. 이미 VBObjectFile2DLibraryGraphicFree()하였거나 VBObjectFile2DLibraryGraphicAlloc()하지 않은 파일을 사용했을 수 도 있습니다.");
    
#endif
    
    *_graphic = VBObjectFile2DLibraryGraphicInit(*_graphic);
    VBSystemFree(*_graphic);
    *_graphic = VBNull;
}

VBObjectFile2DLibraryMovieClip* VBObjectFile2DLibraryMovieClipAlloc(void) {
    VBObjectFile2DLibraryMovieClip* _movie_clip = VBSystemCalloc(1, sizeof(VBObjectFile2DLibraryMovieClip));
#ifdef VBNull
    if(_movie_clip == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryMovieClipAlloc() - 메모리 할당에 실패하였습니다.");
#endif
    
    return _movie_clip;
}

VBObjectFile2DLibraryMovieClip* VBObjectFile2DLibraryMovieClipInit(VBObjectFile2DLibraryMovieClip* _movie_clip) {
#ifdef _VB_DEBUG_
    if(_movie_clip == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryMovieClipInit() - VBNull인 _movie_clip은 초기화 할 수 없습니다. VBObjectFile2DLibraryMovieClipAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
    
    _movie_clip->frame = VBNull;
    
    return _movie_clip;
}

VBObjectFile2DLibraryMovieClip* VBObjectFile2DLibraryMovieClipInitWithData(VBObjectFile2DLibraryMovieClip* _movie_clip,  VBObjectFile2DFrame* _frame) {
#ifdef _VB_DEBUG_
    if(_movie_clip == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryMovieClipInitWithData() - VBNull인 _movie_clip은 초기화 할 수 없습니다.");
#endif
    
    _movie_clip = VBObjectFile2DLibraryMovieClipInit(_movie_clip);
    
    _movie_clip->frame = _frame;
    
    return _movie_clip;
}

VBObjectFile2DFrame* VBObjectFile2DLibraryMovieClipGetFrame(VBObjectFile2DLibraryMovieClip* _movie_clip) {
    return _movie_clip->frame;
}

void VBObjectFile2DLibraryMovieClipFree(VBObjectFile2DLibraryMovieClip** _movie_clip) {
#ifdef _VB_DEBUG_
    if(*_movie_clip == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryMovieClipFree() - VBNull인 _graphic를 free하려고 합니다. 이미 VBObjectFile2DLibraryMovieClipFree()하였거나 VBObjectFile2DLibraryMovieClipAlloc()하지 않은 파일을 사용했을 수 도 있습니다.");
#endif
    
    *_movie_clip = VBObjectFile2DLibraryMovieClipInit(*_movie_clip);
    VBSystemFree(*_movie_clip);
    *_movie_clip = VBNull;
}

VBObjectFile2DLibraryNameID* VBObjectFile2DLibraryGetNameID(VBObjectFile2DLibrary* _library) {
#ifdef _VB_DEBUG_
    if(_library == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryGetNameID() - VBNull인 라이브러리의 이름 아이디를 구할 수 없습니다.");
#endif
    
    return _library->name_id;
}

VBObjectFile2DLibraryType VBObjectFile2DLibraryGetType(VBObjectFile2DLibrary* _library) {
#ifdef _VB_DEBUG_
    if(_library == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryGetType() - VBNull인 라이브러리의 타입을 구할 수 없습니다.");
#endif
    
    return _library->type;
}

void* VBObjectFile2DLibraryGetBase(VBObjectFile2DLibrary* _library) {
#ifdef _VB_DEBUG_
    if(_library == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryGetBase() - VBNull인 라이브러리를의 베이스를 구할 수 없습니다.");
#endif
    
    return _library->library;
}

