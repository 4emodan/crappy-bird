#include "_include/CustomPhysicsScene.h"

USING_NS_CC;

bool CustomPhysicsScene::init() {
	if (AL_DEBUG) {
		debugLayer = DebugLayer::create();
		this->addChild(debugLayer);
	}

	physics = std::make_shared<CustomEngine>(CustomEngine());
	physics->setCollisionListener([this](std::shared_ptr<Collision> c) {
		if (c->getLayerA() == "player" || c->getLayerB() == "player") {
			_director->popScene();
		}
	});

	auto obstaclesLayer = getObstaclesLayer(std::static_pointer_cast<PhysicsEngine>(physics));
	this->addChild(obstaclesLayer, -1);

	auto playerLayer = getPlayerLayer(std::static_pointer_cast<PhysicsEngine>(physics));
	this->addChild(playerLayer, 1);

	auto groundLayer = getGroundLayer(std::static_pointer_cast<PhysicsEngine>(physics));
	this->addChild(groundLayer, -2);

	auto backgroundLayer = BackgroundLayer::create();
	this->addChild(backgroundLayer, -3);

	scheduleUpdate();

	return true;
}

void CustomPhysicsScene::update(float delta) {
	physics->update(delta);
}
