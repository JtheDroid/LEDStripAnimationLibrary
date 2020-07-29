#pragma once

#include "ColorRGB.h"
#include "AnimationDisplay.h"
#include <functional>
#include <utility>

class FunctionAnimationDisplay : public AnimationDisplay {
private:
    std::function<void(unsigned int, ColorRGB)> setFunction;
    std::function<void(void)> showFunction;
public:
    FunctionAnimationDisplay(unsigned int ledNum,
                             std::function<void(unsigned int, ColorRGB)> setFunction,
                             std::function<void(void)> showFunction = []() {}) :
            AnimationDisplay(ledNum),
            setFunction(std::move(setFunction)),
            showFunction(std::move(showFunction)) {}

public:
    void show() override {
        showFunction();
    };

protected:
    void setLedImpl(unsigned int p, ColorRGB color) override {
        setFunction(p, color);
    }
};
