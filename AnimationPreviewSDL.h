#pragma once

#include <SDL.h>
#include "SDLcleanup.h"
#include <iostream>

class AnimationPreviewSDL {
private:
    bool end{false};
    SDL_Window *window{nullptr};
    SDL_Renderer *renderer{nullptr};
    int xSize{0}, ySize{0};

    static void printError(const char *where) {
        std::cout << where << ": " << SDL_GetError() << std::endl;
    }

public:
    AnimationPreviewSDL() {
        begin();
    }

    void begin() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            printError("init");
        }
        int w = 500, h = 500;
        xSize = w;
        ySize = h;
        window = SDL_CreateWindow("AnimationTest", 100, 100, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

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

    bool loop() {
        SDL_Event e;
        while (SDL_PollEvent(&e))
            switch (e.type) {
                case SDL_QUIT:
                    //case SDL_KEYDOWN:
                    //case SDL_MOUSEBUTTONDOWN:
                    end = true;
                    break;
                case SDL_WINDOWEVENT:
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                        xSize = e.window.data1;
                        ySize = e.window.data2;
                    }
                    break;
            }
        //draw();
        return !end;
    }


    void draw_clear() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void draw_show() {
        SDL_RenderPresent(renderer);
    }

    void draw_rect(int x, int y, int xS, int yS, Uint8 r, Uint8 g, Uint8 b) {
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_Rect rect{x, y, xS, yS};
        SDL_RenderFillRect(renderer, &rect);
    }

    void quit() {
        std::cout << "quit" << std::endl;
        cleanup(renderer, window);
        SDL_Quit();
    }

    virtual ~AnimationPreviewSDL() {
        quit();
    }

    int getXSize() const {
        return xSize;
    }

    int getYSize() const {
        return ySize;
    }
};