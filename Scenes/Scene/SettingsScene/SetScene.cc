#include "SetScene.h"

#include <iostream>

SetScene::~SetScene(){

}

SetScene::SetScene(){

    //Create the buttons 
    Button rotateButtonR({(SBW*3)/4 + SBX - (SBW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + SBY + SBX + 10, SBW/3 + BLOCKLENGTH, SBX}, WHITE, &mainScreen);
    getButtonMap()["rotateRight"] = rotateButtonR;

    Button rotateButtonL({(SBW*3)/4 + SBX - (SBW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + SBY + (SBX + 10)*2, SBW/3 + BLOCKLENGTH, SBX}, WHITE, &mainScreen);
    getButtonMap()["rotateLeft"] = rotateButtonL;

    Button leftButton({(SBW*3)/4 + SBX - (SBW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + SBY + (SBX + 10)*3, SBW/3 + BLOCKLENGTH, SBX}, WHITE, &mainScreen);
    getButtonMap()["left"] = leftButton;

    Button rightButton({(SBW*3)/4 + SBX - (SBW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + SBY + (SBX + 10)*4, SBW/3 + BLOCKLENGTH, SBX}, WHITE, &mainScreen);
    getButtonMap()["right"] = rightButton;

    Button downButton({(SBW*3)/4 + SBX - (SBW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + SBY + (SBX + 10)*5, SBW/3 + BLOCKLENGTH, SBX}, WHITE, &mainScreen);
    getButtonMap()["down"] = downButton;

    Button fastDownButton({(SBW*3)/4 + SBX - (SBW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + SBY + (SBX + 10)*6, SBW/3 + BLOCKLENGTH, SBX}, WHITE, &mainScreen);
    getButtonMap()["fastDown"] = fastDownButton;

    Button swapButton({(SBW*3)/4 + SBX - (SBW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + SBY + (SBX + 10)*7, SBW/3 + BLOCKLENGTH, SBX}, WHITE, &mainScreen);
    getButtonMap()["swap"] = swapButton;
}

SDL_Rect SetScene::getSourceRect(){
    return sourceRect;
}

void SetScene::setSourceRect(SDL_Rect rect){
    sourceRect = rect;
}

int SetScene::getDeltaY(){
    return deltaY;
}

void SetScene::setDeltaY(int y){
    deltaY = y;
}

void SetScene::render(){
    if(mainScene != nullptr){
        mainScene->renderWithoutFigures();
    }

    auto map = getButtonMap();
    Button rotateButtonR({(SBW*3)/4 - (SBW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + SBX + 10, SBW/3 + BLOCKLENGTH, SBX}, WHITE, &mainScreen);
    map["rotateRight"] = rotateButtonR;

    Button rotateButtonL({(SBW*3)/4 - (SBW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + (SBX + 10)*2, SBW/3 + BLOCKLENGTH, SBX}, WHITE, &mainScreen);
    map["rotateLeft"] = rotateButtonL;

    Button leftButton({(SBW*3)/4 - (SBW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + (SBX + 10)*3, SBW/3 + BLOCKLENGTH, SBX}, WHITE, &mainScreen);
    map["left"] = leftButton;

    Button rightButton({(SBW*3)/4 - (SBW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + (SBX + 10)*4, SBW/3 + BLOCKLENGTH, SBX}, WHITE, &mainScreen);
    map["right"] = rightButton;

    Button downButton({(SBW*3)/4 - (SBW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + (SBX + 10)*5, SBW/3 + BLOCKLENGTH, SBX}, WHITE, &mainScreen);
    map["down"] = downButton;

    Button fastDownButton({(SBW*3)/4 - (SBW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + (SBX + 10)*6, SBW/3 + BLOCKLENGTH, SBX}, WHITE, &mainScreen);
    map["fastDown"] = fastDownButton;

    Button swapButton({(SBW*3)/4 - (SBW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + (SBX + 10)*7, SBW/3 + BLOCKLENGTH, SBX}, WHITE, &mainScreen);
    map["swap"] = swapButton;

	SDL_Texture* texture = SDL_CreateTexture(mainScreen.getRender(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SBW, SBH + 200);
    SDL_SetRenderTarget(mainScreen.getRender(), texture);
    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, LIGHT_GREY.a);
    SDL_RenderClear(mainScreen.getRender());

    SDL_Rect settingsRect = {SBX, SBY, SBW, SBH};
    // SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, LIGHT_GREY.a);
    // SDL_RenderFillRect(mainScreen.getRender(), &settingsRect);
    

    //Render a title for the keybinds
    Font keyBindText(&mainScreen, "Ubuntu-Regular", 50, "KEYBINDS", BLACK);
    keyBindText.setCoords(SBW/2 - keyBindText.getTextSurface()->w/2, 5);

    keyBindText.drawTextToRender();

    //Render all the buttons

    Font rotateLetterR(&mainScreen, "Ubuntu-Regular", SBX - 13, convertKeyToLetter(CONTROLROTATERIGHT).c_str(), BLACK);
    map["rotateRight"].setFont(&rotateLetterR);
                            
    Font rotateLetterL(&mainScreen, "Ubuntu-Regular", SBX - 13, convertKeyToLetter(CONTROLROTATELEFT).c_str(), BLACK);
    map["rotateLeft"].setFont(&rotateLetterL);
    
    
    Font leftLetter(&mainScreen, "Ubuntu-Regular", SBX - 13, convertKeyToLetter(CONTROLLEFT).c_str(), BLACK);
    map["left"].setFont(&leftLetter);
    
    Font rightLetter(&mainScreen, "Ubuntu-Regular", SBX - 13, convertKeyToLetter(CONTROLRIGHT).c_str(), BLACK);
    map["right"].setFont(&rightLetter);
    
    Font downLetter(&mainScreen, "Ubuntu-Regular", SBX - 13, convertKeyToLetter(CONTROLDOWN).c_str(), BLACK);
    map["down"].setFont(&downLetter);
    
    Font fastDownLetter(&mainScreen, "Ubuntu-Regular", SBX - 13, convertKeyToLetter(CONTROLFASTDOWN).c_str(), BLACK);
    map["fastDown"].setFont(&fastDownLetter);

    Font swapLetter(&mainScreen, "Ubuntu-Regular", SBX - 13, convertKeyToLetter(CONTROLSWAP).c_str(), BLACK);
    map["swap"].setFont(&swapLetter);

    Font rotateRText(&mainScreen, "Ubuntu-Regular", SBX - 15, "Rotate right", BLACK);
    rotateRText.setCoords(SBW/4 - rotateRText.getTextSurface()->w/2, map["rotateRight"].getContainer().y);
    rotateRText.drawTextToRender();

    Font rotateLText(&mainScreen, "Ubuntu-Regular", SBX - 15, "Rotate left", BLACK);
    rotateLText.setCoords(SBW/4 - rotateLText.getTextSurface()->w/2, map["rotateLeft"].getContainer().y);
    rotateLText.drawTextToRender();


    Font moveLeftText(&mainScreen, "Ubuntu-Regular", SBX - 15, "Move left", BLACK);
    moveLeftText.setCoords(SBW/4 - moveLeftText.getTextSurface()->w/2, map["left"].getContainer().y);
    moveLeftText.drawTextToRender();

    Font moveRightText(&mainScreen, "Ubuntu-Regular", SBX - 15, "Move right", BLACK);
    moveRightText.setCoords(SBW/4 - moveRightText.getTextSurface()->w/2, map["right"].getContainer().y);
    moveRightText.drawTextToRender();


    Font moveDownText(&mainScreen, "Ubuntu-Regular", SBX - 15, "Move down", BLACK);
    moveDownText.setCoords(SBW/4 - moveDownText.getTextSurface()->w/2, map["down"].getContainer().y);
    moveDownText.drawTextToRender();

    Font fastDropText(&mainScreen, "Ubuntu-Regular", SBX - 15, "Fast drop", BLACK);
    fastDropText.setCoords(SBW/4 - fastDropText.getTextSurface()->w/2, map["fastDown"].getContainer().y);
    fastDropText.drawTextToRender();

    Font swapText(&mainScreen, "Ubuntu-Regular", SBX - 15, "Swap figure", BLACK);
    swapText.setCoords(SBW/4 - swapText.getTextSurface()->w/2, map["swap"].getContainer().y);
    swapText.drawTextToRender();
    renderButtons(map);

    SDL_SetRenderTarget(mainScreen.getRender(), nullptr);
    
    SDL_Rect rect = getSourceRect();
    SDL_RenderCopy(mainScreen.getRender(), texture, &rect, &settingsRect);

    SDL_DestroyTexture(texture);
}

void SetScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene){
    
    if(mainScene == nullptr){
        mainScene = mScene;
    }
    
    
    if((event.type != SDL_KEYDOWN) && (event.type != SDL_KEYUP) && (event.type != SDL_MOUSEBUTTONDOWN) && (event.type != SDL_MOUSEWHEEL)){
        return;
    }

    if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE)){
        delete curScene;
        curScene = mScene;
        return;
    }

    int delta;
    if (event.type == SDL_MOUSEWHEEL && event.wheel.y != 0) {
        
        SDL_Rect newSrc = getSourceRect();
        int scrollDir = event.wheel.y / abs(event.wheel.y); //-1 or 1
        delta = SCROLLFACTOR * scrollDir;

        int newY = newSrc.y - delta;
    
        if (scrollDir == -1) {
            // Scrolling towards me
            if (newY + newSrc.h <= SBH + 200){
                newSrc.y = newY;
            }
        } else {
            // Scrolling away from me
            if (newY >= 0) {
                newSrc.y = newY;
            }
        }
        setDeltaY(newY);
        setSourceRect(newSrc);
    }
    
    auto maps = getButtonMap();
    for(auto i = maps.begin(); i != maps.end(); i++){
        SDL_Rect rect = i->second.getContainer();
        if((sourceRect.y == 0)){
            rect.y += getDeltaY();
        } 
        else if(((sourceRect.y) == (200))){
            rect.y += SCROLLFACTOR;
        }
        rect.y -= getDeltaY();
        i->second.setContainer(rect);
    }
    
    if(maps["rotateRight"].isClicked(&event)){
        bool valid = false;
        SDL_Event newEvent;
        
        renderKeyBindChange(maps["rotateRight"]);
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

    else if(maps["rotateLeft"].isClicked(&event)){
        
        bool valid = false;
        SDL_Event newEvent;
        
        renderKeyBindChange(maps["rotateLeft"]);
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

    else if(maps["left"].isClicked(&event)){
        
        bool valid = false;
        SDL_Event newEvent;
        
        renderKeyBindChange(maps["left"]);
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

    else if(maps["right"].isClicked(&event)){
        
        bool valid = false;
        SDL_Event newEvent;
        
        renderKeyBindChange(maps["right"]);
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

    else if(maps["down"].isClicked(&event)){
        
        bool valid = false;
        SDL_Event newEvent;
        
        renderKeyBindChange(maps["down"]);
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

    else if(maps["fastDown"].isClicked(&event)){
        
        bool valid = false;
        SDL_Event newEvent;
        
        renderKeyBindChange(maps["fastDown"]);
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

    else if(maps["swap"].isClicked(&event)){
        
        bool valid = false;
        SDL_Event newEvent;
        
        renderKeyBindChange(maps["swap"]);
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

void SetScene::renderButtons(std::map <std::string, Button> map){
    for (auto i = map.begin(); i != map.end(); i++){

        SDL_Rect rect = i->second.getContainer();

        i->second.drawToRender();
        SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        SDL_RenderDrawRect(mainScreen.getRender(), &rect);
    }
} 


//FUNCTIONS

void renderKeyBindChange(Button button){
    SDL_Rect rect = {button.getContainer().x, button.getContainer().y, button.getContainer().w, button.getContainer().h};


    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_BLUE.r, LIGHT_BLUE.g, LIGHT_BLUE.b, LIGHT_BLUE.a);
    SDL_RenderFillRect(mainScreen.getRender(), &rect);
    SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderDrawRect(mainScreen.getRender(), &rect);
    Font font(&mainScreen, "Ubuntu-BoldItalic", 30, "...", BLACK);
    font.setCoords(rect.x + rect.w/2 - font.getTextSurface()->w/2, rect.y + rect.h/2 - font.getTextSurface()->h/2);
    font.drawTextToRender(); 

    SDL_RenderPresent(mainScreen.getRender());
    
}
