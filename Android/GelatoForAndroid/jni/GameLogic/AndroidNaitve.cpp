#include "AndroidNaitve.h"

// ========================= JNI Function =================================

// 프로세스 실행 후 한번만 실행
void nativeInit(JNIEnv* env,jobject thiz)
{
	// LOGV("nativeInit");
	java_dismissDialog();  // dismiss dialog in java area
}

// 화면 크기 변환시 (ex:가로,세로 전환)
void nativeResize(JNIEnv* env,jobject thiz, jint w, jint h)
{
	// LOGV("nativeResize X:%d Y:%d", w, h);
}

// 화면 렌더링 (자동 반복호출 - 스레드)
void nativeRender(JNIEnv* env,jobject thiz)
{
	// LOGV("nativeRender");
}

// 화면에 출력 시작 및 재시작
void nativeResume(JNIEnv* env,jobject thiz)
{
	// LOGV("nativeResume");
}

// 화면 정지 및 백그라운 일때
void nativePause(JNIEnv* env,jobject thiz)
{
	// LOGV("nativePause");
}

// 프로세스 종료
void nativeDestroy(JNIEnv* env,jobject thiz)
{
	// LOGV("nativeDestroy");
}
