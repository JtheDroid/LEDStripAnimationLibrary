#pragma once
//#define Color_RGBW

struct Color {
public:
    unsigned int r, g, b;
#ifdef Color_RGBW
    unsigned int w;
#endif
    static const Color RED, GREEN, BLUE, WHITE, BLACK;

    //mix two colors together, proportion decides the amount of each color (0..1) (full color1..full color2)
    static Color mixColors(double proportion, Color color1, Color color2);
};

const Color Color::RED{255, 0, 0};
const Color Color::GREEN{0, 255, 0};
const Color Color::BLUE{0, 0, 255};
const Color Color::WHITE{255, 255, 255};
const Color Color::BLACK{0, 0, 0};

Color Color::mixColors(double proportion, Color color1, Color color2) {
    return Color{(unsigned int) (color1.r + ((int) color2.r - (int) color1.r) * proportion),
                 (unsigned int) (color1.g + ((int) color2.g - (int) color1.g) * proportion),
                 (unsigned int) (color1.b + ((int) color2.b - (int) color1.b) * proportion)
#ifdef Color_RGBW
            , (unsigned int) (color1.w + ((int) color2.w - (int) color1.w) * proportion)
#endif
    };
}
