#include "VBObjectFile2DLibraryNameID.h"
#include "VBSystem.h"
#include "../VBEngine.h"

VBObjectFile2DLibraryNameID* VBObjectFile2DLibraryNameIDAlloc(void) {
    VBObjectFile2DLibraryNameID* _name_id = VBSystemCalloc(1, sizeof(VBObjectFile2DLibraryNameID));
#ifdef _VB_DEBUG_
    if(_name_id == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryNameIDAlloc() - 메모리 할당에 실패하였습니다.");
#endif
    
    return _name_id;
}

VBObjectFile2DLibraryNameID* VBObjectFile2DLibraryNameIDInit(VBObjectFile2DLibraryNameID* _name_id) {
#ifdef _VB_DEBUG_
    if(_name_id == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryNameIDInit() - VBNull인 라이브러리 이름 아이디를 초기화 할 수 없습니다. VBObjectFile2DLibraryNameIDAlloc()하지 않은 파일을 사용했을 수 있습니다.");
#endif
    
    _name_id->libraryID = 0;
    if(_name_id->libraryName)
        VBStringFree(&_name_id->libraryName);
    return _name_id;
}

VBObjectFile2DLibraryNameID* VBObjectFile2DLibraryNameIDInitWithIDAndName(VBObjectFile2DLibraryNameID* _name_id, VBULong _id, VBString* _name) {
#ifdef _VB_DEBUG_
    if(_name_id == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryNameIDInitWithIDAndName() - VBNull인 라이브러리 이름 아이디를 초기화 할 수 없습니다. VBObjectFile2DLibraryNameIDAlloc()하지 않은 파일을 사용했을 수 있습니다.");
    if(_id == 0)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryNameIDInitWithIDAndName() - 아이디가 유효하지 않습니다.");
    if(_name == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryNameIDInitWithIDAndName() - 이름이 유효하지 않습니다.");
#endif
    
    _name_id = VBObjectFile2DLibraryNameIDInit(_name_id);
    _name_id->libraryID = _id;
    _name_id->libraryName = VBStringCopy(_name);
    return _name_id;
}

void VBObjectFile2DLibraryNameIDFree(VBObjectFile2DLibraryNameID** _name_id) {
#ifdef _VB_DEBUG_
    if(*_name_id == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryNameIDFree() - VBNull인 이름 아이디의 매모리를 해제할 수 없습니다. 이미 VBObjectFile2DLibraryNameIDFree()했거나 VBObjectFile2DLibraryNameIDAlloc하지 않은 파일을 사용했을 수 있습니다.");
#endif
    
    VBObjectFile2DLibraryNameIDInit(*_name_id);
    VBSystemFree(*_name_id);
    _name_id = VBNull;
}

VBULong VBObjectFile2DLibraryNameIDGetID(VBObjectFile2DLibraryNameID* _name_id) {
#ifdef _VB_DEBUG_
    if(_name_id == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryNameIDGetID() - VBNull인 이름 아이디로 라이브러리 아이디를 구할 수 없습니다.");
#endif
    
    return _name_id->libraryID;
}

VBString* VBObjectFile2DLibraryNameIDGetName(VBObjectFile2DLibraryNameID* _name_id) {
#ifdef _VB_DEBUG_
    if(_name_id == VBNull)
        VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
                                         "VBEngine Log: VBObjectFile2DLibraryNameIDGetName() - VBNull인 이름 아이디로 라이브러리 이름을 구할 수 없습니다.");
#endif
    
    return _name_id->libraryName;
}



