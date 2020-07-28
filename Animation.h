#pragma once

#ifndef Arduino_h

#include <chrono>

unsigned long millis() {
    return (unsigned long) std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}

#endif

#include "Color.h"
#include "AnimationDisplay.h"

class Animation {
private:
    AnimationDisplay *display;
    unsigned int ledNum;
    unsigned long counter = 0;
public:
    explicit Animation(AnimationDisplay *display) : display(display), ledNum(display->getLedNum()) {}

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

protected:
    //Set led at position p to color
    virtual void setLed(unsigned int p, Color color) {
        display->setLed(p, color);
    }

    //Set leds from p1 to p2 to color
    void setLeds(unsigned int p1, unsigned int p2, Color color);

    //Set leds from p1 to p2 to transition from color1 to color2
    void setLedsTransition(unsigned int p1, unsigned int p2, Color color1, Color color2);

    //Set all leds to color using setLed
    virtual void setAllLeds(Color color);

    //Set pixel colors using setLed
    virtual void animationStep() = 0;
};

void Animation::run() {
    run(true);
}

void Animation::run(bool showOnRun) {
    animationStep();
    if (showOnRun && display->isShowOnRun()) show();
    ++counter;
}

void Animation::runTimed(unsigned long interval, unsigned long &lastRun) {
    unsigned long now = millis();
    bool shown = false;
    while (now > lastRun && now - lastRun >= interval) {
        Animation::run(false);
        shown = true;
        if (counter == 1) lastRun = now;
        else lastRun += interval;
        if (interval == 0) break;
    }
    if (shown && display->isShowOnRun()) show();
}

void Animation::setAllLeds(Color color) {
    for (unsigned int p = 0; p < ledNum; ++p) setLed(p, color);
}

void Animation::setLeds(unsigned int p1, unsigned int p2, Color color) {
    if (p1 >= ledNum) p1 = ledNum - 1;
    if (p2 >= ledNum) p2 = ledNum - 1;
    if (p2 < p1) p2 = p1;
    for (unsigned int p = p1; p <= p2; ++p) setLed(p, color);
}

void Animation::setLedsTransition(unsigned int p1, unsigned int p2, Color color1, Color color2) {
    if (p2 < p1) p2 = p1;
    int origLength{(int) (p2 - p1)};
    if (p1 >= ledNum) p1 = ledNum - 1;
    if (p2 >= ledNum) p2 = ledNum - 1;
    int length{(int) (p2 - p1)};
    for (int i = 0; i <= length; ++i) {
        double portion{i * 1.0 / origLength};
        setLed(p1 + i, Color::mixColors(portion, color1, color2));
    }

}
