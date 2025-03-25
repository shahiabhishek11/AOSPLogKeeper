LOCAL_PATH := $(call my-dir)

#Module for system log service shared library
include $(CLEAR_VARS)
LOCAL_MODULE := aosp_logs_keeper_lib

LOCAL_SRC_FILES := src/Diagnostics.cpp

		
LOCAL_SHARED_LIBRARIES := \
	libbinder \
	libhidlbase \
	libhidltransport \
	libhwbinder \
	liblog \
	libutils \
	libcutils \
	libc++
	
LOCAL_EXPORT_C_INCLUDE_DIRS := $(LOCAL_PATH)
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
LOCAL_CFLAGS := -Wno-unused-parameter -Wno-unused-variable

include $(BUILD_SHARED_LIBRARY)

#Module for service binary

include $(CLEAR_VARS)
LOCAL_MODULE := aosp_logs_keeper_service
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := src/main.cpp
	
LOCAL_SHARED_LIBRARIES := \
	libbinder \
	libhidlbase \
	libhidltransport \
	libhwbinder \
	liblog \
	libutils \
	libcutils \
	aosp_logs_keeper_lib

LOCAL_PROPRIETARY_MODULE := true
LOCAL_CFLAGS := -Wall -Werror
LOCAL_CFLAGS := -Wno-unused-parameter -Wno-unused-variable
include $(BUILD_EXCUTABLE)



