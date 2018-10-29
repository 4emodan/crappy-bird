#include "_include/AppDelegate.h"

USING_NS_CC;

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glView = director->getOpenGLView();

    if (!glView) {
        glView = GLViewImpl::create("CrappyBird");
        glView->setFrameSize(640, 480);
        glView->setDesignResolutionSize(640, 480, ResolutionPolicy::EXACT_FIT);
        director->setOpenGLView(glView);
    }

    gameSettings = GameSettings::init(640, 480);

    auto scene = MainScene::createScene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {}

void AppDelegate::applicationWillEnterForeground() {}