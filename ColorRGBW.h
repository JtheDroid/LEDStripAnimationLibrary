#pragma once

#include "ColorRGB.h"

class ColorRGBW : public ColorRGB {
public:
    constexpr ColorRGBW() : ColorRGB{0, 0, 0}, w(0) {}
    constexpr ColorRGBW(unsigned int r, unsigned int g, unsigned int b, unsigned int w) : ColorRGB{r, g, b}, w(w) {}
    constexpr ColorRGBW(unsigned int r, unsigned int g, unsigned int b) : ColorRGB{r, g, b}, w(0) {}

    ColorRGBW(const ColorRGB &rgb, unsigned int w) : ColorRGB{rgb}, w(w) {}

    unsigned int w;

    static ColorRGBW mixColors(double proportion, ColorRGBW &color1, ColorRGBW &color2);
};

ColorRGBW ColorRGBW::mixColors(double proportion, ColorRGBW &color1, ColorRGBW &color2) {
    ColorRGB rgb{ColorRGB::mixColors(proportion, color1, color2)};
    return ColorRGBW{rgb.r, rgb.g, rgb.b, (unsigned int)(color1.w + ((int)color2.w - (int)color1.w) * proportion)};
}

ColorRGBW operator*(ColorRGBW &color, double value) {
    ColorRGBW black{0, 0, 0, 0};
    return ColorRGBW::mixColors(value, black, color);
}
