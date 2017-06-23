LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := javah
LOCAL_SRC_FILES := javah.c

include $(BUILD_SHARED_LIBRARY)