#pragma once

#include "cocos2d.h"
#include "Ground.h"
#include "ViewUpdateContract.h"
#include "Physics.h"

class GroundLayer : public cocos2d::Layer, public View<float, GroundPresenter>
{
public:
	CREATE_FUNC(GroundLayer);

	bool init() override;
	void update(float delta) override;
	std::function<void(float)> getUpdateReceiver() override;
};

cocos2d::Layer* getGroundLayer(std::shared_ptr<PhysicsEngine> physics);
