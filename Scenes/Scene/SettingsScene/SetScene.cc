#include "SetScene.h"

SetScene::~SetScene(){

}

SetScene::SetScene(){
    //Create the buttons 
    Button rotateButton({SBX, SBY + SBX + 10, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["rotateRight"] = rotateButton;

    Button leftButton({SBX, SBY + (SBX + 10)*2, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["left"] = leftButton;

    Button rightButton({SBX, SBY + (SBX + 10)*3, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["right"] = rightButton;

    Button downButton({SBX, SBY + (SBX + 10)*4, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["down"] = downButton;

    Button fastDownButton({SBX, SBY + (SBX + 10)*5, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["fastDown"] = fastDownButton;

    Button swapButton({SBX, SBY + (SBX + 10)*6, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["swap"] = swapButton;


}

void SetScene::render(){
    if(mainScene != nullptr){
        mainScene->renderWithoutFigures();
    }
    SDL_Rect settingsRect = {SBX, SBY, SBW, SBH};
    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, LIGHT_GREY.a);
    SDL_RenderFillRect(mainScreen.getRender(), &settingsRect);
    
    //Render all the buttons
    Font rotateLetter(&mainScreen, "Ubuntu-Regular", SBX, convertKeyToLetter(CONTROLROTATERIGHT).c_str(), BLACK);
    getButtonMap()["rotateRight"].setFont(&rotateLetter);

    
    Font leftLetter(&mainScreen, "Ubuntu-Regular", SBX, convertKeyToLetter(CONTROLLEFT).c_str(), BLACK);
    getButtonMap()["left"].setFont(&leftLetter);
    
    Font rightLetter(&mainScreen, "Ubuntu-Regular", SBX, convertKeyToLetter(CONTROLRIGHT).c_str(), BLACK);
    getButtonMap()["right"].setFont(&rightLetter);
    
    Font downLetter(&mainScreen, "Ubuntu-Regular", SBX, convertKeyToLetter(CONTROLDOWN).c_str(), BLACK);
    getButtonMap()["down"].setFont(&downLetter);
    
    Font fastDownLetter(&mainScreen, "Ubuntu-Regular", SBX, convertKeyToLetter(CONTROLFASTDOWN).c_str(), BLACK);
    getButtonMap()["fastDown"].setFont(&fastDownLetter);

    Font swapLetter(&mainScreen, "Ubuntu-Regular", SBX, convertKeyToLetter(CONTROLSWAP).c_str(), BLACK);
    getButtonMap()["swap"].setFont(&swapLetter);

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

    if(getButtonMap()["rotateRight"].isClicked(&event)){
        //maybe trigger a screen to ask for the input
        bool valid = false;
        SDL_Event newEvent;

        while(!valid){
            while(SDL_PollEvent(&newEvent)){
                if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym != SDLK_ESCAPE)){
                    valid = true;
                    CONTROLROTATERIGHT = newEvent.key.keysym.sym;
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
                    break;
                }
                 else if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym == SDLK_ESCAPE)){
                    valid = true;
                    break;
                }

            }
        }
    }

    else if(getButtonMap()["right"].isClicked(&event)){
        //maybe trigger a screen to ask for the input
        bool valid = false;
        SDL_Event newEvent;

        while(!valid){
            while(SDL_PollEvent(&newEvent)){
                if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym != SDLK_ESCAPE)){
                    valid = true;
                    CONTROLRIGHT = newEvent.key.keysym.sym;
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
                    break;
                }
                 else if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym == SDLK_ESCAPE)){
                    valid = true;
                    break;
                }
            }
        }
    }

    else if(getButtonMap()["swap"].isClicked(&event)){
        //maybe trigger a screen to ask for the input
        bool valid = false;
        SDL_Event newEvent;

        while(!valid){
            while(SDL_PollEvent(&newEvent)){
                if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym != SDLK_ESCAPE)){
                    valid = true;
                    CONTROLSWAP = newEvent.key.keysym.sym;
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
    for (auto i = getButtonMap().begin(); i != getButtonMap().end(); i++){
        i->second.drawToRender();
    }
}   