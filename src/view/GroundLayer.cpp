#include "_include/GroundLayer.h"

USING_NS_CC;

cocos2d::Layer* getGroundLayer(std::shared_ptr<PhysicsEngine> physics) {
	auto layer = GroundLayer::create();
	auto presenter = std::make_shared<GroundPresenter>(GroundPresenter(std::move(physics)));
	establishConnection(layer, presenter);

	return layer;
}

bool GroundLayer::init() {
	requestUpdate = [](float) {};
	
	this->scheduleUpdate();
	return true;
}

void GroundLayer::update(float delta) {
	this->requestUpdate(delta);
}

std::function<void(const std::list<std::shared_ptr<GroundChunk>>)> GroundLayer::getUpdateReceiver() {
	return [this](const std::list<std::shared_ptr<GroundChunk>> groundChunks) {
		auto spritesToRemove = std::map<int, Sprite *>(sprites);

		for (const auto& chunk : groundChunks) {
			auto id = chunk->getId();

			if (auto sprite = sprites[id]) {
				// update position
				auto origin = chunk->getViewRect().origin;
				sprite->setPosition(origin.x, origin.y);
			} else {
				// add new sprite
				const auto newSprite = createGroundChunkSprite(chunk->getViewRect());
				this->addChild(newSprite);
				sprites[id] = newSprite;
				log("Ground chunk sprite %d added", id);
			}
			spritesToRemove.erase(id);
		}

		for (auto& s : spritesToRemove) {
			sprites.erase(s.first);
			this->removeChild(s.second);
			log("Ground chunk sprite %d removed", s.first);
		}
	};
}

Sprite *GroundLayer::createGroundChunkSprite(const Rect &rect) {
    auto sprite = Sprite::create("ground_chunk_50x50.png");
    sprite->setAnchorPoint(Vec2(0, 0));
    sprite->setPosition(rect.origin);
    return sprite;
}