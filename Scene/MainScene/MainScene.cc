#include "MainScene.h"

#include <iostream>
#include <random>

MainScene::MainScene(){
    Button settingsButton(mainScreen.getWidth() - 75, mainScreen.getHeight() - 75, 50, 50, WHITE, &mainScreen);
    this->settingsButton = settingsButton;

    //Load the next 3 random figures 
    getRandomFigure(this->nextFigures[0]);
    getRandomFigure(this->nextFigures[1]);
    getRandomFigure(this->nextFigures[2]);
    fetchNextFigure(currentFigure, nextFigures);
}

//this function is inherited and the normal case is that it doesn't need any further coding. Still, at the moment I'm gonna call the father method from the child one in case 
//I need to make extra implementations
void MainScene::update(SDL_Renderer * render){
    Scene::update(render);
}

void MainScene::render(){

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
        SDL_RenderDrawLine(mainScreen.getRender(), BLOCKLENGTH*i + BSX, BSY, BLOCKLENGTH*i + BSX, BSY + BSH);
    }

    for(int j = 1; j <= 20; j++){
        SDL_RenderDrawLine(mainScreen.getRender(), BSX, BSY + j*BLOCKLENGTH, BSX + BSW, BSY + j*BLOCKLENGTH);
    }


    //load an image of settings
    Image settingsImage(settingsButton.getContainer().x, settingsButton.getContainer().y, settingsButton.getContainer().w +10, settingsButton.getContainer().h + 10, "OpScene-settings", "png");
    

    //pass it to the button
    this->settingsButton.setImage(&settingsImage);

    //draw the settings button with the image
    this->settingsButton.drawToRender();



    //Draw the next figures background, figures...
    SDL_Rect nextFiguresBackground = {FSX, FSY, FSW, FSH};

    SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, 230);
    SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(mainScreen.getRender(), &nextFiguresBackground);
    SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_NONE);


    SDL_SetRenderDrawColor(mainScreen.getRender(), GREY.r, GREY.g, GREY.b, GREY.a);
    SDL_RenderDrawRect(mainScreen.getRender(), &nextFiguresBackground);

    Font next(&mainScreen, "Ubuntu-Bold", 30, "NEXT", TEAL);
    next.setCoords(FSX + FSW/2 - next.getTextSurface()->w/2, FSY);

    SDL_Rect nextBg = {FSX, FSY, FSW, next.getTextSurface()->h};

    SDL_SetRenderDrawColor(mainScreen.getRender(), WHITE.r, WHITE.g, WHITE.b, WHITE.a);
    SDL_RenderFillRect(mainScreen.getRender(), &nextBg);

    SDL_SetRenderDrawColor(mainScreen.getRender(), GREY.r, GREY.g, GREY.b, GREY.a);
    SDL_RenderDrawRect(mainScreen.getRender(), &nextBg);

    renderNextFigures(nextFigures, next.getTextSurface()->h);

    next.drawTextToRender();


    //render the points, the level and the lines info
    SDL_Rect infoBackground = {ISX, ISY, ISW, ISH};
    SDL_Rect whiteBar = {ISX, ISY, ISW, ISH/4};

    Font level(&mainScreen, "Ubuntu-Bold", whiteBar.h, "LEVEL", TEAL);
    Font points(&mainScreen, "Ubuntu-Bold", whiteBar.h, "POINTS", TEAL);
    Font lines(&mainScreen, "Ubuntu-Bold", whiteBar.h, "LINES", TEAL); 

    Font levelNum(&mainScreen, "Ubuntu-Bold", whiteBar.h*2, std::to_string(LEVEL).c_str(), WHITE);
    
    Font pointsNum(&mainScreen, "Ubuntu-Bold", whiteBar.h*2, std::to_string(POINTS).c_str(), WHITE);
    
    Font linesNum(&mainScreen, "Ubuntu-Bold", whiteBar.h*2, std::to_string(LINES).c_str(), WHITE);
    
    for(int i = 0; i< 3; i++){
        infoBackground = {ISX, ISY + (ISH + BLOCKLENGTH/3)*i, ISW, ISH};
        whiteBar = {ISX, ISY + (ISH + BLOCKLENGTH/3)*i, ISW, ISH/4};
        
        
        SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, 230);
        SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(mainScreen.getRender(), &infoBackground);
        SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_NONE);
        
        SDL_SetRenderDrawColor(mainScreen.getRender(), WHITE.r, WHITE.g, WHITE.b, WHITE.a);
        SDL_RenderFillRect(mainScreen.getRender(), &whiteBar);
        SDL_SetRenderDrawColor(mainScreen.getRender(), GREY.r, GREY.g, GREY.b, GREY.a);
        SDL_RenderDrawRect(mainScreen.getRender(), &whiteBar);
        
        switch (i){
        case 0:
            points.setCoords(whiteBar.x + whiteBar.w/2 - points.getTextSurface()->w/2, whiteBar.y);
            points.drawTextToRender();
        
            pointsNum.setCoords(whiteBar.x + whiteBar.w/2 - pointsNum.getTextSurface()->w/2,
            whiteBar.y + whiteBar.h + (infoBackground.h - whiteBar.h)/2 - pointsNum.getTextSurface()->h/2);
            pointsNum.setText(std::to_string(POINTS).c_str());
            pointsNum.drawTextToRender();
            break;
        case 1:
            lines.setCoords(whiteBar.x + whiteBar.w/2 - lines.getTextSurface()->w/2, whiteBar.y);
            lines.drawTextToRender();
        
            linesNum.setCoords(whiteBar.x + whiteBar.w/2 - linesNum.getTextSurface()->w/2,
            whiteBar.y + whiteBar.h + (infoBackground.h - whiteBar.h)/2 - linesNum.getTextSurface()->h/2);
            pointsNum.setText(std::to_string(LINES).c_str());
            linesNum.drawTextToRender();
            break;
        case 2:
            level.setCoords(whiteBar.x + whiteBar.w/2 - level.getTextSurface()->w/2, whiteBar.y);
            level.drawTextToRender();
        
            levelNum.setCoords(whiteBar.x + whiteBar.w/2 - levelNum.getTextSurface()->w/2,
            whiteBar.y + whiteBar.h + (infoBackground.h - whiteBar.h)/2 - levelNum.getTextSurface()->h/2);
            pointsNum.setText(std::to_string(LEVEL).c_str());
            levelNum.drawTextToRender();
            break;
        default:
            break;
        }
    }



    //render all the figures that are at the bottom
    for(unsigned int i = 0; i < this->gameBoard.size(); i++){
        this->gameBoard[i]->renderFigure();
    }

    //render the shadow of the current figure
    Figure shadow = *currentFigure;
    Figure * sh = &shadow;

    shadow.setColor(BLACK);

    int largestY = 0;
    for(unsigned int i = 0; i < shadow.getBlocks().size(); i++){
        if(shadow.getBlocks()[i].getBlockY() > largestY){
            largestY = shadow.getBlocks()[i].getBlockY();
        }
    }
    while(!colides(gameBoard, CONTROLDOWN, sh) && (largestY != 19)){
        for(int i = 0; i < shadow.getBlocks().size(); i++){
            shadow.getBlocks()[i].setBlockY(shadow.getBlocks()[i].getBlockY() + 1);
        }
        largestY += 1;
    }
    shadow.renderFigure();

    //Render the figure that is falling
    this->getCurrentFigure()->renderFigure();
    
}

void MainScene::clear(){
    Scene::clear();
    //""
}

void MainScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene){
    //If the setting button is clicked or the user hit ESC open the settings
    if(this->settingsButton.isClicked(&event) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))){
        std::cout << "Settings" << std::endl;
        mScene = curScene;
        curScene = nullptr;
        curScene = new SetScene;
        //mainScene now saves the progres made on the game. Put the var as a global, like curScene
        //find a way to open the settings as a popup (the mainScene still shows on the background). 
    } else if((event.type != SDL_KEYDOWN) && (event.type != SDL_KEYUP)){
        return;
    }

    
    if(((event.key.keysym.sym == CONTROLFASTDOWN) && !spaceBarPressed)){
        int largestY = 0;
        for(unsigned int i = 0; i < this->currentFigure->getBlocks().size(); i++){
            if(this->currentFigure->getBlocks()[i].getBlockY() > largestY){
                largestY = this->currentFigure->getBlocks()[i].getBlockY();
            }
        }
        while(!colides(gameBoard, CONTROLDOWN, currentFigure) && (largestY != 19)){
            currentFigure->getBlocks()[currentFigure->getLeadingBlockPos()].setBlockY(currentFigure->getBlocks()[currentFigure->getLeadingBlockPos()].getBlockY() + 1);
            currentFigure->updateBlocks();
            largestY += 1;
        }
        gameBoard.push_back(currentFigure);
        fetchNextFigure(currentFigure, nextFigures);
        spaceBarPressed = true; 
    } 

    if((event.type == SDL_KEYUP) && (event.key.keysym.sym == CONTROLFASTDOWN)){
        spaceBarPressed = false;
    }
    
    if(colides(this->gameBoard, event.key.keysym.sym, currentFigure)){
        if(event.key.keysym.sym == CONTROLDOWN){
            //calculate the highest point
            if(isDead(gameBoard)){
                dead = true;
            } else{
                gameBoard.push_back(this->currentFigure);
                fetchNextFigure(currentFigure, nextFigures);
            }

        }
    } else{
        currentFigure->update(event);
    }
}

void MainScene::handleLogic(Uint32 * lastTick, Scene *& curScene){
    //IMPLEMENTATION OF THE LOGIC IN THE GAME
    
    Uint32 elapsed = SDL_GetTicks() - *lastTick;
    
    if(elapsed >= FALLSPEED){
        //update the leading block 1 down and reset the ticks
        
        int largestY = 0;
        for(unsigned int i = 0; i < this->currentFigure->getBlocks().size(); i++){
            if(this->currentFigure->getBlocks()[i].getBlockY() > largestY){
                largestY = this->currentFigure->getBlocks()[i].getBlockY();
            }
        }
        
        if((largestY < 19)){
            if(colides(this->gameBoard, CONTROLDOWN, currentFigure)){
                if(isDead(gameBoard)){
                    dead = true;
                } else{
                    gameBoard.push_back(this->currentFigure);
                    fetchNextFigure(currentFigure, nextFigures);
                }
            } else{
                this->currentFigure->getBlocks()[this->currentFigure->getLeadingBlockPos()].setBlockY(this->currentFigure->getBlocks()[this->currentFigure->getLeadingBlockPos()].getBlockY() + 1);
                this->currentFigure->updateBlocks();
            }
        }
        
        *lastTick = SDL_GetTicks();
    }
    
    //when the figure reaches the bottom, place it and change the figure
    int largestY = 0;
    for(unsigned int i = 0; i < this->currentFigure->getBlocks().size(); i++){
        if(this->currentFigure->getBlocks()[i].getBlockY() > largestY){
            largestY = this->currentFigure->getBlocks()[i].getBlockY();
        }
    }
    
    if(largestY == 19){
        gameBoard.push_back(this->currentFigure);
        fetchNextFigure(currentFigure, nextFigures);     
    }
    
    
    //HANDLE LINE ELIMINATION
    
    //calculate the highest point where the figures have gotten to. 
    //Take into account that the y-axis is inverted
    
    int maxHeight = 19;
    for(int i = 0; i < gameBoard.size(); i++){
        for(int j = 0; j < gameBoard[i]->getBlocks().size(); j++){
            if(gameBoard[i]->getBlocks()[j].getBlockY() < maxHeight){
                maxHeight = gameBoard[i]->getBlocks()[j].getBlockY();
            }
        }
    }
    
    int linesCleared = 0;
    
    for(int i = 19; i > maxHeight; i--){
        int blockCount = 0;
        //calculate the number of blocks that are in the current line (i)
        for(int k = 0; k < gameBoard.size(); k++){
            for(int t = 0; t < gameBoard[k]->getBlocks().size(); t++){
                if(gameBoard[k]->getBlocks()[t].getBlockY() == i){
                    blockCount += 1;
                }
            }
        }
        
        if(blockCount == 10){//the line is filled
            LINES += 1;
            linesCleared += 1;
            for(int k = 0; k < gameBoard.size(); k++){
                for(int t = 0; t < gameBoard[k]->getBlocks().size(); t++){
                    if(gameBoard[k]->getBlocks()[t].getBlockY() == i){
                        gameBoard[k]->getBlocks().erase(gameBoard[k]->getBlocks().cbegin() + t);
                        t--;
                    }
                }
            }
            
            //check if there where figures that have no blocks
            for(int k = 0; k < gameBoard.size(); k++){
                if(gameBoard[k]->getBlocks().size() == 0){
                    delete gameBoard[k];
                    gameBoard.erase(gameBoard.cbegin() + k);
                    k--;
                }
            }
            
            for(unsigned int j = 0; j < this->gameBoard.size(); j++){
                for(int k = 0; k < gameBoard[j]->getBlocks().size(); k++){
                    if(gameBoard[j]->getBlocks()[k].getBlockY() < i){
                        gameBoard[j]->getBlocks()[k].setBlockY(gameBoard[j]->getBlocks()[k].getBlockY() + 1);
                    }
                }
            }
            i++;
        }
    }
    POINTS += calculatePoints(linesCleared);
    LEVEL = getLevel();
    FALLSPEED = getFallSpeed();
    
    
    if(dead){
        curScene = nullptr;
        curScene = new LooseScene;
        return;
    }
}

Figure * MainScene::getCurrentFigure(){
    return this->currentFigure;
}


void getRandomFigure(Figure *& curFigure, Figure * lastFigs[]) {

    curFigure = nullptr;
    bool valid = false;

    while (!valid) {

        //Random generator
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> rnd6(0,6);

        int id;
        Figure* newFig = nullptr;

        switch (rnd6(dev)) {
            case 0: id = 0; newFig = new FigL; break;
            case 1: id = 1; newFig = new FigLRight; break;
            case 2: id = 2; newFig = new FigSquare; break;
            case 3: id = 3; newFig = new FigStick; break;
            case 4: id = 4; newFig = new FigT; break;
            case 5: id = 5; newFig = new FigZ; break;
            case 6: id = 6; newFig = new FigZLeft; break;
        }

        valid = true;
        for (int i = 0; i < 3; i++) {
            if (lastFigs[i] != nullptr && lastFigs[i]->getId() == id) {
                valid = false;
                break;
            }
        }

        if (valid) {
            curFigure = newFig;
        } else {
            delete newFig;
        }
    }
}

void getRandomFigure(Figure *& Figure){
    Figure = nullptr;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rnd6(0,6);

    switch (rnd6(dev)){
    case 0:
        Figure = new FigL;
        break;
    case 1:
        Figure = new FigLRight;
        break;
    case 2:
        Figure = new FigSquare;
        break;
    case 3:
        Figure = new FigZ;
        break;
    case 4:
        Figure = new FigZLeft;
        break;
    case 5:
        Figure = new FigT;
        break;
    case 6:
        Figure = new FigStick;
        break;
    default:
        break;
    }
}

void fetchNextFigure(Figure *& curFigure, Figure * nextFigs[]){
    curFigure = nextFigs[0]; 
    nextFigs[0] = nextFigs[1];
    nextFigs[1] = nextFigs[2];
    Figure * arr[] = {curFigure, nextFigs[0], nextFigs[1]};
    getRandomFigure(nextFigs[2], arr);
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
    
     if(CONTROLLEFT == key){

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

     if(CONTROLRIGHT == key){

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

     if(CONTROLROTATE == key){
        
        Figure FigTemp = *curFigure;

        FigTemp.rotate();


        for(int i = 0; i < (int) gameBoard.size(); i++){
            for(int j = 0; j < (int) gameBoard[i]->getBlocks().size(); j++){
                for(int k = 0; k < (int) FigTemp.getBlocks().size(); k++){
                    if((gameBoard[i]->getBlocks()[j].getBlockX() == FigTemp.getBlocks()[k].getBlockX()) &&
                    (gameBoard[i]->getBlocks()[j].getBlockY() == FigTemp.getBlocks()[k].getBlockY())){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    return false;
}

bool isDead(std::vector <Figure*> gameBoard){
    //calculate the highest point
    int maxHeight = 19;
    for(int i = 0; i < gameBoard.size(); i++){
        for(int j = 0; j < gameBoard[i]->getBlocks().size(); j++){
            if(gameBoard[i]->getBlocks()[j].getBlockY() < maxHeight){
                maxHeight = gameBoard[i]->getBlocks()[j].getBlockY();
            }
        }
    }
    if(maxHeight == 0){
        return true;
    }
    return false;
}

void renderNextFigures(Figure * nextFigs[], int nextBgH){
    //Faster access
    int x = FSX;
    int y = FSY + nextBgH;
    int w = FSW;
    int h = FSH - nextBgH;

    //Make a copy of the figures that will be comming next
    Figure figs[3];
    figs[0] = *nextFigs[0];
    figs[1] = *nextFigs[1];
    figs[2] = *nextFigs[2];
    
    int spacing =(int) ((h - BLOCKLENGTH*6)/4);


    for(int i = 0; i < 3; i++){
        //I'll brute force it bc I cn't come up with a clever way to move the figures to the desired position. What comes next is horrible but I didn't find a single way to generalise it
        switch(figs[i].getId()){
            case 0:
                //FigL
                figs[i].getBlocks()[0].setPixelXDereferenced(x + w/2 - (BLOCKLENGTH + BLOCKLENGTH/2));
                figs[i].getBlocks()[0].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[1].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                figs[i].getBlocks()[1].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[2].setPixelXDereferenced(x + w/2 + BLOCKLENGTH/2);
                figs[i].getBlocks()[2].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[3].setPixelXDereferenced(x + w/2 + BLOCKLENGTH/2);
                figs[i].getBlocks()[3].setPixelYDereferenced(y + spacing + i*(BLOCKLENGTH*2 + spacing));

                break;
            case 1:
                //FigLRight
                figs[i].getBlocks()[0].setPixelXDereferenced(x + w/2 - (BLOCKLENGTH + BLOCKLENGTH/2));
                figs[i].getBlocks()[0].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[1].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                figs[i].getBlocks()[1].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[2].setPixelXDereferenced(x + w/2 + BLOCKLENGTH/2);
                figs[i].getBlocks()[2].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[3].setPixelXDereferenced(x + w/2 - (BLOCKLENGTH + BLOCKLENGTH/2));
                figs[i].getBlocks()[3].setPixelYDereferenced(y + spacing + i*(BLOCKLENGTH*2 + spacing));
                break;
             case 2:
                //FigSquare
                figs[i].getBlocks()[0].setPixelXDereferenced(x + w/2 - BLOCKLENGTH);
                figs[i].getBlocks()[0].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[1].setPixelXDereferenced(x + w/2);
                figs[i].getBlocks()[1].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[2].setPixelXDereferenced(x + w/2);
                figs[i].getBlocks()[2].setPixelYDereferenced(y + spacing + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[3].setPixelXDereferenced(x + w/2 - BLOCKLENGTH);
                figs[i].getBlocks()[3].setPixelYDereferenced(y + spacing + i*(BLOCKLENGTH*2 + spacing));
                break;
            case 3:
                //FigStick
                figs[i].getBlocks()[0].setPixelXDereferenced(x + w/2 - BLOCKLENGTH*2);
                figs[i].getBlocks()[0].setPixelYDereferenced(y + spacing + BLOCKLENGTH/2 + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[1].setPixelXDereferenced(x + w/2 - BLOCKLENGTH);
                figs[i].getBlocks()[1].setPixelYDereferenced(y + spacing + BLOCKLENGTH/2 + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[2].setPixelXDereferenced(x + w/2);
                figs[i].getBlocks()[2].setPixelYDereferenced(y + spacing + BLOCKLENGTH/2 + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[3].setPixelXDereferenced(x + w/2 + BLOCKLENGTH);
                figs[i].getBlocks()[3].setPixelYDereferenced(y + spacing + BLOCKLENGTH/2 + i*(BLOCKLENGTH*2 + spacing));
                break;
            case 4:
                //FigT
                figs[i].getBlocks()[0].setPixelXDereferenced(x + w/2 - (BLOCKLENGTH + BLOCKLENGTH/2));
                figs[i].getBlocks()[0].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[1].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                figs[i].getBlocks()[1].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[2].setPixelXDereferenced(x + w/2 + BLOCKLENGTH/2);
                figs[i].getBlocks()[2].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[3].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                figs[i].getBlocks()[3].setPixelYDereferenced(y + spacing + i*(BLOCKLENGTH*2 + spacing));
                break;
            case 5:
                //FigZ
                figs[i].getBlocks()[0].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                figs[i].getBlocks()[0].setPixelYDereferenced(y + spacing + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[1].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                figs[i].getBlocks()[1].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[2].setPixelXDereferenced(x + w/2 + BLOCKLENGTH/2);
                figs[i].getBlocks()[2].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[3].setPixelXDereferenced(x + w/2 - (BLOCKLENGTH + BLOCKLENGTH/2));
                figs[i].getBlocks()[3].setPixelYDereferenced(y + spacing + i*(BLOCKLENGTH*2 + spacing));
                break;
            case 6:
                //FigZLeft
                figs[i].getBlocks()[0].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                figs[i].getBlocks()[0].setPixelYDereferenced(y + spacing + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[1].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                figs[i].getBlocks()[1].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[2].setPixelXDereferenced(x + w/2 - (BLOCKLENGTH + BLOCKLENGTH/2));
                figs[i].getBlocks()[2].setPixelYDereferenced(y + spacing + BLOCKLENGTH + i*(BLOCKLENGTH*2 + spacing));

                figs[i].getBlocks()[3].setPixelXDereferenced(x + w/2 + BLOCKLENGTH/2);
                figs[i].getBlocks()[3].setPixelYDereferenced(y + spacing + i*(BLOCKLENGTH*2 + spacing));
                break;
        }
        figs[i].renderFigure();
    }
    

}