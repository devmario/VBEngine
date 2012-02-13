LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := gamelogic

LOCAL_SRC_FILES := \
	AppDelegate.cpp\
	VBModel.cpp\
	ShareData.cpp\
	MainMenu.cpp\
	Root.cpp\
	View.cpp\
	PackSelect.cpp\
	SubMenu.cpp\
	cJSON.c\
	CppTweener.cpp\
	StageSelect.cpp\
	Pages.cpp\
	NumberText.cpp\
	PackThumb.cpp\
	StageThumb.cpp\
	Shop.cpp\
	ShopThumb.cpp\
	Popup.cpp\
	GameMain.cpp\
	PopupClear.cpp\
	Scroller.cpp\
	ScrollerContainer.cpp\
	IceCream.cpp\
	RecipeContainer.cpp\
	ShopScrollContainer.cpp\
	ToppingContainer.cpp\
	Slider.cpp\
	HintViewer.cpp\
	RecipeAndToppingData.cpp\
	Tweener.cpp\
	IceCreamClearChecker.cpp\
	IceCreamTopping.cpp\
	IceCreamRecipe.cpp\
	VBHTTP.c\
	Android_PlatformFunctions.c\
	Social.cpp\
	User.cpp\
	PlatformFunctions.c\
	SocialGameCenterCallback.cpp\
	SocialFacebookCallback.cpp\
	SelectUser.cpp\
	SelectUserTable.cpp\
	NewAndSelectUser.cpp\
	PlatformFriendList.cpp\
	ManiaFriendList.cpp\
	GameMainRdTd.cpp\
	AndroidNative.cpp\
	FrameTweenController.cpp\
	Text.cpp\
	Language.cpp\
	main.cpp\


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../Cocos2dx \
		$(LOCAL_PATH)/../Cocos2dx/platform \
		$(LOCAL_PATH)/../Cocos2dx/include \
		$(LOCAL_PATH)/../CocosDenshion \
		$(LOCAL_PATH)/../CocosDenshion/include \
		$(LOCAL_PATH)/../VBEngine \
		$(LOCAL_PATH)/../VBEngine/Core/Color \
		$(LOCAL_PATH)/../VBEngine/Core/Linear \
		$(LOCAL_PATH)/../VBEngine/Display \
		$(LOCAL_PATH)/../VBEngine/IO \
		$(LOCAL_PATH)/../VBEngine/Other/png \
		$(LOCAL_PATH)/../VBEngine/Other/zlib \
		$(LOCAL_PATH)/../VBEngine/Util

LOCAL_CFLAGS := -DANDROID_NDK

LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libs/$(TARGET_ARCH_ABI)) \
		-lcocos2d -lcocosdenshion -lvanillaworld -llog -lGLESv1_CM -ljnigraphics

include $(BUILD_SHARED_LIBRARY)