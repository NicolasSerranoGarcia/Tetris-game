#include "Screen.h"

SDL_Window* Screen::window = nullptr;
SDL_Renderer* Screen::render = nullptr;
std::vector<SDL_Texture*> Screen::textures;

Screen::Screen(int w, int h) {
    width = w; //initial width and height
    height = h;

    if ((window == nullptr) && (render == nullptr)) {
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        render = SDL_CreateRenderer(window, -1, 0);
    }
}

unsigned int Screen::getWidth() {
    return width;
}

unsigned int Screen::getHeight() {
    return height;
}

SDL_Window* Screen::getWindow() {
    return window;
}

SDL_Renderer* Screen::getRender() {
    return render;
}

std::vector<SDL_Texture*>* Screen::getTextures() {
    return &textures;
}

//directly shows a sqaure on the window. It will be overlapped with whatever was before. To add a square to the scene use addSquare()
void Screen::showSquare(SDL_Rect rect, SDL_Color color) {
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(render, &rect);
    SDL_RenderPresent(render);
}