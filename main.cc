#include "Screen/Screen.h"
#include "Font/Font.h"
#include "Button/Button.h"
#include "Scene/Scene.h"
#include "Scene/Scenes.h" //This is just a file with all the #include "eachScene.h"
#include "constants/constants.h" //Contains things like SDL_Color colors, positioning variables and so

#include <iostream>

//TODO: Implement a way to render distinct scenes. To be able to call all the methods of the child classes with the same pointer, all the child clases (opScene, mainScene...)
//are handled by the same three methods (or more if there are common paterns), render, update and clear. Render will handle all the logic inside it with the help of C style
//functions and other classes like Font or Button (or Figure for tetris blocks in the future maybe). This way, the main file (this) will just consist of a finite state machine
//where I update the global pointer by checking certain key points like a pressed button or an edge case like the player lost. 
Scene * currentScene = nullptr;



int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    //make sure the events are closed in the correct order
    {
        Screen mainScreen(SCREENWIDTH, SCREENHEIGHT, "Tetris");
        Font Title(&mainScreen, "BungeeTint-Regular", 90, "TETRIS", RED);
        Font Play(&mainScreen, "Ubuntu-Bold", 60, "PLAY", BLACK);
        Button playButton({px(Rposition::POS_CENTER_DOWN, 160), py(Rposition::POS_CENTER_LEFT, 70), 160, 70}, WHITE, &mainScreen);
        playButton.setFont(&Play);

        bool running = true;
        SDL_Event e;

        while (running) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    running = false;
                }

                if (playButton.isClicked(&e)) {
                    //implement the functionality to change renders or screens
                    std::cout << "Hello World" << std::endl;
                }
                
            }
            
            Title.drawTextToRender(Rposition::POS_CENTER_UP);
            playButton.drawToRender();
            SDL_RenderPresent(mainScreen.getRender());
            
            mainScreen.clear(BLACK);

            SDL_Delay(10);
        }
    }

    TTF_Quit();
    return 0;
}