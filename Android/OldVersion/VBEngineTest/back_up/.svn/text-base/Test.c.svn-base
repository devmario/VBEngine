#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>

#include "../VanillaWorld/VBEngine.h"

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "libnav", __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "libnav", __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , "libnav", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , "libnav", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "libnav", __VA_ARGS__)
#define  LOG_TAG    "VBEngine Test"




void Java_com_vanillabreeze_engine_test_vbfile_VBFile_sendResouceToEngine(JNIEnv* env,jobject thiz, jobject jpath, jobject jfd, jlong joff, jlong jlen);
void Java_com_vanillabreeze_engine_test_vbfile_VBFile_nativeResouceCheck(JNIEnv* env, jobject thiz);

void Java_com_vanillabreeze_engine_test_vbfile_VBFile_sendResouceToEngine(JNIEnv* env,jobject thiz, jobject jpath, jobject jfd, jlong joff, jlong jlen) {
	int myfd;
	jclass fdClass = (*env)->FindClass(env, "java/io/FileDescriptor");
	if (fdClass != NULL) {
		jfieldID fdClassDescriptorFieldID = (*env)->GetFieldID(env, fdClass,"descriptor", "I");
		if (fdClassDescriptorFieldID != NULL && jfd != NULL) {
			jint _fd = (*env)->GetIntField(env, jfd, fdClassDescriptorFieldID);
			myfd =  _fd;
		}
	}
	VBSize len = jlen;
	VBSize off = joff;
	VBUShort fd = myfd;
	VBChar* path = (VBChar*) (*env)->GetStringUTFChars(env, jpath, 0);
	VBEngineFileInfo* info = VBEngineFileInfoInit(VBEngineFileInfoAlloc(),
			path, fd, off, len);
	VBEngineFileInfoAdd(info);
	
	//LOGV("path-%s  fd-%d off-%ld len-%ld" , path, fd, off, len);
	(*env)->ReleaseStringUTFChars(env, jpath, path);
}

void Java_com_vanillabreeze_engine_test_vbfile_VBFile_nativeResouceCheck(JNIEnv* env, jobject thiz) {
	VBFileCopy(VBStringInitWithCString(VBStringAlloc(), "crop_ui.mp3"),VBStringInitWithCString(VBStringAlloc(),"/sdcard/croup_ui.txt"));
	
	void* buffer;
	VBSize size = VBFileCopyToMemory(VBStringInitWithCString(VBStringAlloc(), "crop_ui.mp3"), &buffer);
	if(buffer == VBNull)
	{
		LOGV("Failure~!!! : %ld" , size);
	}
	// Momory data È®ÀÎ
	VBFile* _fdes = VBFileInit(VBFileAlloc()); // des stream open -> write mode
	VBString* _des = VBStringInitWithCString(VBStringAlloc(),"/sdcard/test.txt");
	VBFileOpen(_fdes, _des, VBFileMode_Write);
	VBFileWrite(_fdes, buffer, 1, 1507);
}



