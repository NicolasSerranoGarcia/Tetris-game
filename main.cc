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

    SDL_Rect r = {50, 24, 100, 100}; // {x, y, width, height} upper left
    
    bool running = true;
    
    while(running){
        SDL_Event e;
        //setup the current event

        while(SDL_PollEvent(&e)){
            //handle the event
            if(e.type == SDL_QUIT){
                running = false;
            }

            else if(e.type == SDL_KEYDOWN){
            
                switch(e.key.keysym.sym){
                    case SDLK_s:
                        r.y += 10;
                        break;
                    case SDLK_w:
                        r.y -= 10;
                        break;
                    case SDLK_a:
                        r.x -= 10;
                        break;
                    case SDLK_d:
                        r.x += 10;
                        break;
                }
            }

            else if(e.type == SDL_MOUSEMOTION){
                SDL_GetMouseState(&r.x, &r.y);
            }

        }

        //when the event is finished, upload and cleanup the render

        SDL_SetRenderDrawColor(render, 100, 0, 0, 255);
        SDL_RenderFillRect(render, &r);

        SDL_RenderPresent(render); //upload the current frame

        SDL_SetRenderDrawColor(render, 0, 0, 0, 255); //reset the frame
        SDL_RenderClear(render);
        
        SDL_Delay(10);

    }


    return 0;
}