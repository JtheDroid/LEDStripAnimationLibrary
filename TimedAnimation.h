#pragma once

#include "ColorRGB.h"
#include "Animation.h"

template<class Color = ColorRGB>
class TimedAnimation : public virtual Animation<Color> {
private:
    unsigned long interval, lastRun{millis()};
public:
    TimedAnimation(AnimationDisplay<Color> *display, unsigned long interval) : Animation<Color>(display),
                                                                               interval(interval) {}

    void run() override {
        Animation<Color>::runTimed(interval, lastRun);
    }
};