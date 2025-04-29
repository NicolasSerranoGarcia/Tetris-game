#ifndef LOOSESCENE_CC
#define LOOSESCENE_CC

#include "LooseScene.h"
#include <iostream>

//this function is inherited and the normal case is that it doesn't need any further coding. Still, at the moment I'm gonna call the father method from the child one in case 
//I need to make extra implementations
LooseScene::LooseScene(){

}

void LooseScene::update(SDL_Renderer * render){

}

void LooseScene::render(){
    if(mainScene != nullptr){
        mainScene->render();
    }
    std::cout << "Hello world" << std::endl;
}

void LooseScene::clear(){
    Scene::clear();
}

void LooseScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene){
   if(mainScene == nullptr){   
       mainScene = mScene;
    }
}

void LooseScene::handleLogic(Uint32 * lastTick, Scene *& curScene){

}

#endif