LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS += -llog

LOCAL_MODULE    := alipay
LOCAL_SRC_FILES := alipay.c

include $(BUILD_SHARED_LIBRARY)
