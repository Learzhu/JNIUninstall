LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := JniLib
LOCAL_SRC_FILES =: JniLib.cpp
include $(BUILD_SHARED_LIBRARY)
#include $(PREBUILT_SHARED_LIBRARY)
LOCAL_CPPFLAGS += -fexceptions
LOCAL_LDLIBS    := -llog