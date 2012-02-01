LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := gamelogic

LOCAL_SRC_FILES := \
Android_PlatformFunctions.c\
AppDelegate.cpp\
cJSON.c\
CppTweener.cpp\
GameMain.cpp\
HintViewer.cpp\
IceCream.cpp\
IceCreamClearChecker.cpp\
IceCreamRecipe.cpp\
IceCreamTopping.cpp\
MainMenu.cpp\
NumberText.cpp\
PackSelect.cpp\
PackThumb.cpp\
Pages.cpp\
Popup.cpp\
PopupClear.cpp\
RecipeAndToppingData.cpp\
RecipeContainer.cpp\
Root.cpp\
Scroller.cpp\
ScrollerContainer.cpp\
ShareData.cpp\
Shop.cpp\
ShopScrollContainer.cpp\
ShopThumb.cpp\
Social.cpp\
Slider.cpp\
StageSelect.cpp\
StageThumb.cpp\
SubMenu.cpp\
ToppingContainer.cpp\
Tweener.cpp\
vbHTTP.c\
VBModel.cpp\
View.cpp\
main.cpp


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
                -lcocos2d -lcocosdenshion -lvanillaworld -llog 
            
include $(BUILD_SHARED_LIBRARY)
