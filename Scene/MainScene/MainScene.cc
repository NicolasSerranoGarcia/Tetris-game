#include "MainScene.h"
#include <iostream>

MainScene::MainScene(){
    Button settingsButton(mainScreen.getWidth() - 65, mainScreen.getHeight() - 65, 50, 50, WHITE, &mainScreen);
    this->settingsButton = settingsButton;
}

//this function is inherited and the normal case is that it doesn't need any further coding. Still, at the moment I'm gonna call the father method from the child one in case 
//I need to make extra implementations
void MainScene::update(SDL_Renderer * render){
    Scene::update(render);
    //I'll probably place something here hehe
}

void MainScene::render(){

    //draw a WHITE background
    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_GREY.r +10, LIGHT_GREY.g +10, LIGHT_GREY.b +10, LIGHT_GREY.a);
    SDL_RenderClear(mainScreen.getRender());

    SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_Rect boardBackogrund = {mainScreen.getWidth()/2 - (mainScreen.getWidth() - 300)/2, 40, mainScreen.getWidth() - 300, mainScreen.getHeight() - 80};
    SDL_RenderFillRect(mainScreen.getRender(), &boardBackogrund);

    //load an image of settings
    Image settingsImage(settingsButton.getContainer().x, settingsButton.getContainer().y, settingsButton.getContainer().w +10, settingsButton.getContainer().h + 10, "a", "jpg");
    

    //pass it to the button
    this->settingsButton.setImage(&settingsImage);

    //draw the settings button with the image
    this->settingsButton.drawToRender();

    SDL_RenderPresent(mainScreen.getRender());
}

void MainScene::clear(SDL_Renderer * render){
    Scene::clear(render);
    //""
}

void MainScene::handleEvents(SDL_Event event, Scene *& curScene){
    if(this->settingsButton.isClicked(&event)){
        std::cout << "Settings" << std::endl;
    }
}