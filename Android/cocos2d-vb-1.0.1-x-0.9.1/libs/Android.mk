
LOCAL_PATH := $(call my-dir)
# include $(call all-subdir-makefiles)

subdirs := $(LOCAL_PATH)/VBEngine/Android.mk \
           $(LOCAL_PATH)/GameLogic/Android.mk
           
include $(subdirs)