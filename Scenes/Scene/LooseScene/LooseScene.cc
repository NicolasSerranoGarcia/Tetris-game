#ifndef LOOSESCENE_CC
#define LOOSESCENE_CC

#include "LooseScene.h"
#include <iostream>

//this function is inherited and the normal case is that it doesn't need any further coding. Still, at the moment I'm gonna call the father method from the child one in case 
//I need to make extra implementations
LooseScene::LooseScene(){
    Button playAgainButton(px(AbsPosition::POS_CENTER_LEFT, SCREENWIDTH/3), py(AbsPosition::POS_CENTER_LEFT, BLOCKLENGTH*3), SCREENWIDTH/3, BLOCKLENGTH*2, LIGHT_BLUE, &mainScreen);
    getButtonMap()["playAgain"] = playAgainButton;
}

void LooseScene::render(){
    if(mainScene != nullptr){
        mainScene->renderWithoutFigures();
    }

    Font LooseText(&mainScreen, "BungeeTint-Regular", 110, "YOU LOST", BLACK);

    LooseText.setCoords(AbsPosition::POS_CENTER_UP);

    //set the Y position a little higher
    LooseText.setCoords(LooseText.getX(), LooseText.getY() - 50);

    SDL_Rect LooseBg = {LooseText.getX(), LooseText.getY(), LooseText.getTextSurface()->w, LooseText.getTextSurface()->h};

    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, LIGHT_GREY.a);
    SDL_RenderFillRect(mainScreen.getRender(), &LooseBg);

    LooseText.drawTextToRender();

    Font playAgainText(&mainScreen, "BungeeTint-Regular", 40, "PLAY AGAIN", BLACK);

    getButtonMap()["playAgain"].setContainer({LooseBg.x, 
        getButtonMap()["playAgain"].getContainer().y, 
        getButtonMap()["playAgain"].getContainer().w, 
        getButtonMap()["playAgain"].getContainer().h});

    getButtonMap()["playAgain"].setFont(&playAgainText);

    getButtonMap()["playAgain"].drawToRender();

}

void LooseScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene){
    if(getButtonMap()["playAgain"].isClicked(&event)){

        delete curScene;
        curScene = nullptr;
        curScene = new MainScene;

        return;
    }

    if(mainScene == nullptr){ 
       mainScene = mScene;
    }
    
}

void LooseScene::handleLogic(Uint32 *, Scene *&, Scene *& mScene){
    if(mainScene == nullptr){
        mainScene = mScene;
    }
}

#endif