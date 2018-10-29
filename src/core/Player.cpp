#include "_include/Player.h"

USING_NS_CC;

static const std::string LAYER_PLAYER = "player";

PlayerPresenter::PlayerPresenter(std::shared_ptr<PhysicsEngine> physics) {
    this->physics = std::move(physics);
    this->settings = GameSettings::instance();

    // Set player start position
    auto playerSize = settings->playerPixelSize;
    auto rect = Rect(Vec2(settings->frameSize.width * 0.15f, settings->frameSize.height / 2), playerSize);
    player = std::make_shared<Player>(Player(rect));

    this->physics->addDynamicObject(LAYER_PLAYER, std::static_pointer_cast<PhysicalObject>(player));
}

std::function<void(float)> PlayerPresenter::getUpdateSource() {
    return [this](float delta) {
        auto items = physics->getDynamicLayer(LAYER_PLAYER);
        if (!items.empty()) {
            player->setPhysicalRect(items.front()->getPhysicalRect());
        }
        onUpdateFinished(player);
    };
}

void PlayerPresenter::onTouchStart() {
    physics->setDynamicObjectAccelerationY(LAYER_PLAYER, player->getId(), settings->playerUpAcceleration);
}

void PlayerPresenter::onTouchEnd() {
    physics->setDynamicObjectAccelerationY(LAYER_PLAYER, player->getId(), 0);
}


// Data classes

const Rect Player::getPhysicalRect() const {
    return Utils::pixelsToMeters(viewRect);
}

void Player::setPhysicalRect(const cocos2d::Rect &rect) {
    this->viewRect = Utils::metersToPixels(rect);
}