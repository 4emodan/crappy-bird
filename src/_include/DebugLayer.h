#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Utils.h"

class DebugLayer : public cocos2d::Layer, public b2Draw {
public:
    CREATE_FUNC(DebugLayer);

    bool init() override;

    void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;

    void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;

    void DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) override;

    void DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) override;

    void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) override;

    void DrawTransform(const b2Transform &xf) override;

    void DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color) override;

    void update(float delta) override;

private:
    void drawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);

    void drawCircle(const b2Vec2 &center, float32 radius, const b2Color &color);

    cocos2d::DrawNode *drawNode;
    std::function<float(float)> mToPx;

    cocos2d::Vec2 convertVec2(const b2Vec2 &center) const;
};

static inline cocos2d::Color4F convertColor(const b2Color &color) {
    return {color.r, color.g, color.b, std::min(color.a, 0.5f)};
}

