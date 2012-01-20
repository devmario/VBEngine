#include "VBObjectFile2DTexcoord.h"
#include "VBSystem.h"
#include "../VBEngine.h"

VBObjectFile2DTexcoord* VBObjectFile2DTexcoordAlloc(void) {
    VBObjectFile2DTexcoord* _texcoord = VBSystemCalloc(1, sizeof(VBObjectFile2DTexcoord));
#ifdef _VB_DEBUG_
    if(_texcoord == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DTexcoordAlloc() - 메모리를 할당 할 수 없습니다.");
#endif
    
    return _texcoord;
}

VBObjectFile2DTexcoord* VBObjectFile2DTexcoordInit(VBObjectFile2DTexcoord* _texcoord) {
#ifdef _VB_DEBUG_
    if(_texcoord == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DTexcoordInit() - VBNull인 texcoord는 초기화할 수 없습니다. VBObjectFile2DTexcoordAlloc()하지 않았을 수 있습니다.");
#endif
    
    _texcoord->libraryNameID = VBNull;
    _texcoord->texcoord_length = 0;
    if(_texcoord->texcoord) {
        VBSystemFree(_texcoord->texcoord);
        _texcoord->texcoord = VBNull;
    }
    return _texcoord;
}

VBObjectFile2DTexcoord* VBObjectFile2DTexcoordInitWithNameIDAndTexcoordVector(VBObjectFile2DTexcoord* _texcoord,
                                                                              VBObjectFile2DLibraryNameID* _name_id,
                                                                              VBULong _texcoord_vector_length,
                                                                              VBVector2D* _texcoord_vector) {
#ifdef _VB_DEBUG_
    if(_texcoord == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DTexcoordInitWithNameIDAndTexcoordVector() - VBNull인 texcoord는 초기화할 수 없습니다. VBObjectFile2DTexcoordAlloc()하지 않았을 수 있습니다.");
    if(_name_id == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DTexcoordInitWithNameIDAndTexcoordVector() - _name_id가 VBNull입니다.");
    if(_texcoord_vector == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DTexcoordInitWithNameIDAndTexcoordVector() - texcoord_vector가 VBNull입니다.");
#endif
    
    _texcoord->libraryNameID = _name_id;
    _texcoord->texcoord_length = _texcoord_vector_length;
    VBSize _texcoord_size = _texcoord_vector_length * sizeof(VBVector2D);
    _texcoord->texcoord = VBSystemMalloc(_texcoord_size);
    VBSystemMemoryCopy(_texcoord->texcoord, _texcoord_vector, _texcoord_size);
    return _texcoord;
}

void VBObjectFile2DTexcoordFree(VBObjectFile2DTexcoord** _texcoord) {
#ifdef _VB_DEBUG_
    if(*_texcoord == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DTexcoordFree() - VBNull인 texcoor의 메모리를 해제할 수 없습니다. 이미 VBObjectFile2DTexcoordFree()하였거나 VBObjectFile2DTexcoordAlloc()하지 않았을 수 있습니다.");
#endif
    
    VBObjectFile2DTexcoordInit(*_texcoord);
    VBSystemFree(*_texcoord);
    *_texcoord = VBNull;
}

