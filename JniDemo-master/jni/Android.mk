LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := zzyJni

LOCAL_SRC_FILES  := jni_interface.c

LOCAL_LDLIBS :=-llog

LOCAL_LDLIBS    += -lGLESv2 -llog -ldl

include $(BUILD_SHARED_LIBRARY)

