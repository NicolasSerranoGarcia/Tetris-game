#include "screen.h"

int main(int argv, char *argc[]){
    
    Screen mainScreen(640, 480);
    SDL_Rect rect = {640, 460, 10, 10};


    bool running = true;
    SDL_Event e;


    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = false;
            }
        }

        mainScreen.showSquare(rect, {0,0,0,255});

        //always clear window
        SDL_SetRenderDrawColor(mainScreen.getRender(), 0, 0, 0, 255);
        SDL_RenderPresent(mainScreen.getRender());
    }
    
    return 0;
}