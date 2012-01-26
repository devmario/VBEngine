#include "VBEngine.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "IO/VBSystem.h"

#include <OpenGLES/ES1/gl.h>

VBString* _vb_engine_default_res_path = VBNull;
VBString* _vb_engine_default_rw_doc_path = VBNull;

VBDebug* _vb_engine_default_debuger = VBNull;

VBBool _vb_engine_inited = VBFalse;

VBColorRGBA _vb_engine_clear_color;

VBUShort _vb_engine_screen_width = 0;
VBUShort _vb_engine_screen_height = 0;

VBUShort _vb_engine_default_resource_screen_width = 0;
VBUShort _vb_engine_default_resource_screen_height = 0;

VBBool VBEngineStart(const VBChar* _res_path, const VBChar* _rw_doc_path, VBUShort _screen_width, VBUShort _screen_height, VBUShort _default_resource_screen_width, VBUShort _default_resource_screen_height) {
#ifdef _VB_DEBUG_
    if(_res_path == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBEngineStart() - Resource 경로가 VBNull을 사용할 수 없습니다.");
    if(_rw_doc_path == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBEngineStart() - rw_doc 경로가 VBNull을 사용할 수 없습니다.");
#endif
    
	if(_vb_engine_inited == VBFalse) {
		VBChar* _log_path = VBSystemCalloc(strlen(_rw_doc_path) + strlen("/VBDebugLog") + 1, sizeof(VBChar));
		sprintf(_log_path, "%s%s", _rw_doc_path, "/VBDebugLog");
		_vb_engine_default_debuger = VBDebugInitWithLogFilePath(VBDebugAlloc(), _log_path);
		VBSystemFree(_log_path);
        
		_vb_engine_default_res_path = VBStringInitWithCString(VBStringAlloc(), _res_path);
        printf("resource path:%s\n", VBStringGetCString(_vb_engine_default_res_path));
		
		_vb_engine_default_rw_doc_path = VBStringInitWithCString(VBStringAlloc(), _rw_doc_path);
        printf("document path:%s\n", VBStringGetCString(_vb_engine_default_rw_doc_path));
        
        _vb_engine_screen_width = _screen_width;
        _vb_engine_screen_height = _screen_height;
        _vb_engine_default_resource_screen_width = _default_resource_screen_width;
        _vb_engine_default_resource_screen_height = _default_resource_screen_height;
        
		_vb_engine_inited = VBTrue;
        
        return VBTrue;
	}
	return VBFalse;
}

VBBool VBEngineShutdown(void) {
	if(_vb_engine_inited == VBTrue) {
		VBStringFree(&_vb_engine_default_res_path);
		VBStringFree(&_vb_engine_default_rw_doc_path);
		VBDebugFree(&_vb_engine_default_debuger);
		
		_vb_engine_inited = VBFalse;
        return VBTrue;
	}
	return VBFalse;
}

VBBool VBEngineGetIsRunning(void) {
	return _vb_engine_inited;
}

VBDebug* VBEngineGetDefaultDebuger(void) {
	if(_vb_engine_default_debuger == VBNull) {
		VBDebugPrintAbort(VBNull, VBTrue, "VBEngine Log: 엔진이 초기화 되지 않아 기본디버거를 가져올수 없습니다.");
	}
	return _vb_engine_default_debuger;
}

VBString* VBEngineGetResourcePath(void) {
	if(_vb_engine_default_res_path == VBNull)
		VBDebugPrintAbort(VBNull, VBTrue, "VBEngine Log: 엔진이 초기화 되지 않아 기본리소스패스를 가져올수 없습니다.");
	
	return _vb_engine_default_res_path;
}

VBString* VBEngineGetDocumentPath(void) {
	if(_vb_engine_default_rw_doc_path == VBNull)
		VBDebugPrintAbort(VBNull, VBTrue, "VBEngine Log: 엔진이 초기화 되지 않아 기본도큐먼트패스를 가져올수 없습니다.");
	
	return _vb_engine_default_rw_doc_path;
}

void VBEngineSetClearColor(VBColorRGBA _clear_color) {
    _vb_engine_clear_color = _clear_color;
    glClearColor(_vb_engine_clear_color.r, _vb_engine_clear_color.g, _vb_engine_clear_color.b, _vb_engine_clear_color.a);
}

VBColorRGBA VBEngineGetClearColor(void) {
    return _vb_engine_clear_color;
}

void VBEngineClearDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
}

VBVector2D VBEngineGetScreenSize(void) {
    return VBVector2DCreate(_vb_engine_screen_width, _vb_engine_screen_height);
}

VBVector2D VBEngineGetDefaultResourceScreenSize(void) {
    return VBVector2DCreate(_vb_engine_default_resource_screen_width, _vb_engine_default_resource_screen_height);
}







