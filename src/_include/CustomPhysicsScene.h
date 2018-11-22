#pragma once

#include "cocos2d.h"
#include "_include/CustomPhysics.h"
#include "_include/ObstaclesLayer.h"
#include "_include/PlayerLayer.h"
#include "_include/GroundLayer.h"
#include "Utils.h"

#ifndef AL_DEBUG
#define AL_DEBUG true
#endif

class CustomPhysicsScene : public cocos2d::Scene {
public:
    CREATE_FUNC(CustomPhysicsScene);

    bool init() override;

    void update(float delta) override;

private:
    cocos2d::Layer *debugLayer;
    std::shared_ptr<CustomEngine> physics;
};