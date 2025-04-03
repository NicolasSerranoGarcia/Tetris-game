#include <iostream>
#include <SDL2/SDL.h>

    using namespace std;

int main(){

    SDL_Window * window_main = nullptr;
    SDL_Renderer * render = nullptr;

    SDL_Init(SDL_INIT_VIDEO); //initialize SDL library
    SDL_CreateWindowAndRenderer(640, 480, 0, &window_main, &render); //Initialize window 

    SDL_SetRenderDrawColor(render, 0, 0, 0, 255); //set background to black
    SDL_RenderClear(render);

    auto red_texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1000, 1000); //create a texture

    auto blue_texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1000, 1000);

    SDL_SetRenderTarget(render, red_texture); //change the scope of the renderer to a particular texture

    SDL_SetRenderDrawColor(render, 255, 0, 0 , 255); //set the render (our texture currently) to color red
    SDL_RenderClear(render); //on the background (not showing anything to the user), set the color of the texture to red


    SDL_SetRenderTarget(render, blue_texture);
    SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
    SDL_RenderClear(render);

    SDL_SetRenderTarget(render, nullptr); //set the render target back to the main window

    SDL_RenderCopy(render, red_texture, nullptr, nullptr);

    SDL_RenderPresent(render);

    SDL_Delay(5000);

    SDL_RenderCopy(render, blue_texture, nullptr, nullptr);

    SDL_RenderPresent(render);

    SDL_Delay(5000);

    return 0;
}

    