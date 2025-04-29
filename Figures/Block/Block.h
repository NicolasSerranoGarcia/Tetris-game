#ifndef BLOCK_H
#define BLOCK_H

#include "constants/constants.h"

#include <SDL2/SDL.h>

//This class is container for the "virtual" object of a block (I may also refer to it as a tile). Each figure is composed of various blocks that are related to each other 
//by the fact they all pertain to the same figure. There is no specific atribute that selects which figure it is associated to. The way to know where a block belongs to is 
//by searching with the specific coordianates of the block. In each figure you will find a vector of blocks which compose the figure. In reality, any given block is not
// related to any figure in particular (excepet for the fact that the block can be located in the vector array). Each block has coordinates that act as a unique key, as 
//there is no superposition and each block is placed uniquely in the gameboard. the block works as an independent object with respect to the figure.
//
//Another thing to mention is that the blocks have a "special" coordinate (blockX, blockY) which represent the position inside the gameboard. You should not worry much about
//this, as you can work with pixels without having to worry about this property. This is better explained in the documentation file if you want to understand how I implemented it. 
class Block{
    private:
        //The SDL_Rect instance that visually represents the block
        SDL_Rect block;
        
        //The position X in pixels of the block. Internally, it should match
        //the X position of the SDL_Rect atribute. Created for easier access
        int pixelX;
        
        //The position Y in pixels of the block. Internally, it should match
        //the Y position of the SDL_Rect atribute. Created for easier access
        int pixelY;
        
        //The position X in tiles of the block. It automatically updates if
        //the pixel atributes are altered. More info on documentation
        int blockX;

        //The position X in tiles of the block. It automatically updates if
        //the pixel atributes are altered. MOre info on documentation
        int blockY;

        //An SDL_Color instance representing the inside color of 
        //the block. It may be a texture in the future. It normaly 
        //matches the color of the figure it pertains to
        SDL_Color blockColor;

        //An SDL_Color instance representing the outline color of the figure
        SDL_Color outlineColor;

        //A boolean that gives if the block is visible in the gameboard. 
        //Whenever a figure is created, all its blocks are set to placed.
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
        void setPixelXDereferenced(int pixelX){this->pixelX = pixelX; this->block.x = this->pixelX;};
        void setPixelYDereferenced(int pixelY){this->pixelY = pixelY; this->block.y = this->pixelY;};
        void setPlaced(bool placed){this->isPlaced = placed;};


        int convertBlocktoPixelX(){return this->blockX*BLOCKLENGTH + BSX;};
        int convertBlocktoPixelY(){return this->blockY*BLOCKLENGTH + BSY;};

        int convertPixeltoBLockX(){return (this->pixelX-BSX)/BLOCKLENGTH;};
        int convertPixelToBlockY(){return (this->pixelY-BSY)/BLOCKLENGTH;};

        void renderBlock();

};

#endif