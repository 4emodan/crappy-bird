#pragma once

#include "cocos2d.h"
#include "_include/GameSettings.h"
#include "_include/MainScene.h"

class AppDelegate : private cocos2d::Application {
public:
    AppDelegate();

    virtual ~AppDelegate();

    virtual bool applicationDidFinishLaunching();

    virtual void applicationDidEnterBackground();

    virtual void applicationWillEnterForeground();

private:
    std::shared_ptr<const GameSettings> gameSettings;

};