#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.1)

set(APP_NAME CrappyBird)

project(${APP_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

set(USE_CHIPMUNK false)
set(USE_BOX2D true)

include(CocosBuildSet)
if (NOT USE_COCOS_PREBUILT)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif ()

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
        )
if (APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif ()

include_directories(
        src
        ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
        ${COCOS2DX_ROOT_PATH}/external/Box2D/include/
)
# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
        src/AppDelegate.cpp
        src/Utils.cpp
        src/scenes/MainScene.cpp
        src/scenes/CustomPhysicsScene.cpp
        src/scenes/Box2dPhysicsScene.cpp
        src/core/Obstacles.cpp
        src/core/Player.cpp
        src/core/GameSettings.cpp
        src/core/ViewUpdateContract.cpp
        src/core/Ground.cpp
        src/core/Background.cpp
        src/physics/CustomPhysics.cpp
        src/physics/Box2dPhysics.cpp
        src/view/ObstaclesLayer.cpp
        src/view/PlayerLayer.cpp
		src/view/GroundLayer.cpp
		src/view/BackgroundLayer.cpp
        src/view/DebugLayer.cpp
        )
list(APPEND GAME_HEADER
        src/_include/AppDelegate.h
        src/_include/MainScene.h
        src/_include/CustomPhysicsScene.h
        src/_include/Box2dPhysicsScene.h
        src/_include/Obstacles.h
        src/_include/Player.h
        src/_include/Ground.h
        src/_include/Background.h
        src/_include/CustomPhysics.h
        src/_include/Box2dPhysics.h
        src/_include/Utils.h
        src/_include/GameSettings.h
        src/_include/Physics.h
        src/_include/ObstaclesLayer.h
        src/_include/GroundLayer.h
        src/_include/BackgroundLayer.h
        src/_include/PlayerLayer.h
        src/_include/ViewUpdateContract.h
        src/_include/Views.h
        src/_include/DebugLayer.h
        )

if (ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
            proj.android/app/jni/hellocpp/main.cpp
            )
elseif (LINUX)
    list(APPEND GAME_SOURCE
            proj.linux/main.cpp
            )
elseif (WINDOWS)
    list(APPEND GAME_HEADER
            proj.win32/main.h
            proj.win32/resource.h
            )
    list(APPEND GAME_SOURCE
            proj.win32/main.cpp
            proj.win32/game.rc
            ${common_res_files}
            )
elseif (APPLE)
    if (IOS)
        list(APPEND GAME_HEADER
                proj.ios_mac/ios/AppController.h
                proj.ios_mac/ios/RootViewController.h
                )
        set(APP_UI_RES
                proj.ios_mac/ios/LaunchScreen.storyboard
                proj.ios_mac/ios/LaunchScreenBackground.png
                proj.ios_mac/ios/Images.xcassets
                )
        list(APPEND GAME_SOURCE
                proj.ios_mac/ios/main.m
                proj.ios_mac/ios/AppController.mm
                proj.ios_mac/ios/RootViewController.mm
                proj.ios_mac/ios/Prefix.pch
                ${APP_UI_RES}
                )
    elseif (MACOSX)
        set(APP_UI_RES
                proj.ios_mac/mac/Icon.icns
                proj.ios_mac/mac/Info.plist
                )
        list(APPEND GAME_SOURCE
                proj.ios_mac/mac/main.cpp
                proj.ios_mac/mac/Prefix.pch
                ${APP_UI_RES}
                )
    endif ()
    list(APPEND GAME_SOURCE ${common_res_files})
endif ()

# mark app complie info and libs info
set(APP_SRC
        ${GAME_SOURCE}
        ${GAME_HEADER}
        )
cocos_build_app(${APP_NAME}
        APP_SRC "${APP_SRC}"
        DEPEND_COMMON_LIBS "cocos2d"
        DEPEND_ANDROID_LIBS "cocos2d_android"
        )

if (APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if (MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                )
    elseif (IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
    endif ()
elseif (WINDOWS)
    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_BIN_DIR})
endif ()

if (LINUX OR WINDOWS)
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif ()
