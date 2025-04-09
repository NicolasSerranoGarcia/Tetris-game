#include "Font/Font.h"
#include "Button/Button.h"
#include "Scene/Scene.h"
#include "Scene/Scenes.h" //This is just a file with all the #include "eachScene.h"
#include "constants/constants.h" //Contains things like SDL_Color colors, positioning variables and so

#include <iostream>
#include <SDL2/SDL_image.h>

//TODO: Implement a way to render distinct scenes. To be able to call all the methods of the child classes with the same pointer, all the child clases (opScene, mainScene...)
//are handled by the same three methods (or more if there are common paterns), render, update and clear. Render will handle all the logic inside it with the help of C style
//functions and other classes like Font or Button (or Figure for tetris blocks in the future maybe). This way, the main file (this) will just consist of a finite state machine
//where I update the global pointer by checking certain key points like a pressed button or an edge case like the player lost. 
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
        std::cerr << "Error al inicializar SDL_image: " << IMG_GetError() << std::endl;
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