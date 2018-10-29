#pragma once

#include "cocos2d.h"

class ViewObject {
public:
    virtual int getId() const = 0;

    virtual cocos2d::Rect const getViewRect() const = 0;
};