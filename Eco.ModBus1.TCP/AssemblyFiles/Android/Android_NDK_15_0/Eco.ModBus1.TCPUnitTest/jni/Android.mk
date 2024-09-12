﻿LOCAL_PATH:= $(call my-dir)


########################
# prepare Eco.System1
include $(CLEAR_VARS)
LOCAL_MODULE    := lib00000000000000000000000000000100
LOCAL_SRC_FILES := $(ECO_FRAMEWORK)/Eco.System1/BuildFiles/Android/$(TARGET_ARCH_ABI)/StaticRelease/lib00000000000000000000000000000100.a 
include $(PREBUILT_STATIC_LIBRARY)
########################

########################
# prepare Eco.InterfaceBus1
include $(CLEAR_VARS)
LOCAL_MODULE    := lib00000000000000000000000042757331
LOCAL_SRC_FILES := $(ECO_FRAMEWORK)/Eco.InterfaceBus1/BuildFiles/Android/$(TARGET_ARCH_ABI)/StaticRelease/lib00000000000000000000000042757331.a 
include $(PREBUILT_STATIC_LIBRARY)
########################

########################
# prepare Eco.MemoryManager1
include $(CLEAR_VARS)
LOCAL_MODULE    := lib0000000000000000000000004D656D31
LOCAL_SRC_FILES := $(ECO_FRAMEWORK)/Eco.MemoryManager1/BuildFiles/Android/$(TARGET_ARCH_ABI)/StaticRelease/lib0000000000000000000000004D656D31.a 
include $(PREBUILT_STATIC_LIBRARY)
########################

########################
# prepare Eco.FileSystemManagement1
include $(CLEAR_VARS)
LOCAL_MODULE    := lib00000000000000000000000046534D31
LOCAL_SRC_FILES := $(ECO_FRAMEWORK)/Eco.FileSystemManagement1/BuildFiles/Android/$(TARGET_ARCH_ABI)/StaticRelease/lib00000000000000000000000046534D31.a 
include $(PREBUILT_STATIC_LIBRARY)
########################


########################
# prepare Eco.ModBus1.TCP
include $(CLEAR_VARS)
LOCAL_MODULE    := lib7A956018B6B34FAE806E5A5EE7CA43E2
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../../../../BuildFiles/Android/$(TARGET_ARCH_ABI)/StaticRelease/lib7A956018B6B34FAE806E5A5EE7CA43E2.a 
include $(PREBUILT_STATIC_LIBRARY)
########################

#
# EcoModBus1TCPUnitTest
#
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles
LOCAL_C_INCLUDES += $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles
LOCAL_C_INCLUDES += $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles
LOCAL_C_INCLUDES += $(ECO_FRAMEWORK)/Eco.FileSystemManagement1/SharedFiles
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../HeaderFiles
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../HeaderFiles/Android
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../SharedFiles
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../UnitTestFiles/HeaderFiles
TARGET_PLATFORM := android-15
TARGET_OUT := $(LOCAL_PATH)/../build/libs/$(TARGET_ARCH_ABI)/$(CONFIGURATION)
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../../../../UnitTestFiles/SourceFiles/EcoModBus1TCP.c

ifeq ($(TARGET_LINK),0)

LOCAL_MODULE := EcoModBus1TCPUnitTest
LOCAL_CFLAGS := -std=c99 -DECO_LIB -DECO_ANDROID -DUGUID_UTILITY -D__ANDROID__ -DDISABLE_IMPORTGL
LOCAL_LDLIBS := -lc -lm -llog -landroid -latomic -lEGL -lGLESv1_CM
LOCAL_LDFLAGS += -u ANativeActivity_onCreate
LOCAL_STATIC_LIBRARIES := 00000000000000000000000000000100 00000000000000000000000042757331 0000000000000000000000004D656D31 00000000000000000000000046534D31 7A956018B6B34FAE806E5A5EE7CA43E2
include $(BUILD_SHARED_LIBRARY)

else

LOCAL_MODULE := EcoModBus1TCPUnitTest
LOCAL_CFLAGS := -std=c99 -DECO_DLL -DECO_ANDROID -DUGUID_UTILITY -D__ANDROID__

include $(BUILD_SHARED_LIBRARY)

endif