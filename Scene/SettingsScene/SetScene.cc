#ifndef SETSCENE_CC
#define SETSCENE_CC

#include "SetScene.h"
#include <iostream>

SetScene::~SetScene(){

}


//this function is inherited and the normal case is that it doesn't need any further coding. Still, at the moment I'm gonna call the father method from the child one in case 
//I need to make extra implementations
SetScene::SetScene(){

}

void SetScene::update(SDL_Renderer * render){

}

void SetScene::render(Uint32 * lastTick){
    SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderClear(mainScreen.getRender());
    SDL_RenderPresent(mainScreen.getRender());
}

void SetScene::clear(){
    Scene::clear();
}

void SetScene::handleEvents(SDL_Event event, Scene *& curScene){
    std::cout << "Hello" << std::endl;
}


#endif