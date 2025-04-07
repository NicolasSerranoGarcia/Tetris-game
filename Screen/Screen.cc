#ifndef SCREEN_CC
#define SCREEN_CC

#include "Screen.h"

//set the static variables

SDL_Window* Screen::window = nullptr;
SDL_Renderer* Screen::render = nullptr;
std::vector<SDL_Texture*> *Screen::textures = nullptr;

//Constructor
Screen::Screen(int w, int h, const char * title) {
    width = w; //initial width and height (maybe I will do resizable window in the future)
    height = h;
    this->title = title;

    if ((window == nullptr) && (render == nullptr)) {
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
        render = SDL_CreateRenderer(window, -1, 0);
    }
}

//Destructor
Screen::~Screen(){
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_DestroyRenderer(render);
    render = nullptr;
    textures = nullptr;
    this->height = 0;
    this->width = 0;
    this->title = {0};

}

//Getter
unsigned int Screen::getWidth() const{
    return this->width;
}

//Getter
unsigned int Screen::getHeight() const{
    return this->height;
}

//Getter
std::string Screen::getTitle() const{
    return title;
}

//Getter
SDL_Window* Screen::getWindow(){
    return window;
}

//Getter
SDL_Renderer* Screen::getRender(){
    return render;
}

//Getter
std::vector<SDL_Texture*>* Screen::getTextures(){
    return textures;
}

//directly shows a sqaure on the window. It will be overlapped with whatever was before
void Screen::showSquare(SDL_Rect rect, SDL_Color color) const{
    SDL_SetRenderDrawColor(getRender(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(getRender(), &rect);
    SDL_RenderPresent(getRender());
}

//This is just a SDL_RenderPresent() inside the class
void Screen::Update(){
    SDL_RenderPresent(getRender());
}

//reset the screen to the given color
void Screen::clear(SDL_Color color){
    SDL_SetRenderDrawColor(getRender(), color.r, color.g, color.b, color.a);
    SDL_RenderClear(getRender());
}

#endif