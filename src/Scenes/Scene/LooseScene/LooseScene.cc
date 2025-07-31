#ifndef LOOSESCENE_CC
#define LOOSESCENE_CC

#include "LooseScene.h"
#include <iostream>

LooseScene::LooseScene(){
    Button playAgainButton(px(AbsPosition::POS_CENTER, (int) BLOCKLENGTH*2.5), py(AbsPosition::POS_CENTER, (int) BLOCKLENGTH*2.5), (int) BLOCKLENGTH*2.5, (int) BLOCKLENGTH*2.5, LIGHT_BLUE, &mainScreen);
    getButtonMap()["playAgain"] = playAgainButton;

    Button goStartButton(px(AbsPosition::POS_CENTER_LEFT, (int) BLOCKLENGTH*2.5) - 100, py(AbsPosition::POS_CENTER, (int) BLOCKLENGTH*2.5), (int) BLOCKLENGTH*2.5, (int) BLOCKLENGTH*2.5, LIGHT_BLUE, &mainScreen);
    getButtonMap()["goStart"] = goStartButton;

    Button settingsButton(px(AbsPosition::POS_CENTER_RIGHT, (int) BLOCKLENGTH*2.5) + 100, py(AbsPosition::POS_CENTER, (int) BLOCKLENGTH*2.5), (int) BLOCKLENGTH*2.5, (int) BLOCKLENGTH*2.5, LIGHT_BLUE, &mainScreen);
    getButtonMap()["settings"] = settingsButton;
}

LooseScene::~LooseScene(){
    Scene::~Scene();
}


void LooseScene::render(){

    if(mainScene != nullptr){
        mainScene->render();
    }


    Image shadow(0, 0, SCREENWIDTH, SCREENHEIGHT, "LooseScene-background/LooseScene-shadow", "png");

    SDL_SetTextureAlphaMod(shadow.getTexture(), 160);

    shadow.CopyToRender();

    Image bg(0, 0, SCREENWIDTH, SCREENHEIGHT, "LooseScene-background/LooseScene-background", "png");

    bg.CopyToRender();


    Font LooseText(&mainScreen, "BungeeTint-Regular", 110, "YOU LOST", CLEAR_BROWN);

    LooseText.setCoords(AbsPosition::POS_CENTER_UP);

    //set the Y position a little higher
    LooseText.setCoords(LooseText.getX(), LooseText.getY() - 50);

    SDL_Rect LooseBg = {LooseText.getX(), LooseText.getY(), LooseText.getTextSurface()->w, LooseText.getTextSurface()->h};


    Image arrowImage(getButtonMap()["goStart"].getContainer().x, 
                            getButtonMap()["goStart"].getContainer().y, 
                            getButtonMap()["goStart"].getContainer().w,
                            getButtonMap()["goStart"].getContainer().h, "LooseScene-background/LooseScene-arrow", "png");


    // draw a background for showing the stats of the game

    SDL_Rect PointsBg = {getButtonMap()["goStart"].getContainer().x + 40, getButtonMap()["settings"].getContainer().y + getButtonMap()["settings"].getContainer().h + 60,
        SCREENWIDTH/4, (int) (BLOCKLENGTH*1.5)};

    Font PointsNum(&mainScreen, "BungeeTint-Regular", 40, std::to_string(POINTS).c_str(), CLEAR_BROWN);
    
    PointsNum.setCoords((-(PointsBg.x + PointsBg.w) + LooseBg.x + LooseBg.w)/2 + PointsBg.x + PointsBg.w - PointsNum.getTextSurface()->w/2,
    getButtonMap()["settings"].getContainer().y + getButtonMap()["settings"].getContainer().h + 60 + PointsBg.h/2 - PointsNum.getTextSurface()->h/2);
    
    PointsNum.drawTextToRender();


    SDL_Rect LevelBg = {getButtonMap()["goStart"].getContainer().x + 40, getButtonMap()["settings"].getContainer().y + getButtonMap()["settings"].getContainer().h + 60 + PointsBg.h + 20,
        SCREENWIDTH/4, (int) (BLOCKLENGTH*1.5)};

    
    Font LevelNum(&mainScreen, "BungeeTint-Regular", 40, std::to_string(LEVEL).c_str(), CLEAR_BROWN);
    
    LevelNum.setCoords((-(LevelBg.x + LevelBg.w) + LooseBg.x + LooseBg.w)/2 + LevelBg.x + LevelBg.w - LevelNum.getTextSurface()->w/2,
    getButtonMap()["settings"].getContainer().y + getButtonMap()["settings"].getContainer().h + 60 + LevelBg.h/2 - LevelNum.getTextSurface()->h/2 + PointsBg.h + 20);
    
    LevelNum.drawTextToRender();


    SDL_Rect LinesBg = {getButtonMap()["goStart"].getContainer().x + 40, getButtonMap()["settings"].getContainer().y + getButtonMap()["settings"].getContainer().h + 60 + 2*(PointsBg.h + 20),
        SCREENWIDTH/4, (int) (BLOCKLENGTH*1.5)};

    
    Font LinesNum(&mainScreen, "BungeeTint-Regular", 40, std::to_string(LINES).c_str(), CLEAR_BROWN);
    
    LinesNum.setCoords((-(LinesBg.x + LinesBg.w) + LooseBg.x + LooseBg.w)/2 + LinesBg.x + LinesBg.w - LinesNum.getTextSurface()->w/2,
    getButtonMap()["settings"].getContainer().y + getButtonMap()["settings"].getContainer().h + 60 + LinesBg.h/2 - LinesNum.getTextSurface()->h/2 + 2*(PointsBg.h + 20));
    
    LinesNum.drawTextToRender();

    if(isSettingsClicked){
        Image settingsImage(0, 0, SCREENWIDTH, SCREENHEIGHT, "LooseScene-background/LooseScene-settings-clicked", "png");

        settingsImage.CopyToRender();
    }

    if(isReturnClicked){
        Image returnImage(0, 0, SCREENWIDTH, SCREENHEIGHT, "LooseScene-background/LooseScene-home-clicked", "png");

        returnImage.CopyToRender();
    }

    if(isPlayClicked){
        Image playImage(0, 0, SCREENWIDTH, SCREENHEIGHT, "LooseScene-background/LooseScene-return-clicked", "png");

        playImage.CopyToRender();
    }

}

void LooseScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene, Sound *){
    
    if(mainScene == nullptr){ 
       mainScene = mScene;
    }  

    if(getButtonMap()["playAgain"].isClicked(&event) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN))){
        isPlayClicked = true;
        return;
    }

    if(getButtonMap()["settings"].isClicked(&event) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))){
        isSettingsClicked = true;
        return;
    }

    if(getButtonMap()["goStart"].isClicked(&event)){
        isReturnClicked = true;
        return;
    }
    
    if(isPlayClicked){

        isPlayClicked = false;

        //handle the logs for the points before deleting everything

        if(POINTS + LEVEL + LINES != 0){
            updateBestPlays({(int) POINTS, (int) LEVEL, (int) LINES});
        }
        
        LINES = 0;
        LEVEL = 0;
        POINTS = 0;
        FALLSPEED = 1250;
        dead = false;



        delete curScene;
        curScene = nullptr;
        curScene = new MainScene;

        return;
    }

    if(isReturnClicked){

        isReturnClicked = false;

        if(POINTS + LEVEL + LINES != 0){
            updateBestPlays({(int) POINTS, (int) LEVEL, (int) LINES});
        }

        LINES = 0;
        LEVEL = 0;
        POINTS = 0;
        FALLSPEED = 1250;
        dead = false;

        delete curScene;
        curScene = nullptr;
        curScene = new OpScene;

        return;
    }

    if(isSettingsClicked){

        isSettingsClicked = false;

        delete curScene;
        curScene = nullptr;
        curScene = new SetScene;

        return;
    }

}

void LooseScene::handleLogic(Uint32 *, Scene *&, Scene *& mScene){
    if(mainScene == nullptr){
        mainScene = mScene;
    }
}

#endif