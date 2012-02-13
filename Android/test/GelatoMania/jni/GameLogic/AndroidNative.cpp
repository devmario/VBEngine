#ifdef __ANDROID__

#include <android/bitmap.h>

#include "AndroidNative.h"
#include "cJSON.h"


static const char *ClassName =
		"com.vanillabreeze.gelatomania.GelatoManiaActivity";

static PlatformCallback g_FacebookLoginCB;
static PlatformCallback g_FacebookRequestGraphPathCB;
static PlatformCallback g_FacebookAppRequestCB;
static PlatformCallback g_FacebookFeedCB;

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

VBImage* GetTextImageWithSizeDetail(const char* _txt, const char* _fontName, float _text_size, int _width, int _height, const char* _colorCode, const char* _shadowColorCode, VBVector2D _shadowOffset, int align)
{
	return getTextImageWithSizeDetail(_txt, _text_size, _width, _height);

	//return VBImageInitAndClear(VBImageAlloc(), VBColorType_RGBA, 8, _width, _height);
}

VBImage* getTextImageWithSizeDetail(const char* _text, int _text_size, int _width, int _height)
{
		JNIEnv* env = NULL;
		AndroidBitmapInfo info;
		void* pixels;
		int ret;

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

		jmethodID mid = env->GetStaticMethodID(clazz, "getTextImageWithSizeDetail", "(Ljava/lang/String;III)Landroid/graphics/Bitmap;");
		if (mid == NULL) {
			LOGE("Native registration unable to find GetStaticMethodID '%s'  ",
					"getTextImageWithSizeDetail");
		}

		jstring text = env->NewStringUTF(_text);

		jobject bitmap = env->CallStaticObjectMethod(clazz, mid, text, _text_size, _width, _height);

		if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
			LOGE("AndroidBitmap_getInfo() failed! error=%d", ret);
			return false;
		}

		LOGD("AndroidBitmap_getInfo() bitmap: %x, width: %d, height: %d", bitmap, info.width, info.height);

		if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
					LOGE("AndroidBitmap_lockPixels() failed! error=%d", ret);
					return false;
		}

		VBImage* image = VBImageInitWithData(VBImageAlloc(), VBColorType_RGBA, 8, _width, _height, pixels);

		AndroidBitmap_unlockPixels(env, bitmap);

		env->DeleteLocalRef(clazz);
		env->DeleteLocalRef(text);

		return image;
}

bool facebookIsLogin() {
	LOGI("Native facebookIsLogin() <-- in");

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

	jmethodID mid = env->GetStaticMethodID(clazz, "facebookIsLogin", "()Z");
	if (mid == NULL) {
		LOGE("Native registration unable to find GetStaticMethodID '%s'  ",
				"facebookIsLogin");
	}

	bool ret = (bool) env->CallStaticBooleanMethod(clazz, mid);
	env->DeleteLocalRef(clazz);

	LOGI("ret = %d", ret);
	LOGI("Native facebookIsLogin() --> out");

	return ret;
}

bool facebookLogin(PlatformCallback _callback) {

	LOGI("Native facebookLogin() <-- in");
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

	jmethodID mid = env->GetStaticMethodID(clazz, "facebookLogin", "()V");
	if (mid == NULL) {
		LOGE("Native registration unable to find GetStaticMethodID '%s'  ",
				"facebookLogin");
	}

	g_FacebookLoginCB = _callback;

	bool ret = (bool) env->CallStaticBooleanMethod(clazz, mid);
	env->DeleteLocalRef(clazz);

	LOGI("ret = %d", ret);
	LOGI("Native facebookLogin() --> out");

	return ret;
}

bool facebookLogout() {
	LOGI("Native facebookLogout() <-- in");

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

	jmethodID mid = env->GetStaticMethodID(clazz, "facebookLogout", "()Z");
	if (mid == NULL) {
		LOGE("Native registration unable to find GetStaticMethodID '%s'  ",
				"facebookLogout");
	}

	bool ret = (bool) env->CallStaticBooleanMethod(clazz, mid);
	env->DeleteLocalRef(clazz);

	LOGI("ret = %d", ret);
	LOGI("Native facebookLogout() --> out");

	return ret;
}

void facebookRequestGraphPath(PlatformFacebookGraphPath type, PlatformCallback _callback) {

	LOGI("Native facebookRequestGraphPath() <-- in");

	JNIEnv* env = NULL;
	if (jvm == NULL) {
		LOGE("jvm == null : please on load JavaVM");
		return ;
	}

	if (jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
		LOGE("facebookRequestGraphPath -> %s: AttachCurrentThread() failed", __FUNCTION__);
		return ;
	}

	/* invoke the method using the JNI */
	jclass clazz = env->FindClass(ClassName);
	if (clazz == NULL) {
		LOGE("facebookRequestGraphPath -> Native registration unable to find class '%s'", ClassName);
	}

	jmethodID mid = env->GetStaticMethodID(clazz, "facebookRequestGraphPath", "(I)V");
	if (mid == NULL) {
		LOGE("Native registration unable to find GetStaticMethodID '%s'  ",
				"facebookLogin");
	}

	g_FacebookRequestGraphPathCB = _callback;

    env->CallStaticVoidMethod(clazz, mid, type);

    // memory release
    env->DeleteLocalRef(clazz);

    LOGI("Native facebookRequestGraphPath() --> out");
}

void facebookAppRequest(const char* _msg, const char* _to,
		const char* _notification_text, PlatformCallback _callback) {

	LOGI("Native facebookAppRequest() <-- in");

	JNIEnv* env = NULL;
	if (jvm == NULL) {
		LOGE("jvm == null : please on load JavaVM");
		return ;
	}
	if (jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
		LOGE("facebookAppRequest -> %s: AttachCurrentThread() failed", __FUNCTION__);
		return ;
	}

	/* invoke the method using the JNI */
	jclass clazz = env->FindClass(ClassName);
	if (clazz == NULL) {
		LOGE("facebookAppRequest -> Native registration unable to find class '%s'", ClassName);
	}

	jmethodID mid = env->GetStaticMethodID(clazz, "facebookAppRequest", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (mid == NULL) {
		LOGE("Native registration unable to find GetStaticMethodID '%s'  ",
				"facebookAppRequest");
	}

	g_FacebookRequestGraphPathCB = _callback;

	// malloc
		jstring msg = env->NewStringUTF(_msg);
		jstring to = env->NewStringUTF(_to);
		jstring notification_text = env->NewStringUTF(_notification_text);

		// call java method
	    env->CallStaticVoidMethod(clazz, mid, msg, to, notification_text);

	    // memory release
	    env->DeleteLocalRef(clazz);
	    env->DeleteLocalRef(msg);
	    env->DeleteLocalRef(to);
	    env->DeleteLocalRef(notification_text);

	LOGI("Native facebookAppRequest() --> out");
}

void facebookFeed(const char* _name, const char* _caption,
		const char* _description, const char* _link, const char* _picture, PlatformCallback _callback) {

	LOGI("Native facebookRequestGraphPath() <-- in");

	JNIEnv* env = NULL;
	if (jvm == NULL) {
		LOGE("jvm == null : please on load JavaVM");
		return ;
	}
	if (jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
		LOGE("facebookFeed -> %s: AttachCurrentThread() failed", __FUNCTION__);
		return ;
	}

	/* invoke the method using the JNI */
	jclass clazz = env->FindClass(ClassName);
	if (clazz == NULL) {
		LOGE("facebookFeed -> Native registration unable to find class '%s'", ClassName);
	}

	jmethodID mid = env->GetStaticMethodID(clazz, "facebookFeed", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (mid == NULL) {
		LOGE("Native registration unable to find GetStaticMethodID '%s'  ",
				"facebookFeed");
	}

	g_FacebookFeedCB = _callback;

	// malloc
		jstring name = env->NewStringUTF(_name);
		jstring caption = env->NewStringUTF(_caption);
		jstring description = env->NewStringUTF(_description);
		jstring link = env->NewStringUTF(_link);
		jstring picture = env->NewStringUTF(_picture);

		// call java method
	    env->CallStaticVoidMethod(clazz, mid, name, caption, description, link, picture);

	    // memory release
	    env->DeleteLocalRef(clazz);
	    env->DeleteLocalRef(name);
	    env->DeleteLocalRef(caption);
	    env->DeleteLocalRef(description);
	    env->DeleteLocalRef(link);
	    env->DeleteLocalRef(picture);

	LOGI("Native facebookRequestGraphPath() --> out");
}

// ============================================================================================
JNIEXPORT void JNICALL Java_com_vanillabreeze_gelatomania_GelatoManiaActivity_nativeFacebookLogin( JNIEnv* env, jobject thiz, bool isLogin)
{
	LOGV("nativeFacebookLogin isLogin : %d" , isLogin);
	g_FacebookLoginCB.function(NULL, g_FacebookLoginCB.reference);
}



JNIEXPORT void JNICALL Java_com_vanillabreeze_gelatomania_GelatoManiaActivity_nativeFacebookRequestGraphPath( JNIEnv* env, jobject thiz, jstring str)
{
	//Get the native string from javaString
	const char *_str = env->GetStringUTFChars(str, 0);

	//Do something with the nativeString
	LOGV("nativeFacebookRequestGraphPath str : %s" , _str);
	//DON'T FORGET THIS LINE!!!
	cJSON* obj = cJSON_CreateString(_str);
	env->ReleaseStringUTFChars(str, _str);

	//callback function call~!!

	g_FacebookRequestGraphPathCB.function(obj, g_FacebookRequestGraphPathCB.reference);
}

JNIEXPORT void JNICALL Java_com_vanillabreeze_gelatomania_GelatoManiaActivity_nativeFacebookAppRequest( JNIEnv* env, jobject thiz, jstring str)
{
	//Get the native string from javaString
	const char *_str = env->GetStringUTFChars(str, 0);

	//Do something with the nativeString
	LOGV("nativeFacebookAppRequest str : %s" , _str);
	//DON'T FORGET THIS LINE!!!
	env->ReleaseStringUTFChars(str, _str);

	g_FacebookAppRequestCB.function(NULL, g_FacebookAppRequestCB.reference);
}

JNIEXPORT void JNICALL Java_com_vanillabreeze_gelatomania_GelatoManiaActivity_nativeFacebookFeed( JNIEnv* env, jobject thiz, jstring str)
{
	//Get the native string from javaString
	const char *_str = env->GetStringUTFChars(str, 0);

	//Do something with the nativeString
	LOGV("nativeFacebookFeed str : %s" , _str);
	//DON'T FORGET THIS LINE!!!
	env->ReleaseStringUTFChars(str, _str);

	g_FacebookFeedCB.function(NULL, g_FacebookFeedCB.reference);
}

#endif /*__ANDROID__*/
