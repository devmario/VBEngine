#include "VBObjectFile2DKeyFrame.h"
#include "VBSystem.h"
#include "../VBEngine.h"

VBObjectFile2DKeyFrame* VBObjectFile2DKeyFrameAlloc(void) {
    VBObjectFile2DKeyFrame* _key_frame = VBSystemCalloc(1, sizeof(VBObjectFile2DKeyFrame));
#ifdef _VB_DEBUG_
    if(_key_frame == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameAlloc() - 메모리 할당에 실패하였습니다.");
#endif
    return _key_frame;
}

VBObjectFile2DKeyFrame* VBObjectFile2DKeyFrameInit(VBObjectFile2DKeyFrame* _key_frame) {
#ifdef _VB_DEBUG_
    if(_key_frame == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameInit() - VBNull인 _key_frame을 초기화하려고 합니다. VBObjectFile2DKeyFrameAlloc()하지 않은 파일을 사용했을 수 있습니다");        
#endif
    
    _key_frame->begin_frame = 0;
    _key_frame->end_frame = 0;
    _key_frame->element = VBNull;
    _key_frame->library_id = VBNull;
    return _key_frame;
}

VBObjectFile2DKeyFrame* VBObjectFile2DKeyFrameInitWithData(VBObjectFile2DKeyFrame* _key_frame, VBObjectFile2DLibraryNameID* _library_id, VBULong _begin_frame, VBULong _end_frame, VBObjectFile2DKeyFrameElement* _element) {
#ifdef _VB_DEBUG_
    VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                     "VBEngine Log: VBObjectFile2DKeyFrameInitWithData() - VBNull인 _key_frame을 초기화하려고 합니다. VBObjectFile2DKeyFrameAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif
    _key_frame = VBObjectFile2DKeyFrameInit(_key_frame);
    _key_frame->library_id = _library_id;
    _key_frame->begin_frame = _begin_frame;
    _key_frame->end_frame = _end_frame;
    _key_frame->element = _element;
    return _key_frame;
}

void VBObjectFile2DKeyFrameFree(VBObjectFile2DKeyFrame** _key_frame) {
#ifdef _VB_DEBUG_
    if(*_key_frame == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameFree() - VBNull인 _key_frame을 free하려고 합니다. 이미 VBObjectFile2DKeyFrameFree()했거나, VBObjectFile2DKeyFrameAlloc()하지 않은 파일을 사용했을 수 있습니다");
#endif
    
    if((*_key_frame)->none_real_time_color) {
        VBSystemFree((*_key_frame)->none_real_time_color);
    }
    if((*_key_frame)->none_real_time_matrix) {
        VBSystemFree((*_key_frame)->none_real_time_matrix);
    }
    VBSystemFree(*_key_frame);
    *_key_frame = VBNull;
}

VBULong VBObjectFile2DKeyFrameGetBeginFrame(VBObjectFile2DKeyFrame* _key_frame) {
#ifdef _VB_DEBUG_
    if(_key_frame == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameGetBeginFrame() - VBNull인 _key_frame으로 시작 frame을 구할 수 없습니다.");
#endif
    
    return _key_frame->begin_frame;
}

VBULong VBObjectFile2DKeyFrameGetEndFrame(VBObjectFile2DKeyFrame* _key_frame) {
#ifdef _VB_DEBUG_
    if(_key_frame == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameGetEndFrame() - VBNull인 _key_frame으로 끝 frame을 구할 수 없습니다.");
#endif
    
    return _key_frame->end_frame;
}

VBObjectFile2DKeyFrameElement* VBObjectFile2DKeyFrameGetElement(VBObjectFile2DKeyFrame* _key_frame) {
#ifdef _VB_DEBUG_
    if(_key_frame == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DKeyFrameGetElement() - VBNull인 _key_frame으로 element을 구할 수 없습니다.");
#endif
    
    return _key_frame->element;
}




