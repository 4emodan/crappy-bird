#include "_include/Ground.h"

USING_NS_CC;

static const std::string LAYER_GROUND = "ground";

GroundPresenter::GroundPresenter(std::shared_ptr<PhysicsEngine> physics) {
	this->physics = std::move(physics);
	this->settings = GameSettings::instance();

	addGround();
}

std::function<void(float)> GroundPresenter::getUpdateSource() {
	return [this](float delta) { };
}

void GroundPresenter::addGround() const {
	const auto groundRect = cocos2d::Rect(0, 0, settings->physicalFrameSize.width, settings->physicalFrameSize.height / 10.);
	log("Physical height = %.2f", settings->physicalFrameSize.height);
	log("Ground rect = [%.2f, %.2f, %.2f, %.2f]", groundRect.origin.x, groundRect.origin.y, groundRect.size.width, groundRect.size.height);
	const auto ground = std::make_shared<Ground>(Ground(0, groundRect));
	physics->addStaticObject(LAYER_GROUND, ground);
}