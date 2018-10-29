#include "_include/Box2dPhysicsScene.h"

USING_NS_CC;

#ifndef BOX2D_PHYSICS_SCENE_DEBUG
//#define BOX2D_PHYSICS_SCENE_DEBUG true
#define BOX2D_PHYSICS_SCENE_DEBUG false
#endif

bool Box2dPhysicsScene::init() {
    DebugLayer *debugLayer = nullptr;
    if (BOX2D_PHYSICS_SCENE_DEBUG) {
        debugLayer = DebugLayer::create();
        this->addChild(debugLayer, 99);
    }

    physics = std::make_shared<Box2dEngine>(Box2dEngine(debugLayer));
    physics->setCollisionListener([this](std::shared_ptr<Collision> c) {
        if ((c->getLayerA() == "player" && c->getLayerB() == "ground_obstacles") ||
                (c->getLayerB() == "player" && c->getLayerA() == "ground_obstacles")) {
            _director->pause();
        }
    });

    auto obstaclesLayer = getObstaclesLayer(std::static_pointer_cast<PhysicsEngine>(physics));
    this->addChild(obstaclesLayer, -1);

    auto playerLayer = getPlayerLayer(std::static_pointer_cast<PhysicsEngine>(physics));
    this->addChild(playerLayer, 1);

    scheduleUpdate();

//    auto collisionDetector = CollisionDetector::create();
//    collisionDetector->setProviders(obstaclesLayer->sortedObstaclesProvider(), playerLayer->playerProvider());
//    collisionDetector->setCollisionListener(
//            [=](Collision c) {
//                if (AL_DEBUG) {
//                    debugDrawCollision(c, debugLayer);
//                }
//                director->pause();
//            }
//    );
//    this->addChild(collisionDetector, 2);

    return true;
}

void Box2dPhysicsScene::update(float delta) {
    physics->update(delta);
}