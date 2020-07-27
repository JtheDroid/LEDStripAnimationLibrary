#include "TimedAnimation.h"
#include "FunctionAnimationDisplay.h"
#include "AnimationPreviewSDL.h"

class TestAnimation : public TimedAnimation {
public:
    TestAnimation(AnimationDisplay *display, unsigned long interval) : Animation(display),
                                                                       TimedAnimation(display, interval) {}

protected:
    void animationStep() override {
        for (unsigned int i = 0; i < getLedNum(); ++i) {
            unsigned int c = getCounter() + 10 * i;
            setLed(i, {c % 255, c / 2 % 255, c / 4 % 255});
        }
    }
};


int main() {
    struct preview {
        AnimationPreviewSDL sdl;
        TimedAnimation *animation;
    };
    AnimationPreviewSDL sdl{10}, sdl2{100}, sdl3{200};
    TestAnimation anim1{sdl.getSdlDisplayPtr(), 30},
            anim2{sdl2.getSdlDisplayPtr(), 20},
            anim3{sdl3.getSdlDisplayPtr(), 10};
    preview previews[]{{sdl,  &anim1},
                       {sdl2, &anim2},
                       {sdl3, &anim3}};
    bool end{false};
    while (!end) {
        end = true;
        for (int i = 0; i < sizeof(previews) / sizeof(preview); ++i) {
            preview &p{previews[i]};
            if (p.sdl.loop()) {
                p.animation->loop();
                end = false;
            } else p.sdl.quit();
        }
    }
    return 0;
}
