#include "MainScene.h"

#include <iostream>
#include <random>

MainScene::MainScene(){

    Button settingsButton(mainScreen.getWidth() - 75, mainScreen.getHeight() - 75, 50, 50, WHITE, &mainScreen);
    getButtonMap()["settings"] = settingsButton;

    //Load the next 3 random figures 

        getRandomFigure(nextFigures[0]);
        getRandomFigure(nextFigures[1]);
        getRandomFigure(nextFigures[2]);

    //Once the three figures are loaded, move all of them one to the left, adding a new one to the end
    //and making the first one the current figure. This way the scene is automatically handled here.
    //From now on, it will only be necessary to call this method, as the nextFigures array is already 
    //loaded

        fetchNextFigure(currentFigure, nextFigures);
}

MainScene::~MainScene(){
    
    //As the vector contains pointers, we first need to free what is being pointed by them

        for(int i = 0; i < (int) gameBoard.size(); i++){
            delete gameBoard[i];
        }
    gameBoard.~vector();

    delete currentFigure;

    delete nextFigures[0];
    delete nextFigures[1];
    delete nextFigures[2];

    Scene::~Scene();
}

void MainScene::render(){

    //draw a white background

        SDL_SetRenderDrawColor(mainScreen.getRender(), WHITE.r, WHITE.g, WHITE.b, WHITE.a);
        SDL_RenderClear(mainScreen.getRender());

    //draw the background square where the figures fall and the game is played

        SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        SDL_Rect boardBackogrund = {BSX, BSY, BSW, BSH};
        SDL_RenderFillRect(mainScreen.getRender(), &boardBackogrund);

    //draw the vertical and hor. lines that separate each tile 

        SDL_SetRenderDrawColor(mainScreen.getRender(), GREY.r - 30, GREY.g - 30, GREY.b - 30, GREY.a);
        
        //vertical
        for(int i = 1; i <= 10; i++){
            SDL_RenderDrawLine(mainScreen.getRender(), BLOCKLENGTH*i + BSX, BSY, BLOCKLENGTH*i + BSX, BSY + BSH);
        }

        //horizontal
        for(int j = 1; j <= 20; j++){
            SDL_RenderDrawLine(mainScreen.getRender(), BSX, BSY + j*BLOCKLENGTH, BSX + BSW, BSY + j*BLOCKLENGTH);
        }


    //load an image for the settings button. Use the dimensions of the button

        Image settingsImage(getButtonMap()["settings"].getContainer().x, 
                            getButtonMap()["settings"].getContainer().y, 
                            getButtonMap()["settings"].getContainer().w + 10,
                            getButtonMap()["settings"].getContainer().h + 10, "OpScene-settings", "png");
    
        getButtonMap()["settings"].setImage(&settingsImage);

        getButtonMap()["settings"].drawToRender();



    //Draw the next figures background
    
        SDL_Rect nextFiguresBackground = {FSX, FSY, FSW, FSH};

        SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, 230);

        SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(mainScreen.getRender(), &nextFiguresBackground);
        SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_NONE);

    //Draw an outline to the background rectangle

        SDL_SetRenderDrawColor(mainScreen.getRender(), GREY.r, GREY.g, GREY.b, GREY.a);
        SDL_RenderDrawRect(mainScreen.getRender(), &nextFiguresBackground);

    //Set the text of the next figures, the title of the rectangle

        Font next(&mainScreen, "Ubuntu-Bold", 30, "NEXT", TEAL);
        next.setCoords(FSX + FSW/2 - next.getTextSurface()->w/2, FSY);

    //Draw a small rectangle as a background for the title
        
        SDL_Rect nextBg = {FSX, FSY, FSW, next.getTextSurface()->h};
        
        SDL_SetRenderDrawColor(mainScreen.getRender(), WHITE.r, WHITE.g, WHITE.b, WHITE.a);
        SDL_RenderFillRect(mainScreen.getRender(), &nextBg);
        
        //Draw a slight outline
        SDL_SetRenderDrawColor(mainScreen.getRender(), GREY.r, GREY.g, GREY.b, GREY.a);
        SDL_RenderDrawRect(mainScreen.getRender(), &nextBg);
        
    //I'm delaying the rendering of the text, as I want to render it ABOVE the small background
    //we made 

        next.drawTextToRender();
   
    //Render the next figures in order, inside the nextFiguresBackground
    
        renderNextFigures(nextFigures, next.getTextSurface()->h);

    //render the points, the level and the lines info

        SDL_Rect infoBackground = {ISX, ISY, ISW, ISH};

        //This is the same as nextBg but for the level, points and lines titles
        SDL_Rect whiteBar = {ISX, ISY, ISW, ISH/4};

    //We will need a font for each title and number we need to show. The %Num shows the numeric value

        Font level(&mainScreen, "Ubuntu-Bold", whiteBar.h, "LEVEL", TEAL);
        Font levelNum(&mainScreen, "Ubuntu-Bold", whiteBar.h*2, std::to_string(LEVEL).c_str(), WHITE);

        Font points(&mainScreen, "Ubuntu-Bold", whiteBar.h, "POINTS", TEAL);
        Font pointsNum(&mainScreen, "Ubuntu-Bold", whiteBar.h*2, std::to_string(POINTS).c_str(), WHITE);

        Font lines(&mainScreen, "Ubuntu-Bold", whiteBar.h, "LINES", TEAL); 
        Font linesNum(&mainScreen, "Ubuntu-Bold", whiteBar.h*2, std::to_string(LINES).c_str(), WHITE);
    
    //This loop renders all three information boxes

    for(int i = 0; i< 3; i++){

        //Draw the background where the number is placed. It changes it's position depending on the box

            infoBackground = {ISX, ISY + (ISH + BLOCKLENGTH/3)*i, ISW, ISH};
            
            
            SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, 230);
            SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);
            
            SDL_RenderFillRect(mainScreen.getRender(), &infoBackground);
            SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_NONE);
            
        //Draw the background of the titles. It changes it's position depending on the box

            whiteBar = {ISX, ISY + (ISH + BLOCKLENGTH/3)*i, ISW, ISH/4};
            
            SDL_SetRenderDrawColor(mainScreen.getRender(), WHITE.r, WHITE.g, WHITE.b, WHITE.a);
            SDL_RenderFillRect(mainScreen.getRender(), &whiteBar);

            SDL_SetRenderDrawColor(mainScreen.getRender(), GREY.r, GREY.g, GREY.b, GREY.a);
            SDL_RenderDrawRect(mainScreen.getRender(), &whiteBar);
        
        switch (i){
        case 0:
            //Points box

            points.setCoords(whiteBar.x + whiteBar.w/2 - points.getTextSurface()->w/2, whiteBar.y);
            points.drawTextToRender();
        
            pointsNum.setCoords(whiteBar.x + whiteBar.w/2 - pointsNum.getTextSurface()->w/2,
                                whiteBar.y + whiteBar.h + (infoBackground.h - whiteBar.h)/2 - pointsNum.getTextSurface()->h/2);
            pointsNum.drawTextToRender();

            break;
        case 1:
            //Lines box

            lines.setCoords(whiteBar.x + whiteBar.w/2 - lines.getTextSurface()->w/2, whiteBar.y);
            lines.drawTextToRender();
        
            linesNum.setCoords(whiteBar.x + whiteBar.w/2 - linesNum.getTextSurface()->w/2,
                               whiteBar.y + whiteBar.h + (infoBackground.h - whiteBar.h)/2 - linesNum.getTextSurface()->h/2);
            linesNum.drawTextToRender();

            break;
        case 2:
            //Level box

            level.setCoords(whiteBar.x + whiteBar.w/2 - level.getTextSurface()->w/2, whiteBar.y);
            level.drawTextToRender();
        
            levelNum.setCoords(whiteBar.x + whiteBar.w/2 - levelNum.getTextSurface()->w/2,
                               whiteBar.y + whiteBar.h + (infoBackground.h - whiteBar.h)/2 - levelNum.getTextSurface()->h/2);
            levelNum.drawTextToRender();

            break;
        }
    }


    //render all the figures that are already placed

        for(unsigned int i = 0; i < gameBoard.size(); i++){
            gameBoard[i]->renderFigure();
        }

    //render the shadow of the current figure. Make a copy of the currentFigure to freely render it
        
        Figure shadow = *currentFigure;

        //reference to the copied figure
        Figure * sh = &shadow;

        //Only draw the outline of the figure
        shadow.setFigureColor(BLACK);

        //We first calculate the real smallest Y coordinate of the figure
        int smallestY = 0;
        for(unsigned int i = 0; i < shadow.getBlocks().size(); i++){
            if(shadow.getBlocks()[i].getBlockY() > smallestY){
                smallestY = shadow.getBlocks()[i].getBlockY();
            }
        }

        //In each iteration we will check if it is "safe" to move the shadow one position down. 
        //When we get to the point where moving the shadow 1 pos. down will cause it to overlap, stop
        while(!colides(gameBoard, CONTROLDOWN, sh) && (smallestY != 19)){
            for(int i = 0; i < (int) shadow.getBlocks().size(); i++){
                shadow.getBlocks()[i].setBlockY(shadow.getBlocks()[i].getBlockY() + 1);
            }
            smallestY += 1;
        }

        shadow.renderFigure();

    //Render the figure that is falling

        currentFigure->renderFigure();
    
}

void MainScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene){

    //If the settings button is clicked or the user hit ESC open the settings
    if(getButtonMap()["settings"].isClicked(&event) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))){
        mScene = curScene;
        curScene = nullptr;
        curScene = new SetScene;

        //mainScene now saves the progres made on the game even if the settings is opened

    } else if((event.type != SDL_KEYDOWN) && (event.type != SDL_KEYUP)){
        //Events that are not pressing keys are not handled
        return;
    }

    //move this into update if you can
    if(((event.key.keysym.sym == CONTROLFASTDOWN) && !spaceBarPressed)){
        int largestY = 0;
        for(unsigned int i = 0; i < currentFigure->getBlocks().size(); i++){
            if(currentFigure->getBlocks()[i].getBlockY() > largestY){
                largestY = currentFigure->getBlocks()[i].getBlockY();
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
    
    // if((event.type == SDL_KEYUP) && (event.key.keysym.sym == CONTROLROTATE)){
    //     rotateKeyPressed = false;
    // }

    
    if(colides(gameBoard, event.key.keysym.sym, currentFigure)){
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
    if(dead){
        curScene = nullptr;
        curScene = new LooseScene;
    }
    
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
    for(int i = 0; i < (int) gameBoard.size(); i++){
        for(int j = 0; j < (int) gameBoard[i]->getBlocks().size(); j++){
            if(gameBoard[i]->getBlocks()[j].getBlockY() < maxHeight){
                maxHeight = gameBoard[i]->getBlocks()[j].getBlockY();
            }
        }
    }
    
    int linesCleared = 0;
    
    for(int i = 19; i > maxHeight; i--){
        int blockCount = 0;
        //calculate the number of blocks that are in the current line (i)
        for(int k = 0; k < (int) gameBoard.size(); k++){
            for(int t = 0; t < (int) gameBoard[k]->getBlocks().size(); t++){
                if(gameBoard[k]->getBlocks()[t].getBlockY() == i){
                    blockCount += 1;
                }
            }
        }
        
        if(blockCount == 10){//the line is filled
            LINES += 1;
            linesCleared += 1;
            for(int k = 0; k < (int) gameBoard.size(); k++){
                for(int t = 0; t < (int) gameBoard[k]->getBlocks().size(); t++){
                    if(gameBoard[k]->getBlocks()[t].getBlockY() == i){
                        gameBoard[k]->getBlocks().erase(gameBoard[k]->getBlocks().cbegin() + t);
                        t--;
                    }
                }
            }
            
            //check if there where figures that have no blocks
            for(int k = 0; k < (int) gameBoard.size(); k++){
                if(gameBoard[k]->getBlocks().size() == 0){
                    delete gameBoard[k];
                    gameBoard.erase(gameBoard.cbegin() + k);
                    k--;
                }
            }
            
            for(int j = 0; j < (int) gameBoard.size(); j++){
                for(int k = 0; k < (int) gameBoard[j]->getBlocks().size(); k++){
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
            case 1: id = 1; newFig = new FigJ; break;
            case 2: id = 2; newFig = new FigO; break;
            case 3: id = 3; newFig = new FigI; break;
            case 4: id = 4; newFig = new FigT; break;
            case 5: id = 5; newFig = new FigS; break;
            case 6: id = 6; newFig = new FigZ; break;
        }

        valid = true;

        //make sure the figures don't repeat in a range of 3
        for (int i = 0; i < 3; i++) {
            if (lastFigs[i] != nullptr && lastFigs[i]->getId() == id){
                valid = false;
                break;
            }
        }

        if (valid) {
            curFigure = newFig;
        } else{
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
        Figure = new FigJ;
        break;
    case 2:
        Figure = new FigO;
        break;
    case 3:
        Figure = new FigS;
        break;
    case 4:
        Figure = new FigZ;
        break;
    case 5:
        Figure = new FigT;
        break;
    case 6:
        Figure = new FigI;
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

    //What I'm doing here is to treat the new figure that will be inserted into the array as if it was the currentFigure
    getRandomFigure(nextFigs[2], arr);
}

//return true if the figure colides with any other figure of the gameboard
bool colides(std::vector <Figure*> gameBoard, SDL_Keycode key, Figure *&figure){

    if(CONTROLDOWN == key){

        for(int i = 0; i < (int) gameBoard.size(); i++){
            for(int j = 0; j < (int) gameBoard[i]->getBlocks().size(); j++){
                for(int k = 0; k < (int) figure->getBlocks().size(); k++){
                    if((gameBoard[i]->getBlocks()[j].getBlockX() == figure->getBlocks()[k].getBlockX()) &&
                       (gameBoard[i]->getBlocks()[j].getBlockY() == (figure->getBlocks()[k].getBlockY() + 1))){
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
                for(int k = 0; k < (int) figure->getBlocks().size(); k++){
                    if((gameBoard[i]->getBlocks()[j].getBlockX() == figure->getBlocks()[k].getBlockX() - 1) &&
                    (gameBoard[i]->getBlocks()[j].getBlockY() == figure->getBlocks()[k].getBlockY())){
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
                for(int k = 0; k < (int) figure->getBlocks().size(); k++){
                    if((gameBoard[i]->getBlocks()[j].getBlockX() == figure->getBlocks()[k].getBlockX() + 1) &&
                    (gameBoard[i]->getBlocks()[j].getBlockY() == figure->getBlocks()[k].getBlockY())){
                        return true;
                    }
                }
            }
        }
        return false;
    }

     if(CONTROLROTATE == key){
        
        Figure RotatedFigure = *figure;

        RotatedFigure.rotate();


        for(int i = 0; i < (int) gameBoard.size(); i++){
            for(int j = 0; j < (int) gameBoard[i]->getBlocks().size(); j++){
                for(int k = 0; k < (int) RotatedFigure.getBlocks().size(); k++){
                    if((gameBoard[i]->getBlocks()[j].getBlockX() == RotatedFigure.getBlocks()[k].getBlockX()) &&
                    (gameBoard[i]->getBlocks()[j].getBlockY() == RotatedFigure.getBlocks()[k].getBlockY())){
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

    //calculate the highest point. Note that the y-axis is inverted, and 0 > 19 in our system

    int maxHeight = 19;
    for(int i = 0; i < (int) gameBoard.size(); i++){
        for(int j = 0; j < (int) gameBoard[i]->getBlocks().size(); j++){

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
    //The dimensions of the nextFiguresBackground
    int x = FSX;
    int y = FSY + nextBgH;
    int w = FSW;
    int h = FSH - nextBgH;

    //Make a copy of the figures that will be comming next. Note that we
    //are not saving pointers to figures, but figures directly

        Figure figs[3];
        figs[0] = *nextFigs[0];
        figs[1] = *nextFigs[1];
        figs[2] = *nextFigs[2];
    
    int spacing = (int) ((h - BLOCKLENGTH*6)/4);

    //This loop renders the three figures from highest to lowest (the figure that is higher is the closest to being fetched to the gameboard
    //and so on). Note that we need to position the figures in the correct place; this is what the loop is doing. At the end it will also render
    //the figure
    for(int i = 0; i < 3; i++){

        //Choose which figure we are dealing to
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

                //FigO

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

                //FigI

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

                //FigS

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

                //FigZ

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