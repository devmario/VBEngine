#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <jni.h>
#include <android/log.h>

#define LOG_TAG    "Gelato"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)

// 추후 Engine 으로 이동할 header
#include "jni_asset_file_list.h"
#include "importgl.h"

///////////////////////////////////////////////////////////////
//          전역변수 선언부 (충돌방지 static 선언)
///////////////////////////////////////////////////////////////
static int WindowWidth = 240;
static int WindowHeight = 320;
extern FileList* fileList;
static long currTick = 0;
static long oldTick = 0;

// global env , jvm 
// Main Activity class , object
static JNIEnv* g_env;
static JavaVM* g_jvm;
static jobject gelatoObject;
static jclass gelatoClass;
static int isInit = -1;

///////////////////////////////////////////
//          함수 선언부 
///////////////////////////////////////////
void nativeInit(JNIEnv* env, jobject thiz);
void nativeLoadXML(JNIEnv* env, jobject thiz, jobject object);
void nativeLoadResInfo(JNIEnv* env, jobject thiz, jobjectArray paths, jobjectArray fds, jlongArray offs, jlongArray lengs);
void nativeResize(JNIEnv* env, jobject thiz, jint w, jint h);
void nativeRender(JNIEnv* env);
void nativeInitGame(JNIEnv* env, jobject thiz);
void nativeTouch(JNIEnv* env, jobject thiz, jfloat jx, jfloat jy, jint type);
void nativePause(JNIEnv* env, jobject thiz);
void nativeResume(JNIEnv* env, jobject thiz);
void nativeDestroy(JNIEnv* env);

void saveRecord(int score);
jint loadRecord();
void playSound(const char* soundCode);
void playMusic(const char* soundCode);
void startMusic();
void stopMusic();
void pauseMusic();

typedef struct _StageField {
	int stages;
	int icecreamball[2][12];
	int icecreamPattern[2][12];
	int icecreamEye[2][8];

	int icenum;
	jboolean icepattern;
	jboolean icepatterntwo;

	jboolean iceeyes;
	jboolean iceeyestwo;

	int milkcream;
	int cherry;
	int chocochips;
	int nuts;
	int candy;
	int leftspoid;
	int rightspoid;
	int iceice;
	int leftcorncount;
	int leftcorn_v;
	int leftcorn_c;
	int leftcorn_b;
	int leftcorn_g;
	int rightcorncount;
	int rightcorn_v;
	int rightcorn_c;
	int rightcorn_b;
	int rightcorn_g;
	int centercorncount;
	int centercorn_v;
	int centercorn_c;
	int centercorn_b;
	int centercorn_g;

	jboolean TUB_BIG_VANILLA;
	jboolean TUB_BIG_CHOCO;
	jboolean TUB_BIG_BERRY;
	jboolean TUB_BIG_GREEN;
	jboolean TUB_SMALL_VANILLA;
	jboolean TUB_SMALL_CHOCO;
	jboolean TUB_SMALL_BERRY;
	jboolean TUB_SMALL_GREEN;
	jboolean SPOON_H_VANILLA;
	jboolean SPOON_H_CHOCO;
	jboolean SPOON_H_BERRY;
	jboolean SPOON_H_GREEN;

	jboolean SPOON_L_VANILLA;
	jboolean SPOON_L_CHOCO;
	jboolean SPOON_L_BERRY;
	jboolean SPOON_L_GREEN;
	jboolean SPOON_R_VANILLA;
	jboolean SPOON_R_CHOCO;
	jboolean SPOON_R_BERRY;
	jboolean SPOON_R_GREEN;

	jboolean RING_VERTICAL;
	jboolean RING_HORIZON;

	jboolean SUNGLASS;
	jboolean CAP_OBJ;
	jboolean ICE_OBJ;

	jboolean PATTERN_CAST;
	jboolean MIX_OBJ;
	jboolean MASK_OBJ;

	jboolean CenterMilkCream;
	jboolean CenterCherry;
	jboolean CenterChocochips;
	jboolean CenterNuts;
	jboolean CenterCandy;
	jboolean CenterSpoid_v;
	jboolean CenterSpoid_c;
	jboolean CenterSpoid_b;
	jboolean CenterSpoid_g;

	float defaultTime;
	unsigned int defaultMove;
} StageField;



static long _getTime(void) {
	struct timeval now;
	gettimeofday(&now, NULL);
	return (long) (now.tv_sec * 1000 + now.tv_usec / 1000);
}

///////////////////////////////////////////
//          Android JNI Call 
///////////////////////////////////////////

// native fuction name ,  jvm signature , java function name
static JNINativeMethod gelato[] = { 
		{ "nativeInit", "()V", (void*) nativeInit }, 
		{ "nativeLoadXML", "(LUtil/XMLData;)V", (void*) nativeLoadXML }, 
		{ "nativeLoadResInfo", "([Ljava/lang/String;[Ljava/io/FileDescriptor;[J[J)V", (void*) nativeLoadResInfo }
		
};
static JNINativeMethod renderer[] = { 
		{ "nativeResize", "(II)V", (void*) nativeResize }, 
		{ "nativeRender", "()V", (void*) nativeRender }, 
		{ "nativeInitGame", "()V",(void*) nativeInitGame }

};

static JNINativeMethod surface[] = {
		{ "nativePause", "()V", (void*) nativePause }, 
		{ "nativeResume", "()V", (void*) nativeResume }, 
		{ "nativeDestroy", "()V", (void*) nativeDestroy }, 
		{ "nativeTouch", "(FFI)V", (void*) nativeTouch }
};

/*
 * Register several native methods for one class.
 */
static int registerNativeMethods(JNIEnv* env, const char* className, JNINativeMethod* gMethods, int numMethods) {
	jclass clazz;

	clazz = (*env)->FindClass(env, className);
	if (clazz == NULL) {
		LOGE("Native registration unable to find class '%s'\n", className);
		return JNI_FALSE;
	}
	if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
		LOGE("RegisterNatives failed for '%s'\n", className);
		return JNI_FALSE;
	}

	return JNI_TRUE;
}

/*
 * Register native methods for all classes we know about.
 */
static int registerNatives(JNIEnv* env) {

	if (!registerNativeMethods(env, "com/vanillabreeze/gelato/Gelato", gelato, sizeof(gelato) / sizeof(gelato[0])))
		return JNI_FALSE;

	if (!registerNativeMethods(env, "com/vanillabreeze/gelato/GameRenderer", renderer, sizeof(renderer) / sizeof(renderer[0])))
		return JNI_FALSE;

	if (!registerNativeMethods(env, "com/vanillabreeze/gelato/GameSurface", surface, sizeof(surface) / sizeof(surface[0])))
		return JNI_FALSE;

	return JNI_TRUE;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	LOGV("Entering JNI_OnLoad\n");

	g_env = NULL;
	g_jvm = NULL;
	jint result = -1;

	if ((*vm)->GetEnv(vm, (void**) &g_env, JNI_VERSION_1_4) != JNI_OK)
		return result;

	if (g_env == NULL) {
		LOGE("Could not get handle to the VM");
		return result;
	}

	if ((*g_env)->GetJavaVM(g_env, &g_jvm) < 0) {
		LOGE("Could not get handle to the VM");
		return result;
	}

	if (registerNatives(g_env) != JNI_TRUE) {
		LOGE("ERROR: registerNatives failed");
		return result;
	}

	return JNI_VERSION_1_4;
}


