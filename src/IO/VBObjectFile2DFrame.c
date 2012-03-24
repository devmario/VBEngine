#include "VBObjectFile2DFrame.h"
#include "VBSystem.h"
#include "../VBEngine.h"

VBObjectFile2DFrame* VBObjectFile2DFrameAlloc(void) {
    VBObjectFile2DFrame* _frame = VBSystemCalloc(1, sizeof(VBObjectFile2DFrame));
#ifdef _VB_DEBUG_
    if(_frame == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBObjectFile2DFrameAlloc() - 메모리 할당에 실패하였습니다.");
#endif

    _frame->key_frame = VBArrayVectorAlloc();
    return _frame;
}

VBObjectFile2DFrame* VBObjectFile2DFrameInit(VBObjectFile2DFrame* _frame) {
#ifdef _VB_DEBUG_
    if(_frame == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBObjectFile2DFrameInit() - VBNull인 _frame을 초기화하려고 합니다. VBObjectFile2DFrameAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
    
    _frame->key_frame = VBArrayVectorInit(_frame->key_frame);
    return _frame;
}

void VBObjectFile2DFrameFree(VBObjectFile2DFrame** _frame) {
#ifdef _VB_DEBUG_
    if(_frame == VBNull) 
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBObjectFile2DFrameFree() - VBNull인 _frame을 free하려고 합니다. 이미 VBObjectFile2DFrameFree()하였거나, VBObjectFile2DFrameAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
    
    *_frame = VBObjectFile2DFrameInit(*_frame);
    VBArrayVectorFree(&(*_frame)->key_frame);
    VBSystemFree(*_frame);
    *_frame = VBNull;
}

VBULong VBObjectFile2DFrameGetTotalFrame(VBObjectFile2DFrame* _frame) {
    return _frame->total_frame;
}

VBArrayVector* VBObjectFile2DFrameGetKeyFrames(VBObjectFile2DFrame* _frame) {
    return _frame->key_frame;
}