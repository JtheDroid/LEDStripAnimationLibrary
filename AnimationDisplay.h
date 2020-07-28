#pragma once

#include "Color.h"

class AnimationDisplay {
private:
    unsigned int ledNum;
    bool showOnRun = true;
protected:
    virtual void setLedImpl(unsigned int p, Color color) = 0;

public:
    explicit AnimationDisplay(unsigned int ledNum) : ledNum(ledNum) {}

    virtual void show() = 0;

    virtual void setLed(unsigned int p, Color color) {
        setLedImpl(p, color);
    }

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
