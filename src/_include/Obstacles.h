#pragma once

#include "cocos2d.h"
#include "Physics.h"
#include "GameSettings.h"
#include "Utils.h"
#include "ViewUpdateContract.h"
#include "Views.h"


class Obstacle;

class ObstaclesPresenter;

class ObstaclesLayer;


class ObstaclesPresenter : public Presenter<const std::list<std::shared_ptr<Obstacle>>> {
public:
	explicit ObstaclesPresenter(std::shared_ptr<PhysicsEngine> physics);

	virtual ~ObstaclesPresenter();

	std::function<void(float)> getUpdateSource() override;

private:
	std::shared_ptr<PhysicsEngine> physics;
	std::shared_ptr<const GameSettings> settings;
	cocos2d::Director* director = cocos2d::Director::getInstance();

	std::list<std::shared_ptr<Obstacle>> obstacles{};
	float timeSinceLastObstacle = 0;
	int incrementalId = 0;
};


// Data classes

class Obstacle : public PhysicalObject, public ViewObject {
	int id;
	cocos2d::Rect viewRect;

public:
	Obstacle(int id, const cocos2d::Rect& rect) : id(id), viewRect(rect) {};

	int getId() const override { return id; };

	cocos2d::Rect const getPhysicalRect() const override;
	cocos2d::Rect const getViewRect() const override { return viewRect; };
	const ShapeType getShapeType() const override { return ShapeType::RECTANGLE; };

	void setViewRect(const cocos2d::Rect& rect);
	void setPhysicalRect(const cocos2d::Rect& rect);
};
