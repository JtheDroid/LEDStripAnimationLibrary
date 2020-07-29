#pragma once

class ColorRGB {
public:
    constexpr ColorRGB(unsigned int r, unsigned int g, unsigned int b) : r(r), g(g), b(b) {}

    unsigned int r, g, b;
    static const ColorRGB RED, GREEN, BLUE, WHITE, BLACK;

    //mix two colors together, proportion decides the amount of each color (0..1) (full color1..full color2)
    constexpr static ColorRGB mixColors(double proportion, ColorRGB &color1, ColorRGB &color2);
};

constexpr ColorRGB ColorRGB::RED{255, 0, 0};
constexpr ColorRGB ColorRGB::GREEN{0, 255, 0};
constexpr ColorRGB ColorRGB::BLUE{0, 0, 255};
constexpr ColorRGB ColorRGB::WHITE{255, 255, 255};
constexpr ColorRGB ColorRGB::BLACK{0, 0, 0};

constexpr ColorRGB ColorRGB::mixColors(double proportion, ColorRGB &color1, ColorRGB &color2) {
    return ColorRGB{(unsigned int) (color1.r + ((int) color2.r - (int) color1.r) * proportion),
                    (unsigned int) (color1.g + ((int) color2.g - (int) color1.g) * proportion),
                    (unsigned int) (color1.b + ((int) color2.b - (int) color1.b) * proportion)
    };
}