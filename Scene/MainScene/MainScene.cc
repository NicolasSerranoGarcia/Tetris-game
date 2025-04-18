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

    
    Uint32 elapsed = SDL_GetTicks() - *lastTick;
    
    if(elapsed >= FALLDELAY){
        //update the leading block 1 down and reset the ticks
        
        int largestY = 0;
        for(unsigned int i = 0; i < this->currentFigure->getBlocks().size(); i++){
            if(this->currentFigure->getBlocks()[i].getBlockY() > largestY){
                largestY = this->currentFigure->getBlocks()[i].getBlockY();
            }
        }
        
        if((largestY < 19)){
            if(colides(this->gameBoard, SDLK_DOWN, currentFigure)){
                gameBoard.push_back(this->currentFigure);
                currentFigure = nullptr;
                getRandomFigure(currentFigure);
            } else{
                this->currentFigure->getBlocks()[this->currentFigure->getLeadingBlockPos()].setBlockY(this->currentFigure->getBlocks()[this->currentFigure->getLeadingBlockPos()].getBlockY() + 1);
                this->currentFigure->updateBlocks();
            }
        }
        
        *lastTick = SDL_GetTicks();
    }
    
    
    //when the figure reaches the bottom, place it and change the 
    int largestY = 0;
    for(unsigned int i = 0; i < this->currentFigure->getBlocks().size(); i++){
        if(this->currentFigure->getBlocks()[i].getBlockY() > largestY){
            largestY = this->currentFigure->getBlocks()[i].getBlockY();
        }
    }
    
    if(largestY == 19){
        gameBoard.push_back(this->currentFigure);
        currentFigure = nullptr;
        getRandomFigure(currentFigure);
    }
    
    for(unsigned int i = 0; i < this->gameBoard.size(); i++){
        this->gameBoard[i]->renderFigure();
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
    } else if(event.type == SDL_KEYDOWN){
        if(colides(this->gameBoard, event.key.keysym.sym, currentFigure) && (event.key.keysym.sym == CONTROLDOWN)){
            gameBoard.push_back(this->currentFigure);
            currentFigure = nullptr;
            getRandomFigure(currentFigure);
        } else {
            currentFigure->update(event);
        }
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


//return true if the figure colides with any other figure of the gameboard
bool colides(std::vector <Figure*> gameBoard, SDL_Keycode key, Figure *&curFigure){
    //the figure will move in some direction on the next tick. If we create a virtual figure that is already on the next movement and we see that it colides with some
    //other figure, return true. Outside of this function we will add the figure to the vector 
    if(CONTROLDOWN == key){

        for(int i = 0; i < (int) gameBoard.size(); i++){
            for(int j = 0; j < (int) gameBoard[i]->getBlocks().size(); j++){
                for(int k = 0; k < (int) curFigure->getBlocks().size(); k++){
                    if((gameBoard[i]->getBlocks()[j].getBlockX() == curFigure->getBlocks()[k].getBlockX()) &&
                       (gameBoard[i]->getBlocks()[j].getBlockY() == (curFigure->getBlocks()[k].getBlockY() + 1))){
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    else if(CONTROLLEFT == key){

        for(int i = 0; i < (int) gameBoard.size(); i++){
            for(int j = 0; j < (int) gameBoard[i]->getBlocks().size(); j++){
                for(int k = 0; k < (int) curFigure->getBlocks().size(); k++){
                    if((gameBoard[i]->getBlocks()[j].getBlockX() == curFigure->getBlocks()[k].getBlockX() - 1) &&
                    (gameBoard[i]->getBlocks()[j].getBlockY() == curFigure->getBlocks()[k].getBlockY())){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    else if(CONTROLRIGHT == key){

        for(int i = 0; i < (int) gameBoard.size(); i++){
            for(int j = 0; j < (int) gameBoard[i]->getBlocks().size(); j++){
                for(int k = 0; k < (int) curFigure->getBlocks().size(); k++){
                    if((gameBoard[i]->getBlocks()[j].getBlockX() == curFigure->getBlocks()[k].getBlockX() + 1) &&
                    (gameBoard[i]->getBlocks()[j].getBlockY() == curFigure->getBlocks()[k].getBlockY())){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    // else if(CONTROLROTATE == key){
    //     for(int i = gameBoard.size(); i > (int) 0; i--){
    //         for(int j = 0; j < (int) gameBoard[i]->getBlocks().size(); j++){
    //             for(int k = 0; k < (int) curFigure->getBlocks().size(); k++){
    //                 if((gameBoard[i]->getBlocks()[j].getBlockX() == curFigure->getBlocks()[k].getBlockX()) &&
    //                 (gameBoard[i]->getBlocks()[j].getBlockY() == curFigure->getBlocks()[k].getBlockY() + 1)){
    //                     return true;
    //                 }
    //             }
    //         }
    //     }
    //     return false;
    // }

    return false;
}