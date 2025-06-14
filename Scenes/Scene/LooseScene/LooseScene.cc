#ifndef LOOSESCENE_CC
#define LOOSESCENE_CC

#include "LooseScene.h"
#include <iostream>

LooseScene::LooseScene(){
    Button playAgainButton(px(AbsPosition::POS_CENTER_LEFT, SCREENWIDTH/3), py(AbsPosition::POS_CENTER_LEFT, BLOCKLENGTH*3), SCREENWIDTH/3, BLOCKLENGTH*2, LIGHT_BLUE, &mainScreen);
    getButtonMap()["playAgain"] = playAgainButton;

    Button goStartButton(px(AbsPosition::POS_CENTER_LEFT, BLOCKLENGTH*2), py(AbsPosition::POS_CENTER_LEFT, BLOCKLENGTH*3), BLOCKLENGTH*2, BLOCKLENGTH*2, LIGHT_BLUE, &mainScreen);
    getButtonMap()["goStart"] = goStartButton;

    Button settingsButton(px(AbsPosition::POS_CENTER_LEFT, BLOCKLENGTH*2), py(AbsPosition::POS_CENTER_LEFT, BLOCKLENGTH*3), BLOCKLENGTH*2, BLOCKLENGTH*2, LIGHT_BLUE, &mainScreen);
    getButtonMap()["settings"] = settingsButton;
}

void LooseScene::render(){

    if(mainScene != nullptr){
        mainScene->renderWithoutFigures();
    }

    Font LooseText(&mainScreen, "BungeeTint-Regular", 110, "YOU LOST", BLACK);

    LooseText.setCoords(AbsPosition::POS_CENTER_UP);

    //set the Y position a little higher
    LooseText.setCoords(LooseText.getX(), LooseText.getY() - 50);

    SDL_Rect LooseBg = {LooseText.getX(), LooseText.getY(), LooseText.getTextSurface()->w, LooseText.getTextSurface()->h};

    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, LIGHT_GREY.a);
    SDL_RenderFillRect(mainScreen.getRender(), &LooseBg);

    LooseText.drawTextToRender();

    Font playAgainText(&mainScreen, "BungeeTint-Regular", 40, "PLAY AGAIN", BLACK);

    getButtonMap()["playAgain"].setContainer({LooseBg.x, 
        getButtonMap()["playAgain"].getContainer().y, 
        getButtonMap()["playAgain"].getContainer().w,
        getButtonMap()["playAgain"].getContainer().h});

    getButtonMap()["playAgain"].setFont(&playAgainText);

    getButtonMap()["playAgain"].drawToRender();



    getButtonMap()["goStart"].setContainer({LooseBg.x + getButtonMap()["playAgain"].getContainer().w + 32, 
        getButtonMap()["goStart"].getContainer().y, 
        getButtonMap()["goStart"].getContainer().w, 
        getButtonMap()["goStart"].getContainer().h});


    Image arrowImage(getButtonMap()["goStart"].getContainer().x + 15, 
                            getButtonMap()["goStart"].getContainer().y + 15, 
                            getButtonMap()["goStart"].getContainer().w - 30,
                            getButtonMap()["goStart"].getContainer().h - 30, "LooseScene-arrow", "png");
    
    getButtonMap()["goStart"].setImage(&arrowImage);

    getButtonMap()["goStart"].drawToRender();
    

    getButtonMap()["settings"].setContainer({LooseBg.x + LooseBg.w - getButtonMap()["settings"].getContainer().w, 
        getButtonMap()["settings"].getContainer().y, 
        getButtonMap()["settings"].getContainer().w, 
        getButtonMap()["settings"].getContainer().h});


    Image settingsImage(getButtonMap()["settings"].getContainer().x + 10, 
                    getButtonMap()["settings"].getContainer().y + 10, 
                    getButtonMap()["settings"].getContainer().w - 20,
                    getButtonMap()["settings"].getContainer().h - 20, "OpScene-settings", "png");

    getButtonMap()["settings"].setImage(&settingsImage);

    getButtonMap()["settings"].drawToRender();

    // draw a background for showing the stats of the game

    SDL_Rect PointsBg = {getButtonMap()["playAgain"].getContainer().x + 40, getButtonMap()["settings"].getContainer().y + getButtonMap()["settings"].getContainer().h + 60,
        SCREENWIDTH/4, (int) (BLOCKLENGTH*1.5)};

    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, LIGHT_GREY.a);
    SDL_RenderFillRect(mainScreen.getRender(), &PointsBg);

    Font PointsText(&mainScreen, "BungeeTint-Regular", 50, "POINTS", BLACK);

    PointsText.setCoords(PointsBg.x + PointsBg.w/2 - PointsText.getTextSurface()->w/2, PointsBg.y + PointsBg.h/2 - PointsText.getTextSurface()->h/2);

    PointsText.drawTextToRender();

    
    Font PointsNum(&mainScreen, "BungeeTint-Regular", 40, std::to_string(POINTS).c_str(), BLACK);
    
    PointsNum.setCoords((-(PointsBg.x + PointsBg.w) + LooseBg.x + LooseBg.w)/2 + PointsBg.x + PointsBg.w - PointsNum.getTextSurface()->w/2,
    getButtonMap()["settings"].getContainer().y + getButtonMap()["settings"].getContainer().h + 60 + PointsBg.h/2 - PointsNum.getTextSurface()->h/2);
    
    SDL_Rect PointsSquare = {PointsNum.getX() - PointsNum.getTextSurface()->w/2, PointsNum.getY() - 7,
         PointsNum.getTextSurface()->w*2, PointsBg.h};

    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, LIGHT_GREY.a);
    SDL_RenderFillRect(mainScreen.getRender(), &PointsSquare);
    
    PointsNum.drawTextToRender();




    SDL_Rect LevelBg = {getButtonMap()["playAgain"].getContainer().x + 40, getButtonMap()["settings"].getContainer().y + getButtonMap()["settings"].getContainer().h + 60 + PointsBg.h + 20,
        SCREENWIDTH/4, (int) (BLOCKLENGTH*1.5)};

    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, LIGHT_GREY.a);
    SDL_RenderFillRect(mainScreen.getRender(), &LevelBg);

    Font LevelText(&mainScreen, "BungeeTint-Regular", 50, "LEVEL", BLACK);

    LevelText.setCoords(LevelBg.x + LevelBg.w/2 - LevelText.getTextSurface()->w/2, LevelBg.y + LevelBg.h/2 - LevelText.getTextSurface()->h/2);

    LevelText.drawTextToRender();

    
    Font LevelNum(&mainScreen, "BungeeTint-Regular", 40, std::to_string(LEVEL).c_str(), BLACK);
    
    LevelNum.setCoords((-(LevelBg.x + LevelBg.w) + LooseBg.x + LooseBg.w)/2 + LevelBg.x + LevelBg.w - LevelNum.getTextSurface()->w/2,
    getButtonMap()["settings"].getContainer().y + getButtonMap()["settings"].getContainer().h + 60 + LevelBg.h/2 - LevelNum.getTextSurface()->h/2 + PointsBg.h + 20);
    
    SDL_Rect LevelSquare = {LevelNum.getX() - LevelNum.getTextSurface()->w/2, LevelNum.getY() - 7,
         LevelNum.getTextSurface()->w*2, LevelBg.h};

    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, LIGHT_GREY.a);
    SDL_RenderFillRect(mainScreen.getRender(), &LevelSquare);
    
    LevelNum.drawTextToRender();





    SDL_Rect LinesBg = {getButtonMap()["playAgain"].getContainer().x + 40, getButtonMap()["settings"].getContainer().y + getButtonMap()["settings"].getContainer().h + 60 + 2*(PointsBg.h + 20),
        SCREENWIDTH/4, (int) (BLOCKLENGTH*1.5)};

    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, LIGHT_GREY.a);
    SDL_RenderFillRect(mainScreen.getRender(), &LinesBg);

    Font LinesText(&mainScreen, "BungeeTint-Regular", 50, "LINES", BLACK);

    LinesText.setCoords(LinesBg.x + LinesBg.w/2 - LinesText.getTextSurface()->w/2, LinesBg.y + LinesBg.h/2 - LinesText.getTextSurface()->h/2);

    LinesText.drawTextToRender();

    
    Font LinesNum(&mainScreen, "BungeeTint-Regular", 40, std::to_string(LINES).c_str(), BLACK);
    
    LinesNum.setCoords((-(LinesBg.x + LinesBg.w) + LooseBg.x + LooseBg.w)/2 + LinesBg.x + LinesBg.w - LinesNum.getTextSurface()->w/2,
    getButtonMap()["settings"].getContainer().y + getButtonMap()["settings"].getContainer().h + 60 + LinesBg.h/2 - LinesNum.getTextSurface()->h/2 + 2*(PointsBg.h + 20));
    
    SDL_Rect LinesSquare = {LinesNum.getX() - LinesNum.getTextSurface()->w/2, LinesNum.getY() - 7,
         LinesNum.getTextSurface()->w*2, LinesBg.h};

    SDL_SetRenderDrawColor(mainScreen.getRender(), LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, LIGHT_GREY.a);
    SDL_RenderFillRect(mainScreen.getRender(), &LinesSquare);
    
    LinesNum.drawTextToRender();
}

void LooseScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene){
    if(mainScene == nullptr){ 
       mainScene = mScene;
    }  
    
    if(getButtonMap()["playAgain"].isClicked(&event) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN))){
        
        //handle the logs for the points before deleting everything

        updateBestPlays({(int) POINTS, (int) LEVEL, (int) LINES});

        LINES = 0;
        LEVEL = 0;
        POINTS = 0;
        dead = false;



        delete curScene;
        curScene = nullptr;
        curScene = new MainScene;

        return;
    }

    if(getButtonMap()["goStart"].isClicked(&event)){

        updateBestPlays({(int) POINTS, (int) LEVEL, (int) LINES});

        LINES = 0;
        LEVEL = 0;
        POINTS = 0;
        dead = false;

        delete curScene;
        curScene = nullptr;
        curScene = new OpScene;

        return;
    }

    if(getButtonMap()["settings"].isClicked(&event) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))){

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