// SOCIALS:
//  https://linktr.ee/NicolasSerrano
//
//  GITHUB: https://github.com/NicolasSerranoGarcia
//
// ^^Some support would be appreciated^^
//
//
// START DATE OF THE PROJECT: 02/04/2025
//
//
// MADE BY NICOLAS SERRANO GARCIA - FIRST YEAR COMPUTER ENGINEER AT UNIVERSITY OF ALICANTE (AT DATE OF CREATION)
//
//
// THANKS TO/ ATTRIBUTIONS: 
//  - The Builder (https://www.youtube.com/@TheBuilder) for teaching me the basics of SDL
//  - Tetris (https://tetris.com/play-tetris) for letting me visualize and play around with the mechanics of the game
//  - Google Fonts (https://fonts.google.com/) for the fonts I used in the project
//  - CodeCogs (https://editor.codecogs.com/) for letting me create visual formulas in LaTex
//  - Gumichan01 (https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c) for creating functions to render a circle (magic)
//  - The logo of linktree https://iconscout.com/icons/linktree by "https://iconscout.com/contributors/ihdizein" on https://iconscout.com/
//  - Programming 2 class from my University, for teaching me the basics of C++
//  - Explosion Sound retro explosion 4 sfx by stumpbutt -- https://freesound.org/s/630060/ -- License: Creative Commons 0
//  - menu hover 3 by EtherAudio -- https://freesound.org/s/750190/ -- License: Attribution 4.0
//  - countdown-click.wav by Troube -- https://freesound.org/s/631547/ -- License: Creative Commons 0
//  - Pix on youtube for it's playlist on 8 bit ambient music https://www.youtube.com/playlist?list=PLdsGes2mFh92eHpOZVJQgoubb6rF0CcvU
//    His channel https://www.youtube.com/@Pixverses
//  
//
// ABOUT: This project was made from scratch by me. To be honest, I first thought of doing this project right before finishing two C based projects (Pacman and Snake)
//  which by the way you can also find on my github profile. My first idea was to use the linux command line as a visual engine, also using SDL but on a lower level.
//  Turns out on second semester of first year I'm learning OOP by using C++. I knew SDL was commonly used with C++ so I thought of this.
//
//  When I started coding, I literally knew how to create a class with a .h and .cc, declaring methods on public and atributes on private. Little to nothing. This project has also
//  been a way to learn some more advanced things like object polymorphism using abstract classes and virtual methods, dynamic pointers... I've had to deal with a lot of header
//  handling so I have also learnt a bit of make. Other things like .gitignore have been really usefull with a project of this size. I've never made something bigger than 2 files.
//  This is also the first time I've used git and Github in the correct way (I think). I really like this tool. Overall, I have learnt a LOT of things. Rn developing games
//  is the most direct way for me to learn. Follow my github to check out on some other projects I'll be developing in the future.
//
//
//  LICENSE: This project has absolutely no license nor it is aimed to profit me in any financial way. If anything, it is a way for me to show my appreciation for retro
//  games and an attempt to recreate one
//
//  Thanks for reading and enjoy my implementation of tetris ;)
//
//


// The general structure of the project consists of several scenes that switch via events (like button presses or death cases). This scenes are supported by auxilary classes
// like Font or Button that implement SDL functionalities in a fast-access way. There's a pointer to the current scene that switches depending on the events.

#include "Scenes/SceneF/Scene.h" //The father class of the Scenes
#include "Scenes/Scenes.h"        //This is just a file with all the #include "eachScene.h"
#include "constants/constants.h" //Contains things like SDL_Color colors, positioning variables and so

#include <iostream>

Scene *currentScene = new OpScene;
Scene *mainScene = nullptr;

std::string getRandomMusic();

int main(){

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0){
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() != 0){
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0){
        std::cerr << "SDL_Image Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    if(Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK) == 0){
        std::cerr << "SDL_Mix Error: " << Mix_GetError() << std::endl;
        Mix_Quit();
        return -1; 
    }

    Mix_AllocateChannels(16);

    
    // Implement the main program inside a scope to ensure
    // no remainder of classes or objects are left behind
    // without being destroyed
    {

        //play some music ;)

            Sound backgroundMusic;
            backgroundMusic.load(getRandomMusic());
            backgroundMusic.setVolume(GENERALSOUNDLVL);
            backgroundMusic.play();


        bool running = true;
        SDL_Event event;

        Uint32 lastTick = SDL_GetTicks();

        while (running){
            while (SDL_PollEvent(&event)){

                if (event.type == SDL_QUIT){
                    running = false;
                }

                currentScene->handleEvents(event, currentScene, mainScene);
            }

            currentScene->handleLogic(&lastTick, currentScene, mainScene);
            
            currentScene->render();

            currentScene->update(mainScreen.getRender());

            // currentScene->clear();


            //Make sure the music always plays and that the 
            //volume is correctly set

                if(!backgroundMusic.isPlaying()){
                    backgroundMusic.load(getRandomMusic());
                    backgroundMusic.play();
                }
                
                backgroundMusic.setVolume(GENERALSOUNDLVL);
        }
    }

    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}