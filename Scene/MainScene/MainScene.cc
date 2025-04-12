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

    const int bsX = mainScreen.getWidth()/2 - (mainScreen.getWidth() - 300)/2;
    const int bsY = 40;
    const int bsW = mainScreen.getWidth() - 500;
    const int bsH = 920;

    //the number of hor. tiles is 10, the number of vertical tiles is 20. the pixels of a tile are 46x46
    int tile = (mainScreen.getWidth() - 500)/10;

    //draw a WHITE background
    SDL_SetRenderDrawColor(mainScreen.getRender(), WHITE.r, WHITE.g, WHITE.b, WHITE.a);
    SDL_RenderClear(mainScreen.getRender());

    //draw the background square where the game is played
    SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_Rect boardBackogrund = {bsX, bsY, bsW, bsH};
    SDL_RenderFillRect(mainScreen.getRender(), &boardBackogrund);

    //draw the vertical and hor. lines that separate each tile 
    SDL_SetRenderDrawColor(mainScreen.getRender(), GREY.r - 30, GREY.g - 30, GREY.b - 30, GREY.a);
    for(int i = 1; i <= 10; i++){
        SDL_RenderDrawLine(mainScreen.getRender(), tile*i + bsX, bsY, tile*i + bsX, bsY + bsH);
    }

    for(int j = 1; j <= 20; j++){
        SDL_RenderDrawLine(mainScreen.getRender(), bsX, bsY + j*tile, bsX + bsW, bsY + j*tile);
    }


    //load an image of settings
    Image settingsImage(settingsButton.getContainer().x, settingsButton.getContainer().y, settingsButton.getContainer().w +10, settingsButton.getContainer().h + 10, "OpScene-settings", "png");
    

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