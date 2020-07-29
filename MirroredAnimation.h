#pragma once

#include "Animation.h"

class MirroredAnimation : public virtual Animation {
public:
    explicit MirroredAnimation(AnimationDisplay *display) : Animation(display) {}

    unsigned int getLedNum() const override {
        return getFullLedNum() / 2;
    }

    unsigned int getFullLedNum() const {
        return Animation::getLedNum();
    }

protected:
    void setLed(unsigned int p, ColorRGB color) override {
        Animation::setLed(p, color);
        Animation::setLed(getFullLedNum() - 1 - p, color);
    }
};
