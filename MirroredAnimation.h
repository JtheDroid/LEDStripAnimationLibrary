#pragma once

#include "Animation.h"

template<class Color = ColorRGB>
class MirroredAnimation : public virtual Animation<Color> {
public:
    explicit MirroredAnimation(AnimationDisplay<Color> *display) : Animation<Color>(display) {}

    unsigned int getLedNum() const override {
        return getFullLedNum() / 2;
    }

    unsigned int getFullLedNum() const {
        return Animation<Color>::getLedNum();
    }

protected:
    void setLed(unsigned int p, Color color) override {
        Animation<Color>::setLed(p, color);
        Animation<Color>::setLed(getFullLedNum() - 1 - p, color);
    }
};
