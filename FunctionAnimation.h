#pragma once

#include "Animation.h"
#include<functional>
#include <utility>

class FunctionAnimation : public virtual Animation {
private:
    std::function<void(unsigned int, Color)> setFunction;
public:
    FunctionAnimation(unsigned int ledNum, std::function<void(unsigned int, Color)> setFunction,
                      std::function<void(void)> showFunction = []() {});

private:
    std::function<void(void)> showFunction;
public:
    void show() override;

protected:
    void setLed(unsigned int p, Color color) override;
};

void FunctionAnimation::show() {
    showFunction();
}

void FunctionAnimation::setLed(unsigned int p, Color color) {
    setFunction(p, color);
}

FunctionAnimation::FunctionAnimation(unsigned int ledNum, std::function<void(unsigned int, Color)> setFunction,
                                     std::function<void(void)> showFunction) : Animation(ledNum),
                                                                               setFunction(std::move(setFunction)),
                                                                               showFunction(std::move(showFunction)) {}
