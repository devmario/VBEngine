#include "AndroidNaitve.h"

#include "Root.h"
#include "cocos2d.h"
#include "AppDelegate.h"
using namespace cocos2d;

// ========================= JNI Function =================================

// 프로세스 실행 후 한번만 실행
void nativeInit(JNIEnv* env,jobject thiz)
{
	// LOGV("nativeInit");
	java_dismissDialog();  // dismiss dialog in java area

	int w = 480;
	int h = 320;

    if (!cocos2d::CCDirector::sharedDirector()->getOpenGLView())
    {
	cocos2d::CCEGLView *view = &cocos2d::CCEGLView::sharedOpenGLView();
        view->setFrameWidthAndHeight(w, h);
        // if you want to run in WVGA with HVGA resource, set it
        // view->create(480, 320);
        cocos2d::CCDirector::sharedDirector()->setOpenGLView(view);

        AppDelegate *pAppDelegate = new AppDelegate();
        cocos2d::CCApplication::sharedApplication().run();
    }
    else
    {
        cocos2d::CCTextureCache::reloadAllTextures();
        cocos2d::CCDirector::sharedDirector()->setGLDefaultValues();
    }

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
