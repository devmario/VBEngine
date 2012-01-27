LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := gamelogic

LOCAL_SRC_FILES := \
AppDelegate.cpp\
cJSON.c\
CppTweener.cpp\
HintViewer.cpp\
IceCream.cpp\
MainMenu.cpp\
NumberText.cpp\
PackSelect.cpp\
PackThumb.cpp\
Pages.cpp\
Popup.cpp\
PopupClear.cpp\
RecipeAndToppingData.cpp\
RecipeContainer.cpp\
Scroller.cpp\
ScrollerContainer.cpp\
ShareData.cpp\
Shop.cpp\
ShopScrollContainer.cpp\
ShopThumb.cpp\
Slider.cpp\
StageSelect.cpp\
StageThumb.cpp\
SubMenu.cpp\
ToppingContainer.cpp\
Tweener.cpp\
VBModel.cpp\
View.cpp\
Root.cpp\
GameMain.cpp\
AndroidNaitve.cpp


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

LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libs/$(TARGET_ARCH_ABI)) \
                -lcocos2d -lcocosdenshion -lvanillaworld -llog 
            
include $(BUILD_SHARED_LIBRARY)