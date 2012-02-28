#include "VBEngineFileInfo.h"
#include "VBSystem.h"
#include <stdio.h>
#include <memory.h>
#include <string.h>

VBArrayVector* _vb_engine_file_info_vec = VBNull;

VBEngineFileInfo* VBEngineFileInfoAlloc(void) {
	VBEngineFileInfo* _info = (VBEngineFileInfo*)VBSystemCalloc(1, sizeof(VBEngineFileInfo));
	
#ifdef _VB_DEBUG_
	if(_info == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBEngineFileInfoAlloc() - 메모리할당에 실패하였습니다.");
#endif

_info->path = VBStringAlloc();
#ifdef _VB_DEBUG_
	if(_info->path  == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBEngineFileInfoAlloc() _info->path - 메모리할당에 실패하였습니다.");
#endif
	
	return _info;
}


VBEngineFileInfo* VBEngineFileInfoInit(VBEngineFileInfo* _info, VBChar* _path, VBUShort _fd, VBSize _off, VBSize _len) {
#ifdef _VB_DEBUG_
	if(_info == VBNull || _path == VBNull || _fd < 0 || _off < 0 || _len < 0)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBEngineFileInfoInit() - 초기화에 실패하였습니다.");
#endif
	_info->len = _len;
	_info->off = _off;
	_info->fd = _fd;
	_info->path = VBStringInitWithCString(_info->path, _path);
	return _info;
}


void VBEngineFileInfoAdd(VBEngineFileInfo* _info) {
	if(_vb_engine_file_info_vec == VBNull){
		_vb_engine_file_info_vec = VBArrayVectorInit(VBArrayVectorAlloc());
	}
#ifdef _VB_DEBUG_
	if(_info == VBNull || _vb_engine_file_info_vec == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), 
										 VBTrue, 
										 "VBEngine Log: VBEngineFileInfoAdd() - 벡터 메모리할당에 실패하하였습니다.");
#endif
	VBArrayVectorAddBack(_vb_engine_file_info_vec, _info);
}

VBArrayVector* VBEngineFileInfoGetVector(void) {
	return _vb_engine_file_info_vec;
}


void VBEngineFileInfoFree(VBEngineFileInfo** _info) {
	if(*_info) {
		if((*_info)->path) {
			VBStringFree(&(*_info)->path);
		}
		VBSystemFree(*_info);
		*_info = VBNull;
	}
}

