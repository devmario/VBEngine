#ifndef __ANDROID_NATIVE_H__
#define __ANDROID_NATIVE_H__
#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>
#define LOG_TAG  "#@#"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)

#include "PlatformFunctions.h"

#ifdef __cplusplus
	extern "C" {
#endif

static JavaVM *jvm = NULL;

typedef union {
    JNIEnv* env;
    void* venv;
} UnionJNIEnvToVoid;

// =================================== JAVA Interface (C/C++ -> JAVA) =========================================
bool facebookIsLogin();

bool facebookLogin(PlatformCallback _callback);

bool facebookLogout();

void facebookRequestGraphPath(PlatformFacebookGraphPath type, PlatformCallback _callback);

void facebookAppRequest(const char* _msg, const char* _to, const char* _notification_text, PlatformCallback _callback);

void facebookFeed(const char* _name, const char* _caption, const char* _description, const char* _link, const char* _picture, PlatformCallback _callback);
// =============================================================================================================



// =================================== Native Interface (JAVA -> C/C++) =========================================
JNIEXPORT void JNICALL Java_com_vanillabreeze_gelatomania_GelatoManiaActivity_nativeFacebookRequestGraphPath( JNIEnv* env, jobject thiz, jstring str);

JNIEXPORT void JNICALL Java_com_vanillabreeze_gelatomania_GelatoManiaActivity_nativeFacebookAppRequest( JNIEnv* env, jobject thiz, jstring str);

JNIEXPORT void JNICALL Java_com_vanillabreeze_gelatomania_GelatoManiaActivity_nativeFacebookFeed( JNIEnv* env, jobject thiz, jstring str);
// =============================================================================================================

#ifdef __cplusplus
}
#endif
#endif //__ANDROID_NATIVE_H__
