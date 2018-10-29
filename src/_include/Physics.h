#pragma once

#include "cocos2d.h"

class PhysicsEngine;

class PhysicalObject;

class Collision;

enum ShapeType {
    RECTANGLE,
    CIRCLE
};

class PhysicsEngine {
public:
    virtual void addDynamicObject(const std::string &layer, std::shared_ptr<PhysicalObject> object) = 0;

    virtual void addStaticObject(const std::string &layer, std::shared_ptr<PhysicalObject> object) = 0;

    virtual void removeStaticObject(const std::string &layer, int id) = 0;

    virtual void setDynamicObjectAccelerationY(const std::string &layer, int id, float acceleration) = 0;

    virtual void setStaticLayerVelocity(const std::string &layer, float speed) = 0;

    virtual void setCollisionListener(const std::function<void(std::shared_ptr<Collision>)> &listener) = 0;

    virtual std::list<std::shared_ptr<PhysicalObject>> getStaticLayer(const std::string &layer) = 0;

    virtual std::list<std::shared_ptr<PhysicalObject>> getDynamicLayer(const std::string &layer) = 0;

    virtual void update(float delta) = 0;
};

class PhysicalObject {
public:
    virtual int getId() const = 0;

    virtual cocos2d::Rect const getPhysicalRect() const = 0;

    virtual ShapeType const getShapeType() const = 0;
};

class Collision {
public:
    explicit Collision(std::string layerA, std::string layerB)
            : layerA(std::move(layerA)), layerB(std::move(layerB)) {};

    const std::string getLayerA() const { return layerA; };

    const std::string getLayerB() const { return layerB; };

private:
    const std::string layerA;
    const std::string layerB;
};

// Helper functions


