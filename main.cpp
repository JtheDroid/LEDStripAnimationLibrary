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

void drawLed(AnimationPreviewSDL &sdl, unsigned int index, unsigned int length, Color color) {
    int size = (int) (sdl.getXSize() / length);
    sdl.draw_rect(size * (int) index, 0, size, sdl.getYSize(), color.r, color.g, color.b);
}

int main() {
    AnimationPreviewSDL sdl{};
    FunctionAnimationDisplay sdlDisplay{10, [&sdl, &sdlDisplay](unsigned int pixel, Color c) {
        drawLed(sdl, pixel, sdlDisplay.getLedNum(), c);
    }, [&sdl]() {
        sdl.draw_show();
    }};
    TestAnimation testAnimation{&sdlDisplay, 50};
    while (sdl.loop()) {
        //sdl.draw_clear();
        testAnimation.loop();
        sdl.draw_show();
    }
    return 0;
}
