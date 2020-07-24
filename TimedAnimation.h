#pragma once

#include "Animation.h"

class TimedAnimation : public virtual Animation {
private:
    unsigned long interval, lastRun{millis()};
public:
    TimedAnimation(unsigned int ledNum, unsigned long interval) : Animation(ledNum), interval(interval) {}

    void loop() {
        runTimed(interval, lastRun);
    }
};