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
										 "VBEngine Log: VBTextureAlloc() - λ©λͺ¨λ¦?? λΉ???€ν¨?μ??΅λ??");
#endif
	
	return _tex;
}

VBTexture* VBTextureInit(VBTexture* _tex) {
#ifdef _VB_DUBEG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureInit() - VBNull???μ€μ³λ? μ΄κΈ°???λ €κ³??©λ?? VBTextureAlloc?μ? ?μ? ?΄λ?μ§λ₯??¬μ©?μ ???μ΅?λ€.");
#endif
	
	VBTextureUnload(_tex);
	
	return _tex;
}

VBTexture* VBTextureInitAndLoadWithImage(VBTexture* _tex, VBImage* _img) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureInitAndLoadWithImage() - VBNull???μ€μ³λ? μ΄κΈ°???λ €κ³??©λ?? VBTextureAlloc?μ? ?μ? ?΄λ?μ§λ₯??¬μ©?μ ???μ΅?λ€.");
#endif
	
	_tex = VBTextureInit(_tex);
	VBTextureLoadImage(_tex, _img);
	
	return _tex;
}

VBTexture* VBTextureInitAndLoadWithImagePath(VBTexture* _tex, VBString* _path) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureInitAndLoadWithImagePath() - VBNull???μ€μ³λ? μ΄κΈ°???λ €κ³??©λ?? VBTextureAlloc?μ? ?μ? ?΄λ?μ§λ₯??¬μ©?μ ???μ΅?λ€.");
#endif
	
	_tex = VBTextureInit(_tex);
	VBTextureLoadImagePath(_tex, _path);
	
	return _tex;
}

void VBTextureFree(VBTexture** _tex) {
#ifdef _VB_DEBUG_
	if(*_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureFree() - VBNull???μ€μ³λ? Free?λ €κ³??©λ?? ?΄λ? VBTextureFree?μ?κ±°λ VBTextureAlloc?μ? ?μ? ?μΌ???¬μ©?μ ???μ΅?λ€.");
#endif
	
	VBTextureInit(*_tex);
	
	VBSystemFree(*_tex);
	*_tex = VBNull;
}

void VBTextureLoadImage(VBTexture* _tex, VBImage* _img) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureLoadImage() - VBNull???μ€μ³λ? Load ?λ €κ³??©λ?? VBTextureAlloc?μ? ?μ? ?΄λ?μ§λ₯??¬μ©?μ ???μ΅?λ€.");
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
										 "VBEngine Log: VBTextureLoadImage() - ?μ€μ³λ κ°λ‘μ? ?Έλ‘κ° 32pixel ?΄μ?΄μ΄???©λ??");
	
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
										 "VBEngine Log: VBTextureLoadImage() - ?μ€μ³λ‘ ?¬μ©???΄λ?μ§??λΉνΈ?κ? μ§?νμ§ ?λ λΉνΈ???λ??(?μ¬ 8λΉνΈλ§?κ°?₯ν¨.)");
#endif
    
    glTexImage2D(GL_TEXTURE_2D, 0, _format, VBImageGetWidth(_img), VBImageGetHeight(_img), 0, _format, GL_UNSIGNED_BYTE, VBImageGetImageData(_img));
    
    _tex->width = VBImageGetWidth(_img);
    _tex->height = VBImageGetHeight(_img);
    
#ifdef _VB_DEBUG_
	if(glGetError() != GL_NO_ERROR)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureLoadImage() - ?μ€μ³λ? κ·Έλ??μΉ΄λ???¬λ¦¬??μ€μ OpenGL?λ¬κ° λ°μ?μ??΅λ??");
#endif
}

void VBTextureLoadImagePath(VBTexture* _tex, VBString* _path) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureLoadImagePath() - VBNull???μ€μ³λ? Load ?λ €κ³??©λ?? VBTextureAlloc?μ? ?μ? ?΄λ?μ§λ₯??¬μ©?μ ???μ΅?λ€.");
#endif
	
	VBImage* _img = VBImageInitWithPath(VBImageAlloc(), _path);
	
	VBTextureLoadImage(_tex, _img);
	
	VBImageFree(&_img);
}

void VBTextureUnload(VBTexture* _tex) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureUnload() - VBNull???μ€μ³λ? Unload ?λ €κ³??©λ?? VBTextureAlloc?μ? ?μ? ?΄λ?μ§λ₯??¬μ©?μ ???μ΅?λ€.");
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
										 "VBEngine Log: VBTextureGetID() - VBNull???μ€μ³μ ?κ·Ό ?λ €κ³??©λ?? VBTextureAlloc?μ? ?μ? ?΄λ?μ§λ₯??¬μ©?μ ???μ΅?λ€.");
#endif
	
	return _tex->tid;
}

VBULong VBTextureGetWidth(VBTexture* _tex) {
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureGetWidth() - VBNull???μ€μ³μ ?κ·Ό ?λ €κ³??©λ?? VBTextureAlloc?μ? ?μ? ?΄λ?μ§λ₯??¬μ©?μ ???μ΅?λ€.");
	
	return _tex->width;
}

VBULong VBTextureGetHeight(VBTexture* _tex) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureGetHeight() - VBNull???μ€μ³μ ?κ·Ό ?λ €κ³??©λ?? VBTextureAlloc?μ? ?μ? ?΄λ?μ§λ₯??¬μ©?μ ???μ΅?λ€.");
#endif
	
	return _tex->height;
}

VBColorType VBTextureGetColorType(VBTexture* _tex) {
#ifdef _VB_DEBUG_
	if(_tex == VBNull)
		VBDebugPrintAndPrintLogFileAbort(VBEngineGetDefaultDebuger(), VBTrue, 
										 "VBEngine Log: VBTextureGetColorType() - VBNull???μ€μ³μ ?κ·Ό ?λ €κ³??©λ?? VBTextureAlloc?μ? ?μ? ?΄λ?μ§λ₯??¬μ©?μ ???μ΅?λ€.");
#endif
	
	return _tex->color_type;
}
