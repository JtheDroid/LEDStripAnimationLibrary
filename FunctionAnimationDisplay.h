#pragma once

#include "ColorRGB.h"
#include "AnimationDisplay.h"
#include <functional>
#include <utility>

template<class Color = ColorRGB>
class FunctionAnimationDisplay : public AnimationDisplay<Color> {
private:
    std::function<void(unsigned int, Color)> setFunction;
    std::function<void(void)> showFunction;
public:
    FunctionAnimationDisplay(unsigned int ledNum,
                             std::function<void(unsigned int, Color)> setFunction,
                             std::function<void(void)> showFunction = []() {}) :
            AnimationDisplay<Color>(ledNum),
            setFunction(std::move(setFunction)),
            showFunction(std::move(showFunction)) {}

public:
    void show() override {
        showFunction();
    };

protected:
    void setLedImpl(unsigned int p, Color color) override {
        setFunction(p, color);
    }
};
