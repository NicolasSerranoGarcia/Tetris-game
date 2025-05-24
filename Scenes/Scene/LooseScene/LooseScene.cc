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