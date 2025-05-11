#include "Figures/FigureF/Figure.h"

Figure::Figure(){
    id = -1;
    angle = 0;
    figureColor = WHITE;
    leadingBlockPos = 0;
}

Figure::~Figure(){
    id = -1;
    blocks.clear();
    angle = 0;
    figureColor = WHITE;
    leadingBlockPos = -1;
}


int Figure::getId(){
    return id;
}

std::vector <Block>& Figure::getBlocks(){
    return blocks;
}

int Figure::getAngle(){
     return angle;
}

SDL_Color Figure::getFigureColor(){
     return figureColor;
}

int Figure::getLeadingBlockPos() {
    return leadingBlockPos;
}


void Figure::setId(int id){
    this->id = id;
}

void Figure::setAngle(int angle){
    this->angle = angle;
}

void Figure::setFigureColor(SDL_Color color){
     figureColor = color;
     for(int i = 0; i < (int) blocks.size(); i++){
        blocks[i].setInlineColor(figureColor);
     }
}

void Figure::setLeadingBlockPos(int pos){
    leadingBlockPos = pos;
}


int Figure::update(SDL_Event event){

    //handle all the edge cases
    if((event.type != SDL_KEYDOWN) || !((event.key.keysym.sym == CONTROLDOWN) || 
       (event.key.keysym.sym == CONTROLLEFT)  || 
       (event.key.keysym.sym == CONTROLRIGHT) || 
       (event.key.keysym.sym == CONTROLROTATERIGHT) ||
       (event.key.keysym.sym == CONTROLROTATELEFT))){
        return -1;
    }

    // Once we handle all edge cases, we can know for sure we will have to update the figure in some way.

    int largestY = 0;
    int largestX = 0;
    int smallestX = 9;

    for(unsigned int i = 0; i < this->blocks.size(); i++){

        if(blocks[i].getBlockY() > largestY){
            largestY = blocks[i].getBlockY();
        }

        if(blocks[i].getBlockX() > largestX){
            largestX = blocks[i].getBlockX();
        }

        if(blocks[i].getBlockX() < smallestX){
            smallestX = blocks[i].getBlockX();
        }

    }

    //handle the keys

    Block *leadingBlock = &blocks[leadingBlockPos];

    if((event.key.keysym.sym == CONTROLDOWN) && (largestY < 19)){
        leadingBlock->setBlockY(leadingBlock->getBlockY() + 1);
    }

    else if((event.key.keysym.sym == CONTROLRIGHT) && (largestX < 9)){
        leadingBlock->setBlockX(leadingBlock->getBlockX() + 1);
    }

    else if((event.key.keysym.sym == CONTROLLEFT) && (smallestX > 0)){
        leadingBlock->setBlockX(leadingBlock->getBlockX() - 1);
    }

    else if(event.key.keysym.sym == CONTROLROTATERIGHT && !event.key.repeat){
        //ensure the angle is betweeen 0º and 360º
        angle -= 90;
        if(angle < 0){
            angle = 360 + angle;
        }
    } 
    else if(event.key.keysym.sym == CONTROLROTATELEFT && !event.key.repeat){
        angle += 90;
        if(angle >= 360){
            angle -= 360;
        }
    }
    updateBlocks();
    
    //When we rotate the figure, the figure might have gone out of boundaries. In the case the figure is out, 
    //make a "push" effect, where the figure reallocates to the inside. We will have to recalculate the
    //boundaries of the figure as rotating is not as "predictable" as moving down, left or right
    if((event.key.keysym.sym == CONTROLROTATERIGHT) || (event.key.keysym.sym == CONTROLROTATELEFT)){

        largestY = 0;
        largestX = 0;
        smallestX = 9;
        int smallestY = 19;

        for(unsigned int i = 0; i < blocks.size(); i++){

            if(blocks[i].getBlockY() > largestY){
                largestY = blocks[i].getBlockY();
            }

            if(blocks[i].getBlockX() > largestX){
                largestX = blocks[i].getBlockX();
            }

            if(blocks[i].getBlockX() < smallestX){
                smallestX = blocks[i].getBlockX();
            }

            if(blocks[i].getBlockY() < smallestY){
                smallestY = blocks[i].getBlockY();
            }
        }
    

        if(smallestY < 0){
            leadingBlock->setBlockY(leadingBlock->getBlockY() - smallestY);
        }
        
        if(largestY > 19){
            leadingBlock->setBlockY(leadingBlock->getBlockY() - (largestY - 19));
        }

        if(largestX > 9){
            leadingBlock->setBlockX(leadingBlock->getBlockX() - (largestX - 9));
        }

        if(smallestX < 0){
            leadingBlock->setBlockX(leadingBlock->getBlockX() - smallestX);
        }
        updateBlocks();
    }

    return 0;
}

int Figure::updateBlocks(){
    return 0;
}

void Figure::rotateRight(){

    Block leadingBlock = blocks[leadingBlockPos];

    /*  x' = x*cos(theta) - y*sin(theta)
    *   y' = x*sin(theta) + y*cos(theta)
    *
    *   As in my case, the "origin" of the coordinates is the leading block, I will "reallocate"
    *   the origin by summing the position of the leading block
    */

    //for each block in the figure, rotate it by the angle

    for(unsigned int i = 0; i < blocks.size(); i ++){
        //the leading block is not rotated, as it is the axis of rotation
        if((int) i != leadingBlockPos){
            //The original formula simplifies as the rotations are always by 90 degrees
            int x_prime = leadingBlock.getBlockX() + (blocks[i].getBlockY() - leadingBlock.getBlockY());
            int y_prime = leadingBlock.getBlockY() - (blocks[i].getBlockX() - leadingBlock.getBlockX());
            
            blocks[i].setBlockX(x_prime);
            blocks[i].setBlockY(y_prime);
        }
    }
}


void Figure::rotateLeft(){

    Block leadingBlock = blocks[leadingBlockPos];

    /*  x' = x*cos(theta) - y*sin(theta)
    *   y' = x*sin(theta) + y*cos(theta)
    *
    *   As in my case, the "origin" of the coordinates is the leading block, I will "reallocate"
    *   the origin by summing the position of the leading block
    */

    //for each block in the figure, rotate it by the angle

    for(unsigned int i = 0; i < blocks.size(); i ++){
        //the leading block is not rotated, as it is the axis of rotation
        if((int) i != leadingBlockPos){
            //The original formula simplifies as the rotations are always by -90 degrees
            int x_prime = leadingBlock.getBlockX() - (blocks[i].getBlockY() - leadingBlock.getBlockY());
            int y_prime = leadingBlock.getBlockY() + (blocks[i].getBlockX() - leadingBlock.getBlockX());
            
            blocks[i].setBlockX(x_prime);
            blocks[i].setBlockY(y_prime);
        }
    }
}

bool Figure::loadInitialBlocks(bool constructor){
    return constructor;
}

void Figure::deleteBlock(int pos){
    blocks.erase(blocks.cbegin() + pos);
}

void Figure::deleteAllBlocks(){
    for(unsigned int i = 0; i < blocks.size(); i++){
        if((int) i != leadingBlockPos){
            deleteBlock(i);
            i--;
        }
    }
}

void Figure::addBlock(Block block){
    blocks.push_back(block);
}

void Figure::renderFigure(){
    SDL_SetRenderDrawColor(mainScreen.getRender(), figureColor.r, figureColor.g, figureColor.b, figureColor.a);
    for(unsigned int i = 0; i < blocks.size(); i++){
        blocks[i].renderBlock();
    }
}