LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../src/AppDelegate.cpp\
                   $(LOCAL_PATH)/../../../src/Utils.cpp\
                   $(LOCAL_PATH)/../../../src/scenes/MainScene.cpp\
                   $(LOCAL_PATH)/../../../src/scenes/CustomPhysicsScene.cpp\
                   $(LOCAL_PATH)/../../../src/scenes/Box2dPhysicsScene.cpp\
                   $(LOCAL_PATH)/../../../src/core/Obstacles.cpp\
                   $(LOCAL_PATH)/../../../src/core/Player.cpp\
                   $(LOCAL_PATH)/../../../src/core/GameSettings.cpp\
                   $(LOCAL_PATH)/../../../src/core/ViewUpdateContract.cpp\
                   $(LOCAL_PATH)/../../../src/physics/CustomPhysics.cpp\
                   $(LOCAL_PATH)/../../../src/physics/Box2dPhysics.cpp\
                   $(LOCAL_PATH)/../../../src/view/ObstaclesLayer.cpp\
                   $(LOCAL_PATH)/../../../src/view/PlayerLayer.cpp\
                   $(LOCAL_PATH)/../../../src/view/DebugLayer.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../src

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
