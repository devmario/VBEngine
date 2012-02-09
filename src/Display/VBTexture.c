#include "VBTexture.h"
#include "../VBConfig.h"
#include "../VBEngine.h"

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <string.h>
#include <stdlib.h>


#ifdef __ANDROID__
VBArrayVector* _texVec = NULL;
void VBTextureStackReloadBuffer(void) {
    for(int i = 0; i < _texVec->len; i++) {
        VBTexture* _tex = VBArrayVectorGetDataAt(_texVec, i);
        VBImage* _tmp_img = VBImageCopy(_tex->img_android);
        VBTextureUnload(_tex);
        VBTextureLoadImage(_tex, _tmp_img);
        VBImageFree(&_tmp_img);
    }
}
#endif

VBTexture* VBTextureAlloc(void) {
	VBTexture* _tex = VBSystemCalloc(1, sizeof(VBTexture));
	
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureAlloc() - 메모리 할당에 실패하였습니다.");
#endif
	
    #ifdef __ANDROID__
    if(_texVec == NULL)
        _texVec = VBArrayVectorInit(VBArrayVectorAlloc());
    VBArrayVectorAddBack(_texVec, _tex);
    #endif
    
	return _tex;
}

VBTexture* VBTextureInit(VBTexture* _tex) {
#ifdef _VB_DUBEG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureInit() - VBNull인 텍스쳐를 초기화 하려고 합니다. VBTextureAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
	
	VBTextureUnload(_tex);
	
	return _tex;
}

VBTexture* VBTextureInitAndLoadWithImage(VBTexture* _tex, VBImage* _img) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureInitAndLoadWithImage() - VBNull인 텍스쳐를 초기화 하려고 합니다. VBTextureAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
	
	_tex = VBTextureInit(_tex);
	VBTextureLoadImage(_tex, _img);
	
	return _tex;
}

VBTexture* VBTextureInitAndLoadWithImagePath(VBTexture* _tex, VBString* _path) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureInitAndLoadWithImagePath() - VBNull인 텍스쳐를 초기화 하려고 합니다. VBTextureAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
	
	_tex = VBTextureInit(_tex);
	VBTextureLoadImagePath(_tex, _path);
	
	return _tex;
}

void VBTextureFree(VBTexture** _tex) {
#ifdef _VB_DEBUG_
	if(*_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureFree() - VBNull인 텍스쳐를 Free하려고 합니다. 이미 VBTextureFree하였거나 VBTextureAlloc하지 않은 파일을 사용했을 수 있습니다.");
#endif
	
	VBTextureInit(*_tex);
	
    #ifdef __ANDROID__
    VBArrayVectorRemove(_texVec, *_tex);
    if(_texVec->len == 0)
        VBArrayVectorFree(&_texVec);
    #endif
    
	VBSystemFree(*_tex);
	*_tex = VBNull;
}

void VBTextureLoadImage(VBTexture* _tex, VBImage* _img) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureLoadImage() - VBNull인 텍스쳐를 Load 하려고 합니다. VBTextureAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
	
    #ifdef __ANDROID__
    _tex->img_android = VBImageCopy(_img);
    #endif
    
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	GLboolean _state;
	glGetBooleanv(GL_TEXTURE_2D, &_state);
	if(_state == VBFalse)
		glEnable(GL_TEXTURE_2D);
	
    if(_tex->tid == 0)
        glGenTextures(1, (GLuint*)&_tex->tid);
	glBindTexture(GL_TEXTURE_2D, _tex->tid);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
#ifdef _VB_DEBUG_
	if(VBImageGetWidth(_img) < 32 || VBImageGetHeight(_img) < 32)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureLoadImage() - 텍스쳐는 가로와 세로가 32pixel 이상이어야 합니다");
	
#define _IsPower(_num) (!((_num - 1) & _num))
	
	
#undef _IsPower
#endif
	
	_img->color_type = VBImageGetColorType(_img);
	
	GLenum _format;
    int _byte = 0;
	switch(_img->color_type) {
		case VBColorType_G:
			_format = GL_LUMINANCE;
            _byte = 1;
			break;
		case VBColorType_GA:
			_format = GL_LUMINANCE_ALPHA;
            _byte = 2;
			break;
		case VBColorType_RGB:
			_format = GL_RGB;
            _byte = 3;
			break;
		case VBColorType_RGBA:
			_format = GL_RGBA;
            _byte = 4;
			break;
		default:
			break;
	}
	
#ifdef _VB_DEBUG_
	if(VBImageGetColorBit(_img) != 8)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureLoadImage() - 텍스쳐로 사용될 이미지의 비트수가 지원하지 않는 비트수 입니다.(현재 8비트만 가능함.)");
#endif
    
    _tex->width = 2;
    while(_tex->width < VBImageGetWidth(_img))
        _tex->width *= 2;
    _tex->shiftX = _tex->width / 2 - VBImageGetWidth(_img) / 2;

    _tex->height = 2;
    while(_tex->height < VBImageGetHeight(_img))
        _tex->height *= 2;
    _tex->shiftY = _tex->height / 2 - VBImageGetHeight(_img) / 2;
    
    unsigned char* _data = calloc(_tex->width * _tex->height, _byte);
    unsigned char* _ptr = _data + _tex->shiftX * _byte;
    
    for(int i = 0; i < _tex->height; i++) {
        int _y = i - _tex->shiftY;
        if(_y >= 0 && _y < VBImageGetHeight(_img)) {
            memcpy(_ptr, VBImageGetPixelColor(_img, 0, _y), VBImageGetWidth(_img) * _byte);
        }
        _ptr += _tex->width * _byte;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, _format, _tex->width, _tex->height, 0, _format, GL_UNSIGNED_BYTE, _data);
    free(_data);
    
#ifdef _VB_DEBUG_
	if(glGetError() != GL_NO_ERROR)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureLoadImage() - 텍스쳐를 그래픽 카드에 올리는 중에 OpenGL에러가 발생하였습니다.");
#endif
}

void VBTextureLoadImagePath(VBTexture* _tex, VBString* _path) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureLoadImagePath() - VBNull인 텍스쳐를 Load 하려고 합니다. VBTextureAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
	
	VBImage* _img = VBImageInitWithPath(VBImageAlloc(), _path);
	
	VBTextureLoadImage(_tex, _img);
	
	VBImageFree(&_img);
}

void VBTextureUnload(VBTexture* _tex) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureUnload() - VBNull인 텍스쳐를 Unload 하려고 합니다. VBTextureAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
	
	if(_tex->tid != 0) {
		_tex->color_type = VBColorType_None;
        glBindTexture(GL_TEXTURE_2D, _tex->tid);
		glDeleteTextures(1, (GLuint*)&_tex->tid);
		_tex->tid = 0;
		_tex->width = 0;
		_tex->height = 0;
	}
#ifdef __ANDROID__
    if(_tex->img_android)
        VBImageFree(&_tex->img_android);
#endif
}

VBUShort VBTextureGetID(VBTexture* _tex) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureGetID() - VBNull인 텍스쳐에 접근 하려고 합니다. VBTextureAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
	
	return _tex->tid;
}

VBULong VBTextureGetWidth(VBTexture* _tex) {
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureGetWidth() - VBNull인 텍스쳐에 접근 하려고 합니다. VBTextureAlloc하지 않은 이미지를 사용했을 수 있습니다.");
	
	return _tex->width;
}

VBULong VBTextureGetHeight(VBTexture* _tex) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureGetHeight() - VBNull인 텍스쳐에 접근 하려고 합니다. VBTextureAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
	
	return _tex->height;
}

VBColorType VBTextureGetColorType(VBTexture* _tex) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureGetColorType() - VBNull인 텍스쳐에 접근 하려고 합니다. VBTextureAlloc하지 않은 이미지를 사용했을 수 있습니다.");
#endif
	
	return _tex->color_type;
}
