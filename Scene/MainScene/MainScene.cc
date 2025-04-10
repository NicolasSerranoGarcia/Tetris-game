#include "MainScene.h"
#include <iostream>

//this function is inherited and the normal case is that it doesn't need any further coding. Still, at the moment I'm gonna call the father method from the child one in case 
//I need to make extra implementations
void MainScene::update(SDL_Renderer * render){
    Scene::update(render);
    //I'll probably place something here hehe
}

void MainScene::render(){

    Button settingsButton(mainScreen.getWidth() - 70, 0, 70, 70, WHITE, &mainScreen);
    //load an image of settings
    Image settingsImage(settingsButton.getContainer().x, settingsButton.getContainer().y, settingsButton.getContainer().w, settingsButton.getContainer().h, "OpScene-settings");
    
    //pass it to the button
    settingsButton.setImage(&settingsImage);

    //draw the settings button with the image
    settingsButton.drawToRender();

    SDL_RenderPresent(mainScreen.getRender());

}

void MainScene::clear(SDL_Renderer * render){
    Scene::clear(render);
    //""
}

void MainScene::handleEvents(SDL_Event event, Scene *& curScene){
}