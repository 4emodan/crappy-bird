#include "_include/GameSettings.h"

static std::shared_ptr<const GameSettings> _instance = nullptr;

std::shared_ptr<const GameSettings> GameSettings::instance() {
    return _instance; // TODO check for null
}

std::shared_ptr<const GameSettings> GameSettings::init(int frameWidth, int frameHeight) {
    float pixelsInMeter = frameWidth / PHYSICAL_FRAME_WIDTH;

    auto frameSize = cocos2d::Size(frameWidth, frameHeight);
    auto physicalFrameSize = cocos2d::Size(PHYSICAL_FRAME_WIDTH, frameHeight / pixelsInMeter);
    float groundHeight = frameHeight / 10.f;
    float playerSpeedMps = PHYSICAL_FRAME_WIDTH / SECONDS_SINGLE_SCREEN_STAYS_VISIBLE;
    float gravity = REAL_WORLD_GRAVITY * 4;
    float upAcceleration = -gravity * 4;

    _instance = std::make_shared<const GameSettings>(
            GameSettings(
                    gravity,
                    pixelsInMeter,
                    frameSize,
                    physicalFrameSize,
                    cocos2d::Size(50, 200),
                    cocos2d::Size(80, 100),
                    groundHeight,
                    playerSpeedMps,
                    upAcceleration,
                    MIN_SECONDS_BETWEEN_OBSTACLES,
                    [pixelsInMeter](float p) { return p / pixelsInMeter; },
                    [pixelsInMeter](float p) { return p * pixelsInMeter; }
            ));
    return _instance;
}
