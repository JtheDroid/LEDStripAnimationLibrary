#ifdef ADAFRUIT_NEOPIXEL_H
#pragma once

#include "AnimationDisplay.h"
#include "ColorRGB.h"
#include "ColorRGBW.h"

template <class Color = ColorRGB>
class NeopixelAnimationDisplay : public AnimationDisplay<Color> {
public:
    NeopixelAnimationDisplay(Adafruit_NeoPixel *strip) : AnimationDisplay<Color>(strip->numPixels(), true), strip(strip) {}

    void show() override {
        strip->show();
    }

    void clear() override {
        strip->clear();
    }

    void setAllLeds(Color color);

protected:
    void setLedImpl(unsigned int p, Color color) override;

    void copyLed(unsigned int from, unsigned int to) override {
        strip->setPixelColor(to, strip->getPixelColor(from));
    }

    Color getLedColor(unsigned int p) override;

private:
    Adafruit_NeoPixel *strip;
};

template <>
void NeopixelAnimationDisplay<ColorRGB>::setAllLeds(ColorRGB color) {
    strip->fill(Adafruit_NeoPixel::Color(color.r, color.g, color.b));
}

template <>
void NeopixelAnimationDisplay<ColorRGBW>::setAllLeds(ColorRGBW color) {
    strip->fill(Adafruit_NeoPixel::Color(color.r, color.g, color.b, color.w));
}

template <>
void NeopixelAnimationDisplay<ColorRGB>::setLedImpl(unsigned int p, ColorRGB color) {
    strip->setPixelColor(p, color.r, color.g, color.b);
}

template <>
void NeopixelAnimationDisplay<ColorRGBW>::setLedImpl(unsigned int p, ColorRGBW color) {
template <>
ColorRGB NeopixelAnimationDisplay<ColorRGB>::getLedColor(unsigned int p) {
    uint32_t color{strip->getPixelColor(p)};
    return {(uint8_t)(color >> 16), (uint8_t)(color >> 8), (uint8_t)(color)};
}

template <>
ColorRGBW NeopixelAnimationDisplay<ColorRGBW>::getLedColor(unsigned int p) {
    uint32_t color{strip->getPixelColor(p)};
    return {(uint8_t)(color >> 16), (uint8_t)(color >> 8), (uint8_t)(color), (uint8_t)(color >> 24)};
}
#endif
