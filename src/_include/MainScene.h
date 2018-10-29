#pragma once

#include "cocos2d.h"
#include "CustomPhysicsScene.h"
#include "Box2dPhysicsScene.h"
#include "Utils.h"

class MainScene : public cocos2d::Layer {
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    CREATE_FUNC(MainScene);

private:
    cocos2d::Director *director;
};