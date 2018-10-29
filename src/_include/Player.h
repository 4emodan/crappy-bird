#pragma once

#include "cocos2d.h"
#include "Physics.h"
#include "GameSettings.h"
#include "Views.h"
#include "Utils.h"
#include "ViewUpdateContract.h"

class Player;

class PlayerPresenter;

class PlayerPresenter : public Presenter<const std::shared_ptr<Player>> {
public:
    explicit PlayerPresenter(std::shared_ptr<PhysicsEngine> physics);

    virtual ~PlayerPresenter() = default;

    std::function<void(float)> getUpdateSource() override;

    void onTouchStart();

    void onTouchEnd();

private:
    std::shared_ptr<PhysicsEngine> physics;
    std::shared_ptr<const GameSettings> settings;
    std::shared_ptr<Player> player;
};


// Data classes

class Player : public PhysicalObject, public ViewObject {
public:
    explicit Player(const cocos2d::Rect &rect) : viewRect(rect) {};

    int getId() const override { return 0; };

    const cocos2d::Rect getViewRect() const override { return viewRect; };

    const cocos2d::Rect getPhysicalRect() const override;

    const ShapeType getShapeType() const override { return ShapeType::CIRCLE; };

    void setPhysicalRect(const cocos2d::Rect &rect);

private:
    cocos2d::Rect viewRect;
};