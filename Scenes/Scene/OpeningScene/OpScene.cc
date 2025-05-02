#include "OpScene.h"

#include "Image/Image.h"
#include "Scenes/Scenes.h"

#include <SDL2/SDL_image.h>

OpScene::OpScene(){
    Button playButton({px(AbsPosition::POS_CENTER_DOWN, 320), py(AbsPosition::POS_CENTER_LEFT, 140), 320, 140}, GREEN, &mainScreen);
    getButtonMap()["play"] = playButton;
}

//this function is inherited and the normal case is that it doesn't need any further coding. Still, at the moment I'm gonna call the father method from the child one in case 
//I need to make extra implementations
void OpScene::update(SDL_Renderer * render){
    Scene::update(render);
    //I'll probably place something here hehe
}

void OpScene::render(){
    //All the implementation of the scene is going here. 

    //Load the background image
    Image background(0, 0, mainScreen.getWidth(), mainScreen.getHeight(), "OpScene-background", "png");
    background.setAsBackground();

    //Load the title and the play button
    Font Title(&mainScreen, "BungeeTint-Regular", 150, "TETRIS", RED);
    Title.setCoords(AbsPosition::POS_UP);
    //set the text a little bit lower
    Title.setCoords(Title.getX(), Title.getY() + 50);
    Title.drawTextToRender();


    Font Play(&mainScreen, "Ubuntu-Bold", 125, "PLAY", BLACK);
    getButtonMap()["play"].setFont(&Play);
    getButtonMap()["play"].drawToRender();

    SDL_RenderPresent(mainScreen.getRender());

}

void OpScene::clear(){
    Scene::clear();
    //""
}

void OpScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene){
    if(getButtonMap()["play"].isClicked(&event) || ((event.type == SDL_KEYDOWN) && event.key.keysym.sym == SDLK_RETURN)){
        OpScene::clear();
        delete curScene;
        curScene = new MainScene;
        mScene = curScene;
    }
}

void OpScene::handleLogic(Uint32 *, Scene *&){

}