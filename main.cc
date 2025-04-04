#include "Screen/Screen.h"
#include "Font/Font.h"

int main(){
    
    Screen mainScreen(640, 480);

    bool running = true;
    SDL_Event e;


    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = false;
            }
        }
        
        //always clear screen
        mainScreen.clear({0,0,0,255});

        SDL_Delay(16); //allow CPU rest
    }
    
    return 0;
}