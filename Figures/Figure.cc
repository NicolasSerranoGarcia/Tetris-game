#include "Figure.h"

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

    }

    if(event.key.keysym.sym == CONTROLLEFT){
        
    }

    if(event.key.keysym.sym == CONTROLRIGHT){
        
    }

    if(event.key.keysym.sym == CONTROLROTATE){
        if(this->angle + 90 >= 360){
            this->angle = this->angle + 90 - 360;
        } else{
            this->angle += 90;
        }
    }

    return 0;
}

int Figure::updateBlocks(){
    return 0;
}

int Figure::getAngle(){ return angle;}
SDL_Color Figure::getFigureColor(){ return figureColor;}
std::vector <Block>& Figure::getBlocks(){return blocks;}
int Figure::getLeadingBlockPos() {return leadingBlockPos;}

void Figure::setColor(SDL_Color color){ this->figureColor = color;}
void Figure::setLeadingBlockPos(int pos){this->leadingBlockPos = pos;}
void Figure::setAngle(int angle){this->angle = angle;}
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