#include "_include/Obstacles.h"

USING_NS_CC;

// ObstaclesController

static const std::string LAYER_GROUND_OBSTACLES = "ground_obstacles";

ObstaclesPresenter::ObstaclesPresenter(std::shared_ptr<PhysicsEngine> physics) {
    log("ObstacleController constructed");

    this->physics = physics;
    this->settings = GameSettings::instance();
    physics->setStaticLayerVelocity(LAYER_GROUND_OBSTACLES, -settings->playerSpeedMps);
}

std::function<void(float)> ObstaclesPresenter::getUpdateSource() {
    return [this](float delta) {
        { // Add new obstacle if needed
            timeSinceLastObstacle += delta;
            if (timeSinceLastObstacle >= settings->minSecondsBetweenObstacles) {
                auto size = settings->obstaclePixelSize;
                auto obstacle = std::make_shared<Obstacle>(Obstacle(
                        incrementalId++,
                        Rect(
                                settings->frameSize.width,
                                0,
                                size.width,
                                size.height
                        )
                ));
                physics->addStaticObject(LAYER_GROUND_OBSTACLES, std::static_pointer_cast<PhysicalObject>(obstacle));
                obstacles.push_back(obstacle);

                timeSinceLastObstacle = 0;
            }
        }

        auto groundObstacles = physics->getStaticLayer(LAYER_GROUND_OBSTACLES);

        { // Update positions and remove offscreen obstacles
            //auto extractKey = [](std::shared_ptr<PhysicalObject> o) -> int { return o->getId(); };
            //auto map = Utils::listToMap(groundObstacles,
            //                            (std::function<int(std::shared_ptr<PhysicalObject>)>) extractKey);

            std::map<int, std::shared_ptr<PhysicalObject>> map;
            for (auto const &t : groundObstacles) {
                map.insert({t->getId(), t});
            }

            obstacles.remove_if([this, &map](std::shared_ptr<Obstacle> o) -> bool {
                if (auto physicalObject = map[o->getId()]) {
                    o->setPhysicalRect(physicalObject->getPhysicalRect());

                    auto viewRect = o->getViewRect();
                    if (viewRect.origin.x <= -viewRect.size.width) {
                        physics->removeStaticObject(LAYER_GROUND_OBSTACLES, o->getId());
                        log("Obstacle %d removed!", o->getId());
                        return true;
                    }
                } else {
                    return true;
                }
                return false;
            });
        }

//        auto viewObjects = std::list<std::shared_ptr<ViewObject>>();
//        std::transform(obstacles.begin(), obstacles.end(), std::back_inserter(viewObjects),
//                       [](std::shared_ptr<Obstacle> o) -> std::shared_ptr<ViewObject> {
//            return std::static_pointer_cast<ViewObject>(o);
//        });
        this->onUpdateFinished(obstacles);
    };
}

ObstaclesPresenter::~ObstaclesPresenter() {
    log("ObstaclesPresenter destructed");
}


// Data classes

void Obstacle::setViewRect(const cocos2d::Rect &rect) {
    this->viewRect = rect;
}

void Obstacle::setPhysicalRect(const cocos2d::Rect &rect) {
    this->viewRect = Utils::metersToPixels(rect);
}

cocos2d::Rect const Obstacle::getPhysicalRect() const {
    return Utils::pixelsToMeters(viewRect);
}