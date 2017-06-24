
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog


LOCAL_MODULE    := NDK_04
LOCAL_SRC_FILES := CToJava.c

include $(BUILD_SHARED_LIBRARY)

