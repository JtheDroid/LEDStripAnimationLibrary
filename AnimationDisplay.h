#pragma once

#include "ColorRGB.h"

template <class Color = ColorRGB>
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

    virtual void setAllLeds(Color color) {
        for (unsigned int p = 0; p < ledNum; ++p) {
            setLed(p, color);
        }
    }

    virtual void clear() {
        setAllLeds({0, 0, 0});
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

    virtual ~AnimationDisplay() = default;
};
