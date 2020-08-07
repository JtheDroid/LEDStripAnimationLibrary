#pragma once

#ifdef ADAFRUIT_NEOPIXEL_H
#include "AnimationDisplay.h"
#include "ColorRGB.h"
#include "ColorRGBW.h"

class NeopixelAnimationDisplayRGB : public AnimationDisplay<ColorRGB> {
public:
    NeopixelAnimationDisplayRGB(Adafruit_NeoPixel *strip)
        : AnimationDisplay<ColorRGB>(strip->numPixels()), strip(strip) {}

    void show() override {
        strip->show();
    }

protected:
    void setLedImpl(unsigned int p, ColorRGB color) override {
        strip->setPixelColor(p, color.r, color.g, color.b);
    }

private:
    Adafruit_NeoPixel *strip;
};

class NeopixelAnimationDisplayRGBW : public AnimationDisplay<ColorRGBW> {
public:
    NeopixelAnimationDisplayRGBW(Adafruit_NeoPixel *strip)
        : AnimationDisplay<ColorRGBW>(strip->numPixels()), strip(strip) {}

    void show() override {
        strip->show();
    }

protected:
    void setLedImpl(unsigned int p, ColorRGBW color) override {
        strip->setPixelColor(p, color.r, color.g, color.b, color.w);
    }

private:
    Adafruit_NeoPixel *strip;
};
#endif