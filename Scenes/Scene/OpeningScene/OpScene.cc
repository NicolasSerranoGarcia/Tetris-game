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

        Score best = bestScores[0];

        SDL_Rect bestPlays = {getButtonMap()["play"].getContainer().x + getButtonMap()["play"].getContainer().w/3, getButtonMap()["play"].getContainer().y + getButtonMap()["play"].getContainer().h + 20, 
            getButtonMap()["play"].getContainer().w/3, BLOCKLENGTH};

        SDL_SetRenderDrawColor(mainScreen.getRender(), WHITE.r, WHITE.g, WHITE.b, WHITE.a);
        SDL_RenderFillRect(mainScreen.getRender(), &bestPlays);

        Font bestText(&mainScreen, "Ubuntu-Regular", bestPlays.h - 10, "BEST", BLACK);

        bestText.setCoords(bestPlays.x + bestPlays.w/2 - bestText.getTextSurface()->w/2, bestPlays.y + bestPlays.h/2 - bestText.getTextSurface()->h/2);

        bestText.drawTextToRender();
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