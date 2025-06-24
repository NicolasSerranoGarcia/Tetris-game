#ifndef SCREEN_CC
#define SCREEN_CC

#include "Screen.h"

//set static variables

SDL_Window * Screen::window = nullptr;
SDL_Renderer * Screen::render = nullptr;
std::vector<SDL_Texture*> Screen::textures;


Screen::Screen(int w, int h, const char * title) {
    width = w;
    height = h;
    this->title = title;

    //handle errors
    if ((window == nullptr) && (render == nullptr)) {
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
        render = SDL_CreateRenderer(window, -1, 0);
    }
}

Screen::~Screen(){
    //SDL destructors
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);

    for(int i = 0; i < (int) textures.size(); i++){
        SDL_DestroyTexture(textures[i]);
    }
    
    //Make sure the pointers are correctly reset
    window = nullptr;
    render = nullptr;

    height = 0;
    width = 0;
    title = "";
}


int Screen::getWidth() const{
    return width;
}

int Screen::getHeight() const{
    return height;
}

std::string Screen::getTitle() const{
    return title;
}

SDL_Window* Screen::getWindow(){
    return window;
}

SDL_Renderer* Screen::getRender(){
    return render;
}

std::vector<SDL_Texture*> Screen::getTextures(){
    return textures;
}


void Screen::setWidth(int w){
    width = w;
}

void Screen::setHeight(int h){
    height = h;
}

void Screen::setTitle(int title){
    this->title = title;
}


void Screen::showSquare(SDL_Rect rect, SDL_Color color) const{
    SDL_SetRenderDrawColor(getRender(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(getRender(), &rect);
    SDL_RenderPresent(getRender());
}

void Screen::clear(SDL_Color color){
    SDL_SetRenderDrawColor(getRender(), color.r, color.g, color.b, color.a);
    SDL_RenderClear(getRender());
}

#endif