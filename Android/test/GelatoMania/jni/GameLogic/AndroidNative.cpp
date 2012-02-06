#include "AndroidNative.h"

static const char *ClassName =
		"com.vanillabreeze.gelatomania.GelatoManiaActivity";

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
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

	return JNI_VERSION_1_4;
}

bool facebookLogin() {
	LOGI("facebookLogin");

	JNIEnv* env = NULL;
	if (jvm == NULL) {
		LOGE("jvm == null : please on load JavaVM");
		return false;
	}
	if (jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
		LOGE("%s: AttachCurrentThread() failed", __FUNCTION__);
		return false;
	}

	/* invoke the method using the JNI */
	jclass clazz = env->FindClass(ClassName);
	if (clazz == NULL) {
		LOGE("Native registration unable to find class '%s'", ClassName);
	}

	jmethodID mid = env->GetStaticMethodID(clazz, "facebookLogin", "()Z");
	if (mid == NULL) {
		LOGE("Native registration unable to find GetStaticMethodID '%s'  ",
				"facebookLogin");
	}

	bool ret = (bool) env->CallBooleanMethod(clazz, mid);
	env->DeleteLocalRef(clazz);

	return ret;
}

void facebookRequestGraphPath(const char* _path) {
	LOGI("facebookRequestGraphPath");
	JNIEnv* env = NULL;
	if (jvm == NULL) {
		LOGE("jvm == null : please on load JavaVM");
		return false;
	}
	if (jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
		LOGE("facebookRequestGraphPath -> %s: AttachCurrentThread() failed", __FUNCTION__);
		return false;
	}

	/* invoke the method using the JNI */
	jclass clazz = env->FindClass(ClassName);
	if (clazz == NULL) {
		LOGE("facebookRequestGraphPath -> Native registration unable to find class '%s'", ClassName);
	}

	jmethodID mid = env->GetStaticMethodID(clazz, "facebookRequestGraphPath", "()Z");
	if (mid == NULL) {
		LOGE("Native registration unable to find GetStaticMethodID '%s'  ",
				"facebookLogin");
	}

	int size = strlen(_path);
	char* path =  (char*) malloc();
	jstring jpath = env->NewStringUTF(_path);

    env->CallVoidMethod(clazz, mid);

    env->DeleteLocalRef(clazz);
    env->ReleaseStringUTFChars(jpath, path);

}

void facebookAppRequest(const char* _msg, const char* _to,
		const char* _notification_text) {
	LOGI("facebookAppRequest");
	JNIEnv* env = NULL;
	if (jvm == NULL) {
		LOGE("jvm == null : please on load JavaVM");
		return false;
	}
	if (jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
		LOGE("facebookAppRequest -> %s: AttachCurrentThread() failed", __FUNCTION__);
		return false;
	}

	/* invoke the method using the JNI */
	jclass clazz = env->FindClass(ClassName);
	if (clazz == NULL) {
		LOGE("facebookAppRequest -> Native registration unable to find class '%s'", ClassName);
	}

	jmethodID mid = env->GetStaticMethodID(clazz, "facebookAppRequest", "()");
	if (mid == NULL) {
		LOGE("Native registration unable to find GetStaticMethodID '%s'  ",
				"facebookAppRequest");
	}

//	bool ret = (bool) env->CallBooleanMethod(clazz, mid);
//	env->DeleteLocalRef(clazz);
}

void facebookFeed(const char* _name, const char* _caption,
		const char* _description, const char* _link, const char* _picture) {
	LOGI("facebookRequestGraphPath");
	JNIEnv* env = NULL;
	if (jvm == NULL) {
		LOGE("jvm == null : please on load JavaVM");
		return false;
	}
	if (jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
		LOGE("facebookFeed -> %s: AttachCurrentThread() failed", __FUNCTION__);
		return false;
	}

	/* invoke the method using the JNI */
	jclass clazz = env->FindClass(ClassName);
	if (clazz == NULL) {
		LOGE("facebookFeed -> Native registration unable to find class '%s'", ClassName);
	}

	jmethodID mid = env->GetStaticMethodID(clazz, "facebookLogin", "()Z");
	if (mid == NULL) {
		LOGE("Native registration unable to find GetStaticMethodID '%s'  ",
				"facebookFeed");
	}

//	bool ret = (bool) env->CallBooleanMethod(clazz, mid);
//	env->DeleteLocalRef(clazz);
}

// ============================================================================================
JNIEXPORT void JNICALL Java_com_vanillabreeze_gelatomania_GelatoManiaActivity_nativeFacebookRequestGraphPath( JNIEnv* env, jobject thiz, jstring str)
{
	//Get the native string from javaString
	const char *_str = env->GetStringUTFChars(str, 0);

	//Do something with the nativeString
	LOGV("nativeFacebookRequestGraphPath str : %s" , _str);
	//DON'T FORGET THIS LINE!!!
	env->ReleaseStringUTFChars(str, _str);
}

JNIEXPORT void JNICALL Java_com_vanillabreeze_gelatomania_GelatoManiaActivity_nativeFacebookAppRequest( JNIEnv* env, jobject thiz, jstring str)
{
	//Get the native string from javaString
	const char *_str = env->GetStringUTFChars(str, 0);

	//Do something with the nativeString
	LOGV("nativeFacebookAppRequest str : %s" , _str);
	//DON'T FORGET THIS LINE!!!
	env->ReleaseStringUTFChars(str, _str);
}

JNIEXPORT void JNICALL Java_com_vanillabreeze_gelatomania_GelatoManiaActivity_nativeFacebookFeed( JNIEnv* env, jobject thiz, jstring str)
{
	//Get the native string from javaString
	const char *_str = env->GetStringUTFChars(str, 0);

	//Do something with the nativeString
	LOGV("nativeFacebookFeed str : %s" , _str);
	//DON'T FORGET THIS LINE!!!
	env->ReleaseStringUTFChars(str, _str);
}
