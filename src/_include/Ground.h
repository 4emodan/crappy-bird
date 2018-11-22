#pragma once

#include "cocos2d.h"
#include "ViewUpdateContract.h"
#include "Physics.h"
#include "GameSettings.h"

class GroundPresenter : public Presenter<float> {
public:
	explicit GroundPresenter(std::shared_ptr<PhysicsEngine> physics);
	virtual ~GroundPresenter() = default;

	std::function<void(float)> getUpdateSource() override;

private:
	std::shared_ptr<PhysicsEngine> physics;
	std::shared_ptr<const GameSettings> settings;

	void addGround() const;
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
