#pragma once

#include <iterator>
#include "cocos2d.h"
#include "GameSettings.h"
#include "Box2D/Box2D.h"
#include "Physics.h"
#include "Utils.h"

class Box2dEngine;

class Box2dObject;

class Box2dContactListener;

class Box2dEngine : public PhysicsEngine {
public:
    Box2dEngine(b2Draw *debugDraw = nullptr);

    virtual ~Box2dEngine() = default;

    void addDynamicObject(const std::string &layer, std::shared_ptr<PhysicalObject> object) override;

    void addStaticObject(const std::string &layer, std::shared_ptr<PhysicalObject> object) override;

    void removeStaticObject(const std::string &layer, int id) override;

    void setDynamicObjectAccelerationY(const std::string &layer, int id, float acceleration) override;

    std::list<std::shared_ptr<PhysicalObject>> getStaticLayer(const std::string &layer) override;

    std::list<std::shared_ptr<PhysicalObject>> getDynamicLayer(const std::string &layer) override;

    void setCollisionListener(const std::function<void(std::shared_ptr<Collision>)> &listener) override {
        notifyCollision = listener;
    };

    void setStaticLayerVelocity(const std::string &layer, float speed) override;

    void update(float delta) override;

private:
    std::shared_ptr<const GameSettings> settings;

    static const int velocityIterations = 8;
    static const int positionIterations = 3;
    std::shared_ptr<b2World> world;
    std::shared_ptr<Box2dContactListener> contactListener;
    std::function<void(std::shared_ptr<Collision>)> notifyCollision = [](const std::shared_ptr<Collision> &) {};

    std::multimap<std::string, std::shared_ptr<Box2dObject>> dynamicObjects{};
    std::multimap<std::string, std::shared_ptr<Box2dObject>> staticObjects{};
    std::map<std::string, float> layerVelocities = std::map<std::string, float>();

    std::shared_ptr<Box2dObject>
    createBox2dObject(const std::string &layer, std::shared_ptr<PhysicalObject> o, bool movable);
};


// Box2dContactListener

class Box2dContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact *contact) override { this->contact = contact; };

    b2Contact *getContact() const { return contact; }

    void clear() { contact = nullptr; };

private:
    b2Contact *contact = nullptr;
};


// Data classes

class Box2dObject : public PhysicalObject {
public:
    Box2dObject(int id, cocos2d::Rect &rect, ShapeType shapeType, b2Body *body) :
            id(id), body(body), rect(rect), shapeType(shapeType) {};

    int getId() const override { return id; };

    const cocos2d::Rect getPhysicalRect() const override { return rect; };

    const ShapeType getShapeType() const override { return shapeType; };

    b2Body *getBody() const { return body; }

    void setRect(cocos2d::Rect &rect) {
        this->rect.setRect(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    }

private:
    b2Body *body;
    int id;
    cocos2d::Rect rect;
    ShapeType shapeType;
};


// Helper functions

static void updatePositions(std::multimap<std::string, std::shared_ptr<Box2dObject>> map);

// Objects have anchor point at the center in Box2D
static cocos2d::Vec2 getCenterAnchorPoint(const std::shared_ptr<PhysicalObject> &o) {
    const auto &rect = o->getPhysicalRect();
    return cocos2d::Vec2(rect.origin.x + rect.size.width / 2.f, rect.origin.y + rect.size.height / 2.f);
}

// Cocos2d have anchor point at the bottom-left corner by default
static cocos2d::Vec2 getBottomLeftAnchorPoint(const std::shared_ptr<Box2dObject> &o) {
    auto position = o->getBody()->GetPosition();
    const auto &rect = o->getPhysicalRect();
    return cocos2d::Vec2(position.x - rect.size.width / 2.f, position.y - rect.size.height / 2.f);
}

static std::pair<std::string, int> *getUserData(b2Body *body) {
    return (std::pair<std::string, int> *) body->GetUserData();
}

static void setUserData(b2Body *body, const std::string &layer, int id) {
    auto userData = new std::pair<std::string, int>(layer, id);
    body->SetUserData((void *) userData);
}

