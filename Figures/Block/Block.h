#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include "constants/constants.h"


//Each figure is composed of various blocks that are related to each other by the fact they all pertain to the same figure. There is no specific atribute that selects
//which figure it is associated to. The way to know where a block belongs to is by searching with the specific coordianates of the block. Each block has coordinates that
//act as a unique key, as there is no superposition and each block is placed uniquely in the gameboard. the block works as an independent object with respect to the figure
class Block{
    private:
        SDL_Rect block;
        SDL_Color blockColor; //normaly matches the color of the figure it pertains to
        SDL_Color outlineColor;
        int pixelX;
        int pixelY;
        int blockX;
        int blockY;
        bool isPlaced;
    public:
        Block();
        SDL_Rect getBlock() const{return block;};
        SDL_Color getBlockColor() const{return blockColor;};
        int getPixelX() const{return pixelX;};
        int getPixelY() const{return pixelY;};
        int getBlockX() const{return blockX;};
        int getBlockY() const{return blockY;};

        void setBlockColor(SDL_Color color){this->blockColor = color;};
        void setOutlineColor(SDL_Color color){this->outlineColor = color;};
        void setPixelX(int pixelX){this->pixelX = pixelX; this->blockX = this->convertPixeltoBLockX(); this->block.x = this->pixelX;};
        void setPixelY(int pixelY){this->pixelY = pixelY; this->blockY = this->convertPixelToBlockY(); this->block.y = this->pixelY;};
        void setBlockX(int blockX){this->blockX = blockX; this->pixelX = this->convertBlocktoPixelX(); this->block.x = this->pixelX;};
        void setBlockY(int blockY){this->blockY = blockY; this->pixelY = this->convertBlocktoPixelY(); this->block.y = this->pixelY;};
        void setPlaced(bool placed){this->isPlaced = placed;};


        int convertBlocktoPixelX(){return this->blockX*BLOCKLENGTH + BSX;};
        int convertBlocktoPixelY(){return this->blockY*BLOCKLENGTH + BSY;};

        int convertPixeltoBLockX(){return (this->pixelX-BSX)/BLOCKLENGTH;};
        int convertPixelToBlockY(){return (this->pixelY-BSY)/BLOCKLENGTH;};

        void renderBlock();

};

#endif