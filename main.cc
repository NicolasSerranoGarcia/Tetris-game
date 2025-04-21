// SOCIALS:
//  https://linktr.ee/NicolasSerrano
//
//  GITHUB: https://github.com/NicolasSerranoGarcia
//
// ^^Some support would be apreciated^^
//
//
// START DATE OF THE PROJECT: 02/04/2025
//
//
// MADE BY NICOLAS SERRANO GARCÍA - FIRST YEAR COMPUTER ENGINEER AT UNIVERSITY OF ALICANTE (AT DATE OF CREATION)
//
//
// THANKS TO: 
//  - The Builder (https://www.youtube.com/@TheBuilder) for teaching me the basics of SDL
//  - Tetris (https://tetris.com/play-tetris) for letting me visualize and play arround with the mechanics of the game
//  - Google Fonts (https://fonts.google.com/) for the fonts I used in the project
//
//
// ABOUT: This project was made from scratch by me. To be honest, I first thought of doing this project right before finishing two C based projects (Pacman and Snake)
//  which by the way you can also find on my github profile. My first idea was to use the linux command line as a visual engine, also using SDL but on a lower level.
//  Turns out on second semester of first year I'm learning OOP by using C++. I knew SDL was commonly used with C++ so I thought of this.
//
//  When I started coding, I literally knew how to create a class with a .h and .cc, declaring methods on public and atributes on private. Little to nothing. This project has also
//  been a way to learn some more advanced things like object polimorfhism using abstract classes and virtual methods, dynamic pointers... I've had to deal with a lot of header
//  handling so I have also learnt a bit of make. Other things like .gitignore have been really usefull with a project of this size. I've never made something bigger than 2 files.
//  This is also the first time I've used git and Github in the correct way (I think). I really like this tool. Overall, I have learnt a LOT of things. Rn developing games
//  is the most direct way for me of learning. Follow my github to check out on some other projects I'll be developing in the future.
//
//
//  LICENSE: This project has absolutely no license nor it is aimed to profit me in any financial way. If anything, it is a way for me to show my apreciation for retro
//  games and an attempt to recreate one
//
//  Thanks for reading and enjoy my implementation of tetris ;)
//
//


// The general structure of the project consists of several scenes that switch via events (like button presses or death cases). This scenes are supported by auxilary classes
// like Font or Button that implement SDL functionalities in a fast-access way. There's a pointer to the current scene that switches depending on the events.

#include "Font/Font.h"
#include "Button/Button.h"
#include "Scene/Scene.h"
#include "Scene/Scenes.h"        //This is just a file with all the #include "eachScene.h"
#include "constants/constants.h" //Contains things like SDL_Color colors, positioning variables and so

#include <iostream>

Scene *currentScene = new OpScene;
Scene *mainScene = nullptr;

int main()
{
    std::srand(time(NULL));

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() != 0)
    {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        std::cerr << "SDL_Image Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Implement the main program inside a scope to ensure
    // no remainder of classes or objects are left behind
    // without being destroyed
    {
        bool running = true;
        SDL_Event e;

        Uint32 lastTick = SDL_GetTicks();
        while (running)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    running = false;
                }
                currentScene->handleEvents(e, currentScene, mainScene);
            }

            currentScene->handleLogic(&lastTick);

            currentScene->render();

            currentScene->clear();

            SDL_Delay(10);
        }
    }

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}