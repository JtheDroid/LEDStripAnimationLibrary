#include "AnimationPreviewSDL.h"
#include <iostream>

unsigned int AnimationPreviewSDL::counter{0};

AnimationPreviewSDL::AnimationPreviewSDL(unsigned int numPixels) : numPixels(numPixels) {
    begin();
}

void AnimationPreviewSDL::drawRect(int x, int y, int xS, int yS, Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_Rect rect{x, y, xS, yS};
    SDL_RenderFillRect(renderer, &rect);
}

void AnimationPreviewSDL::drawLed(unsigned int index, ColorRGB color) {
    int size = (int) (xSize / numPixels);
    drawRect(size * (int) index, 0, size, ySize, (Uint8) color.r, (Uint8) color.g, (Uint8) color.b);
}

void AnimationPreviewSDL::printError(const char *where) {
    std::cout << where << ": " << SDL_GetError() << std::endl;
}

void AnimationPreviewSDL::begin() {
    if (!counter++)
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            printError("init");
        }
    SDL_Rect screen;
    SDL_GetDisplayUsableBounds(0, &screen);
    xSize = screen.w;
    ySize = (int) (xSize / numPixels);
    if (ySize > screen.h) ySize = screen.h;
    window = SDL_CreateWindow("AnimationPreview", screen.x, (int) (screen.y + 100 * (counter - 1)),
                              xSize, ySize, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window) {
        printError("window");
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        printError("renderer");
        return;
    }
    std::cout << "initialized" << std::endl;
}

bool AnimationPreviewSDL::loop() {
    if (end) return !end;
    SDL_Event e;
    while (SDL_PollEvent(&e))
        switch (e.type) {
            case SDL_QUIT:
                //case SDL_KEYDOWN:
                //case SDL_MOUSEBUTTONDOWN:
                end = true;
                break;
            case SDL_WINDOWEVENT:
                if (SDL_GetWindowID(window) == e.window.windowID) {
                    switch (e.window.event) {
                        case SDL_WINDOWEVENT_RESIZED:
                            xSize = e.window.data1;
                            ySize = e.window.data2;
                            break;
                        case SDL_WINDOWEVENT_CLOSE:
                            end = true;
                            break;
                        default:
                            break;
                    }
                } else {
                    SDL_PushEvent(&e);
                    return !end;
                }
                break;
            default:
                break;
        }
    return !end;
}

void AnimationPreviewSDL::draw_clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void AnimationPreviewSDL::draw_show() {
    SDL_RenderPresent(renderer);
}

void AnimationPreviewSDL::quit() {
    if (quitCalled) return;
    end = quitCalled = true;
    std::cout << "quit" << std::endl;
    cleanup(renderer, window);
    if (!--counter)
        SDL_Quit();
}

AnimationPreviewSDL::~AnimationPreviewSDL() {
    quit();
}
