#pragma once

#include "Animation.h"

class AnimationDisplay {
private:
    unsigned int ledNum;
    bool showOnRun = true;
public:
    AnimationDisplay(unsigned int ledNum) : ledNum(ledNum) {}

    virtual void show() = 0;

    virtual void setLed(unsigned int p, Color color) = 0;

    unsigned int getLedNum() const {
        return ledNum;
    }

    void setShowOnRun(bool showOnRun_) {
        showOnRun = showOnRun_;
    }

    bool isShowOnRun() const {
        return showOnRun;
    }
};
