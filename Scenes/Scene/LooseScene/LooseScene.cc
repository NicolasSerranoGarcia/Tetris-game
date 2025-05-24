#ifndef LOOSESCENE_CC
#define LOOSESCENE_CC

#include "LooseScene.h"
#include <iostream>

//this function is inherited and the normal case is that it doesn't need any further coding. Still, at the moment I'm gonna call the father method from the child one in case 
//I need to make extra implementations
LooseScene::LooseScene(){

}

void LooseScene::render(){
    if(mainScene != nullptr){
        mainScene->renderWithoutFigures();
    }

    Font Title(&mainScreen, "BungeeTint-Regular", 120, "YOU LOST", BLACK);

    Title.setCoords(AbsPosition::POS_CENTER_UP);

    //set the Y position a little lower
    Title.setCoords(Title.getX(), Title.getY() + 50);

    Title.drawTextToRender();

}

void LooseScene::handleEvents(SDL_Event, Scene *&, Scene *& mScene){
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