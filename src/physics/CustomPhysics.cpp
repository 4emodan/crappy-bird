#include "_include/CustomPhysics.h"

USING_NS_CC;

void CustomEngine::addDynamicObject(const std::string &layer, std::shared_ptr<PhysicalObject> object) {
    insertCustomObject(dynamicObjects, layer, object);
}

void CustomEngine::addStaticObject(const std::string &layer, std::shared_ptr<PhysicalObject> object) {
    insertCustomObject(staticObjects, layer, object);
}

void CustomEngine::removeStaticObject(const std::string &layer, int id) {
    Utils::removeObject(staticObjects, layer, id);
}

void CustomEngine::setStaticLayerVelocity(const std::string &layer, float speed) {
    layerVelocities.insert({layer, speed});
}

void CustomEngine::setDynamicObjectAccelerationY(const std::string &layer, int id, float accelerationY) {
    auto i = std::find_if(dynamicObjects.begin(), dynamicObjects.end(),
                          [&id](auto &i) -> bool {
                              auto object = i.second;
                              return object->getId() == id;
                          });
    if (i != dynamicObjects.end()) {
        auto object = i->second;
        object->setAccelerationY(accelerationY);
    }
}

void CustomEngine::update(float delta) {
    { // Update static objects
        std::for_each(layerVelocities.begin(), layerVelocities.end(), [this, delta](std::pair<std::string, float> p) {
            auto layer = p.first;
            auto speed = p.second;

            auto distance = speed * delta;

            auto range = staticObjects.equal_range(layer);
            for (auto i = range.first; i != range.second; ++i) {
                auto object = i->second;
                object->setRect(Utils::moveRectX(object->getPhysicalRect(), distance));
            }
        });
    }

    std::list<std::shared_ptr<Collision>> collisions{};
    { // Update dynamic objects
        for (auto &pair: dynamicObjects) {
            auto object = pair.second;
            auto currentSpeed = object->getSpeedY();
            auto currentRect = object->getPhysicalRect();

            auto compoundAcceleration = object->getAccelerationY() + gravity;
            auto distance = currentSpeed * delta + compoundAcceleration * pow(delta, 2) / 2;

            object->setSpeedY(currentSpeed + compoundAcceleration * delta);
            object->setRect(Utils::moveRectY(currentRect, distance));

            // Detect collisions
            if (auto collision = findCollision(pair, staticObjects)) {
                collisions.push_back(collision);
            }
            if (auto collision = findCollision(pair, dynamicObjects)) {
                collisions.push_back(collision);
            }
        }
    }

    { // Notify collision listener
        for (const auto &c: collisions) {
            notifyCollision(c);
        }
    }
}

std::list<std::shared_ptr<PhysicalObject>> CustomEngine::getStaticLayer(const std::string &layer) {
    return Utils::getLayerObjects(staticObjects, layer);
}

std::list<std::shared_ptr<PhysicalObject>> CustomEngine::getDynamicLayer(const std::string &layer) {
    return Utils::getLayerObjects(dynamicObjects, layer);
}

std::shared_ptr<Collision>
CustomEngine::findCollision(const std::pair<std::string, std::shared_ptr<CustomObject>> &aPair,
                            const std::multimap<std::string, std::shared_ptr<CustomObject>> &collection) {
    for (const std::pair<std::string, std::shared_ptr<CustomObject>> &bPair: collection) {
        if (collide(aPair, bPair)) {
            return std::make_shared<Collision>(Collision(aPair.first, bPair.first));
        }
    }
    return nullptr;
}


// Helper functions

static bool collide(const std::pair<std::string, std::shared_ptr<CustomObject>> &aPair,
                    const std::pair<std::string, std::shared_ptr<CustomObject>> &bPair) {
    auto a = aPair.second;
    auto aRect = a->getPhysicalRect();

    auto b = bPair.second;
    auto bRect = b->getPhysicalRect();

    if (aPair.first == bPair.first && a->getId() == b->getId()) { return false; } // Don't detect collision with self

	bool detected = false;
    if (aRect.intersectsRect(bRect)) {
        auto aShape = a->getShapeType();
        auto bShape = b->getShapeType();

		if (aShape == RECTANGLE && bShape == RECTANGLE) {
			detected = true; // Sufficient for rectangles
		} else if (aShape == CIRCLE && bShape == RECTANGLE) {
            detected = Utils::intersectsCircle(bRect, aRect);
        } else if (bShape == CIRCLE && aShape == RECTANGLE) {
			detected = Utils::intersectsCircle(aRect, bRect);
        } else if (aShape == CIRCLE && bShape == CIRCLE) {
            auto aCenter = Utils::getRectCenter(aRect);
            auto bCenter = Utils::getRectCenter(bRect);
            auto aRadius = Utils::getRectRadius(aRect);
            auto bRadius = Utils::getRectRadius(bRect);
			detected = aCenter.distance(bCenter) <= aRadius + bRadius;
		}
		if (detected) {
			log("Collide detected: %s to %s", Utils::toString(aShape).c_str(), Utils::toString(bShape).c_str());
		}
    }
    return detected;
}
