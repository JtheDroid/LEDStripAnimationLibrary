#pragma once

#include "Animation.h"

class FiniteAnimation : public virtual Animation {
public:
    FiniteAnimation(AnimationDisplay *display) : Animation(display) {}

private:
    bool done{false};
public:
    bool isDone() const {
        return done;
    }
};
