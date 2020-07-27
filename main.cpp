#include "TimedAnimation.h"
#include "FunctionAnimationDisplay.h"
#include "AnimationPreviewSDL.h"

class TestAnimation : public TimedAnimation {
public:
    TestAnimation(AnimationDisplay *display, unsigned long interval) : Animation(display),
                                                                       TimedAnimation(display, interval) {}

protected:
    void animationStep() override {
        setAllLeds({getCounter() % 255, getCounter() / 2 % 255, getCounter() / 4 % 255});
    }
};


int main() {
    AnimationPreviewSDL sdl{10};
    TestAnimation testAnimation{sdl.getSdlDisplayPtr(), 30};
    while (sdl.loop()) testAnimation.loop();
    return 0;
}
