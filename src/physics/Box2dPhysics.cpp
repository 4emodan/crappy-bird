#include "_include/Box2dPhysics.h"

USING_NS_CC;

Box2dEngine::Box2dEngine(b2Draw *debugDraw) {
    settings = GameSettings::instance();
    world = std::make_shared<b2World>(*(new b2World(b2Vec2(0, settings->gravity))));
    world->SetAutoClearForces(false);

    contactListener = std::make_shared<Box2dContactListener>(Box2dContactListener());
    world->SetContactListener(contactListener.get());

    if (debugDraw) {
        debugDraw->SetFlags(b2Draw::e_shapeBit);
        world->SetDebugDraw(debugDraw);
    }
}

void Box2dEngine::update(float delta) {
    // Make simulation
    world->Step(delta, velocityIterations, positionIterations);

    // Update object positions
    updatePositions(staticObjects);
    updatePositions(dynamicObjects);

    world->DrawDebugData();

    // Check for collisions
    if (auto contact = contactListener->getContact()) {
        do {
            auto userDataA = getUserData(contact->GetFixtureA()->GetBody());
            auto userDataB = getUserData(contact->GetFixtureB()->GetBody());

            notifyCollision(std::make_shared<Collision>(Collision(userDataA->first, userDataB->first)));
            contact = contact->GetNext();
        } while (contact != nullptr);

        contactListener->clear();
    }
}

void Box2dEngine::addDynamicObject(const std::string &layer, std::shared_ptr<PhysicalObject> object) {
    dynamicObjects.insert({layer, createBox2dObject(layer, object, true)});
}

void Box2dEngine::addStaticObject(const std::string &layer, std::shared_ptr<PhysicalObject> object) {
    auto box2dObject = createBox2dObject(layer, object, false);
    if (auto layerVelocity = layerVelocities[layer]) {
        box2dObject->getBody()->SetLinearVelocity(b2Vec2(layerVelocity, 0.f));
    }
    staticObjects.insert({layer, box2dObject});
}

std::shared_ptr<Box2dObject> Box2dEngine::createBox2dObject(const std::string &layer,
                                                            std::shared_ptr<PhysicalObject> o,
                                                            bool movable) {
    auto rect = o->getPhysicalRect();
    auto getShape = [&o, &rect]() -> std::shared_ptr<b2Shape> {
        switch (o->getShapeType()) {
            case CIRCLE: {
                auto shape = std::make_shared<b2CircleShape>(b2CircleShape());
                shape->m_radius = Utils::getRectRadius(rect);
                return shape;
            }
            case RECTANGLE: {
                auto shape = std::make_shared<b2PolygonShape>(b2PolygonShape());
                shape->SetAsBox(rect.size.width / 2.f, rect.size.height / 2.f); // This function requires halved values
                return shape;
            }
        }
        throw std::invalid_argument("Shape type unsupported");
    };

    auto anchorPoint = getCenterAnchorPoint(o);
    auto def = b2BodyDef();
    def.type = movable ? b2_dynamicBody : b2_kinematicBody;
    def.position.Set(anchorPoint.x, anchorPoint.y);

    auto body = world->CreateBody(&def);
    body->CreateFixture(getShape().get(), 1.f);
    setUserData(body, layer, o->getId());

    return std::make_shared<Box2dObject>(Box2dObject(o->getId(), rect, o->getShapeType(), body));
}

void Box2dEngine::setStaticLayerVelocity(const std::string &layer, float speed) {
    auto range = this->staticObjects.equal_range(layer);
    for (auto it = range.first; it != range.second; ++it) {
        auto object = it->second;
        object->getBody()->SetLinearVelocity(b2Vec2(speed, 0.f));
    }
    layerVelocities[layer] = speed;
}

std::list<std::shared_ptr<PhysicalObject>> Box2dEngine::getStaticLayer(const std::string &layer) {
    return Utils::getLayerObjects(staticObjects, layer);
}

void Box2dEngine::removeStaticObject(const std::string &layer, int id) {
    if (auto o = Utils::getObject(staticObjects, layer, id)) {
        delete getUserData(o->getBody());
        world->DestroyBody(o->getBody());
        Utils::removeObject(staticObjects, layer, id);
        log("Body %d destroyed", id);
    }
}

std::list<std::shared_ptr<PhysicalObject>> Box2dEngine::getDynamicLayer(const std::string &layer) {
    return Utils::getLayerObjects(dynamicObjects, layer);
}

// TODO continuous forces will not work when we'd have more than one dynamic body
void Box2dEngine::setDynamicObjectAccelerationY(const std::string &layer, int id, float acceleration) {
    if (auto o = Utils::getObject(dynamicObjects, layer, id)) {
        float force = o->getBody()->GetMass() * acceleration;

        if ((acceleration - 0.01f) <= 0) {
            world->ClearForces();
        } else {
            o->getBody()->ApplyForceToCenter(b2Vec2(0, force), true);
        }
    }
}


// Helper functions

void updatePositions(std::multimap<std::string, std::shared_ptr<Box2dObject>> map) {
    for (auto &i : map) {
        std::shared_ptr<Box2dObject> object = i.second;

        auto newRect = object->getPhysicalRect();
        newRect.origin = getBottomLeftAnchorPoint(object);

        object->setRect(newRect);
    }
}