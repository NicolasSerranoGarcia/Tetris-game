#include <iostream>
#include <SDL2/SDL.h>

int main(){

    SDL_Window * window_main = nullptr;
    SDL_Renderer * render = nullptr;

    SDL_Init(SDL_INIT_VIDEO); //initialize SDL library
    SDL_CreateWindowAndRenderer(640*4, 480*4, 0, &window_main, &render); //Initialize window 
    

    return 0;
}