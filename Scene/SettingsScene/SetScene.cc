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

void SetScene::render(){
    if(mainScene != nullptr){
        mainScene->render();
    }
    SDL_Rect rect = {50, SCREENHEIGHT/6 ,SCREENWIDTH - 100 , SCREENHEIGHT/1.5};
    SDL_SetRenderDrawColor(mainScreen.getRender(), WHITE.r, WHITE.g, WHITE.b, WHITE.a);
    SDL_RenderFillRect(mainScreen.getRender(), &rect);
    
}

void SetScene::clear(){
    Scene::clear();
}

void SetScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene){
    if(this->mainScene == nullptr){
        mainScene = mScene;
    }
    if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE)){
        std::cout << "Go back" << std::endl;
        delete curScene;
        curScene = mScene;
    }
}

void SetScene::handleLogic(Uint32 * lastTick){
    
}


#endif