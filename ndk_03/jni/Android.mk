LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := MyNdk
LOCAL_SRC_FILES := AddAndSub.c Encrypt.c

include $(BUILD_SHARED_LIBRARY)