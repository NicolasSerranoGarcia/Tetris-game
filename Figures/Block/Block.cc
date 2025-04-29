#include "Block.h"

Block::Block(){
    this->block = {BSX, BSY, BLOCKLENGTH, BLOCKLENGTH};
    this->inlineColor = WHITE;
    this->outlineColor = WHITE;
    this->blockX = 0;
    this->blockY = 0;
    this->pixelX = BSX;
    this->pixelY = BSY;
}

Block::~Block(){
    this->block = {0,0,0,0};
    this->inlineColor = WHITE;
    this->outlineColor = WHITE;
    this->blockX = 0;
    this->blockY = 0;
    this->pixelX = 0;
    this->pixelY = 0;
}

SDL_Rect Block::getBlock() const{
    return block;
}

SDL_Color Block::getInlineColor() const{
    return inlineColor;
}

SDL_Color Block::getOutlineColor() const{
    return inlineColor;
}


int Block::getPixelX() const{
    return pixelX;
}

int Block::getPixelY() const{
    return pixelY;
}

int Block::getBlockX() const{
    return blockX;
}

int Block::getBlockY() const{
    return blockY;
}


void Block::renderBlock(){
    SDL_SetRenderDrawColor(mainScreen.getRender(), inlineColor.r, inlineColor.g, inlineColor.b, inlineColor.a);
    SDL_RenderFillRect(mainScreen.getRender(), &this->block);
    
    SDL_SetRenderDrawColor(mainScreen.getRender(), outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
    SDL_RenderDrawRect(mainScreen.getRender(), &this->block);
}

