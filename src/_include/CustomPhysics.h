#pragma once

#include "cocos2d.h"
#include "Physics.h"
#include "GameSettings.h"
#include "Utils.h"

class CustomEngine;

class CustomObject;

class CustomEngine : public PhysicsEngine {
public:
    void addDynamicObject(const std::string &layer, std::shared_ptr<PhysicalObject> object) override;

    void addStaticObject(const std::string &layer, std::shared_ptr<PhysicalObject> object) override;

    void removeStaticObject(const std::string &layer, int id) override;

    void setCollisionListener(const std::function<void(std::shared_ptr<Collision>)> &listener) override {
        notifyCollision = listener;
    };

    void setDynamicObjectAccelerationY(const std::string &layer, int id, float accelerationY) override;

    void setStaticLayerVelocity(const std::string &layer, float speed) override;

    std::list<std::shared_ptr<PhysicalObject>> getDynamicLayer(const std::string &layer) override;

    void update(float delta) override;

    std::list<std::shared_ptr<PhysicalObject>> getStaticLayer(const std::string &layer) override;

private:
    float gravity = GameSettings::instance()->gravity;

    std::multimap<std::string, std::shared_ptr<CustomObject>> dynamicObjects{};
    std::multimap<std::string, std::shared_ptr<CustomObject>> staticObjects{};
    std::map<std::string, float> layerVelocities = std::map<std::string, float>();

    std::function<void(std::shared_ptr<Collision>)> notifyCollision = [](const std::shared_ptr<Collision> &) {};

    std::shared_ptr<Collision> findCollision(const std::pair<std::string, std::shared_ptr<CustomObject>> &objectPair,
                            const std::multimap<std::string, std::shared_ptr<CustomObject>> &collection);
};


// Data classes

class CustomObject : public PhysicalObject {
public:
    CustomObject(int id, const cocos2d::Rect &rect, ShapeType shapeType) : id(id), rect(rect), shapeType(shapeType) {};

    int getId() const override { return id; };

    cocos2d::Rect const getPhysicalRect() const override { return rect; };

    const ShapeType getShapeType() const override { return shapeType; };

    void setRect(const cocos2d::Rect &rect) { this->rect = rect; };

    float getSpeedY() const { return speedY; }

    void setSpeedY(float value) { this->speedY = value; }

    float getAccelerationY() const { return accelerationY; };

    void setAccelerationY(float accelerationY) { this->accelerationY = accelerationY; };

private:
    int id;
    cocos2d::Rect rect;
    ShapeType shapeType;
    float speedY = 0;
    float accelerationY = 0;
};


// Helper functions

static inline CustomObject create(const std::shared_ptr<PhysicalObject> &p) {
    return CustomObject(p->getId(), p->getPhysicalRect(), p->getShapeType());
}

static void insertCustomObject(std::multimap<std::string, std::shared_ptr<CustomObject>> &map,
                               const std::string &layer,
                               const std::shared_ptr<PhysicalObject> &object) {
    map.insert({layer, std::make_shared<CustomObject>(create(object))});
}

static cocos2d::Rect getIntersection(const cocos2d::Rect &r1, const cocos2d::Rect &r2) {
    auto x0 = std::max(r1.getMinX(), r2.getMinX());
    auto x1 = std::min(r1.getMaxX(), r2.getMaxX());
    auto y0 = std::max(r1.getMinY(), r2.getMinY());
    auto y1 = std::min(r1.getMaxY(), r2.getMaxY());
    return cocos2d::Rect(x0, y0, x1 - x0, y1 - y0);
}

static bool collide(const std::pair<std::string, std::shared_ptr<CustomObject>> &aPair,
                    const std::pair<std::string, std::shared_ptr<CustomObject>> &bPair);