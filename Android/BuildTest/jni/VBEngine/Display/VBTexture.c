#include "VBTexture.h"
#include "../VBConfig.h"
#include "../VBEngine.h"

#ifdef _VB_IPHONE_
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#endif

#ifdef _VB_ANDROID_
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif

VBTexture* VBTextureAlloc(void) {
	VBTexture* _tex = VBSystemCalloc(1, sizeof(VBTexture));
	
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureAlloc() - 메모�??�당???�패?��??�니??");
#endif
	
	return _tex;
}

VBTexture* VBTextureInit(VBTexture* _tex) {
#ifdef _VB_DUBEG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureInit() - VBNull???�스쳐�? 초기???�려�??�니?? VBTextureAlloc?��? ?��? ?��?지�??�용?�을 ???�습?�다.");
#endif
	
	VBTextureUnload(_tex);
	
	return _tex;
}

VBTexture* VBTextureInitAndLoadWithImage(VBTexture* _tex, VBImage* _img) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureInitAndLoadWithImage() - VBNull???�스쳐�? 초기???�려�??�니?? VBTextureAlloc?��? ?��? ?��?지�??�용?�을 ???�습?�다.");
#endif
	
	_tex = VBTextureInit(_tex);
	VBTextureLoadImage(_tex, _img);
	
	return _tex;
}

VBTexture* VBTextureInitAndLoadWithImagePath(VBTexture* _tex, VBString* _path) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureInitAndLoadWithImagePath() - VBNull???�스쳐�? 초기???�려�??�니?? VBTextureAlloc?��? ?��? ?��?지�??�용?�을 ???�습?�다.");
#endif
	
	_tex = VBTextureInit(_tex);
	VBTextureLoadImagePath(_tex, _path);
	
	return _tex;
}

void VBTextureFree(VBTexture** _tex) {
#ifdef _VB_DEBUG_
	if(*_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureFree() - VBNull???�스쳐�? Free?�려�??�니?? ?��? VBTextureFree?��?거나 VBTextureAlloc?��? ?��? ?�일???�용?�을 ???�습?�다.");
#endif
	
	VBTextureInit(*_tex);
	
	VBSystemFree(*_tex);
	*_tex = VBNull;
}

void VBTextureLoadImage(VBTexture* _tex, VBImage* _img) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureLoadImage() - VBNull???�스쳐�? Load ?�려�??�니?? VBTextureAlloc?��? ?��? ?��?지�??�용?�을 ???�습?�다.");
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
										 "VBEngine Log: VBTextureLoadImage() - ?�스쳐는 가로�? ?�로가 32pixel ?�상?�어???�니??");
	
#define _IsPower(_num) (!((_num - 1) & _num))
	
	
#undef _IsPower
#endif
	
	_img->color_type = VBImageGetColorType(_img);
	
	GLenum _format;
	switch(_img->color_type) {
		case VBColorType_G:
			_format = GL_LUMINANCE;
			break;
		case VBColorType_GA:
			_format = GL_LUMINANCE_ALPHA;
			break;
		case VBColorType_RGB:
			_format = GL_RGB;
			break;
		case VBColorType_RGBA:
			_format = GL_RGBA;
			break;
		default:
			break;
	}
	
#ifdef _VB_DEBUG_
	if(VBImageGetColorBit(_img) != 8)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureLoadImage() - ?�스쳐로 ?�용???��?지??비트?��? 지?�하지 ?�는 비트???�니??(?�재 8비트�?가?�함.)");
#endif
    
    glTexImage2D(GL_TEXTURE_2D, 0, _format, VBImageGetWidth(_img), VBImageGetHeight(_img), 0, _format, GL_UNSIGNED_BYTE, VBImageGetImageData(_img));
    
    _tex->width = VBImageGetWidth(_img);
    _tex->height = VBImageGetHeight(_img);
    
#ifdef _VB_DEBUG_
	if(glGetError() != GL_NO_ERROR)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureLoadImage() - ?�스쳐�? 그래??카드???�리??중에 OpenGL?�러가 발생?��??�니??");
#endif
}

void VBTextureLoadImagePath(VBTexture* _tex, VBString* _path) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureLoadImagePath() - VBNull???�스쳐�? Load ?�려�??�니?? VBTextureAlloc?��? ?��? ?��?지�??�용?�을 ???�습?�다.");
#endif
	
	VBImage* _img = VBImageInitWithPath(VBImageAlloc(), _path);
	
	VBTextureLoadImage(_tex, _img);
	
	VBImageFree(&_img);
}

void VBTextureUnload(VBTexture* _tex) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureUnload() - VBNull???�스쳐�? Unload ?�려�??�니?? VBTextureAlloc?��? ?��? ?��?지�??�용?�을 ???�습?�다.");
#endif
	
	if(_tex->tid != 0) {
		_tex->color_type = VBColorType_None;
        glBindTexture(GL_TEXTURE_2D, _tex->tid);
		glDeleteTextures(1, (GLuint*)&_tex->tid);
		_tex->tid = 0;
		_tex->width = 0;
		_tex->height = 0;
	}
}

VBUShort VBTextureGetID(VBTexture* _tex) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureGetID() - VBNull???�스쳐에 ?�근 ?�려�??�니?? VBTextureAlloc?��? ?��? ?��?지�??�용?�을 ???�습?�다.");
#endif
	
	return _tex->tid;
}

VBULong VBTextureGetWidth(VBTexture* _tex) {
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureGetWidth() - VBNull???�스쳐에 ?�근 ?�려�??�니?? VBTextureAlloc?��? ?��? ?��?지�??�용?�을 ???�습?�다.");
	
	return _tex->width;
}

VBULong VBTextureGetHeight(VBTexture* _tex) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureGetHeight() - VBNull???�스쳐에 ?�근 ?�려�??�니?? VBTextureAlloc?��? ?��? ?��?지�??�용?�을 ???�습?�다.");
#endif
	
	return _tex->height;
}

VBColorType VBTextureGetColorType(VBTexture* _tex) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureGetColorType() - VBNull???�스쳐에 ?�근 ?�려�??�니?? VBTextureAlloc?��? ?��? ?��?지�??�용?�을 ???�습?�다.");
#endif
	
	return _tex->color_type;
}
