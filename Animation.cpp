#include "Animation.h"

template<class Color>
void Animation<Color>::setLeds(unsigned int p1, unsigned int p2, Color color) {
    if (p1 >= ledNum) p1 = ledNum - 1;
    if (p2 >= ledNum) p2 = ledNum - 1;
    if (p2 < p1) p2 = p1;
    for (unsigned int p = p1; p <= p2; ++p) setLed(p, color);
}

template<class Color>
void Animation<Color>::setLedsTransition(unsigned int p1, unsigned int p2, Color color1, Color color2) {
    if (p2 < p1) p2 = p1;
    int origLength{(int) (p2 - p1)};
    if (p1 >= ledNum) p1 = ledNum - 1;
    if (p2 >= ledNum) p2 = ledNum - 1;
    int length{(int) (p2 - p1)};
    for (int i = 0; i <= length; ++i) {
        double portion{i * 1.0 / origLength};
        setLed(p1 + i, Color::mixColors(portion, color1, color2));
    }

}