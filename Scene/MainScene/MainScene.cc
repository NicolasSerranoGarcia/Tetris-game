#include "MainScene.h"
#include <iostream>

const Uint32 FALLDELAY = 1000;

MainScene::MainScene(){
    getRandomFigure(currentFigure);
    Button settingsButton(mainScreen.getWidth() - 75, mainScreen.getHeight() - 75, 50, 50, WHITE, &mainScreen);
    this->settingsButton = settingsButton;
}

//this function is inherited and the normal case is that it doesn't need any further coding. Still, at the moment I'm gonna call the father method from the child one in case 
//I need to make extra implementations
void MainScene::update(SDL_Renderer * render){
    Scene::update(render);
}

void MainScene::render(Uint32 * lastTick){

    //the number of hor. tiles is 10, the number of vertical tiles is 20. the pixels of a tile are 46x46
    int tile = (mainScreen.getWidth() - 500)/10;

    //draw a WHITE background
    SDL_SetRenderDrawColor(mainScreen.getRender(), WHITE.r, WHITE.g, WHITE.b, WHITE.a);
    SDL_RenderClear(mainScreen.getRender());

    //draw the background square where the game is played
    SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_Rect boardBackogrund = {BSX, BSY, BSW, BSH};
    SDL_RenderFillRect(mainScreen.getRender(), &boardBackogrund);

    //draw the vertical and hor. lines that separate each tile 
    SDL_SetRenderDrawColor(mainScreen.getRender(), GREY.r - 30, GREY.g - 30, GREY.b - 30, GREY.a);
    for(int i = 1; i <= 10; i++){
        SDL_RenderDrawLine(mainScreen.getRender(), tile*i + BSX, BSY, tile*i + BSX, BSY + BSH);
    }

    for(int j = 1; j <= 20; j++){
        SDL_RenderDrawLine(mainScreen.getRender(), BSX, BSY + j*tile, BSX + BSW, BSY + j*tile);
    }


    //load an image of settings
    Image settingsImage(settingsButton.getContainer().x, settingsButton.getContainer().y, settingsButton.getContainer().w +10, settingsButton.getContainer().h + 10, "OpScene-settings", "png");
    

    //pass it to the button
    this->settingsButton.setImage(&settingsImage);

    //draw the settings button with the image
    this->settingsButton.drawToRender();

    //TODO: draw the rectangles and the borders of the timer, the points of the player...


    //IMPLEMENTATION OF THE LOGIC IN THE GAME

    for(unsigned int i = 0; i < this->gameBoard.size(); i++){
        this->gameBoard[i]->renderFigure();
    }

    Uint32 elapsed = SDL_GetTicks() - *lastTick;

    if(elapsed >= FALLDELAY){
        //update the leading block 1 down and reset the ticks

        int largestY = 0;
        for(unsigned int i = 0; i < this->currentFigure->getBlocks().size(); i++){
            if(this->currentFigure->getBlocks()[i].getBlockY() > largestY){
                largestY = this->currentFigure->getBlocks()[i].getBlockY();
            }
        }

        if(largestY < 19){
            this->currentFigure->getBlocks()[this->currentFigure->getLeadingBlockPos()].setBlockY(this->currentFigure->getBlocks()[this->currentFigure->getLeadingBlockPos()].getBlockY() + 1);
            this->currentFigure->updateBlocks();
        }

        *lastTick = SDL_GetTicks();
    }

    this->getCurrentFigure()->renderFigure();



    //Show all the scene

    SDL_RenderPresent(mainScreen.getRender());
}

void MainScene::clear(){
    Scene::clear();
    //""
}

void MainScene::handleEvents(SDL_Event event, Scene *& curScene){
    //If the setting button is clicked or the user hit ESC open the settings
    if(this->settingsButton.isClicked(&event) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))){
        std::cout << "Settings" << std::endl;
        delete curScene;
        curScene = nullptr;
        curScene = new SetScene;
        //find a way to open the settings as a popup (the mainScene still shows on the background). 
    } else{
        currentFigure->update(event);
    }
}

Figure * MainScene::getCurrentFigure(){
    return this->currentFigure;
}

//FUNCTIONS
void getRandomFigure(Figure *& curFigure){
    delete curFigure;
    curFigure = nullptr;

    //Future implementation when all the figures are created
    int number = std::rand() % 7;
    switch (number){
    case 0:
        curFigure = new FigL;
        break;
    case 1:
        curFigure = new FigLRight;
        break;
    case 2:
        curFigure = new FigSquare;
        break;
    case 3:
        curFigure = new FigZ;
        break;
    case 4:
        curFigure = new FigZLeft;
        break;
    case 5:
        curFigure = new FigT;
        break;
    case 6:
        curFigure = new FigStick;
        break;
    default:
        break;
    }
}