#include "SetScene.h"

#include <iostream>

SetScene::~SetScene(){

}

SetScene::SetScene(){

    //Setup the keys for an easier loading

    keys = {"rotateRight", "rotateLeft", "left", "right", "down", "fastDown", "swap"};
   
    for(int i = 0; i < (int) keys.size(); i++){
        Button button({(SETTINGSBACKGROUNDW*3)/4 + SETTINGSBACKGROUNDX - (SETTINGSBACKGROUNDW/3 + BLOCKLENGTH)/2, BLOCKLENGTH/2 + SETTINGSBACKGROUNDY + (SETTINGSBACKGROUNDX + 10)*(i+1), SETTINGSBACKGROUNDW/3 + BLOCKLENGTH, SETTINGSBACKGROUNDX}, WHITE, &mainScreen);
        getButtonMap()[keys[i]] = button;

        //set the clicked map with the same info as 
        mapButtonPressed[keys[i]] = {button, false};
    }

    //Create the right slider 

    Button sliderButton(SETTINGSBACKGROUNDX + SETTINGSBACKGROUNDW - BLOCKLENGTH/3, SETTINGSBACKGROUNDY, BLOCKLENGTH/3, (int) ( (SETTINGSBACKGROUNDH*SETTINGSBACKGROUNDH) / (SETTINGSTEXTUREH) ), GREY, &mainScreen);
    rightSlider = {sliderButton, SETTINGSBACKGROUNDY, SETTINGSBACKGROUNDY + sourceRect.h, GREY};

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

    //Every time the settings is shown, also show the mainScene in the background

        if(mainScene != nullptr){
            mainScene->renderWithoutFigures();
        }

    //Create a settingsTexture so that we can "slide" trough the settings. It will be set as the render target and all the elements will be render on it

        SDL_Texture* settingsTexture = SDL_CreateTexture(mainScreen.getRender(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SETTINGSBACKGROUNDW, SETTINGSTEXTUREH);

        SDL_SetRenderTarget(mainScreen.getRender(), settingsTexture);


    //IMPORTANT: From now on, all the rendering is being made on the settingsTexture


    //Set a grey background

        SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, LIGHT_GREY.a);

        SDL_RenderClear(mainScreen.getRender());    

    //Render a title for the keybinds

        Font keyBindText(&mainScreen, "Ubuntu-Regular", 50, "KEYBINDS", BLACK);
        keyBindText.setCoords(SETTINGSBACKGROUNDW/2 - keyBindText.getTextSurface()->w/2, 5);

        keyBindText.drawTextToRender();

    //Render all the buttons

        for(int i = 0; i < (int) keys.size(); i++){

            //render the button associated with the keybind
            
                Font keybind(&mainScreen, "Ubuntu-Regular", SETTINGSBACKGROUNDX - 13, convertKeyToLetter(getKeyBindByKey(keys[i])).c_str(), BLACK);

                getButtonMap()[keys[i]].setFont(&keybind);

                renderButton(getButtonMap()[keys[i]]);

            //Render the text info that comes with the keybind

                //refers to the text that comes with the keybind that says which action is it
                Font infoText(&mainScreen, "Ubuntu-Regular", SETTINGSBACKGROUNDX - 15, getMessageByKey(keys[i]), BLACK);
                infoText.setCoords(SETTINGSBACKGROUNDW/4 - infoText.getTextSurface()->w/2, getButtonMap()[keys[i].c_str()].getContainer().y - SETTINGSBACKGROUNDY);
            
                infoText.drawTextToRender();

        }

    //If there is a button that has been pressed, render a rectangle above the position of the 
    //button to indicate that it needs to be changed
    
    if(anyButtonPressed){

        //Search for the button that is pressed

        for(auto i = mapButtonPressed.begin(); i != mapButtonPressed.end(); i++){

            if(i->second.clicked){
                renderKeyBindChange(i->second.button, *this);
                break;
            }
        }
    }

    //Set the render target back to the mainScreen

        SDL_SetRenderTarget(mainScreen.getRender(), nullptr);
    

    //IMPORTANT: From now on all the rendering is being done on the mainScreen


    //Render the settingsTexture to the screen

        SDL_Rect sourceRect = getSourceRect();

        SDL_Rect destRect = {SETTINGSBACKGROUNDX, SETTINGSBACKGROUNDY, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH};

        SDL_RenderCopy(mainScreen.getRender(), settingsTexture, &sourceRect, &destRect);

    //render the slider to the screen

        rightSlider.render();

    SDL_DestroyTexture(settingsTexture);
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
            if (((rightSlider.getSliderButton().getContainer().y + rightSlider.getSliderButton().getContainer().h + (event.motion.yrel)) <= SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH) && 
            (((rightSlider.getSliderButton().getContainer().y + (event.motion.yrel)) >= SETTINGSBACKGROUNDY))){
                Button button = rightSlider.getSliderButton();
            
                button.setContainer({button.getContainer().x, rightSlider.getSliderButton().getContainer().y + (event.motion.yrel), button.getContainer().w, button.getContainer().h});
                rightSlider.setSliderButton(button);
            }

        SDL_Rect newSrc = getSourceRect();
        int delta = (abs(event.motion.yrel)) * scrollDir;

        int newY = newSrc.y - delta;
    
        if (scrollDir == -1){
            // Scrolling towards me
            if (newY + newSrc.h <= SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH){
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
            if (newY + newSrc.h <= SETTINGSBACKGROUNDH + 200){
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

        if (((rightSlider.getSliderButton().getContainer().y + rightSlider.getSliderButton().getContainer().h + (-delta)) <= SETTINGSBACKGROUNDY + SETTINGSBACKGROUNDH) && 
            (((rightSlider.getSliderButton().getContainer().y + (-delta)) >= SETTINGSBACKGROUNDY))){
                Button button = rightSlider.getSliderButton();
            
                button.setContainer({button.getContainer().x, rightSlider.getSliderButton().getContainer().y -delta, button.getContainer().w, button.getContainer().h});
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

            if((i->second.button.getContainer().y < SETTINGSBACKGROUNDY) && i->second.button.isClickedSubdivision(&event, 
                                                        {0, 
                                                        SETTINGSBACKGROUNDY - i->second.button.getContainer().y, 
                                                        i->second.button.getContainer().w, 
                                                        i->second.button.getContainer().h - (SETTINGSBACKGROUNDY - i->second.button.getContainer().y)})){

                i->second.clicked = true;
                anyButtonPressed = true;
            }

            if(i->second.button.getContainer().y > SETTINGSBACKGROUNDY){
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

        
        i->second.setContainer({i->second.getContainer().x - SETTINGSBACKGROUNDX, i->second.getContainer().y - SETTINGSBACKGROUNDY, i->second.getContainer().w, i->second.getContainer().h});
        i->second.drawToRender();

        SDL_Rect rect = i->second.getContainer();
        SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        SDL_RenderDrawRect(mainScreen.getRender(), &rect);

        i->second.setContainer({i->second.getContainer().x + SETTINGSBACKGROUNDX, i->second.getContainer().y + SETTINGSBACKGROUNDY, i->second.getContainer().w, i->second.getContainer().h});

    }
} 

void SetScene::renderButton(Button button){

    button.setContainer({button.getContainer().x - SETTINGSBACKGROUNDX, button.getContainer().y - SETTINGSBACKGROUNDY, button.getContainer().w, button.getContainer().h});

    button.drawToRender();

    SDL_Rect rect = button.getContainer();
    SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderDrawRect(mainScreen.getRender(), &rect);
}

//FUNCTIONS

void renderKeyBindChange(Button button, SetScene & s){

    SDL_Rect coverRect = {button.getContainer().x - SETTINGSBACKGROUNDX,
                          button.getContainer().y - SETTINGSBACKGROUNDY + s.getSourceRect().y,
                          button.getContainer().w,
                          button.getContainer().h};
    
    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_BLUE.r, LIGHT_BLUE.g, LIGHT_BLUE.b, LIGHT_BLUE.a);
    SDL_RenderFillRect(mainScreen.getRender(), &coverRect);

    SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderDrawRect(mainScreen.getRender(), &coverRect);

    Font font(&mainScreen, "Ubuntu-BoldItalic", 30, "...", BLACK);
    font.setCoords(coverRect.x + coverRect.w/2 - font.getTextSurface()->w/2, coverRect.y + coverRect.h/2 - font.getTextSurface()->h/2);
    font.drawTextToRender();    
}

SDL_Keycode getKeyBindByKey(std::string key){

    if(key == "rotateRight"){
        return CONTROLROTATERIGHT;
    } 
    else if(key == "rotateLeft"){
        return CONTROLROTATELEFT;
    } 
    else if(key == "left"){
        return CONTROLLEFT;
    } 
    else if(key == "right"){
        return CONTROLRIGHT;
    } 
    else if(key == "down"){
        return CONTROLDOWN;
    } 
    else if(key == "fastDown"){
        return CONTROLFASTDOWN;
    } 
    else if(key == "swap"){
        return CONTROLSWAP;
    }

    return SDLK_SPACE;
}

const char * getMessageByKey(std::string key){

    if(key == "rotateRight"){
        return "Rotate right";
    } 
    else if(key == "rotateLeft"){
        return "Rotate left";
    } 
    else if(key == "left"){
        return "Move left";
    } 
    else if(key == "right"){
        return "Move right";
    } 
    else if(key == "down"){
        return "Move down";
    } 
    else if(key == "fastDown"){
        return "Fast Down";
    } 
    else if(key == "swap"){
        return "Swap figure";
    }

    return "Unknown";
}
