#include "VBEngine.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "IO/VBSystem.h"

#ifdef _VB_IPHONE_
#include <OpenGLES/ES1/gl.h>
#endif

#ifdef __ANDROID__
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <unistd.h>
#endif

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

#ifdef __ANDROID__
static const char *ClassName =
		"kr.daum_mobage.am_db.g12009230.GelatoManiaActivity";
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
	jint result = -1;
	JNIEnv* env = NULL;
	LOGI("JNI_OnLoad");
	if ((*vm)->GetEnv(vm, (void**)&env, JNI_VERSION_1_4) != JNI_OK) {
		LOGE("ERROR: GetEnv failed");
		return result;
	}

	if ((*env)->GetJavaVM(env, &g_jvm) < 0) {
		LOGE("Could not get handle to the VM");
		return result;
	}

	LOGD("## JNI_OnLoad VBEngine ## g_jvm: %x", g_jvm);

	return JNI_VERSION_1_4;
}

char* getResourcePath()
{
	JNIEnv* env = NULL;
	if (g_jvm == NULL) {
		LOGE("g_jvm == null : please on load JavaVM");
		return NULL;
	}

	if ((*g_jvm)->AttachCurrentThread(g_jvm, &env, NULL) != JNI_OK) {
		LOGE("%s: AttachCurrentThread() failed", __FUNCTION__);
		return NULL;
	}

	/* invoke the method using the JNI */
	jclass clazz = (*env)->FindClass(env, ClassName);
	if (clazz == NULL) {
		LOGE("Native registration unable to find class '%s'", ClassName);
		return NULL;
	}

	jmethodID mid = (*env)->GetStaticMethodID(env, clazz, "getResourcePath", "()Ljava/lang/String;");
	if (mid == NULL) {
		LOGE("Native registration unable to find GetStaticMethodID '%s'  ",
				"getResourcePath");
		return NULL;
	}

	jstring path = (jstring)(*env)->CallStaticObjectMethod(env, clazz, mid);
	(*env)->DeleteLocalRef(env, clazz);
	return (char*)(*env)->GetStringUTFChars(env, path, false);
}

bool android_fcheck(const char* filename)
{
	bool ret = false;
	char* resPath = getResourcePath();
	if ( strstr(filename, getResourcePath) )
	{
		if (access(filename, R_OK) == 0)
		{
			ret = true;
		}
		else
		{
			char name[128] = {0,};
			char temp[256] = {0,};
			char* p = NULL;
			const char* delim = "/";
			strcpy(temp, filename);
			p = strtok((char*)temp, delim);
			if (p) {
				strcpy(name, p);
			}
			while (p) {
				p = strtok(NULL, delim);
				if (p) {
					strcpy(name, p);
				}
			}

			if (fileCopy(name, filename)) {
				ret = true;
			} else {
				ret = false;
			}
		}
	}

	//LOGD("android_fcheck() filename: %s, ret: %x", filename, ret);

	return ret;
}

bool fileCopy(const char* _srcPath, const char* _dstPath)
{
	JNIEnv* env = NULL;
	if (g_jvm == NULL) {
		LOGE("g_jvm == null : please on load JavaVM");
		return false;
	}
	if ((*g_jvm)->AttachCurrentThread(g_jvm, &env, NULL) != JNI_OK) {
		LOGE("facebookAppRequest -> %s: AttachCurrentThread() failed", __FUNCTION__);
		return false;
	}

	/* invoke the method using the JNI */
	jclass clazz = (*env)->FindClass(env, ClassName);
	if (clazz == NULL) {
		LOGE("facebookAppRequest -> Native registration unable to find class '%s'", ClassName);
		return false;
	}

	jmethodID mid = (*env)->GetStaticMethodID(env, clazz, "fileCopy", "(Ljava/lang/String;Ljava/lang/String;)Z");
	if (mid == NULL) {
		LOGE("Native registration unable to find GetStaticMethodID '%s'  ",
				"fileCopy");
		return false;
	}

	jstring srcPath = (*env)->NewStringUTF(env, _srcPath);
	jstring dstPath = (*env)->NewStringUTF(env, _dstPath);

	// call java method
	bool ret = (*env)->CallStaticBooleanMethod(env, clazz, mid, srcPath, dstPath);

	// memory release
	(*env)->DeleteLocalRef(env, clazz);
	(*env)->DeleteLocalRef(env, srcPath);
	(*env)->DeleteLocalRef(env, dstPath);

	return ret;
}

FILE* android_fopen(const char* filename, const char* mode)
{
	FILE* fp = NULL;
	char* resPath = getResourcePath();
	if ( strstr(filename, resPath) )
	{
		if (access(filename, R_OK) == 0)
		{
			fp = fopen(filename, mode);
		}
		else
		{
			char name[128] = {0,};
			char temp[256] = {0,};
			char* p = NULL;
			const char* delim = "/";
			strcpy(temp, filename);
			p = strtok((char*)temp, delim);
			if (p) {
				strcpy(name, p);
			}
			while (p) {
				p = strtok(NULL, delim);
				if (p) {
					strcpy(name, p);
				}
			}

			if (fileCopy(name, filename)) {
				fp = fopen(filename, mode);
			} else {
				return fp;
			}
		}
	}
	else
	{
		fp = fopen(filename, mode);
	}

	//LOGD("android_fopen() filename: %s, fp: %x", filename, fp);

	return fp;
}
#endif





