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

//This method will likely only be used when the figure is the current figure (the one which is falling). Anyways, using the previous state of the figure (angle and leading
//block) and an event, it changes the state of the leading block and consecutively, the rest of the blocks. To change the rest of the blocks for each specific figure
//without overriding this method in the child classes, the method calls another method from the class called updateBlocks() which will be overritten by each child. This
//way we mantain the event -> render structure in the scenes.
//RETURNS:
//-1 if the movement cannot be executed
//0 if the movement was done correctly
int Figure::update(SDL_Event event){
    if(event.type != SDL_KEYDOWN){
        return -1;
        //or do smth else
    }


    if(event.key.keysym.sym == CONTROLDOWN){
        int largestY = 0;
        for(unsigned int i = 0; i < this->blocks.size(); i++){
            if(this->blocks[i].getBlockY() > largestY){
                largestY = this->blocks[i].getBlockY();
            }
        }

        if((largestY < 19)){
            this->blocks[leadingBlockPos].setBlockY(this->blocks[leadingBlockPos].getBlockY() + 1);
        }
        this->updateBlocks();
    }

    if(event.key.keysym.sym == CONTROLRIGHT){
        int largestX = 0;
        for(unsigned int i = 0; i < this->blocks.size(); i++){
            if(this->blocks[i].getBlockX() > largestX){
                largestX = this->blocks[i].getBlockX();
            }
        }

        if(largestX < 9){
            this->blocks[leadingBlockPos].setBlockX(this->blocks[leadingBlockPos].getBlockX() + 1);
        }
        this->updateBlocks();
    }

    if(event.key.keysym.sym == CONTROLLEFT){
        int smallestX = 9;
        for(unsigned int i = 0; i < this->blocks.size(); i++){
            if(this->blocks[i].getBlockX() < smallestX){
                smallestX = this->blocks[i].getBlockX();
            }
        }

        if(smallestX > 0){
            this->blocks[leadingBlockPos].setBlockX(this->blocks[leadingBlockPos].getBlockX() - 1);
        }
        this->updateBlocks();
    }

    if(event.key.keysym.sym == CONTROLROTATE){
        
        this->angle -= 90;
        if(this->angle < 0){
            this->angle = 360 + this->angle;
        }
        //the previous is to ensure the angle is always between 0º and 360ª

        //in this function I check the angle of the figure and update it accordingly
        this->updateBlocks();

        //I don't know why but when I was playing tetris to get a hint on how the figures rotate, it happens that the stick figure doesn't quite "rotate" with
        //the leading block as the center of rotation. In fact the whole figure rotates relative to the point on the center-right of the figure. In any case 
        //the way to go is to apply the formulas using pixels instead and moving the center of rotation
 
    }

    //When we update the figure, the figure might have gone out of boundaries. In the case the figure is out, make a "push" effect, where the figure reallocates to the inside

    int largestY = 0;
    for(unsigned int i = 0; i < this->blocks.size(); i++){
        if(this->blocks[i].getBlockY() > largestY){
            largestY = this->blocks[i].getBlockY();
        }
    }

    if(largestY > 19){
        this->blocks[getLeadingBlockPos()].setBlockY(19 - (largestY - 19));
        this->updateBlocks();
    }

    int smallestY = 0;
    for(unsigned int i = 0; i < this->blocks.size(); i++){
        if(this->blocks[i].getBlockY() < smallestY){
            smallestY = this->blocks[i].getBlockY();
        }
    }

    if(smallestY < 0){
        this->blocks[getLeadingBlockPos()].setBlockY(-smallestY);
        this->updateBlocks();
    }



    int largestX = 0;
    for(unsigned int i = 0; i < this->blocks.size(); i++){
        if(this->blocks[i].getBlockX() > largestX){
            largestX = this->blocks[i].getBlockX();
        }
    }

    if(largestX > 9){
        this->blocks[getLeadingBlockPos()].setBlockX(9 - (largestX - 9));
        this->updateBlocks();
    }

    int smallestX = 0;
    for(unsigned int i = 0; i < this->blocks.size(); i++){
        if(this->blocks[i].getBlockX() < smallestX){
            smallestX = this->blocks[i].getBlockX();
        }
    }

    if(smallestX < 0){
        this->blocks[getLeadingBlockPos()].setBlockX(-smallestX);
        this->updateBlocks();
    }
    


    return 0;
}

void Figure::rotate(){
    int tile = (mainScreen.getWidth() - 500)/10;

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

void Figure::loadInitialBlocks(bool constructor){
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

std::string Figure::getType() {
    return this->type;
}

void Figure::setType(std::string type){
    this->type = type;
}

void Figure::setColor(SDL_Color color){
     this->figureColor = color;
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

