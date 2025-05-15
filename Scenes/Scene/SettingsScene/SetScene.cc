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

    for(auto i = getButtonMap().begin(); i != getButtonMap().end(); i++){
        mapButtonPressed[i->first] = {i->second, false};
    }

    Button sliderButton(SBX + SBW - BLOCKLENGTH/3, SBY, BLOCKLENGTH/3, (int) (SBH*(SBH/((float) (SBH + 200)))), GREY, &mainScreen);

    rightSlider = {sliderButton, BSY, BSY + 200, GREY};
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

	SDL_Texture* texture = SDL_CreateTexture(mainScreen.getRender(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SBW, SBH + 200);
    SDL_SetRenderTarget(mainScreen.getRender(), texture);

    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, LIGHT_GREY.a);
    SDL_RenderClear(mainScreen.getRender());

    SDL_Rect settingsRect = {SBX, SBY, SBW, SBH};
    

    //Render a title for the keybinds
    Font keyBindText(&mainScreen, "Ubuntu-Regular", 50, "KEYBINDS", BLACK);
    keyBindText.setCoords(SBW/2 - keyBindText.getTextSurface()->w/2, 5);

    keyBindText.drawTextToRender();

    //Render all the buttons

    Font rotateLetterR(&mainScreen, "Ubuntu-Regular", SBX - 13, convertKeyToLetter(CONTROLROTATERIGHT).c_str(), BLACK);
    getButtonMap()["rotateRight"].setFont(&rotateLetterR);
                            
    Font rotateLetterL(&mainScreen, "Ubuntu-Regular", SBX - 13, convertKeyToLetter(CONTROLROTATELEFT).c_str(), BLACK);
    getButtonMap()["rotateLeft"].setFont(&rotateLetterL);
    
    
    Font leftLetter(&mainScreen, "Ubuntu-Regular", SBX - 13, convertKeyToLetter(CONTROLLEFT).c_str(), BLACK);
    getButtonMap()["left"].setFont(&leftLetter);
    
    Font rightLetter(&mainScreen, "Ubuntu-Regular", SBX - 13, convertKeyToLetter(CONTROLRIGHT).c_str(), BLACK);
    getButtonMap()["right"].setFont(&rightLetter);
    
    Font downLetter(&mainScreen, "Ubuntu-Regular", SBX - 13, convertKeyToLetter(CONTROLDOWN).c_str(), BLACK);
    getButtonMap()["down"].setFont(&downLetter);
    
    Font fastDownLetter(&mainScreen, "Ubuntu-Regular", SBX - 13, convertKeyToLetter(CONTROLFASTDOWN).c_str(), BLACK);
    getButtonMap()["fastDown"].setFont(&fastDownLetter);

    Font swapLetter(&mainScreen, "Ubuntu-Regular", SBX - 13, convertKeyToLetter(CONTROLSWAP).c_str(), BLACK);
    getButtonMap()["swap"].setFont(&swapLetter);

    Font rotateRText(&mainScreen, "Ubuntu-Regular", SBX - 15, "Rotate right", BLACK);
    rotateRText.setCoords(SBW/4 - rotateRText.getTextSurface()->w/2, getButtonMap()["rotateRight"].getContainer().y - SBY);
    rotateRText.drawTextToRender();

    Font rotateLText(&mainScreen, "Ubuntu-Regular", SBX - 15, "Rotate left", BLACK);
    rotateLText.setCoords(SBW/4 - rotateLText.getTextSurface()->w/2, getButtonMap()["rotateLeft"].getContainer().y - SBY);
    rotateLText.drawTextToRender();


    Font moveLeftText(&mainScreen, "Ubuntu-Regular", SBX - 15, "Move left", BLACK);
    moveLeftText.setCoords(SBW/4 - moveLeftText.getTextSurface()->w/2, getButtonMap()["left"].getContainer().y - SBY);
    moveLeftText.drawTextToRender();

    Font moveRightText(&mainScreen, "Ubuntu-Regular", SBX - 15, "Move right", BLACK);
    moveRightText.setCoords(SBW/4 - moveRightText.getTextSurface()->w/2, getButtonMap()["right"].getContainer().y - SBY);
    moveRightText.drawTextToRender();


    Font moveDownText(&mainScreen, "Ubuntu-Regular", SBX - 15, "Move down", BLACK);
    moveDownText.setCoords(SBW/4 - moveDownText.getTextSurface()->w/2, getButtonMap()["down"].getContainer().y - SBY);
    moveDownText.drawTextToRender();

    Font fastDropText(&mainScreen, "Ubuntu-Regular", SBX - 15, "Fast drop", BLACK);
    fastDropText.setCoords(SBW/4 - fastDropText.getTextSurface()->w/2, getButtonMap()["fastDown"].getContainer().y - SBY);
    fastDropText.drawTextToRender();

    Font swapText(&mainScreen, "Ubuntu-Regular", SBX - 15, "Swap figure", BLACK);
    swapText.setCoords(SBW/4 - swapText.getTextSurface()->w/2, getButtonMap()["swap"].getContainer().y - SBY);
    swapText.drawTextToRender();

    renderButtons(getButtonMap());

    if(anyButtonPressed){
        for(auto i = mapButtonPressed.begin(); i != mapButtonPressed.end(); i++){
            if(i->second.clicked){
                renderKeyBindChange(i->second.button, *this);
                break;
            }
        }
    }
    SDL_SetRenderTarget(mainScreen.getRender(), nullptr);
    
    SDL_Rect rect = getSourceRect();
    SDL_RenderCopy(mainScreen.getRender(), texture, &rect, &settingsRect);

    rightSlider.render();

    SDL_DestroyTexture(texture);
}

void SetScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene){

    if(mainScene == nullptr){
        mainScene = mScene;
    }
    
    
    if((event.type != SDL_KEYDOWN) && (event.type != SDL_KEYUP) && (event.type != SDL_MOUSEBUTTONDOWN) && 
       (event.type != SDL_MOUSEWHEEL) && (event.type != SDL_MOUSEMOTION) && (event.type != SDL_MOUSEBUTTONUP)){
        return;
    }


    if(rightSlider.isClicked(&event)){
        rightSlider.setClickedNow(true);
    }

    if((event.type == SDL_MOUSEBUTTONUP) && rightSlider.getClickedNow()){
        rightSlider.setClickedNow(false);
        return;
    }

    if((event.type == SDL_MOUSEMOTION) && rightSlider.getClickedNow()){
        int scrollDir = -(event.motion.yrel / abs(event.motion.yrel)); //-1 or 1

            // Scrolling towards me
            if (((rightSlider.getSliderButton().getContainer().y + rightSlider.getSliderButton().getContainer().h + (event.motion.yrel)) <= SBY + SBH) && 
            (((rightSlider.getSliderButton().getContainer().y + (event.motion.yrel)) >= SBY))){
                Button button = rightSlider.getSliderButton();
            
                button.setContainer({button.getContainer().x, rightSlider.getSliderButton().getContainer().y + (event.motion.yrel), button.getContainer().w, button.getContainer().h});
                rightSlider.setSliderButton(button);
            }

        SDL_Rect newSrc = getSourceRect();
        int delta = (abs(event.motion.yrel)) * scrollDir;

        int newY = newSrc.y - delta;
    
        if (scrollDir == -1){
            // Scrolling towards me
            if (newY + newSrc.h <= SBY + SBH){
                newSrc.y = newY;
            }
        } else{
            // Scrolling away from me
            if (newY >= 0) {
                newSrc.y = newY;
            }
        }
        setDeltaY(newY);
        setSourceRect(newSrc);

        auto maps = getButtonMap();
        for(auto i = maps.begin(); i != maps.end(); i++){
            SDL_Rect rect = i->second.getContainer();
            if(((sourceRect.y) == (200))){
                rect.y += event.motion.yrel;
            }
            if((sourceRect.y != 0)){
                rect.y -= getDeltaY();
            } 
            i->second.setContainer(rect);

            if((i->second.getContainer().y + i->second.getContainer().h) <= sourceRect.y){
                i->second.setVisibility(false);
            } else{
                i->second.setVisibility(true);
            }
            
            mapButtonPressed[i->first].button = i->second;
        }
    }

    if (event.type == SDL_MOUSEWHEEL && event.wheel.y != 0) {
        SDL_Rect newSrc = getSourceRect();
        int scrollDir = event.wheel.y / abs(event.wheel.y); //-1 or 1
        int delta = SCROLLFACTOR * scrollDir;

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

        if (((rightSlider.getSliderButton().getContainer().y + rightSlider.getSliderButton().getContainer().h + (-delta)) <= SBY + SBH) && 
            (((rightSlider.getSliderButton().getContainer().y + (-delta)) >= SBY))){
                Button button = rightSlider.getSliderButton();
            
                button.setContainer({button.getContainer().x, rightSlider.getSliderButton().getContainer().y + (-delta), button.getContainer().w, button.getContainer().h});
                rightSlider.setSliderButton(button);
            }

        auto maps = getButtonMap();
        for(auto i = maps.begin(); i != maps.end(); i++){
            SDL_Rect rect = i->second.getContainer();
            if(((sourceRect.y) == (200))){
                rect.y += SCROLLFACTOR;
            }
            if((sourceRect.y != 0)){
                rect.y -= getDeltaY();
            } 
            i->second.setContainer(rect);

            if((i->second.getContainer().y + i->second.getContainer().h) <= sourceRect.y){
                i->second.setVisibility(false);
            } else{
                i->second.setVisibility(true);
            }
            
            mapButtonPressed[i->first].button = i->second;
        }
        return;
    }

    for(auto i = mapButtonPressed.begin(); (i != mapButtonPressed.end()); i++){
        if((i->second.button.getContainer().y + i->second.button.getContainer().h) <= sourceRect.y){
            i->second.button.setVisibility(false);
        } else{
            i->second.button.setVisibility(true);
        }
        if(i->second.clicked){
            if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym != SDLK_ESCAPE)){
                if(i->first == "rotateRight"){
                    CONTROLROTATERIGHT = event.key.keysym.sym;
                }
                else if(i->first == "rotateLeft"){
                    CONTROLROTATELEFT = event.key.keysym.sym;
                }
                else if(i->first == "left"){
                    CONTROLLEFT = event.key.keysym.sym;
                }
                else if(i->first == "right"){
                    CONTROLRIGHT = event.key.keysym.sym;
                }
                else if(i->first == "down"){
                    CONTROLDOWN = event.key.keysym.sym;
                }
                else if(i->first == "fastDown"){
                    CONTROLFASTDOWN = event.key.keysym.sym;
                }
                else if(i->first == "swap"){
                    CONTROLSWAP = event.key.keysym.sym;
                }
                anyButtonPressed = false;
                i->second.clicked = false;
                return;
            }
             else if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE)){
                i->second.clicked = false;
                anyButtonPressed = false;
                return;
            }
        }
    }

    if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE) && !anyButtonPressed){
        delete curScene;
        curScene = mScene;
        return;
    }

    for(auto i = mapButtonPressed.begin(); i != mapButtonPressed.end(); i++){
        if(i->second.button.getVisibility() && i->second.button.isClicked(&event) && !anyButtonPressed){

            if((i->second.button.getContainer().y < SBY) && i->second.button.isClickedSubdivision(&event, 
                                                        {0, 
                                                        SBY - i->second.button.getContainer().y, 
                                                        i->second.button.getContainer().w, 
                                                        i->second.button.getContainer().h - (SBY - i->second.button.getContainer().y)})){

                i->second.clicked = true;
                anyButtonPressed = true;
            }

            if(i->second.button.getContainer().y > SBY){
                i->second.clicked = true;
                anyButtonPressed = true;
            }
            return;
        }
    }
}

void SetScene::handleLogic(Uint32 *, Scene *&){
    
}

void SetScene::renderButtons(std::map <std::string, Button> map){
    for (auto i = map.begin(); i != map.end(); i++){

        
        i->second.setContainer({i->second.getContainer().x - SBX, i->second.getContainer().y - SBY, i->second.getContainer().w, i->second.getContainer().h});
        i->second.drawToRender();
        SDL_Rect rect = i->second.getContainer();
        SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        SDL_RenderDrawRect(mainScreen.getRender(), &rect);
    }
} 


//FUNCTIONS

void renderKeyBindChange(Button button, SetScene & s){
    SDL_Rect rect = {button.getContainer().x - SBX, button.getContainer().y - SBY  + s.getSourceRect().y/* + (SCROLLFACTOR)*(s.getSourceRect().y/SCROLLFACTOR) */, button.getContainer().w, button.getContainer().h};


    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_BLUE.r, LIGHT_BLUE.g, LIGHT_BLUE.b, LIGHT_BLUE.a);
    SDL_RenderFillRect(mainScreen.getRender(), &rect);
    SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderDrawRect(mainScreen.getRender(), &rect);
    Font font(&mainScreen, "Ubuntu-BoldItalic", 30, "...", BLACK);
    font.setCoords(rect.x + rect.w/2 - font.getTextSurface()->w/2, rect.y + rect.h/2 - font.getTextSurface()->h/2);
    font.drawTextToRender();    
}
