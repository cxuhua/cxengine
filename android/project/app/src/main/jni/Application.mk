
#set ndk path and src root path

NDK_PATH := /Users/xuhua/android/android-ndk
CX_ENGINE_PATH := /Users/xuhua/Documents/cxengine

NDK_TOOLCHAIN_VERSION := clang3.6

APP_STL := gnustl_static

APP_PLATFORM := android-9

APP_ABI := armeabi

NDK_MODULE_PATH += $(CX_ENGINE_PATH)