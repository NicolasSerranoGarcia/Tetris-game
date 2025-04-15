#ifndef LOOSESCENE_CC
#define LOOSESCENE_CC

#include "LooseScene.h"

//this function is inherited and the normal case is that it doesn't need any further coding. Still, at the moment I'm gonna call the father method from the child one in case 
//I need to make extra implementations
LooseScene::LooseScene(){

}

void LooseScene::update(SDL_Renderer * render){

}

void LooseScene::render(Uint32 * lastTick){

}

void LooseScene::clear(){
    Scene::clear();
}

void LooseScene::handleEvents(SDL_Event event, Scene *& curScene){

}


#endif