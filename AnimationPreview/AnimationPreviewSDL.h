#pragma once

#include <SDL.h>
#include "SDLcleanup.h"
#include "ColorRGB.h"
#include "FunctionAnimationDisplay.h"

class AnimationPreviewSDL {
private:
    static unsigned int counter;
    bool end{false}, quitCalled{false};
    SDL_Window *window{nullptr};
    SDL_Renderer *renderer{nullptr};
    int xSize{0}, ySize{0};
    unsigned int numPixels;
    FunctionAnimationDisplay<> sdlDisplay{
            numPixels,
            [this](unsigned int pixel, ColorRGB c) { drawLed(pixel, c); },
            [this]() { draw_show(); }};

    void drawRect(int x, int y, int xS, int yS, Uint8 r, Uint8 g, Uint8 b);

    void drawLed(unsigned int index, ColorRGB color);

    static void printError(const char *where);

public:
    explicit AnimationPreviewSDL(unsigned int numPixels);

    FunctionAnimationDisplay<> *getSdlDisplayPtr() { return &sdlDisplay; }

    void begin();

    bool loop();

    void draw_clear();

    void draw_show();

    void quit();

    virtual ~AnimationPreviewSDL();
};
