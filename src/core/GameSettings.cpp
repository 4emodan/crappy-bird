#include "_include/GameSettings.h"

static std::shared_ptr<const GameSettings> _instance = nullptr;

std::shared_ptr<const GameSettings> GameSettings::instance() {
    return _instance; // TODO check for null
}

std::shared_ptr<const GameSettings> GameSettings::init(int frameWidth, int frameHeight) {
    float pointsInMeter = PHYSICAL_FRAME_WIDTH / frameWidth;

    auto frameSize = cocos2d::Size(frameWidth, frameHeight);
    auto physicalFrameSize = cocos2d::Size(PHYSICAL_FRAME_WIDTH, frameHeight / pointsInMeter);

    float playerSpeedMps = PHYSICAL_FRAME_WIDTH / SECONDS_SINGLE_SCREEN_STAYS_VISIBLE;
    float gravity = REAL_WORLD_GRAVITY * 4;
    float upAcceleration = -gravity * 4;

    _instance = std::make_shared<const GameSettings>(
            GameSettings(
                    gravity,
                    pointsInMeter,
                    frameSize,
                    physicalFrameSize,
                    cocos2d::Size(50, 200),
                    cocos2d::Size(80, 100),
                    playerSpeedMps,
                    upAcceleration,
                    MIN_SECONDS_BETWEEN_OBSTACLES,
                    [pointsInMeter](float p) { return p * pointsInMeter; },
                    [pointsInMeter](float p) { return p / pointsInMeter; }
            ));
    return _instance;
}
