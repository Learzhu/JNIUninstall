LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := JniLib
LOCAL_SRC_FILES =: JniLib.cpp
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:=UninstallObserver
LOCAL_SRC_FILES:=UninstallObserver.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/include
LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog
include $(BUILD_SHARED_LIBRARY)

#include $(PREBUILT_SHARED_LIBRARY)
LOCAL_CPPFLAGS += -fexceptions
LOCAL_LDLIBS    := -llog

