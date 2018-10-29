#pragma once

#include "cocos2d.h"
#include "Physics.h"
#include "Player.h"
#include "ViewUpdateContract.h"

class PlayerLayer : public cocos2d::Layer, public View<const std::shared_ptr<Player>, PlayerPresenter> {
public:
    CREATE_FUNC(PlayerLayer);

    std::function<void(const std::shared_ptr<Player>)> getUpdateReceiver() override;

    bool init() override;

    void update(float delta) override;

private:
    cocos2d::Sprite *playerSprite;
};

cocos2d::Layer *getPlayerLayer(std::shared_ptr<PhysicsEngine> physics);