#include "Block.h"

Block::Block(){
    this->block = {BSX, BSY, BLOCKLENGTH, BLOCKLENGTH};

    this->pixelX = BSX;
    this->pixelY = BSY;

    this->blockX = 0;
    this->blockY = 0;
    

    this->inlineColor = WHITE;
    this->outlineColor = WHITE;
}

Block::~Block(){
    this->block = {0,0,0,0};

    this->pixelX = 0;
    this->pixelY = 0;

    this->blockX = 0;
    this->blockY = 0;

    this->inlineColor = WHITE;
    this->outlineColor = WHITE;
}


SDL_Rect Block::getBlock() const{
    return block;
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

SDL_Color Block::getInlineColor() const{
    return inlineColor;
}

SDL_Color Block::getOutlineColor() const{
    return outlineColor;
}


void Block::setPixelX(int pixelX){
    this->pixelX = pixelX; 
    blockX = convertPixeltoBlockX(); 
    block.x = this->pixelX;
}

void Block::setPixelY(int pixelY){
    this->pixelY = pixelY; 
    blockY = convertPixelToBlockY(); 
    block.y = this->pixelY;
}

void Block::setBlockX(int blockX){
    this->blockX = blockX; 
    pixelX = convertBlocktoPixelX();
    block.x = pixelX;
}

void Block::setBlockY(int blockY){
    this->blockY = blockY; 
    pixelY = convertBlocktoPixelY(); 
    block.y = pixelY;
}

void Block::setInlineColor(SDL_Color color){
    inlineColor = color;
}

void Block::setOutlineColor(SDL_Color color){
    outlineColor = color;
}

void Block::setPixelXDereferenced(int pixelX){
    this->pixelX = pixelX; block.x = this->pixelX;
}

void Block::setPixelYDereferenced(int pixelY){
    this->pixelY = pixelY; block.y = this->pixelY;
}


int Block::convertBlocktoPixelX(){
    return blockX*BLOCKLENGTH + BSX;
}

int Block::convertBlocktoPixelY(){
    return blockY*BLOCKLENGTH + BSY;
}

int Block::convertPixeltoBlockX(){
    return (pixelX-BSX)/BLOCKLENGTH;
}

int Block::convertPixelToBlockY(){
    return (pixelY-BSY)/BLOCKLENGTH;
}

void Block::renderBlock(){
    SDL_SetRenderDrawColor(mainScreen.getRender(), inlineColor.r, inlineColor.g, inlineColor.b, inlineColor.a);
    SDL_RenderFillRect(mainScreen.getRender(), &block);
    
    SDL_SetRenderDrawColor(mainScreen.getRender(), outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
    SDL_RenderDrawRect(mainScreen.getRender(), &block);
}

