#include "_include/BackgroundLayer.h"

USING_NS_CC;

bool BackgroundLayer::init() {
	auto settings = GameSettings::instance();

	auto bgSprite = Sprite::create("background_960x600.png");

	auto spriteWidth = bgSprite->getContentSize().width;
	auto spriteHeight = bgSprite->getContentSize().height;

	auto ratioX = settings->frameSize.width / spriteWidth;
	auto ratioY = settings->frameSize.height / spriteHeight;

	bgSprite->setScale(std::max(ratioX, ratioY));
	bgSprite->setAnchorPoint(Vec2(0, 0));
	bgSprite->setPosition(Vec2(0, 0));

	this->addChild(bgSprite);

	return true;
}
