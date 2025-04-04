#include "Screen/Screen.h"

int main(){
    
    Screen mainScreen(640, 480);
    SDL_Rect rect = {300, 200, 50, 50};

    bool running = true;
    SDL_Event e;


    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = false;
            }
        }
        SDL_SetRenderDrawColor(mainScreen.getRender(), 0, 0, 0, 255);
        SDL_RenderClear(mainScreen.getRender());
        mainScreen.showSquare(rect, {255,255,255,255});
        
        //always clear window
        SDL_SetRenderDrawColor(mainScreen.getRender(), 0, 0, 0, 255);
        SDL_RenderClear(mainScreen.getRender());

        SDL_Delay(16);
    }
    
    return 0;
}