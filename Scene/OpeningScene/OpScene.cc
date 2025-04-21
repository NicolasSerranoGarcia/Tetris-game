#include "OpScene.h"

#include <iostream>
#include <SDL2/SDL_image.h>
#include "Image/Image.h"
#include "Scene/Scenes.h"

OpScene::OpScene(){
    Button playButton({px(AbsPosition::POS_CENTER_DOWN, 320), py(AbsPosition::POS_CENTER_LEFT, 140), 320, 140}, GREEN, &mainScreen);
    this->playButton = playButton;
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
    this->playButton.setFont(&Play);
    this->playButton.drawToRender();

    SDL_RenderPresent(mainScreen.getRender());

}

void OpScene::clear(){
    Scene::clear();
    //""
}

//ERROR: right now I don't know why changing the lobal pointer is not working. Anyways I will find a way
void OpScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene){
    if(this->playButton.isClicked(&event) || ((event.type == SDL_KEYDOWN) && event.key.keysym.sym == SDLK_RETURN)){
        std::cout << "Play" << std::endl; 
        OpScene::clear();
        delete curScene;
        curScene = new MainScene;
        mScene = curScene;
    }
}

void OpScene::handleLogic(Uint32 * lastTick){

}