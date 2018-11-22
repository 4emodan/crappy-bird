#pragma once

#include "cocos2d.h"

#define REAL_WORLD_GRAVITY -9.8f

#define PHYSICAL_FRAME_WIDTH 100.f
#define SECONDS_SINGLE_SCREEN_STAYS_VISIBLE 5.f
#define MIN_SECONDS_BETWEEN_OBSTACLES 2.f

class GameSettings {
public:
    static std::shared_ptr<const GameSettings> instance();

    static std::shared_ptr<const GameSettings> init(int frameWidth, int frameHeight);

    float gravity;
    float pointsInMeter;
    cocos2d::Size frameSize;
    cocos2d::Size physicalFrameSize;

    cocos2d::Size obstaclePixelSize; // TODO move to some adaptive scale utility
    cocos2d::Size playerPixelSize; // TODO move to some adaptive scale utility
    float groundHeight;

    float playerSpeedMps;
    float playerUpAcceleration;
    float minSecondsBetweenObstacles;

    std::function<float(float)> pixelsToMeters;
    std::function<float(float)> metersToPixels;

private:
    GameSettings(
            float gravity,
            float pointsInMeter,
            const cocos2d::Size &frameSize,
            const cocos2d::Size &physicalFrameSize,
            const cocos2d::Size &obstacleSize,
            const cocos2d::Size &playerSize,
            float groundHeight,
            float playerSpeed,
            float playerUpAcceleration,
            float minSecondsBetweenObstacles,
            std::function<float(float)> pixelsToMeters,
            std::function<float(float)> metersToPixels) :
            gravity(gravity),
            pointsInMeter(pointsInMeter),
            frameSize(frameSize),
            physicalFrameSize(physicalFrameSize),
            obstaclePixelSize(obstacleSize),
            playerPixelSize(playerSize),
            groundHeight(groundHeight),
            playerSpeedMps(playerSpeed),
            playerUpAcceleration(playerUpAcceleration),
            minSecondsBetweenObstacles(minSecondsBetweenObstacles),
            pixelsToMeters(std::move(pixelsToMeters)),
            metersToPixels(std::move(metersToPixels)) {};
};