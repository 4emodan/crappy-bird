#pragma once

#include "cocos2d.h"
#include "Box2dPhysics.h"
#include "ObstaclesLayer.h"
#include "PlayerLayer.h"
#include "DebugLayer.h"

class Box2dPhysicsScene : public cocos2d::Scene {
public:

    bool init() override;

    CREATE_FUNC(Box2dPhysicsScene)

    void update(float delta) override;

private:
    std::shared_ptr<Box2dEngine> physics;
};