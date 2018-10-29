#include "_include/ObstaclesLayer.h"

USING_NS_CC;

// ObstaclesLayer

Layer *getObstaclesLayer(std::shared_ptr<PhysicsEngine> physics) {
    auto layer = ObstaclesLayer::create();
    auto presenter = std::make_shared<ObstaclesPresenter>(ObstaclesPresenter(std::move(physics)));
    establishConnection(layer, presenter);

    return layer;
}

bool ObstaclesLayer::init() {
    obstacleSprites = std::map<int, Sprite *>();
    requestUpdate = [](float) {};

    this->scheduleUpdate();
    return true;
}

void ObstaclesLayer::update(float delta) {
    requestUpdate(delta);
}

std::function<void(const std::list<std::shared_ptr<Obstacle>>)> ObstaclesLayer::getUpdateReceiver() {
    return [this](const std::list<std::shared_ptr<Obstacle>> &obstacles) {
        auto spritesToRemove = std::map<int, Sprite *>(obstacleSprites);

        for (const auto &o : obstacles) {
            auto id = o->getId();

            if (auto sprite = obstacleSprites[id]) { // update position
                auto origin = o->getViewRect().origin;
                sprite->setPosition(origin.x, origin.y);
            } else { // add new obstacle sprite
                auto newSprite = createObstacleSprite(o->getViewRect());
                this->addChild(newSprite);
                obstacleSprites[id] = newSprite;
                log("Obstacle sprite %d added", id);
            }
            spritesToRemove.erase(id);
        }

        for (auto &s: spritesToRemove) {
            obstacleSprites.erase(s.first);
            this->removeChild(s.second);
            log("Obstacle sprite %d removed", s.first);
        }
    };
}

Sprite *ObstaclesLayer::createObstacleSprite(const Rect &rect) {
    auto sprite = Sprite::create("obstacle_50x200.png");
    sprite->setAnchorPoint(Vec2(0, 0));
    sprite->setPosition(rect.origin);
    return sprite;
}