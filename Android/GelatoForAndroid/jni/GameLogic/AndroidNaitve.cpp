#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "../VBEngine/VBEngine.h"

#include <android/log.h>
#define LOG_TAG  "VBEngine Test"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)



static long prev_time;
static timeval end_point ,start_point;
static float operating_time;
static JavaVM *jvm = NULL;
using namespace std;

void java_dismissDialog();

// ========================= JNI Function =================================
void nativeInit(JNIEnv* env,jobject thiz)
{
	// VBEngineStart("assets", "sdcard/VBEngine");
    // VBString* _res_path = VBStringInitWithCString(VBStringAlloc(), VBStringGetCString(VBEngineGetResourcePath()));
    VBString* _res_path = VBStringInitWithCString(VBStringAlloc(), "this is test");   
    // sample = EngineSampleInit(EngineSampleAlloc(), _res_path, 480, 800);
    VBStringFree(&_res_path);
	java_dismissDialog();  // dismiss dialog in java area
	gettimeofday(&start_point, NULL);
}

void nativeResume(JNIEnv* env,jobject thiz)
{
	LOGV("nativeResume");

	gettimeofday(&start_point, NULL);
}

void nativePause(JNIEnv* env,jobject thiz)
{
	LOGV("nativePause");
}

void nativeDestroy(JNIEnv* env,jobject thiz)
{
	LOGV("nativeDestroy");
	// EngineSampleFree(&sample);    
    // VBEngineShutdown();
}



void nativeResize(JNIEnv* env,jobject thiz, jint w, jint h)
{
	LOGV("nativeResize X:%d Y:%d", w, h);
}

void nativeRender(JNIEnv* env,jobject thiz)
{
	gettimeofday(&end_point, NULL); 
	
	operating_time = (float)(end_point.tv_sec)+(float)(end_point.tv_usec)/1000000.0-(float)(start_point.tv_sec)-(float)(start_point.tv_usec)/1000000.0;
	
    //EngineSampleUpdateAndDraw(sample, operating_time);
	//EngineSampleUpdateAndDraw(sample, 1.0 / 60);
	//EngineSampleUpdateAndDraw(sample, 1.0 / 100);
	if(operating_time < 0)
		operating_time = 1.0 + operating_time;
	//LOGV("%f\n",operating_time);
	gettimeofday(&start_point, NULL);
}

void nativeDone(JNIEnv* env,jobject thiz)
{
	//LOGV("nativeDone");
}

void nativeResourceInit(JNIEnv* env,jobject thiz, jstring jpath, jobject jfd, jlong joff, jlong jlen) {
	//LOGV("nativeResourceInit");
	int myfd;
	jclass fdClass = env->FindClass("java/io/FileDescriptor");
	if (fdClass != NULL) {
		jfieldID fdClassDescriptorFieldID = env->GetFieldID(fdClass,"descriptor", "I");
		if (fdClassDescriptorFieldID != NULL && jfd != NULL) {
			jint _fd = env->GetIntField(jfd, fdClassDescriptorFieldID);
			myfd =  _fd;
		}
	}
	VBSize len = jlen;
	VBSize off = joff;
	VBUShort fd = myfd;
	VBChar* path = (VBChar*) env->GetStringUTFChars(jpath, 0);
	VBEngineFileInfo* info = VBEngineFileInfoInit(VBEngineFileInfoAlloc(),path, fd, off, len);
	VBEngineFileInfoAdd(info);
	
	LOGV("path-%s  fd-%d off-%ld len-%ld" , path, fd, off, len);
	env->ReleaseStringUTFChars(jpath, path);
}


// =================================== JNI_OnLoad =============================================
/*
 * This is called by the VM when the shared library is first loaded.
 */
 
typedef union {
    JNIEnv* env;
    void* venv;
} UnionJNIEnvToVoid;

/*
 * Register native methods for all classes we know about.
 *
 * returns JNI_TRUE on success.
 */
int registerNatives(JNIEnv* env)
{
    jclass clazz;
	const char *VBGLSurfaceViewClass = "lowmans/test/vbengine/VBGLSurfaceView";
    clazz = env->FindClass(VBGLSurfaceViewClass);
    if (clazz == NULL) {
        LOGE("Native registration unable to find class '%s'", VBGLSurfaceViewClass);
        return JNI_FALSE;
    }
	
	static JNINativeMethod VBGLSurfaceViewMethods[] = {
	   // native fuction name ,  jvm signature , java function name 
	  {"nativeResume", "()V", (void*)nativeResume},
	  {"nativePause", "()V", (void*)nativePause},
	  {"nativeDestroy", "()V", (void*)nativeDestroy},
	};
	
    if (env->RegisterNatives(clazz, VBGLSurfaceViewMethods, sizeof(VBGLSurfaceViewMethods)/ sizeof(VBGLSurfaceViewMethods[0])) < 0) {
	    LOGE("RegisterNatives failed for '%s'", VBGLSurfaceViewClass);
        return JNI_FALSE;
    }
	
	const char *VBGLSurfaceViewRendererClass = "lowmans/test/vbengine/VBGLSurfaceViewRenderer";
    clazz = env->FindClass(VBGLSurfaceViewRendererClass);
    if (clazz == NULL) {
        LOGE("Native registration unable to find class '%s'", VBGLSurfaceViewRendererClass);
        return JNI_FALSE;
    }
	
	static JNINativeMethod VBGLSurfaceViewRendererMethods[] = {
	   // native fuction name ,  jvm signature , java function name 
	  {"nativeInit", "()V", (void*)nativeInit},
	  {"nativeResize", "(II)V", (void*)nativeResize},
	  {"nativeRender", "()V", (void*)nativeRender},
	  {"nativeDone", "()V", (void*)nativeDone},
	  {"nativeResourceInit", "(Ljava/lang/String;Ljava/io/FileDescriptor;JJ)V", (void*)nativeResourceInit},
	  
	};
	
    if (env->RegisterNatives(clazz, VBGLSurfaceViewRendererMethods, sizeof(VBGLSurfaceViewRendererMethods)/ sizeof(VBGLSurfaceViewRendererMethods[0])) < 0) {
	    LOGE("RegisterNatives failed for '%s'", VBGLSurfaceViewRendererClass);
        return JNI_FALSE;
    }
	
	return JNI_TRUE;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    UnionJNIEnvToVoid uenv;
    uenv.venv = NULL;
    jint result = -1;
    JNIEnv* env = NULL;
    LOGI("JNI_OnLoad");
    if (vm->GetEnv(&uenv.venv, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("ERROR: GetEnv failed");
        return result;
    }
	
	env = uenv.env;
	
	if (env->GetJavaVM(&jvm) < 0) { 
		LOGE("Could not get handle to the VM");
		return result;
	}
    
    if (registerNatives(env) != JNI_TRUE) {
        LOGE("ERROR: registerNatives failed");
        return result;
    }

    return JNI_VERSION_1_4;
}
// ========================================================================================================

// =================================== JAVA Interface =========================================
void java_dismissDialog()
{
	LOGI("java_dismissDialog");
	const char *ClassName = "lowmans/test/vbengine/VBEngineTest";
	JNIEnv* env = NULL;
	if(jvm == NULL)
	{
		LOGE("jvm == null : please on load JavaVM");
		return ;
	}
	if (jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
		LOGE("%s: AttachCurrentThread() failed", __FUNCTION__);
		return ;
	}		

	/* invoke the method using the JNI */ 
    jclass clazz = env->FindClass(ClassName);
    if (clazz == NULL) {
        LOGE("Native registration unable to find class '%s'", ClassName);
    }
	
	jmethodID mid = env->GetStaticMethodID(clazz, "dismissDialog", "()V");
	if (mid == NULL) {
        LOGE("Native registration unable to find GetStaticMethodID '%s'  ", "dismissDialog");
    }
	
    env->CallStaticVoidMethod(clazz, mid); 
	
	env->DeleteLocalRef(clazz);
}	
// ============================================================================================