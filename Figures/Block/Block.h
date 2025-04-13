#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include "constants/constants.h"

class Block{
    private:
        SDL_Rect block = {0, 0, BLOCKLENGTH, BLOCKLENGTH};
        SDL_Color blockColor; //normaly matches the color of the figure it pertains to
        int pixelX;
        int pixelY;
        int blockX;
        int blockY;
    public:
        SDL_Rect getBlock() const{return block;};
        SDL_Color getBlockColor() const{return blockColor;};
        int getPixelX() const{return pixelX;};
        int getPixelY() const{return pixelY;};
        int getBlockX() const{return blockX;};
        int getBlockY() const{return blockY;};

        void setBlockColor(SDL_Color color){this->blockColor = color;};
        int setPixelX(int pixelX){this->pixelX = pixelX; this->blockX = this->convertPixeltoBLockX();};
        int setPixelY(int pixelY){this->pixelY = pixelY; this->blockY = this->convertPixelToBlockY();};
        int convertBlocktoPixelX(){return this->blockX*BLOCKLENGTH + BSX;};
        int convertBlocktoPixelY(){return this->blockY*BLOCKLENGTH + BSY;};

        int convertPixeltoBLockX(){return (this->pixelX-BSX)/BLOCKLENGTH;};
        int convertPixelToBlockY(){return (this->pixelY-BSY)/BLOCKLENGTH;};



};

#endif