#include "Font/Font.h"
#include "Button/Button.h"
#include "Scene/Scene.h"
#include "Scene/Scenes.h" //This is just a file with all the #include "eachScene.h"
#include "constants/constants.h" //Contains things like SDL_Color colors, positioning variables and so

#include <iostream>
#include <SDL2/SDL_image.h>

Scene * currentScene = new OpScene;

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

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        std::cerr << "SDL_Image Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    {
        bool running = true;
        SDL_Event e;

        while (running) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    running = false;
                }
                
                currentScene->handleEvents(e);
            }
            
            currentScene->render();

            mainScreen.clear(BLACK);

            SDL_Delay(10);
        }
    }

    TTF_Quit();
    return 0;
}