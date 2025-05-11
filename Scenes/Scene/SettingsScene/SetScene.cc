#include "SetScene.h"

SetScene::~SetScene(){

}

SetScene::SetScene(){
    //Create the buttons 
    Button rotateButtonR({SBX + SBW/2, SBY + SBX + 10, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["rotateRight"] = rotateButtonR;

    Button rotateButtonL({SBX + SBW/2, SBY + (SBX + 10)*2, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["rotateLeft"] = rotateButtonL;

    Button leftButton({SBX + SBW/2, SBY + (SBX + 10)*3, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["left"] = leftButton;

    Button rightButton({SBX + SBW/2, SBY + (SBX + 10)*4, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["right"] = rightButton;

    Button downButton({SBX + SBW/2, SBY + (SBX + 10)*5, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["down"] = downButton;

    Button fastDownButton({SBX + SBW/2, SBY + (SBX + 10)*6, SBW/2, SBX}, WHITE, &mainScreen);
    getButtonMap()["fastDown"] = fastDownButton;

    Button swapButton({SBX + SBW/2, SBY + (SBX + 10)*7, SBW/2, SBX}, WHITE, &mainScreen);
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

    Font rotateLetterR(&mainScreen, "Ubuntu-Regular", SBX, convertKeyToLetter(CONTROLROTATERIGHT).c_str(), BLACK);
    rotateLetterR.setCoords(getButtonMap()["rotateRight"].getContainer().x + getButtonMap()["rotateRight"].getContainer().w/2 - rotateLetterR.getTextSurface()->w/2,
                            getButtonMap()["rotateRight"].getContainer().y + getButtonMap()["rotateRight"].getContainer().h/2 - rotateLetterR.getTextSurface()->h/2);
    getButtonMap()["rotateRight"].setFont(&rotateLetterR);
                            
    Font rotateLetterL(&mainScreen, "Ubuntu-Regular", SBX, convertKeyToLetter(CONTROLROTATELEFT).c_str(), BLACK);
    getButtonMap()["rotateLeft"].setFont(&rotateLetterL);
    
    
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
        bool valid = false;
        SDL_Event newEvent;
        
        renderKeyBindChange();
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

    else if(getButtonMap()["rotateLeft"].isClicked(&event)){
        
        bool valid = false;
        SDL_Event newEvent;
        
        renderKeyBindChange();
        while(!valid){
            while(SDL_PollEvent(&newEvent)){
                if((newEvent.type == SDL_KEYDOWN) && (newEvent.key.keysym.sym != SDLK_ESCAPE)){
                    valid = true;
                    CONTROLROTATELEFT = newEvent.key.keysym.sym;
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
        
        bool valid = false;
        SDL_Event newEvent;
        
        renderKeyBindChange();
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
        
        bool valid = false;
        SDL_Event newEvent;
        
        renderKeyBindChange();
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
        
        bool valid = false;
        SDL_Event newEvent;
        
        renderKeyBindChange();
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
        
        bool valid = false;
        SDL_Event newEvent;
        
        renderKeyBindChange();
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
        
        bool valid = false;
        SDL_Event newEvent;
        
        renderKeyBindChange();
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


//FUNCTIONS

void renderKeyBindChange(){
    SDL_Rect rect = {0,0, SBW/2, SBH/2};
    rect.x = py(AbsPosition::POS_CENTER, rect.w);
    rect.y = py(AbsPosition::POS_CENTER, rect.h);

    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_BLUE.r, LIGHT_BLUE.g, LIGHT_BLUE.b, LIGHT_BLUE.a);
    SDL_RenderFillRect(mainScreen.getRender(), &rect);
    Font font(&mainScreen, "Ubuntu-BoldItalic", 30, "Press any key", BLACK);
    font.setCoords(AbsPosition::POS_CENTER);
    font.drawTextToRender(); 

    SDL_RenderPresent(mainScreen.getRender());
}
