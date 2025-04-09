#ifndef MAINSCENE_CC
#define MAINSCENE_CC

#include "MainScene.h"

//this function is inherited and the normal case is that it doesn't need any further coding. Still, at the moment I'm gonna call the father method from the child one in case 
//I need to make extra implementations
void MainScene::update(SDL_Renderer * render){
    Scene::update(render);
    //I'll probably place something here hehe
}

void MainScene::render(){
    //same here hehe

}

void MainScene::clear(SDL_Renderer * render){
    Scene::clear(render);
    //""
}

#endif