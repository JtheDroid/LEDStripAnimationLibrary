#pragma once

#include "Animation.h"

class MirroredAnimationDisplay : public virtual AnimationDisplay {
private:
    unsigned int fullLedNum;
public:
    explicit MirroredAnimationDisplay(unsigned int ledNum) : AnimationDisplay(ledNum / 2), fullLedNum(ledNum) {}

    void setLed(unsigned int p, ColorRGB color) override {
        setLedImpl(p, color);
        setLedImpl(fullLedNum - 1 - p, color);
    }
};
