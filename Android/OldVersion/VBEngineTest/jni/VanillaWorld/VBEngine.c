#include "VBEngine.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "IO/VBSystem.h"

#ifdef _VB_IPHONE_
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif

#ifdef _VB_ANDROID_
//#include <GLES/gl.h>
//#include <GLES/glext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#define GL_COLOR_MATERIAL                 0x0B57
//typedef char GLchar; 

#include <android/log.h>
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "libnav", __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "libnav", __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , "libnav", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , "libnav", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "libnav", __VA_ARGS__)


#endif

VBBool _VBEngineOpenGLCompileShader(GLuint* _shader, GLenum _type, VBString* _path);

VBBool _VBEngineOpenGLLoadShader(GLuint _program, VBString* _vtx_path, VBString* _frag_path);

VBBool _VBEngineOpenGLLinkProgram(VBULong _program);

VBLong _vb_engine_uniforms[NUM_UNIFORMS];

VBString* _vb_engine_default_res_path = VBNull;
VBString* _vb_engine_default_rw_doc_path = VBNull;

VBDebug* _vb_engine_default_debuger = VBNull;

VBBool _vb_engine_inited = VBFalse;

VBTexture* _vb_engine_default_graphic_2d_line_texture = VBNull;

VBBool _vb_engine_open_gl_is_suported_shader = VBFalse;

VBULong _vb_engine_open_gl_program = 0;

VBColorRGBAf _vb_engine_clear_color;

VBBool VBEngineStart(const VBChar* _res_path, const VBChar* _rw_doc_path) {

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
		_vb_engine_default_debuger = VBDebugInit(VBDebugAlloc(), _log_path);
		VBSystemFree(_log_path);
        
		_vb_engine_default_res_path = VBStringInitWithCString(VBStringAlloc(), _res_path);
		
		_vb_engine_default_rw_doc_path = VBStringInitWithCString(VBStringAlloc(), _rw_doc_path);
        VBString* _open_gl_version_string = VBStringInitWithCString(VBStringAlloc(), (const VBChar*)glGetString(GL_VERSION));
		VBString* _path = VBStringInitWithCString(VBStringAlloc(), VBStringGetCString(VBEngineGetResourcePath()));
		VBStringAddCString(_path, "/grap_line_64.png");
		_vb_engine_default_graphic_2d_line_texture = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _path);
		VBStringFree(&_path);

        #ifdef _VB_ANDROID_
        LOGV("open gl version : %s\n", _open_gl_version_string->data);
	 #endif
        printf("open gl version : %s\n", _open_gl_version_string->data);
        VBStringSlice(_open_gl_version_string, 0, 13);

        _vb_engine_open_gl_is_suported_shader = VBStringIsEqualToCString(_open_gl_version_string, "OpenGL ES 2.0");

        //_vb_engine_open_gl_is_suported_shader = VBStringIsEqualToCString(_open_gl_version_string, "OpenGL ES 2.0 APPLE");
        //_vb_engine_open_gl_is_suported_shader = VBStringIsEqualToCString(_open_gl_version_string, "OpenGL ES 2.0 IMGSGX535-48.14.1");
        //_vb_engine_open_gl_is_suported_shader = VBStringIsEqualToCString(_open_gl_version_string, "OpenGL ES 2.0 IMGSGX535-63.4.2");
        VBStringFree(&_open_gl_version_string);
        
        if(_vb_engine_open_gl_is_suported_shader) {
            VBString* _vtx_shader_path = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/VBShader2D.vsh", VBStringGetCString(_vb_engine_default_res_path));
            VBString* _flag_shader_path = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/VBShader2D.fsh", VBStringGetCString(_vb_engine_default_res_path));
            
            _vb_engine_open_gl_program = glCreateProgram();
            _VBEngineOpenGLLoadShader(_vb_engine_open_gl_program, _vtx_shader_path, _flag_shader_path);
            
            VBStringFree(&_vtx_shader_path);
            VBStringFree(&_flag_shader_path);
            
            glUseProgram(_vb_engine_open_gl_program);
        }
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_COLOR_MATERIAL);
		
		_vb_engine_inited = VBTrue;
	}
	return VBFalse;
}

VBBool VBEngineShutdown(void) {
	if(_vb_engine_inited == VBTrue) {
		VBTextureFree(&_vb_engine_default_graphic_2d_line_texture);
		
		VBSystemFree(_vb_engine_default_rw_doc_path);
		VBStringFree(&_vb_engine_default_res_path);
		VBDebugFree(&_vb_engine_default_debuger);
		
		_vb_engine_inited = VBFalse;
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

VBTexture* VBEngineGetGraphic2DLineTexture(void) {
	if(_vb_engine_default_graphic_2d_line_texture == VBNull)
		VBDebugPrintAbort(VBNull, VBTrue, "VBEngine Log: 엔진이 초기화 되지 않아 기본2D 그래픽 텍스쳐를 가져올수 없습니다.");
	
	return _vb_engine_default_graphic_2d_line_texture;
}

VBFloat VBEngineOpenGLGetIsSuportedShader(void) {
    return _vb_engine_open_gl_is_suported_shader;
}

VBBool _VBEngineOpenGLLinkProgram(VBULong _program) {
    VBLong status;
    
    glLinkProgram(_program);
    GLint logLength;
    glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logLength);
    if(logLength > 0) {
        VBChar *log = (VBChar*)malloc(logLength);
        glGetProgramInfoLog(_program, logLength, &logLength, log);
        printf("Program link log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(_program, GL_LINK_STATUS, (GLint*)&status);
    if(status == 0) 
        return VBFalse;
    return VBTrue;
}

VBBool _VBEngineOpenGLCompileShader(GLuint* _shader, GLenum _type, VBString* _path) {
    GLint status;
    
    VBFile* _shader_file = VBFileInitWithOpen(VBFileAlloc(), _path, VBFileMode_Read);
    VBSize _shader_file_size = VBFileGetSize(_shader_file);
    const GLchar* _shader_c_string = VBSystemCalloc(_shader_file_size + 1, sizeof(GLchar));
    VBFileReadBytes(_shader_file, (VBByte*)_shader_c_string, _shader_file_size);
    VBFileFree(&_shader_file);
    
    *_shader = glCreateShader(_type);
    glShaderSource(*_shader, 1, &_shader_c_string, NULL);
    glCompileShader(*_shader);
    
    VBSystemFree((void*)_shader_c_string);
    
    GLint _log_length;
    glGetProgramiv(_vb_engine_open_gl_program, GL_INFO_LOG_LENGTH, &_log_length);
    if(_log_length > 0) {
        VBChar* _log = (VBChar*)VBSystemMalloc(_log_length);
        glGetProgramInfoLog(_vb_engine_open_gl_program, _log_length, &_log_length, _log);
        printf("Program link log:\n%s", _log);
        VBSystemFree(_log);
    }
    
    glGetShaderiv(*_shader, GL_COMPILE_STATUS, &status);
    if(status == 0) {
        glDeleteShader(*_shader);
        return VBFalse;
    }
    
    return VBTrue;
}

VBBool _VBEngineOpenGLLoadShader(GLuint _program, VBString* _vtx_path, VBString* _frag_path) {
    GLuint vert_shader, frag_shader;
    
    if(!_VBEngineOpenGLCompileShader(&vert_shader, GL_VERTEX_SHADER, _vtx_path)) {
        printf("Failed to compile vertex shader\n");
        return VBFalse;
    }
    
    if(!_VBEngineOpenGLCompileShader(&frag_shader, GL_FRAGMENT_SHADER, _frag_path)) {
        printf("Failed to compile fragment shader\n");
        return VBFalse;
    }
    
    glAttachShader(_program, vert_shader);
    
    glAttachShader(_program, frag_shader);
    
    glBindAttribLocation(_vb_engine_open_gl_program, ATTRIB_VERTEX, "at_vtx");
    glBindAttribLocation(_vb_engine_open_gl_program, ATTRIB_TEXCOORD, "at_txc");
    glBindAttribLocation(_vb_engine_open_gl_program, ATTRIB_COLOR_PERCENT, "at_color_per");
    glBindAttribLocation(_vb_engine_open_gl_program, ATTRIB_COLOR_ADD, "at_color_add");
    
    _VBEngineOpenGLLinkProgram(_vb_engine_open_gl_program);
    
    
    if (vert_shader)
    {
        glDetachShader(_program, vert_shader);
        glDeleteShader(vert_shader);
    }
    if (frag_shader)
    {
        glDetachShader(_program, frag_shader);
        glDeleteShader(frag_shader);
    }
    
    return VBTrue;
}

VBULong VBEngineOpenGLGetProgram(void) {
    return _vb_engine_open_gl_program;
}

VBLong* VBEngineOpenGLGetUniform() {
    return _vb_engine_uniforms;
}

void VBEngineSetClearColor(VBColorRGBAf _clear_color) {
    _vb_engine_clear_color = _clear_color;
    glClearColor(_vb_engine_clear_color.r, _vb_engine_clear_color.g, _vb_engine_clear_color.b, _vb_engine_clear_color.a);
}

VBColorRGBAf VBEngineGetClearColor(void) {
    return _vb_engine_clear_color;
}

void VBEngineClearDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
}









