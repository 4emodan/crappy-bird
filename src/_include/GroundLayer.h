#pragma once

#include "cocos2d.h"
#include "Ground.h"
#include "ViewUpdateContract.h"
#include "Physics.h"

class GroundLayer : public cocos2d::Layer,
                    public View<const std::list<std::shared_ptr<GroundChunk>>, GroundPresenter> {
public:
	CREATE_FUNC(GroundLayer);

	bool init() override;
	void update(float delta) override;
	std::function<void(const std::list<std::shared_ptr<GroundChunk>>)> getUpdateReceiver() override;

private:
	std::map<int, cocos2d::Sprite*> sprites{};

	cocos2d::Sprite* createGroundChunkSprite(const cocos2d::Rect& rect);
};

cocos2d::Layer* getGroundLayer(std::shared_ptr<PhysicsEngine> physics);
