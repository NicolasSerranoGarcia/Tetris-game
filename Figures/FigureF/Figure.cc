#include "Figures/FigureF/Figure.h"

Figure::Figure(){
    this->leadingBlockPos = 0;
    this->figureColor = WHITE;
    this->angle = 0;
}

Figure::~Figure(){
    this->angle = 0;
    this->blocks.clear();
    this->figureColor = WHITE;
    this->leadingBlockPos = -1;
}

int Figure::update(SDL_Event event){
    if((event.type != SDL_KEYDOWN) || !((event.key.keysym.sym == CONTROLDOWN) || 
       (event.key.keysym.sym == CONTROLLEFT)  || 
       (event.key.keysym.sym == CONTROLRIGHT) || 
       (event.key.keysym.sym == CONTROLROTATE))){
        return -1;
    }

    // Once we handle all edge cases, we can know for sure we will have to update the figure in some way.
    //Calculate once all the limits of the

    int largestY = 0;
    int largestX = 0;
    int smallestX = 9;
    for(unsigned int i = 0; i < this->blocks.size(); i++){
        if(this->blocks[i].getBlockY() > largestY){
            largestY = this->blocks[i].getBlockY();
        }
        if(this->blocks[i].getBlockX() > largestX){
            largestX = this->blocks[i].getBlockX();
        }
        if(this->blocks[i].getBlockX() < smallestX){
            smallestX = this->blocks[i].getBlockX();
        }
    }

    if(event.key.keysym.sym == CONTROLDOWN){

        if((largestY < 19)){
            this->blocks[leadingBlockPos].setBlockY(this->blocks[leadingBlockPos].getBlockY() + 1);
        }
    }

    else if(event.key.keysym.sym == CONTROLRIGHT){

        if(largestX < 9){
            this->blocks[leadingBlockPos].setBlockX(this->blocks[leadingBlockPos].getBlockX() + 1);
        }
    }

    else if(event.key.keysym.sym == CONTROLLEFT){

        if(smallestX > 0){
            this->blocks[leadingBlockPos].setBlockX(this->blocks[leadingBlockPos].getBlockX() - 1);
        }
    }

    else if(event.key.keysym.sym == CONTROLROTATE){
        
        this->angle -= 90;
        if(this->angle < 0){
            this->angle = 360 + this->angle;
        }
        //the previous is to ensure the angle is always between 0º and 360ª

        //in this function I check the angle of the figure and update it accordingly
    }
    updateBlocks();
    
    //When we rotate the figure, the figure might have gone out of boundaries. In the case the figure is out, make a "push" effect, where the figure reallocates to the inside
    if(event.key.keysym.sym == CONTROLROTATE){
        largestY = 0;
        largestX = 0;
        smallestX = 9;
        int smallestY = 0;
        for(unsigned int i = 0; i < this->blocks.size(); i++){

            if(this->blocks[i].getBlockY() > largestY){
                largestY = this->blocks[i].getBlockY();
            }

            if(this->blocks[i].getBlockX() > largestX){
                largestX = this->blocks[i].getBlockX();
            }

            if(this->blocks[i].getBlockX() < smallestX){
                smallestX = this->blocks[i].getBlockX();
            }

            if(this->blocks[i].getBlockY() < smallestY){
                smallestY = this->blocks[i].getBlockY();
            }
        }
    
        if(smallestY < 0){
            this->blocks[getLeadingBlockPos()].setBlockY(-smallestY);
            this->updateBlocks();
        }
        

        if(largestY > 19){
            this->blocks[getLeadingBlockPos()].setBlockY(19 - (largestY - 19));
            this->updateBlocks();
        }


        if(largestX > 9){
            this->blocks[getLeadingBlockPos()].setBlockX(9 - (largestX - 9));
            this->updateBlocks();
        }

        if(smallestX < 0){
            this->blocks[getLeadingBlockPos()].setBlockX(-smallestX);
            this->updateBlocks();
        }
    }
    


    return 0;
}

void Figure::rotate(){
    //int tile = (mainScreen.getWidth() - 500)/10;

    Block leadingBlock = this->blocks[this->getLeadingBlockPos()];

    /*  x' = x*cos(theta) - y*sin(theta)
    *   y' = x*sin(theta) + y*cos(theta)
    *
    *   Here leadingBlock.setBlockX() <=> x' and leadingBlock.setBlockY() <=> y'
    *   As in my case, the "origin" of the coordinates is the leading block, I will "reallocate"
    *   the origin by summing the position of the leading block
    */

    //for each block in the figure, rotate it by the angle

    for(unsigned int i = 0; i < this->getBlocks().size(); i ++){
        if((int) i != getLeadingBlockPos()){
            //The original formula simplifies as the rotations are always by -90 degrees
            int x_prime = leadingBlock.getBlockX() + (blocks[i].getBlockY() - leadingBlock.getBlockY());
            int y_prime = leadingBlock.getBlockY() - (blocks[i].getBlockX() - leadingBlock.getBlockX());
            
            blocks[i].setBlockX(x_prime);
            blocks[i].setBlockY(y_prime);
        }
    }
}

//set that returns boolean and return the param
void Figure::loadInitialBlocks(bool constructor){
    constructor = constructor;
    return;
}


int Figure::updateBlocks(){
    return 0;
}

int Figure::getAngle(){
     return angle;
}

SDL_Color Figure::getFigureColor(){
     return figureColor;
}

std::vector <Block>& Figure::getBlocks(){
    return blocks;
}

int Figure::getLeadingBlockPos() {
    return leadingBlockPos;
}

int Figure::getId(){
    return id;
}

void Figure::setId(int id){
    this->id = id;
}

void Figure::setFigureColor(SDL_Color color){
     this->figureColor = color;
     for(int i = 0; i < this->blocks.size(); i++){
        this->blocks[i].setInlineColor(figureColor);
     }
}

void Figure::setLeadingBlockPos(int pos){
    this->leadingBlockPos = pos;
}

void Figure::setAngle(int angle){
    this->angle = angle;
}

void Figure::deleteBlock(int pos){
    getBlocks().erase(pos + getBlocks().cbegin());
}

void Figure::addBlock(Block block){
    getBlocks().push_back(block);
}


void Figure::renderFigure(){
    SDL_SetRenderDrawColor(mainScreen.getRender(), getFigureColor().r, getFigureColor().g, getFigureColor().b, getFigureColor().a);
    for(unsigned int i = 0; i < getBlocks().size(); i++){
        getBlocks()[i].renderBlock();
    }
}

void Figure::deleteAllBlocks(){
    for(unsigned int i = 0; i < this->getBlocks().size(); i++){
        if((int) i != getLeadingBlockPos()){
            this->deleteBlock(i);
            i--;
        }
    }
}

