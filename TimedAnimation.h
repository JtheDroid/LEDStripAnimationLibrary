#pragma once

#include "Animation.h"

class TimedAnimation : public virtual Animation {
private:
    unsigned long interval, lastRun{millis()};
public:
    TimedAnimation(AnimationDisplay *display, unsigned long interval) : Animation(display), interval(interval) {}

    void loop() {
        runTimed(interval, lastRun);
    }
};