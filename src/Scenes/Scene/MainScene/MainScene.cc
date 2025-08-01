#include "MainScene.h"

#include <iostream>

MainScene::MainScene(){
    updateKeybindsFile();

    explosionEffect.load("src/Sounds/Effects/explosion.wav");

    explosionEffect.setVolume(EFFECTSSOUNDLVL);

    Button settingsButton({mainScreen.getWidth() - 70, mainScreen.getHeight() - 70, 60, 60}, WHITE, &mainScreen);
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

        Image background(0,0,SCREENWIDTH, SCREENHEIGHT, "MainScene-background/blocks", "png");

        background.setAsBackground();

        background.CopyToRender();


    //Draw the next figures background

        SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, 230);

        Image nextFigsBg(0, 0, SCREENWIDTH, SCREENHEIGHT, "MainScene-background/blue-bg", "png");

        nextFigsBg.CopyToRender();

        Image skyBg(0, 0, SCREENWIDTH, SCREENHEIGHT, "MainScene-background/sky", "png");

        skyBg.CopyToRender();


    //draw the vertical and hor. lines that separate each tile 

        SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(mainScreen.getRender(), GREY.r - 30, GREY.g - 30, GREY.b - 30, 100);
        SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_NONE);
        
        //vertical
        for(int i = 1; i <= 10; i++){
            SDL_RenderDrawLine(mainScreen.getRender(), BLOCKLENGTH*i + BSX, BSY, BLOCKLENGTH*i + BSX, BSY + BSH);
        }

        //horizontal
        for(int j = 1; j <= 20; j++){
            SDL_RenderDrawLine(mainScreen.getRender(), BSX, BSY + j*BLOCKLENGTH, BSX + BSW, BSY + j*BLOCKLENGTH);
        }



    //Set the text of the next figures, the title of the rectangle

        Font next(&mainScreen, "04B_30__", 30, "NEXT", TEAL);      

    //Render the next figures in order, inside the nextFiguresBackground
    
        renderNextFigures(nextFigures, next.getTextSurface()->h - 25);

    //render the points, the level and the lines info

        SDL_Rect infoBackground = {ISX, ISY, ISW, ISH};

        //This is the same as nextBg but for the level, points and lines titles
        SDL_Rect whiteBar = {ISX, ISY, ISW, ISH/4};

    //We will need a font for each title and number we need to show. The %Num shows the numeric value

        Font levelNum(&mainScreen, "04B_30__", whiteBar.h*2, std::to_string(LEVEL).c_str(), CIANSH);

        Font pointsNum(&mainScreen, "04B_30__", whiteBar.h*2, std::to_string(POINTS).c_str(), CIANSH);

        Font linesNum(&mainScreen, "04B_30__", whiteBar.h*2, std::to_string(LINES).c_str(), CIANSH);
    
    //This loop renders all three information boxes

    for(int i = 0; i< 3; i++){

        //Draw the background where the number is placed. It changes it's position depending on the box

            infoBackground = {ISX, ISY + (ISH + BLOCKLENGTH/3)*i, ISW, ISH};
            
            
            SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, 230);
            SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);
            
        //Draw the background of the titles. It changes it's position depending on the box

            whiteBar = {ISX, ISY + (ISH + BLOCKLENGTH/3)*i, ISW, ISH/4};
        
        switch (i){
        case 0:
            //Points box

            pointsNum.setCoords(whiteBar.x + whiteBar.w/2 - pointsNum.getTextSurface()->w/2,
                                whiteBar.y + whiteBar.h + (infoBackground.h - whiteBar.h)/2 - pointsNum.getTextSurface()->h/2 - 10);
            pointsNum.drawTextToRender();

            break;
        case 1:
            //Lines box
        
            linesNum.setCoords(whiteBar.x + whiteBar.w/2 - linesNum.getTextSurface()->w/2,
                               whiteBar.y + whiteBar.h + (infoBackground.h - whiteBar.h)/2 - linesNum.getTextSurface()->h/2 - 3);
            linesNum.drawTextToRender();

            break;
        case 2:
            //Level box
        
            levelNum.setCoords(whiteBar.x + whiteBar.w/2 - levelNum.getTextSurface()->w/2,
                               whiteBar.y + whiteBar.h + (infoBackground.h - whiteBar.h)/2 - levelNum.getTextSurface()->h/2 - 5);
            levelNum.drawTextToRender();

            break;
        }
    }

    //Render the background for the hold figure

        SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);

        if(heldFigure == nullptr){

            Font holdText(&mainScreen, "04B_30__", 50, "HOLD", {LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, 100});
            
            holdText.setCoords(HFX + HFW/2 - holdText.getTextSurface()->w/2, HFY + HFH/2 - holdText.getTextSurface()->h/2);
            
            SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);
            holdText.drawTextToRender();
            SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_NONE);
        }


        if(heldFigure != nullptr){
            Figure * fig = heldFigure;

            changeSwappedFigurePosition(fig);
            fig->renderFigure();
        }

    //render all the figures that are already placed

        for(unsigned int i = 0; i < gameBoard.size(); i++){
            gameBoard[i]->renderFigure();
        }

    //render the shadow of the current figure. Make a copy of the currentFigure to freely render it
        
        Figure shadow = *currentFigure;

        //reference to the copied figure
        Figure * sh = &shadow;
        for(int i = 0; i < (int) shadow.getBlocks().size(); i++){
            SDL_SetTextureAlphaMod(shadow.getBlocks()[i].getBlockTexture(), 30);
        }
        
        SDL_Color colorInline = shadow.getBlocks()[0].getInlineColor();
        SDL_Color colorOutline = shadow.getBlocks()[0].getOutlineColor();

        colorInline.a = 50;
        colorOutline.a = 140;
        for(int i = 0; i < (int) shadow.getBlocks().size(); i++){
            shadow.getBlocks()[i].setInlineColor(colorInline);
            shadow.getBlocks()[i].setOutlineColor(colorOutline);
        }

        //We first calculate the real smallest Y coordinate of the figure
        int smallestY = 0;

        for(unsigned int i = 0; i < shadow.getBlocks().size(); i++){
            if(shadow.getBlocks()[i].getBlockY() > smallestY){
                smallestY = shadow.getBlocks()[i].getBlockY();
            }
        }

        //In each iteration we will check if it is "safe" to move the shadow one position down. 
        //When we get to the point where moving the shadow 1 pos. down will cause it to overlap, stop
        while(!collides(gameBoard, CONTROLDOWN, sh) && (smallestY != 19)){
            for(int i = 0; i < (int) shadow.getBlocks().size(); i++){
                shadow.getBlocks()[i].setBlockY(shadow.getBlocks()[i].getBlockY() + 1);

                //If we detect a block of the shadow that is outside of the grid, we'll move the figure
                //the number of tiles the block we found is outside. I do this because of a very specific
                //thing. When a figure is out of bounds it gets pushed back inside, but the shadow doesn't.
                //Sometimes the shadow is seen outside the grid even though the figure is inside. 

                    if(shadow.getBlocks()[i].getBlockX() < 0){

                        int offset = -shadow.getBlocks()[i].getBlockX();

                        for(int j = 0; j < (int) shadow.getBlocks().size(); j++){
                            shadow.getBlocks()[j].setBlockX(shadow.getBlocks()[j].getBlockX() + offset);
                        }
                    }
                    else if(shadow.getBlocks()[i].getBlockX() > 19){

                        int offset = 19 - shadow.getBlocks()[i].getBlockX();

                        for(int j = 0; j < (int) shadow.getBlocks().size(); j++){
                            shadow.getBlocks()[j].setBlockX(shadow.getBlocks()[j].getBlockX() - offset);
                        }
                    }
            }
            smallestY += 1;
        }

        SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);
        shadow.renderFigure();
        SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_NONE);

        for(int i = 0; i < (int) shadow.getBlocks().size(); i++){
            SDL_SetTextureAlphaMod(shadow.getBlocks()[i].getBlockTexture(), 255);
        }

    //Render the figure that is falling

        currentFigure->renderFigure();

    Image borders(0,0, SCREENWIDTH, SCREENHEIGHT, "MainScene-background/border", "png");

    borders.CopyToRender();
    
}

void MainScene::renderWithoutFigures(){

    //draw a white background

        SDL_SetRenderDrawColor(mainScreen.getRender(), WHITE.r, WHITE.g, WHITE.b, 100);
        SDL_RenderClear(mainScreen.getRender());

        Image background(0, 0, SCREENWIDTH, SCREENHEIGHT, "MainScene-background/blocks", "png");

        background.setAsBackground();

        background.CopyToRender();

    //Draw the next figures background

        SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, 100);

        Image nextFigsBg(0, 0, SCREENWIDTH, SCREENHEIGHT, "MainScene-background/blue-bg", "png");

        nextFigsBg.CopyToRender();

        Image skyBg(0, 0, SCREENWIDTH, SCREENHEIGHT, "MainScene-background/sky", "png");

        skyBg.CopyToRender();


    //draw the vertical and hor. lines that separate each tile 

        SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(mainScreen.getRender(), GREY.r - 30, GREY.g - 30, GREY.b - 30, 100);
        SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_NONE);
        
        //vertical
        for(int i = 1; i <= 10; i++){
            SDL_RenderDrawLine(mainScreen.getRender(), BLOCKLENGTH*i + BSX, BSY, BLOCKLENGTH*i + BSX, BSY + BSH);
        }

        //horizontal
        for(int j = 1; j <= 20; j++){
            SDL_RenderDrawLine(mainScreen.getRender(), BSX, BSY + j*BLOCKLENGTH, BSX + BSW, BSY + j*BLOCKLENGTH);
        }


    //Draw an outline to the background rectangle

    //Set the text of the next figures, the title of the rectangle

        Font next(&mainScreen, "04B_30__", 30, "NEXT", TEAL);

    //render the points, the level and the lines info

        SDL_Rect infoBackground = {ISX, ISY, ISW, ISH};

        //This is the same as nextBg but for the level, points and lines titles
        SDL_Rect whiteBar = {ISX, ISY, ISW, ISH/4};

    //We will need a font for each title and number we need to show. The %Num shows the numeric value

        Font levelNum(&mainScreen, "04B_30__", whiteBar.h*2, std::to_string(LEVEL).c_str(), CIANSH);

        Font pointsNum(&mainScreen, "04B_30__", whiteBar.h*2, std::to_string(POINTS).c_str(), CIANSH);

        Font linesNum(&mainScreen, "04B_30__", whiteBar.h*2, std::to_string(LINES).c_str(), CIANSH);
    
    //This loop renders all three information boxes

    for(int i = 0; i< 3; i++){

        //Draw the background where the number is placed. It changes it's position depending on the box

            infoBackground = {ISX, ISY + (ISH + BLOCKLENGTH/3)*i, ISW, ISH};
            
            
            SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, 100);
            SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);
            
        //Draw the background of the titles. It changes it's position depending on the box

            whiteBar = {ISX, ISY + (ISH + BLOCKLENGTH/3)*i, ISW, ISH/4};
        
        switch (i){
        case 0:
            //Points box

        
            pointsNum.setCoords(whiteBar.x + whiteBar.w/2 - pointsNum.getTextSurface()->w/2,
                                whiteBar.y + whiteBar.h + (infoBackground.h - whiteBar.h)/2 - pointsNum.getTextSurface()->h/2 - 10);
            pointsNum.drawTextToRender();

            break;
        case 1:
            //Lines box
        
            linesNum.setCoords(whiteBar.x + whiteBar.w/2 - linesNum.getTextSurface()->w/2,
                               whiteBar.y + whiteBar.h + (infoBackground.h - whiteBar.h)/2 - linesNum.getTextSurface()->h/2 - 3);
            linesNum.drawTextToRender();

            break;
        case 2:
            //Level box
        
            levelNum.setCoords(whiteBar.x + whiteBar.w/2 - levelNum.getTextSurface()->w/2,
                               whiteBar.y + whiteBar.h + (infoBackground.h - whiteBar.h)/2 - levelNum.getTextSurface()->h/2 - 5);
            levelNum.drawTextToRender();

            break;
        }
    }

    //Render the background for the hold figure

        SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, 100);

        if(heldFigure == nullptr){

            Font holdText(&mainScreen, "04B_30__", 50, "HOLD", {LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, 100});
            
            holdText.setCoords(HFX + HFW/2 - holdText.getTextSurface()->w/2, HFY + HFH/2 - holdText.getTextSurface()->h/2);
            
            holdText.drawTextToRender();
            SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_NONE);
        }


    Image borders(0,0, SCREENWIDTH, SCREENHEIGHT, "MainScene-background/border", "png");

    borders.CopyToRender();
    
}

void MainScene::handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene, Sound *){

    //Events that are not pressing keys or mousebuttons are not handled
    if((event.type != SDL_KEYDOWN) && (event.type != SDL_KEYUP) && (event.type != SDL_MOUSEBUTTONDOWN)){
        return;
    }

    //If the settings button is clicked or the user hit ESC open the settings
    if(getButtonMap()["settings"].isClicked(&event) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))){
        //mainScene now saves the progres made on the game even if the settings is opened

        Image settingsImage(getButtonMap()["settings"].getContainer().x, 
                            getButtonMap()["settings"].getContainer().y, 
                            getButtonMap()["settings"].getContainer().w,
                            getButtonMap()["settings"].getContainer().h, "MainScene-background/MainScene-button-clicked", "png");

        settingsImage.CopyToRender();

        curScene->update(mainScreen.getRender());

        mScene = curScene;
        curScene = nullptr;
        curScene = new SetScene;
        
        //To make sure there is no delay between opening the settings and the figures 
        //disappearing on the background, the scene without figures is immediately rendered

            mScene->renderWithoutFigures();

        return;
    }

    //Handle the swapping of the figure. The function does everything
    if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == CONTROLSWAP) && !event.key.repeat){
        handleSwap(currentFigure, heldFigure, nextFigures, &numberSwaps, gameBoard);
        return;
    }

    
    bool collision = collides(gameBoard, event.key.keysym.sym, currentFigure);
    
    //If there is no collision then it is safe to update
    if(!collision && !isDead(gameBoard, currentFigure)){
        currentFigure->update(event);
        handleFastDrop(event, currentFigure, *this);

        dead = isDead(gameBoard, currentFigure);
    } 

    //If there will be a collision and the user wants to move the figure down, place the figure.
    //Also check if the user is dead after placing
    
    else if(event.key.keysym.sym == CONTROLDOWN && !isDead(gameBoard, currentFigure)){
        gameBoard.push_back(currentFigure);
        fetchNextFigure(currentFigure, nextFigures);

        //reset
        numberSwaps = 0;

        dead = isDead(gameBoard, currentFigure);
    }

    dead = isDead(gameBoard, currentFigure);
    if(dead){
        render();
        mScene = curScene;
        curScene = nullptr;
        curScene = new LooseScene;
        curScene->render();
    }
}

void MainScene::handleLogic(Uint32 * lastTick, Scene *& curScene, Scene *& mScene){

    //We calculate the current figure's highest y value. It will be reused

        int largestY = 0;

        for(unsigned int i = 0; i < currentFigure->getBlocks().size(); i++){
            if(currentFigure->getBlocks()[i].getBlockY() > largestY){
                largestY = currentFigure->getBlocks()[i].getBlockY();
            }
        }

        //Then we check if the figure is at the bottom
        if(largestY == 19){
            gameBoard.push_back(currentFigure);
            fetchNextFigure(currentFigure, nextFigures);  

            dead = isDead(gameBoard, currentFigure) ? true : false;
            //reset
            numberSwaps = 0;
        }

    //This piece of code updates the figure one position down depending on the interval of time (FALLSPEED).
    //Keep in mind the fallspeed changes depending on the level. Consequently, this block will not execute every time 
    //handleLogic() is called, only when enough time has passed.

        Uint32 elapsed = SDL_GetTicks() - *lastTick;
    
        if(elapsed >= FALLSPEED){   
            //We know for sure the figure's highest y value is at most 18 (if it was 19 it would have been updated).
            //We are guaranteed to have at least one more down movement, so we can execute this code without checking

            //We create an artificial event of moving down. We "simulate" the down key being pressed
            SDL_Event event;
            event.type = SDL_KEYDOWN;
            event.key.keysym.sym = CONTROLDOWN;

            bool collision = collides(gameBoard, event.key.keysym.sym, currentFigure);

            //If there is no collision then it is safe to update
            if(!collision){
                currentFigure->update(event);
            }
            else{
                gameBoard.push_back(currentFigure);
                fetchNextFigure(currentFigure, nextFigures);

                dead = isDead(gameBoard, currentFigure) ? true : false;

                //reset
                numberSwaps = 0;

            }
            
            
            *lastTick = SDL_GetTicks();
        } 

        dead = isDead(gameBoard, currentFigure) ? true : false;

        if(dead){ 

            renderWithoutFigures();
            mScene = curScene;
            curScene = nullptr;
            curScene = new LooseScene;

            return;
        }
        
        
    //At this point, all the events will have been handled (the handleEvents() loop is already called).
    //We also have taken care of automatic falling. This means that at this point the figure cannot
    //move in any way. Also, if it needed to be placed (and consequently belonging to the gameBoard at that moment),
    //it was before this point. Now we have a static gameBoard and a static figure. We need to take care of the lines
    //that need to be cleared
    
    
    //We start by calculating the height of the gameBoard figures. It will be needed later

        int maxHeight = 19;
        
        for(int i = 0; i < (int) gameBoard.size(); i++){
            for(int j = 0; j < (int) gameBoard[i]->getBlocks().size(); j++){
                if(gameBoard[i]->getBlocks()[j].getBlockY() < maxHeight){
                    maxHeight = gameBoard[i]->getBlocks()[j].getBlockY();
                }
            }
        }

    //If there is a line that needs to be cleared, it will be between [19, maxHeight].
    //To check if there is a line that needs to be cleared, we will check all the lines
    //in the range, and see if any of them has 10 blocks of figures in it
    
        int linesCleared = 0; //at most 4
        
        for(int i = 19; i > maxHeight; i--){

            
            //Here we calculate the number of blocks that are in the current line (i)
            //We check all the blocks and see if their y coord. coincides with the current line
            
                int blockCount = 0;

                for(int j = 0; j < (int) gameBoard.size(); j++){
                    for(int k = 0; k < (int) gameBoard[j]->getBlocks().size(); k++){
                        if(gameBoard[j]->getBlocks()[k].getBlockY() == i){
                            blockCount += 1;
                        }
                    }
                }
            
            //If the line has 10 blocks, then it needs to be cleared

            if(blockCount == 10){

                //The total number of cleared lines is updated, as well as the lines of the current tick
                LINES += 1;
                linesCleared += 1;

                //We check all the figures again, deleting the blocks that are in the line, as now we know
                //that the line needs to be cleared
                for(int j = 0; j < (int) gameBoard.size(); j++){
                    for(int k = 0; k < (int) gameBoard[j]->getBlocks().size(); k++){
                        if(gameBoard[j]->getBlocks()[k].getBlockY() == i){
                            gameBoard[j]->getBlocks().erase(gameBoard[j]->getBlocks().cbegin() + k);
                            k--;
                        }
                    }
                }
                
                //Deleting a line by deleting the blocks of the figure can lead to having a figure whose
                //vector of blocks is empty (we delete blocks, but not figures). Here we check if
                //there is a figure with no blocks and delete it from the game board

                    for(int k = 0; k < (int) gameBoard.size(); k++){
                        if(gameBoard[k]->getBlocks().size() == 0){
                            delete gameBoard[k];
                            gameBoard.erase(gameBoard.cbegin() + k);
                            k--;
                        }
                    }

                //Lastly we need to move the blocks that are above our line one position down. We do this by checking
                //if a block y position is bigger than the line. Then we just sum +1 to the blocks y position
                
                    for(int j = 0; j < (int) gameBoard.size(); j++){
                        for(int k = 0; k < (int) gameBoard[j]->getBlocks().size(); k++){
                            if(gameBoard[j]->getBlocks()[k].getBlockY() < i){
                                gameBoard[j]->getBlocks()[k].setBlockY(gameBoard[j]->getBlocks()[k].getBlockY() + 1);
                            }
                        }
                    }
                //Moving the blocks means that the next line we have to check is already the one that we are in.
                i++;
            }
        }
        
        //In the case there are lines cleared, update the general info

            if(linesCleared){
                EFFECTSSOUNDLVL != 0 ? explosionEffect.play() : 0;

                POINTS += calculatePoints(linesCleared);
                LEVEL = getLevel();
                FALLSPEED = getFallSpeed();
            }
}


Figure * MainScene::getCurrentFigure() const{
    return currentFigure;
}

Figure ** MainScene::getNextFigures(){
    return nextFigures;
}

std::vector<Figure*>& MainScene::getGameBoard(){
    return gameBoard;
}

void MainScene::setNumSwaps(int swap){
    numberSwaps = swap;
}

//FUNCTIONS

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

    Figure->setHasTexture(true);

}

void getRandomFigure(Figure *& curFigure, Figure * lastFigs[]) {

    curFigure = nullptr;
    bool valid = false;

    while (!valid) {

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
            curFigure->setHasTexture(true);

        } else{
            delete newFig;
        }
    }
}

void fetchNextFigure(Figure *& curFigure, Figure * nextFigs[]){

    curFigure = nullptr;
    curFigure = nextFigs[0]; 
    nextFigs[0] = nextFigs[1];
    nextFigs[1] = nextFigs[2];

    Figure * arr[] = {curFigure, nextFigs[0], nextFigs[1]};

    //What I'm doing here is to treat the new figure that will be inserted into the array as if it was the currentFigure
    getRandomFigure(nextFigs[2], arr);
}

bool collides(std::vector <Figure*> gameBoard, SDL_Keycode key, Figure * const &figure){

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

     if(CONTROLROTATERIGHT == key){
        
        Figure rotatedFigure = *figure;

        rotatedFigure.rotate();


        for(int i = 0; i < (int) gameBoard.size(); i++){
            for(int j = 0; j < (int) gameBoard[i]->getBlocks().size(); j++){
                for(int k = 0; k < (int) rotatedFigure.getBlocks().size(); k++){
                    if((gameBoard[i]->getBlocks()[j].getBlockX() == rotatedFigure.getBlocks()[k].getBlockX()) &&
                    (gameBoard[i]->getBlocks()[j].getBlockY() == rotatedFigure.getBlocks()[k].getBlockY())){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    //Any other key is not handled
    return false;
}

bool collidesStatic(std::vector <Figure*> gameBoard, Figure *&figure){
    for(int i = 0; i < (int) gameBoard.size(); i++){
        for(int j = 0; j < (int) gameBoard[i]->getBlocks().size(); j++){
            for(int k = 0; k < (int) figure->getBlocks().size(); k++){
                if((gameBoard[i]->getBlocks()[j].getBlockX() == figure->getBlocks()[k].getBlockX()) &&
                   (gameBoard[i]->getBlocks()[j].getBlockY() == figure->getBlocks()[k].getBlockY())){
                    return true;
                }
            }
        }
    }

    int smallestY = 0;
    int largestY = 0;
    int smallestX = 0;
    int largestX = 0;

    for(unsigned int i = 0; i < figure->getBlocks().size(); i++){
        if(figure->getBlocks()[i].getBlockY() > smallestY){
            smallestY = figure->getBlocks()[i].getBlockY();
        }
        if(figure->getBlocks()[i].getBlockY() > smallestX){
            smallestX = figure->getBlocks()[i].getBlockY();
        }
        if(figure->getBlocks()[i].getBlockY() < largestY){
            largestY = figure->getBlocks()[i].getBlockY();
        }
        if(figure->getBlocks()[i].getBlockY() < largestX){
            largestX = figure->getBlocks()[i].getBlockY();
        }
        
    }

    if((smallestX < 0) || (smallestY < 0) || (largestX > 9) || (largestY > 19)){
        return true;
    }


    return false;   
}

void handleFastDrop(SDL_Event event, Figure*& figure, MainScene& m){

    if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == CONTROLFASTDOWN) && !event.key.repeat){

        int largestY = 0;

        for(unsigned int i = 0; i < figure->getBlocks().size(); i++){
            if(figure->getBlocks()[i].getBlockY() > largestY){
                largestY = figure->getBlocks()[i].getBlockY();
            }
        }

        //Move the figure down until it collides
        while(!collides(m.getGameBoard(), CONTROLDOWN, figure) && (largestY != 19)){
            figure->getBlocks()[figure->getLeadingBlockPos()].setBlockY(figure->getBlocks()[figure->getLeadingBlockPos()].getBlockY() + 1);
            figure->updateBlocks();
            largestY += 1;
        }

        m.getGameBoard().push_back(figure);
        fetchNextFigure(figure, m.getNextFigures());
        m.setNumSwaps(0);
    }
}

void renderNextFigures(Figure * nextFigs[], int nextBgH){
    //The dimensions of the nextFiguresBackground
    int x = FSX;
    int y = FSY + nextBgH;
    int w = FSW;
    int h = FSH - nextBgH;

    //Make a copy of the figures that will be coming next. Note that we
    //are not saving pointers to figures, but figures directly

        Figure figs[3];
        figs[0] = *nextFigs[0];
        figs[1] = *nextFigs[1];
        figs[2] = *nextFigs[2];
    
    int spacing = (int) ((h - BLOCKLENGTH*6)/4);

    //This loop renders the three figures from highest to lowest (the figure that is higher is the closest to being fetched to the game board
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

bool isDead(std::vector <Figure*> gameBoard, Figure *& currentFigure){
    if(collidesStatic(gameBoard, currentFigure)){
        return true;
    }
    return false;
}

void handleSwap(Figure *& fallingFigure, Figure *& heldFigure, Figure * nextFigs[], int * numSwaps, std::vector <Figure*> gameBoard){
    if(heldFigure == nullptr){
        heldFigure = fallingFigure;
        fetchNextFigure(fallingFigure, nextFigs);

        *numSwaps = 0;
        return;
    }
    Figure * temp = heldFigure;
    temp->getBlocks()[temp->getLeadingBlockPos()].setBlockX(fallingFigure->getBlocks()[fallingFigure->getLeadingBlockPos()].getBlockX());
    temp->getBlocks()[temp->getLeadingBlockPos()].setBlockY(fallingFigure->getBlocks()[fallingFigure->getLeadingBlockPos()].getBlockY());
    temp->updateBlocks();

    if((*numSwaps != 2) && !collidesStatic(gameBoard, temp)){
        temp = fallingFigure;
        //check if the swap makes the figure collide. If it does, swap is not enabled
        heldFigure->getBlocks()[heldFigure->getLeadingBlockPos()].setBlockX(fallingFigure->getBlocks()[fallingFigure->getLeadingBlockPos()].getBlockX());
        heldFigure->getBlocks()[heldFigure->getLeadingBlockPos()].setBlockY(fallingFigure->getBlocks()[fallingFigure->getLeadingBlockPos()].getBlockY());
        heldFigure->updateBlocks();
        fallingFigure = heldFigure;
        heldFigure = temp;

        *numSwaps += 1;
    }
}

void changeSwappedFigurePosition(Figure *& heldFigure){

    int x = HFX;
    int y = HFY;
    int w = HFW;
    int h = HFH;

    int spacing = (int) ((h - BLOCKLENGTH*6)/10);    

    //Choose which figure we are dealing to
        switch(heldFigure->getId()){
            case 0:

                //FigL

                heldFigure->getBlocks()[0].setPixelXDereferenced(x + w/2 - (BLOCKLENGTH + BLOCKLENGTH/2));
                heldFigure->getBlocks()[0].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[1].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                heldFigure->getBlocks()[1].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[2].setPixelXDereferenced(x + w/2 + BLOCKLENGTH/2);
                heldFigure->getBlocks()[2].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[3].setPixelXDereferenced(x + w/2 + BLOCKLENGTH/2);
                heldFigure->getBlocks()[3].setPixelYDereferenced(y - spacing);

                break;
            case 1:

                //FigLRight

                heldFigure->getBlocks()[0].setPixelXDereferenced(x + w/2 - (BLOCKLENGTH + BLOCKLENGTH/2));
                heldFigure->getBlocks()[0].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[1].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                heldFigure->getBlocks()[1].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[2].setPixelXDereferenced(x + w/2 + BLOCKLENGTH/2);
                heldFigure->getBlocks()[2].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[3].setPixelXDereferenced(x + w/2 - (BLOCKLENGTH + BLOCKLENGTH/2));
                heldFigure->getBlocks()[3].setPixelYDereferenced(y - spacing);

                break;
             case 2:

                //FigO

                heldFigure->getBlocks()[0].setPixelXDereferenced(x + w/2 - BLOCKLENGTH);
                heldFigure->getBlocks()[0].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[1].setPixelXDereferenced(x + w/2);
                heldFigure->getBlocks()[1].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[2].setPixelXDereferenced(x + w/2);
                heldFigure->getBlocks()[2].setPixelYDereferenced(y - spacing);

                heldFigure->getBlocks()[3].setPixelXDereferenced(x + w/2 - BLOCKLENGTH);
                heldFigure->getBlocks()[3].setPixelYDereferenced(y - spacing);

                break;
            case 3:

                //FigI

                heldFigure->getBlocks()[0].setPixelXDereferenced(x + w/2 - BLOCKLENGTH*2);
                heldFigure->getBlocks()[0].setPixelYDereferenced(y - spacing + BLOCKLENGTH/2);

                heldFigure->getBlocks()[1].setPixelXDereferenced(x + w/2 - BLOCKLENGTH);
                heldFigure->getBlocks()[1].setPixelYDereferenced(y - spacing + BLOCKLENGTH/2);

                heldFigure->getBlocks()[2].setPixelXDereferenced(x + w/2);
                heldFigure->getBlocks()[2].setPixelYDereferenced(y - spacing + BLOCKLENGTH/2);

                heldFigure->getBlocks()[3].setPixelXDereferenced(x + w/2 + BLOCKLENGTH);
                heldFigure->getBlocks()[3].setPixelYDereferenced(y - spacing + BLOCKLENGTH/2);

                break;
            case 4:

                //FigT

                heldFigure->getBlocks()[0].setPixelXDereferenced(x + w/2 - (BLOCKLENGTH + BLOCKLENGTH/2));
                heldFigure->getBlocks()[0].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[1].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                heldFigure->getBlocks()[1].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[2].setPixelXDereferenced(x + w/2 + BLOCKLENGTH/2);
                heldFigure->getBlocks()[2].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[3].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                heldFigure->getBlocks()[3].setPixelYDereferenced(y - spacing);

                break;
            case 5:

                //FigS

                heldFigure->getBlocks()[0].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                heldFigure->getBlocks()[0].setPixelYDereferenced(y - spacing);

                heldFigure->getBlocks()[1].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                heldFigure->getBlocks()[1].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[2].setPixelXDereferenced(x + w/2 + BLOCKLENGTH/2);
                heldFigure->getBlocks()[2].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[3].setPixelXDereferenced(x + w/2 - (BLOCKLENGTH + BLOCKLENGTH/2));
                heldFigure->getBlocks()[3].setPixelYDereferenced(y - spacing);

                break;
            case 6:

                //FigZ

                heldFigure->getBlocks()[0].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                heldFigure->getBlocks()[0].setPixelYDereferenced(y - spacing);

                heldFigure->getBlocks()[1].setPixelXDereferenced(x + w/2 - BLOCKLENGTH/2);
                heldFigure->getBlocks()[1].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[2].setPixelXDereferenced(x + w/2 - (BLOCKLENGTH + BLOCKLENGTH/2));
                heldFigure->getBlocks()[2].setPixelYDereferenced(y - spacing + BLOCKLENGTH);

                heldFigure->getBlocks()[3].setPixelXDereferenced(x + w/2 + BLOCKLENGTH/2);
                heldFigure->getBlocks()[3].setPixelYDereferenced(y - spacing);

                break;
        }
}

