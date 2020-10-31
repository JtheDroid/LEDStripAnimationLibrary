#pragma once

#include "ColorRGB.h"
#include "Animation.h"

template<class Color = ColorRGB>
class FiniteAnimation : public virtual Animation<Color> {
public:
    explicit FiniteAnimation(AnimationDisplay<Color> *display) : Animation<Color>(display) {}

protected:
    bool done{false};
public:
    bool isDone() const {
        return done;
    }
    void run() override {
        if(!done) Animation<Color>::run();
    }
};
