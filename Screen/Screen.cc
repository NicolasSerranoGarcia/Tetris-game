#include "screen.h"

SDL_Window *window = nullptr; // creates a window
SDL_Renderer *render = nullptr; //creates a render
std::vector <SDL_Texture> * textures = NULL;


Screen::Screen(int w, int h){ //constructor

    SDL_CreateWindowAndRenderer(w, h, 0, &window, &render); //load the render and the window

    SDL_Init(SDL_INIT_EVERYTHING); //initialize SDL library
}

unsigned int Screen::getWidth(){ //getter
    return this->width;
}

unsigned int Screen::getHeight(){ //getter
    return this->height;
}

SDL_Window * Screen::getWindow(){ //getter
    return window;
}

SDL_Renderer * Screen::getRender(){ //getter
    return render;
}

std::vector <SDL_Texture> * getTextures(){ //getter
    return textures;
}

void Screen::showSquare(SDL_Rect rect, SDL_Color color){
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(render, &rect);
    SDL_RenderPresent(render);
}   