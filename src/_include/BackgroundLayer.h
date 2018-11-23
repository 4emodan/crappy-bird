#pragma once

#include "cocos2d.h"
#include "GameSettings.h"

class BackgroundLayer : public cocos2d::Layer {
public:
	CREATE_FUNC(BackgroundLayer);

	bool init() override;
};
