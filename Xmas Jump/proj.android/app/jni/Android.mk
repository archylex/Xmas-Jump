LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/BackgroundLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/HeadLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/IceBlock.cpp \
                   $(LOCAL_PATH)/../../../Classes/Isometry.cpp \
                   $(LOCAL_PATH)/../../../Classes/MenuLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/Player.cpp \
                   $(LOCAL_PATH)/../../../Classes/Toy.cpp \
                   $(LOCAL_PATH)/../../../Classes/TitleScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/PublicVariables.cpp \
                   $(LOCAL_PATH)/../../../Classes/LoadingScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/AddMob.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameOverLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/LineLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/CharacterLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/ClipObject.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

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
