#include "Block.h"

Block::Block(){
    this->block = {BSX, BSY, BLOCKLENGTH, BLOCKLENGTH};
    this->blockColor = WHITE;
    this->outlineColor = WHITE;
    this->isPlaced = false;
    this->blockX = 0;
    this->blockY = 0;
    this->pixelX = BSX;
    this->pixelY = BSY;
}

void Block::renderBlock(){
    SDL_SetRenderDrawColor(mainScreen.getRender(), blockColor.r, blockColor.g, blockColor.b, blockColor.a);
    SDL_RenderFillRect(mainScreen.getRender(), &this->block);
    
    SDL_SetRenderDrawColor(mainScreen.getRender(), outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
    SDL_RenderDrawRect(mainScreen.getRender(), &this->block);
}

