#include "Screen/Screen.h"
#include "Font/Font.h"
#include "Button/Button.h"

#include <iostream>

#define RED {255, 0, 0, 255}
#define GREEN {0, 255, 0, 255}
#define BLUE {0, 0, 255, 255}
#define BLACK {0, 0, 0, 255}
#define WHITE {255, 255, 255, 255}

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
        Screen mainScreen(640, 480, "Tetris");
        Font Title(&mainScreen, "BungeeTint-Regular", 90, "TETRIS", RED);
        Font Play(&mainScreen, "Ubuntu-Bold", 60, "PLAY", BLACK);
        Button playButton({240, 240, 160, 70}, WHITE, &mainScreen);
        playButton.setFont(&Play);

        bool running = true;
        SDL_Event e;

        while (running) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    running = false;
                }
            }

            mainScreen.clear(BLACK);
            Title.drawTextToRender(Font::FONT_CENTER_UP);
            playButton.drawToRender();
            mainScreen.Update();

            if (playButton.isClicked()) {
                //implement the functionality to change renders or screens
            }

            SDL_Delay(10);
        }
    }

    TTF_Quit();
    return 0;
}