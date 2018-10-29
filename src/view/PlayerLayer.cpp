#include "_include/PlayerLayer.h"

USING_NS_CC;

Layer *getPlayerLayer(std::shared_ptr<PhysicsEngine> physics) {
    auto layer = PlayerLayer::create();
    auto presenter = std::make_shared<PlayerPresenter>(PlayerPresenter(std::move(physics)));
    establishConnection(layer, presenter);

    return layer;
}

bool PlayerLayer::init() {
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [=](Touch *touch, Event *event) -> bool {
        presenter->onTouchStart();
        return true;
    };
    touchListener->onTouchEnded = [=](Touch *touch, Event *event) -> bool {
        presenter->onTouchEnd();
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    this->scheduleUpdate();

    return true;
}

void PlayerLayer::update(float delta) {
    requestUpdate(delta);
}

std::function<void(const std::shared_ptr<Player>)> PlayerLayer::getUpdateReceiver() {
    return [this](const std::shared_ptr<Player> player) {
        if (!playerSprite) {
            playerSprite = Sprite::create("balloon_80x100.png");
            playerSprite->setAnchorPoint(Vec2(0, 0));
            this->addChild(playerSprite);
        }
        playerSprite->setPosition(player->getViewRect().origin);
    };
}