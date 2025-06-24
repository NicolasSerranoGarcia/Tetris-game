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


    //Render the best play, if there is

        std::vector <Score> bestScores = getBestPlays();

        if(!bestScores.empty()){

            SDL_Rect bestPlays = {getButtonMap()["play"].getContainer().x + getButtonMap()["play"].getContainer().w/3, getButtonMap()["play"].getContainer().y + getButtonMap()["play"].getContainer().h + 20, 
                getButtonMap()["play"].getContainer().w/3, BLOCKLENGTH};

            SDL_SetRenderDrawColor(mainScreen.getRender(), WHITE.r, WHITE.g, WHITE.b, WHITE.a);
            SDL_RenderFillRect(mainScreen.getRender(), &bestPlays);

            Font bestText(&mainScreen, "Ubuntu-Regular", bestPlays.h - 10, "BEST", BLACK);

            bestText.setCoords(bestPlays.x + bestPlays.w/2 - bestText.getTextSurface()->w/2, bestPlays.y + bestPlays.h/2 - bestText.getTextSurface()->h/2);

            bestText.drawTextToRender();


            //Draw everything related to the points

            SDL_Rect pointsTitleRect = {getButtonMap()["play"].getContainer().x, bestText.getY() + bestText.getTextSurface()->h + 40, 
                getButtonMap()["play"].getContainer().w/3, (int) (BLOCKLENGTH/1.5)};

            SDL_RenderFillRect(mainScreen.getRender(), &pointsTitleRect);


            Font pointsTitleText(&mainScreen, "Ubuntu-Regular", pointsTitleRect.h - 3, "POINTS", BLACK);

            pointsTitleText.setCoords(pointsTitleRect.x + pointsTitleRect.w/2 - pointsTitleText.getTextSurface()->w/2, pointsTitleRect.y + pointsTitleRect.h/2 - pointsTitleText.getTextSurface()->h/2);

            pointsTitleText.drawTextToRender();
            
            
            SDL_Rect pointsTitleNum = {getButtonMap()["play"].getContainer().x + pointsTitleRect.w + 20, bestText.getY() + bestText.getTextSurface()->h + 40, 
                getButtonMap()["play"].getContainer().w / 2 + 32, (int) (BLOCKLENGTH/1.5)};

            SDL_RenderFillRect(mainScreen.getRender(), &pointsTitleNum);
        
            Font pointsNum(&mainScreen, "Ubuntu-Regular", pointsTitleNum.h - 3, std::to_string(getBestPlays()[0].points).c_str(), BLACK);

            pointsNum.setCoords(pointsTitleNum.x + pointsTitleNum.w/2 - pointsNum.getTextSurface()->w/2, 
            pointsTitleNum.y + pointsTitleNum.h/2 - pointsNum.getTextSurface()->h/2);
            
            pointsNum.drawTextToRender();


            // draw everything related to the lines

            SDL_Rect linesTitleRect = {getButtonMap()["play"].getContainer().x, bestText.getY() + bestText.getTextSurface()->h + 40 + 120, 
                getButtonMap()["play"].getContainer().w/3, (int) (BLOCKLENGTH/1.5)};

            SDL_RenderFillRect(mainScreen.getRender(), &linesTitleRect);


            Font linesTitleText(&mainScreen, "Ubuntu-Regular", linesTitleRect.h - 3, "LINES", BLACK);

            linesTitleText.setCoords(linesTitleRect.x + linesTitleRect.w/2 - linesTitleText.getTextSurface()->w/2, linesTitleRect.y + linesTitleRect.h/2 - linesTitleText.getTextSurface()->h/2);

            linesTitleText.drawTextToRender();
            
            
            SDL_Rect linesTitleNum = {getButtonMap()["play"].getContainer().x + linesTitleRect.w + 20, bestText.getY() + bestText.getTextSurface()->h + 40 + 120, 
                getButtonMap()["play"].getContainer().w / 2 + 32, (int) (BLOCKLENGTH/1.5)};

            SDL_RenderFillRect(mainScreen.getRender(), &linesTitleNum);


            Font linesNum(&mainScreen, "Ubuntu-Regular", linesTitleNum.h - 3, std::to_string(getBestPlays()[0].lines).c_str(), BLACK);

            linesNum.setCoords(linesTitleNum.x + linesTitleNum.w/2 - linesNum.getTextSurface()->w/2, 
            linesTitleNum.y + linesTitleNum.h/2 - linesNum.getTextSurface()->h/2);
            
            linesNum.drawTextToRender();

            // draw everything related to the level

            SDL_Rect levelTitleRect = {getButtonMap()["play"].getContainer().x, bestText.getY() + bestText.getTextSurface()->h + 40 + 60, 
                getButtonMap()["play"].getContainer().w/3, (int) (BLOCKLENGTH/1.5)};

            SDL_RenderFillRect(mainScreen.getRender(), &levelTitleRect);


            Font levelTitleText(&mainScreen, "Ubuntu-Regular", levelTitleRect.h - 3, "LEVEL", BLACK);

            levelTitleText.setCoords(levelTitleRect.x + levelTitleRect.w/2 - levelTitleText.getTextSurface()->w/2, levelTitleRect.y + levelTitleRect.h/2 - levelTitleText.getTextSurface()->h/2);

            levelTitleText.drawTextToRender();
            
            
            SDL_Rect levelTitleNum = {getButtonMap()["play"].getContainer().x + levelTitleRect.w + 20, bestText.getY() + bestText.getTextSurface()->h + 40 + 60, 
                getButtonMap()["play"].getContainer().w / 2 + 32, (int) (BLOCKLENGTH/1.5)};

            SDL_RenderFillRect(mainScreen.getRender(), &levelTitleNum);


            Font levelNum(&mainScreen, "Ubuntu-Regular", levelTitleNum.h - 3, std::to_string(getBestPlays()[0].level).c_str(), BLACK);

            levelNum.setCoords(levelTitleNum.x + levelTitleNum.w/2 - levelNum.getTextSurface()->w/2, 
            levelTitleNum.y + levelTitleNum.h/2 - levelNum.getTextSurface()->h/2);
            
            levelNum.drawTextToRender();
        }

}

void OpScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene){

    //The user can either press the button or press ENTER
    if(getButtonMap()["play"].isClicked(&event) || ((event.type == SDL_KEYDOWN) && event.key.keysym.sym == SDLK_RETURN)){

        delete curScene;
        curScene = new MainScene;
        mScene = curScene;
    }
}