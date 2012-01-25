LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := gamelogic

LOCAL_SRC_FILES := main.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../Cocos2dx \
                    $(LOCAL_PATH)/../Cocos2dx/platform \
                    $(LOCAL_PATH)/../Cocos2dx/include \
                    $(LOCAL_PATH)/../CocosDenshion \
                    $(LOCAL_PATH)/../CocosDenshion/include \
                    $(LOCAL_PATH)/../VBEngine

LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libs/$(TARGET_ARCH_ABI)) \
                -lcocos2d -lcocosdenshion -lvanillaworld -llog 
            
include $(BUILD_SHARED_LIBRARY)