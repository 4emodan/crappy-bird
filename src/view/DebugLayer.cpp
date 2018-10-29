#include "_include/DebugLayer.h"

USING_NS_CC;

void DebugLayer::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    drawPolygon(vertices, vertexCount, color);
}

void DebugLayer::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    drawPolygon(vertices, vertexCount, color);
}

void DebugLayer::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) {
    drawCircle(center, radius, color);
}

void DebugLayer::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) {
    drawCircle(center, radius, color);
}

void DebugLayer::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
}

void DebugLayer::DrawTransform(const b2Transform &xf) {
}

void DebugLayer::DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color) {
}

bool DebugLayer::init() {
    this->mToPx = GameSettings::instance()->metersToPixels;

    drawNode = cocos2d::DrawNode::create();
    this->addChild(drawNode);

    scheduleUpdate();
    return true;
}

void DebugLayer::update(float delta) {
    drawNode->clear();
}

void DebugLayer::drawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    auto ccVerts = new Vec2[vertexCount];
    for (int i = 0; i < vertexCount; ++i) {
        ccVerts[i] = convertVec2(vertices[i]);
    }

    auto fillColor = Color4F(color.r, color.g, color.b, std::min(color.a, 0.5f));
    drawNode->drawPolygon(ccVerts, vertexCount, fillColor, 0, fillColor);

    delete[] ccVerts;

//    if (vertexCount == 4) {
//        auto v = std::vector<b2Vec2>({vertices[0], vertices[1], vertices[2], vertices[3]});
//        std::sort(v.begin(), v.end(), [](b2Vec2 &a, b2Vec2 &b) -> bool {
//            if (a.x == b.x) return a.y < b.y; else return a.x < b.x;
//        });
//
//        auto sprite = Utils::createColorRectangleSprite(
//                Size(metersToPx(v[3].x - v[0].x), metersToPx(v[1].y - v[0].y)),
//                Color3B(color.r * 255, color.g * 255, color.b * 255));
//        sprite->setPosition(metersToPx(v[0].x), metersToPx(v[0].y));
//
//        this->addChild(sprite);
//    }
}

void DebugLayer::drawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) {
    drawNode->drawSolidCircle(convertVec2(center), mToPx(radius), 0, 16, convertColor(color));
}

inline Vec2 DebugLayer::convertVec2(const b2Vec2 &center) const {
    return {mToPx(center.x), mToPx(center.y)};
}


