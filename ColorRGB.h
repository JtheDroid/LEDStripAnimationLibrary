#pragma once

class ColorRGB {
public:
    constexpr ColorRGB() : r(0), g(0), b(0) {}
    constexpr ColorRGB(unsigned int r, unsigned int g, unsigned int b) : r(r), g(g), b(b) {}

    unsigned int r, g, b;
    static ColorRGB RED, GREEN, BLUE, WHITE, BLACK;

    // mix two colors together, proportion decides the amount of each color (0..1) (full color1..full color2)
    constexpr static ColorRGB mixColors(double proportion, ColorRGB &color1, ColorRGB &color2);
};

constexpr ColorRGB ColorRGB::mixColors(double proportion, ColorRGB &color1, ColorRGB &color2) {
    return ColorRGB{(unsigned int)(color1.r + ((int)color2.r - (int)color1.r) * proportion),
                    (unsigned int)(color1.g + ((int)color2.g - (int)color1.g) * proportion),
                    (unsigned int)(color1.b + ((int)color2.b - (int)color1.b) * proportion)};
}

ColorRGB operator*(ColorRGB &color, double value) {
    ColorRGB black{0, 0, 0};
    return ColorRGB::mixColors(value, black, color);
}