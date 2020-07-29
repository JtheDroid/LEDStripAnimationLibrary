#pragma once

#include "ColorRGB.h"
#include "Animation.h"

template<class Color = ColorRGB>
class MirroredAnimationDisplay : public virtual AnimationDisplay<Color> {
private:
    unsigned int fullLedNum;
public:
    explicit MirroredAnimationDisplay(unsigned int ledNum) : AnimationDisplay<Color>(ledNum / 2), fullLedNum(ledNum) {}

    void setLed(unsigned int p, Color color) override {
        setLedImpl(p, color);
        setLedImpl(fullLedNum - 1 - p, color);
    }
};
