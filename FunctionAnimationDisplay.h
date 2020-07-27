#pragma once

#include "Color.h"
#include "AnimationDisplay.h"
#include <functional>
#include <utility>

class FunctionAnimationDisplay : public AnimationDisplay {
private:
    std::function<void(unsigned int, Color)> setFunction;
public:
    FunctionAnimationDisplay(unsigned int ledNum,
                             std::function<void(unsigned int, Color)> setFunction,
                             std::function<void(void)> showFunction = []() {}) :
            AnimationDisplay(ledNum),
            setFunction(std::move(setFunction)),
            showFunction(std::move(showFunction)) {}

private:
    std::function<void(void)> showFunction;
public:
    void show() override {
        showFunction();
    };

protected:
    void setLed(unsigned int p, Color color) override {
        setFunction(p, color);
    }
};
