#include "Screen/Screen.h"
#include "Font/Font.h"

#define RED {255, 0, 0, 255}
#define GREEN {0, 255, 0, 255}
#define BLUE {0, 0, 255, 255}
#define BLACK {0, 0, 0, 255}
#define WHITE {255, 255, 255, 255}


int main(){
    
    Screen mainScreen(640, 480, "Tetris");
    Font text(&mainScreen, "BungeeTint-Regular", 90, "Tetris", RED);

    bool running = true;
    SDL_Event e;


    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = false;
            }
        }

        text.drawTextToRender(Font::FONT_CENTER_UP);
        mainScreen.Update();

        //I should draw a square that can be pressed and that has a text inside with "Play". 


        //always clear screen
        mainScreen.clear({0,0,0,255});

        SDL_Delay(16); //allow CPU rest
    }
    
    return 0;
}