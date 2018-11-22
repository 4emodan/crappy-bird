#include "_include/GroundLayer.h"

USING_NS_CC;

cocos2d::Layer* getGroundLayer(std::shared_ptr<PhysicsEngine> physics) {
	auto layer = GroundLayer::create();
	auto presenter = std::make_shared<GroundPresenter>(GroundPresenter(std::move(physics)));
	establishConnection(layer, presenter);

	return layer;
}

bool GroundLayer::init() { return true; }

void GroundLayer::update(float delta) {
	this->requestUpdate(delta);
}

std::function<void(float)> GroundLayer::getUpdateReceiver() {
	return [this](float delta) {};
}
