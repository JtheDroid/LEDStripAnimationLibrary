#pragma once

#ifndef Arduino_h

#include <chrono>

unsigned long millis() {
    return (unsigned long)std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}

#endif

#include "AnimationDisplay.h"
#include "ColorRGB.h"

template <class Color = ColorRGB>
class Animation {
private:
    AnimationDisplay<Color> *display;
    unsigned int ledNum;
    unsigned long counter = 0;

public:
    explicit Animation(AnimationDisplay<Color> *display) : display(display), ledNum(display->getLedNum()) {}

    virtual unsigned int getLedNum() const {
        return ledNum;
    }

    unsigned long getCounter() const {
        return counter;
    }

    virtual void run();

    void run(bool showOnRun);

    void runTimed(unsigned long interval, unsigned long &lastRun);

    void show() {
        display->show();
    };

    /** @brief Skip frames if running too slow to keep up with interval
     *
     *  If runTimed is not called fast enough to keep up with the interval, multiple animation steps are executed.
     *
     *  For some animations, this might not work well
     *
     *  @param skipFrames_ enable or disable this behavior
     */
    void setSkipFrames(bool skipFrames_) {
        skipFrames = skipFrames_;
    }

    bool isDisplayBuffered() {
        return display->isBuffered();
    }

    virtual ~Animation() = default;

protected:
    // Set led at position p to color
    virtual void setLed(unsigned int p, Color color) {
        display->setLed(p, color);
    }

    // Set leds from p1 to p2 to color
    void setLeds(unsigned int p1, unsigned int p2, Color color);

    // Set leds from p1 to p2 to transition from color1 to color2
    void setLedsTransition(unsigned int p1, unsigned int p2, Color color1, Color color2);

    // Set all leds to color using display method
    virtual void setAllLeds(Color color) {
        display->setAllLeds(color);
    }

    virtual void copyLed(unsigned int from, unsigned int to) {
        display->copyLed(from, to);
    }

    virtual Color getLedColor(unsigned int p) {
        return display->getLedColor(p);
    }

    virtual void clear() {
        display->clear();
    }

    // Set pixel colors using setLed
    virtual void animationStep() = 0;

private:
    bool skipFrames{true};
};

template <class Color>
void Animation<Color>::run(bool showOnRun) {
    animationStep();
    if (showOnRun && display->isShowOnRun())
        show();
    ++counter;
}

template <class Color>
void Animation<Color>::run() {
    run(true);
}

template <class Color>
void Animation<Color>::setLeds(unsigned int p1, unsigned int p2, Color color) {
    if (p1 >= ledNum)
        p1 = ledNum - 1;
    if (p2 >= ledNum)
        p2 = ledNum - 1;
    if (p2 < p1)
        p2 = p1;
    for (unsigned int p = p1; p <= p2; ++p)
        setLed(p, color);
}

template <class Color>
void Animation<Color>::setLedsTransition(unsigned int p1, unsigned int p2, Color color1, Color color2) {
    if (p2 < p1)
        p2 = p1;
    int origLength{(int)(p2 - p1)};
    if (p1 >= ledNum)
        p1 = ledNum - 1;
    if (p2 >= ledNum)
        p2 = ledNum - 1;
    int length{(int)(p2 - p1)};
    for (int i = 0; i <= length; ++i) {
        double portion{origLength > 0 ? i * 1.0 / origLength : 1.0};
        setLed(p1 + i, Color::mixColors(portion, color1, color2));
    }
}

template <class Color>
void Animation<Color>::runTimed(unsigned long interval, unsigned long &lastRun) {
    unsigned long now = millis();
    bool shown = false;
    while (now > lastRun && now - lastRun >= interval) {
        Animation::run(false);
        shown = true;
        if (skipFrames) {
            if (counter == 1)
                lastRun = now;
            else
                lastRun += interval;
            if (interval == 0)
                break;
        } else {
            lastRun = now;
            break;
        }
    }
    if (shown && display->isShowOnRun())
        show();
}