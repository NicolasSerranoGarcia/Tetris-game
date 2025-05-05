#include "SetScene.h"

#include <iostream>

SetScene::~SetScene(){

}

SetScene::SetScene(){
    //Create the buttons 
    Button rotateButton({SBX, SBY + SBX + 10, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["rotate"] = rotateButton;

    Button leftButton({SBX, SBY + (SBX + 10)*2, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["left"] = leftButton;

    Button rightButton({SBX, SBY + (SBX + 10)*3, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["right"] = rightButton;

    Button downButton({SBX, SBY + (SBX + 10)*4, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["down"] = downButton;

    Button fastDownButton({SBX, SBY + (SBX + 10)*5, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["fastDown"] = fastDownButton;

}

void SetScene::render(){
    if(mainScene != nullptr){
        mainScene->render();
    }
    SDL_Rect settingsRect = {SBX, SBY, SBW, SBH};
    SDL_SetRenderDrawColor(mainScreen.getRender(), NAVY.r, NAVY.g, NAVY.b, NAVY.a);
    SDL_RenderFillRect(mainScreen.getRender(), &settingsRect);
    
    //Render all the buttons
    Font rotateLetter(&mainScreen, "Ubuntu-Regular", SBX, convertKeyToLetter(CONTROLROTATE).c_str(), BLACK);
    getButtonMap()["rotate"].setFont(&rotateLetter);

    
    Font leftLetter(&mainScreen, "Ubuntu-Regular", SBX, convertKeyToLetter(CONTROLLEFT).c_str(), BLACK);
    getButtonMap()["left"].setFont(&leftLetter);
    
    Font rightLetter(&mainScreen, "Ubuntu-Regular", SBX, convertKeyToLetter(CONTROLRIGHT).c_str(), BLACK);
    getButtonMap()["right"].setFont(&rightLetter);
    
    Font downLetter(&mainScreen, "Ubuntu-Regular", SBX, convertKeyToLetter(CONTROLDOWN).c_str(), BLACK);
    getButtonMap()["down"].setFont(&downLetter);
    
    Font fastDownLetter(&mainScreen, "Ubuntu-Regular", SBX, convertKeyToLetter(CONTROLFASTDOWN).c_str(), BLACK);
    getButtonMap()["fastDown"].setFont(&fastDownLetter);

    renderButtons();


}

void SetScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene){
    
    if(mainScene == nullptr){
        mainScene = mScene;
    }

    if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE)){
        delete curScene;
        curScene = mScene;
        return;
    }

    if(getButtonMap()["rotate"].isClicked(&event)){
        //maybe trigger a screen to ask for the input
        bool valid = false;
        SDL_Event newEvent;

        while(!valid){
            while(SDL_PollEvent(&newEvent)){
                if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym != SDLK_ESCAPE)){
                    valid = true;
                    CONTROLROTATE = newEvent.key.keysym.sym;
                    SDL_PushEvent(&newEvent);
                    break;
                }
                 else if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym == SDLK_ESCAPE)){
                    valid = true;
                    break;
                }

            }
        }
    }

    else if(getButtonMap()["left"].isClicked(&event)){
        //maybe trigger a screen to ask for the input
        bool valid = false;
        SDL_Event newEvent;

        while(!valid){
            while(SDL_PollEvent(&newEvent)){
                if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym != SDLK_ESCAPE)){
                    valid = true;
                    CONTROLLEFT = newEvent.key.keysym.sym;
                    SDL_PushEvent(&newEvent);
                    break;
                }
                 else if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym == SDLK_ESCAPE)){
                    valid = true;
                    break;
                }

            }
        }
    }

    if(getButtonMap()["right"].isClicked(&event)){
        //maybe trigger a screen to ask for the input
        bool valid = false;
        SDL_Event newEvent;

        while(!valid){
            while(SDL_PollEvent(&newEvent)){
                if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym != SDLK_ESCAPE)){
                    valid = true;
                    CONTROLRIGHT = newEvent.key.keysym.sym;
                    SDL_PushEvent(&newEvent);
                    break;
                }
                 else if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym == SDLK_ESCAPE)){
                    valid = true;
                    break;
                }

            }
        }
    }

    else if(getButtonMap()["down"].isClicked(&event)){
        //maybe trigger a screen to ask for the input
        bool valid = false;
        SDL_Event newEvent;

        while(!valid){
            while(SDL_PollEvent(&newEvent)){
                if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym != SDLK_ESCAPE)){
                    valid = true;
                    CONTROLDOWN = newEvent.key.keysym.sym;
                    SDL_PushEvent(&newEvent);
                    break;
                }
                 else if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym == SDLK_ESCAPE)){
                    valid = true;
                    break;
                }

            }
        }
    }

    else if(getButtonMap()["fastDown"].isClicked(&event)){
        //maybe trigger a screen to ask for the input
        bool valid = false;
        SDL_Event newEvent;

        while(!valid){
            while(SDL_PollEvent(&newEvent)){
                if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym != SDLK_ESCAPE)){
                    valid = true;
                    CONTROLFASTDOWN = newEvent.key.keysym.sym;
                    SDL_PushEvent(&newEvent);
                    break;
                }
                 else if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym == SDLK_ESCAPE)){
                    valid = true;
                    break;
                }

            }
        }
    }
}

void SetScene::handleLogic(Uint32 *, Scene *&){
    
}

void SetScene::renderButtons(){

    getButtonMap()["rotate"].drawToRender();
    getButtonMap()["left"].drawToRender();
    getButtonMap()["right"].drawToRender();
    getButtonMap()["down"].drawToRender();
    getButtonMap()["fastDown"].drawToRender();

}   