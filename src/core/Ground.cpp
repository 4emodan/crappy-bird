#include "_include/Ground.h"

USING_NS_CC;

static const std::string LAYER_GROUND = "ground";

GroundPresenter::GroundPresenter(std::shared_ptr<PhysicsEngine> physics) {
	this->physics = std::move(physics);
	this->settings = GameSettings::instance();

	this->ground = createGround();
	this->physics->addStaticObject(LAYER_GROUND, ground);


}

std::function<void(float)> GroundPresenter::getUpdateSource() {
	return [this](float delta) {
		auto distance = settings->metersToPixels(settings->playerSpeedMps * delta);

		// Update position and remove offscreen chunks
		groundChunks.remove_if([&distance](std::shared_ptr<GroundChunk> chunk)-> bool {
			const auto viewRect = Utils::moveRectX(chunk->getViewRect(), -distance);
			chunk->setViewRect(viewRect);

			if (viewRect.origin.x <= -viewRect.size.width) {
				log("Ground chunk %d deleted", chunk->getId());
				return true;
			} else { return false; }
			// return viewRect.origin.x <= -viewRect.size.width;
		});

		// Add chunks if needed
		auto rightBorder = groundChunks.empty() ? 0.f : groundChunks.back()->getViewRect().getMaxX();
		while (rightBorder < settings->frameSize.width) {
			auto newChunk = std::make_shared<GroundChunk>(GroundChunk(incrementalId++,
			                                                          cocos2d::Rect(
				                                                          cocos2d::Vec2(rightBorder, 0.f),
				                                                          settings->groundChunkPixelSize)));
			groundChunks.push_back(newChunk);
			rightBorder += settings->groundChunkPixelSize.width;
		}

		onUpdateFinished(groundChunks);
	};
}

std::shared_ptr<Ground> GroundPresenter::createGround() const {
	const auto groundRect = cocos2d::Rect(0, 0, settings->physicalFrameSize.width,
	                                      settings->physicalFrameSize.height / 10.);
	return std::make_shared<Ground>(Ground(0, groundRect));
}


// Data classes

void GroundChunk::setViewRect(const cocos2d::Rect& rect) {
	this->rect = rect;
}
