#pragma once

#include "cocos2d.h"
#include "ViewUpdateContract.h"
#include "Physics.h"
#include "GameSettings.h"
#include "Views.h"
#include "Utils.h"

class Ground;
class GroundChunk;

class GroundPresenter : public Presenter<const std::list<std::shared_ptr<GroundChunk>>> {
public:
	explicit GroundPresenter(std::shared_ptr<PhysicsEngine> physics);
	virtual ~GroundPresenter() = default;

	std::function<void(float)> getUpdateSource() override;

private:
	int incrementalId = 0;

	std::shared_ptr<PhysicsEngine> physics;
	std::shared_ptr<const GameSettings> settings;
	std::list<std::shared_ptr<GroundChunk>> groundChunks{};
	std::shared_ptr<Ground> ground;

	std::shared_ptr<Ground> createGround() const;
};

class Ground : public PhysicalObject {
	int id;
	cocos2d::Rect rect;

public:
	Ground(int id, const cocos2d::Rect& rect): id(id), rect(rect) {};

	int getId() const override { return id; };
	cocos2d::Rect const getPhysicalRect() const override { return rect; };
	ShapeType const getShapeType() const override { return ShapeType::RECTANGLE; };
};

class GroundChunk : public ViewObject {
	int id;
	cocos2d::Rect rect;
public:
	GroundChunk(int id, const cocos2d::Rect& rect): id(id), rect(rect) {}

	int getId() const override { return id; }
	cocos2d::Rect const getViewRect() const override { return rect; }

	void setViewRect(const cocos2d::Rect &rect);
};
