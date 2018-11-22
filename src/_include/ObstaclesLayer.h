#pragma once

#include "cocos2d.h"
#include "Obstacles.h"
#include "Physics.h"
#include "ViewUpdateContract.h"

class ObstaclesLayer : public cocos2d::Layer,
                       public View<const std::list<std::shared_ptr<Obstacle>>, ObstaclesPresenter> {
public:
	CREATE_FUNC(ObstaclesLayer);

	bool init() override;

	void update(float delta) override;

	std::function<void(const std::list<std::shared_ptr<Obstacle>>)> getUpdateReceiver() override;

private:
	std::map<int, cocos2d::Sprite *> obstacleSprites;
	//    std::function<void(float delta)> requestUpdate;

	cocos2d::Sprite* createObstacleSprite(const cocos2d::Rect& rect);
};

cocos2d::Layer* getObstaclesLayer(std::shared_ptr<PhysicsEngine> physics);
