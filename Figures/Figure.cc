#include "Figure.h"

Figure::Figure(){
    this->leadingBlockPos = 0;
    this->figureColor = WHITE;
    this->angle = 0;
}

Figure::~Figure(){

}

void Figure::update(/*pass some form of coordinates maybe?*/){

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