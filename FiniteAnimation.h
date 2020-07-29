#pragma once

#include "ColorRGB.h"
#include "Animation.h"

template<class Color = ColorRGB>
class FiniteAnimation : public virtual Animation<Color> {
public:
    explicit FiniteAnimation(AnimationDisplay *display) : Animation<Color>(display) {}

private:
    bool done{false};
public:
    bool isDone() const {
        return done;
    }
};
