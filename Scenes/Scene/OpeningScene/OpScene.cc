#include "OpScene.h"

OpScene::OpScene(){

    Button playButton({px(AbsPosition::POS_CENTER_DOWN, 320), py(AbsPosition::POS_CENTER_LEFT, 140), 320, 140}, GREEN, &mainScreen);
    getButtonMap()["play"] = playButton;
}


void OpScene::render(){

    //Load the background image

        Image background(0, 0, mainScreen.getWidth(), mainScreen.getHeight(), "OpScene-background", "png");

        background.setAsBackground();


    //Load the title

        Font Title(&mainScreen, "BungeeTint-Regular", 150, "TETRIS", RED);

        Title.setCoords(AbsPosition::POS_UP);

        //set the Y position a little lower
        Title.setCoords(Title.getX(), Title.getY() + 50);

        Title.drawTextToRender();


    //Finish setting up the play button by loading a font

        Font Play(&mainScreen, "Ubuntu-Bold", 125, "PLAY", BLACK);

        getButtonMap()["play"].setFont(&Play);

        getButtonMap()["play"].drawToRender();
}

void OpScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene){

    //The user can either press the button or press ENTER
    if(getButtonMap()["play"].isClicked(&event) || ((event.type == SDL_KEYDOWN) && event.key.keysym.sym == SDLK_RETURN)){
        
        LINES = 0;
        LEVEL = 0;
        POINTS = 0;
        dead = false;

        delete curScene;
        curScene = new MainScene;
        mScene = curScene;
    }
}