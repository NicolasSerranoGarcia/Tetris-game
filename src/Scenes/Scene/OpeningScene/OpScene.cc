#include "OpScene.h"

OpScene::OpScene(){
     std::vector <Score> bestScores = getBestPlays();

    if(!bestScores.empty()){
        Button playButton({225, 510, 515, 160}, GREEN, &mainScreen);
        getButtonMap()["play"] = playButton;
    } else {
        Button playButton({225, 655, 515, 160}, GREEN, &mainScreen);
        getButtonMap()["play"] = playButton;
    }
}


void OpScene::render(){

    //Load the background image

        std::vector <Score> bestScores = getBestPlays();

        if(SDL_GetTicks() - ticks >= 1000){
            sprite = !sprite;
            ticks = SDL_GetTicks();
        }

        std::string path;

        if(!bestScores.empty()){
            path = sprite ? "OpScene-background2": "OpScene-background1";
        } else{
            path = sprite ? "OpScene-background-nostats2": "OpScene-background-nostats1";
        }

        Image background(0, 0, mainScreen.getWidth(), mainScreen.getHeight(), path, "png");

        background.setAsBackground();

    //Render the best play, if there is

        if(isClicked){
            if(!bestScores.empty()){
                Image button(0, 0, mainScreen.getWidth(), mainScreen.getHeight(), "OpScene-background/OpScene-play-pressed", "png");
            button.CopyToRender();
            } else {
                Image button(0, 145, mainScreen.getWidth(), mainScreen.getHeight(), "OpScene-background/OpScene-play-pressed", "png");
                button.CopyToRender();
            }
        }

        if(!bestScores.empty()){

            Image statsSpace(0, 0, mainScreen.getWidth(), mainScreen.getHeight(), "OpScene-background/OpScene-stats", "png");

            statsSpace.CopyToRender();

            SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, 100);
            SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);

            SDL_Rect bestPlays = {getButtonMap()["play"].getContainer().x + getButtonMap()["play"].getContainer().w/3, getButtonMap()["play"].getContainer().y + getButtonMap()["play"].getContainer().h + 20, 
                getButtonMap()["play"].getContainer().w/3, BLOCKLENGTH};

            Font bestText(&mainScreen, "04B_30__", bestPlays.h - 10, "BEST", CIANSH);

            bestText.setCoords(bestPlays.x + bestPlays.w/2 - bestText.getTextSurface()->w/2 + 5, bestPlays.y + bestPlays.h/2 - bestText.getTextSurface()->h/2 + 20);

            bestText.drawTextToRender();


            //Draw everything related to the points

            SDL_Rect pointsTitleRect = {getButtonMap()["play"].getContainer().x, bestText.getY() + bestText.getTextSurface()->h + 40, 
                getButtonMap()["play"].getContainer().w/3, (int) (BLOCKLENGTH/1.5)};


            Font pointsTitleText(&mainScreen, "04B_30__", pointsTitleRect.h - 3, "POINTS", CIANSH);

            pointsTitleText.setCoords(pointsTitleRect.x + pointsTitleRect.w/2 - pointsTitleText.getTextSurface()->w/2 + 60, pointsTitleRect.y + pointsTitleRect.h/2 - pointsTitleText.getTextSurface()->h/2 - 20);

            pointsTitleText.drawTextToRender();
            
            
            SDL_Rect pointsTitleNum = {getButtonMap()["play"].getContainer().x + pointsTitleRect.w + 20, bestText.getY() + bestText.getTextSurface()->h + 40, 
                getButtonMap()["play"].getContainer().w / 2 + 32, (int) (BLOCKLENGTH/1.5)};
        
            Font pointsNum(&mainScreen, "04B_30__", pointsTitleNum.h - 3, std::to_string(getBestPlays()[0].points).c_str(), CIANSH);

            pointsNum.setCoords(pointsTitleNum.x + pointsTitleNum.w/2 - pointsNum.getTextSurface()->w/2 + 60, 
            pointsTitleNum.y + pointsTitleNum.h/2 - pointsNum.getTextSurface()->h/2 - 20);
            
            pointsNum.drawTextToRender();


            // draw everything related to the lines

            SDL_Rect linesTitleRect = {getButtonMap()["play"].getContainer().x, bestText.getY() + bestText.getTextSurface()->h + 40 + 120, 
                getButtonMap()["play"].getContainer().w/3, (int) (BLOCKLENGTH/1.5)};


            Font linesTitleText(&mainScreen, "04B_30__", linesTitleRect.h - 3, "LINES", CIANSH);

            linesTitleText.setCoords(linesTitleRect.x + linesTitleRect.w/2 - linesTitleText.getTextSurface()->w/2 + 60, linesTitleRect.y + linesTitleRect.h/2 - linesTitleText.getTextSurface()->h/2 - 40);

            linesTitleText.drawTextToRender();
            
            
            SDL_Rect linesTitleNum = {getButtonMap()["play"].getContainer().x + linesTitleRect.w + 20, bestText.getY() + bestText.getTextSurface()->h + 40 + 120, 
                getButtonMap()["play"].getContainer().w / 2 + 32, (int) (BLOCKLENGTH/1.5)};


            Font linesNum(&mainScreen, "04B_30__", linesTitleNum.h - 3, std::to_string(getBestPlays()[0].lines).c_str(), CIANSH);

            linesNum.setCoords(linesTitleNum.x + linesTitleNum.w/2 - linesNum.getTextSurface()->w/2 + 60,
            linesTitleNum.y + linesTitleNum.h/2 - linesNum.getTextSurface()->h/2 - 40);
            
            linesNum.drawTextToRender();

            // draw everything related to the level

            SDL_Rect levelTitleRect = {getButtonMap()["play"].getContainer().x, bestText.getY() + bestText.getTextSurface()->h + 40 + 60, 
                getButtonMap()["play"].getContainer().w/3, (int) (BLOCKLENGTH/1.5)};


            Font levelTitleText(&mainScreen, "04B_30__", levelTitleRect.h - 3, "LEVEL", CIANSH);

            levelTitleText.setCoords(levelTitleRect.x + levelTitleRect.w/2 - levelTitleText.getTextSurface()->w/2 + 60, levelTitleRect.y + levelTitleRect.h/2 - levelTitleText.getTextSurface()->h/2 - 30);

            levelTitleText.drawTextToRender();
            
            
            SDL_Rect levelTitleNum = {getButtonMap()["play"].getContainer().x + levelTitleRect.w + 20, bestText.getY() + bestText.getTextSurface()->h + 40 + 60, 
                getButtonMap()["play"].getContainer().w / 2 + 32, (int) (BLOCKLENGTH/1.5)};


            Font levelNum(&mainScreen, "04B_30__", levelTitleNum.h - 3, std::to_string(getBestPlays()[0].level).c_str(), CIANSH);

            levelNum.setCoords(levelTitleNum.x + levelTitleNum.w/2 - levelNum.getTextSurface()->w/2 + 60, 
            levelTitleNum.y + levelTitleNum.h/2 - levelNum.getTextSurface()->h/2 - 30);
            
            levelNum.drawTextToRender();
        }

}

void OpScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene, Sound *){

    //The user can either press the button or press ENTER
    if(getButtonMap()["play"].isClicked(&event) || ((event.type == SDL_KEYDOWN) && event.key.keysym.sym == SDLK_RETURN)){

        isClicked = true;

        return;
    }

    if((isClicked && (event.type = SDL_MOUSEBUTTONUP)) || ((event.type == SDL_KEYUP) && event.key.keysym.sym == SDLK_RETURN)){

        isClicked = false;

        delete curScene;
        curScene = new MainScene;
        mScene = curScene;
    }
}