#pragma once

#include "ColorRGB.h"

class ColorRGBW : public ColorRGB {
public:
    constexpr ColorRGBW(unsigned int r, unsigned int g, unsigned int b, unsigned int w) : ColorRGB{r, g, b}, w(w) {}

    constexpr ColorRGBW(const ColorRGB &rgb, unsigned int w) : ColorRGB{rgb}, w(w) {}

    unsigned int w;

    constexpr static ColorRGBW mixColors(double proportion, ColorRGBW &color1, ColorRGBW &color2);
};

constexpr ColorRGBW ColorRGBW::mixColors(double proportion, ColorRGBW &color1, ColorRGBW &color2) {
    ColorRGB rgb{ColorRGB::mixColors(proportion, color1, color2)};
    return ColorRGBW{
            rgb.r, rgb.g, rgb.b,
            (unsigned int) (color1.w + ((int) color2.w - (int) color1.w) * proportion)};
}
