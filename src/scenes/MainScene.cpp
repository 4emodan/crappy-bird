#include "_include/MainScene.h"


USING_NS_CC;

namespace {
    static const float SPACE_BETWEEN_LABELS = 50;
    static const float FADE_TRANSITION_TIME = 0.5;
}

Scene *MainScene::createScene() {
    auto scene = Scene::create();
    auto layer = MainScene::create();

    scene->addChild(layer);

    return scene;
}

bool MainScene::init() {
    if (!Layer::init()) {
        return false;
    }
    director = Director::getInstance();

    auto visibleSize = director->getVisibleSize();
    auto center = Vec2(visibleSize.width / 2, visibleSize.height / 2);

    auto customMenuItem = MenuItemFont::create("Custom Physics", [=](Ref *sender) {
        director->replaceScene(TransitionFade::create(FADE_TRANSITION_TIME, CustomPhysicsScene::create()));
    });
    auto box2dMenuItem = MenuItemFont::create("Box2D Physics", [=](Ref *sender) {
        director->replaceScene(TransitionFade::create(FADE_TRANSITION_TIME, Box2dPhysicsScene::create()));
    });

    auto menu = Menu::create(box2dMenuItem, customMenuItem, NULL);
    menu->alignItemsHorizontallyWithPadding(SPACE_BETWEEN_LABELS);
    menu->setPosition(center);
    this->addChild(menu, 1);

    return true;
}