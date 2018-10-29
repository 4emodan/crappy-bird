#include "_include/Utils.h"

USING_NS_CC;
using namespace std::placeholders;

static cocos2d::Rect convert(const cocos2d::Rect &rect, const std::function<float(float)> &_convert) {
    return cocos2d::Rect(
            _convert(rect.origin.x),
            _convert(rect.origin.y),
            _convert(rect.size.width),
            _convert(rect.size.height));
}

Sprite *Utils::createColorRectangleSprite(const Size &size, const Color3B &color) {
    auto sprite = Sprite::create();
    sprite->setTextureRect(Rect(0, 0, size.width, size.height));
    sprite->setColor(color);
    sprite->setOpacity(127);
    sprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    sprite->setIgnoreAnchorPointForPosition(false);
    return sprite;
}

//static const float MIN_DRAW_SIZE = 3;
//void Utils::debugDrawCollision(Collision collision, Layer *debugLayer) {
//    auto size = collision.getIntersection().size;
//    auto collisionZone = getRedRectangleSprite(
//            Size(std::max(size.width, MIN_DRAW_SIZE), std::max(size.height, MIN_DRAW_SIZE)));
//    collisionZone->setPosition(collision.getIntersection().origin);
//    debugLayer->addChild(collisionZone);
//}

cocos2d::Rect Utils::pixelsToMeters(const cocos2d::Rect &rect) {
    return convert(rect, GameSettings::instance()->pixelsToMeters);
}

cocos2d::Rect Utils::metersToPixels(const cocos2d::Rect &rect) {
    return convert(rect, GameSettings::instance()->metersToPixels);
}

cocos2d::Vec2 Utils::getRectCenter(const cocos2d::Rect &rect) {
    return cocos2d::Vec2(rect.getMidX(), rect.getMidY());
}

bool Utils::intersectsCircle(const cocos2d::Rect &rect, const cocos2d::Rect &circleRect) {
    return rect.intersectsCircle(getRectCenter(circleRect), getRectRadius(circleRect));
}

float Utils::getRectRadius(const cocos2d::Rect &rect) {
    return std::min(rect.size.width, rect.size.height) / 2.f;
}

cocos2d::Rect Utils::moveRectY(const cocos2d::Rect &rect, float yDelta) {
    return cocos2d::Rect(rect.origin.x, rect.origin.y + yDelta, rect.size.width, rect.size.height);
}

cocos2d::Rect Utils::moveRectX(const cocos2d::Rect &rect, float xDelta) {
    return cocos2d::Rect(rect.origin.x + xDelta, rect.origin.y, rect.size.width, rect.size.height);
}

std::string Utils::toString(ShapeType shapeType) {
	switch (shapeType)
	{
	case CIRCLE:
		return "CIRCLE";
	case RECTANGLE:
		return "RECTANGLE";
	default:
		return "UNKNOWN";
	}
}
