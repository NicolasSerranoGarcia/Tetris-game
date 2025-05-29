#ifndef BLOCK_H
#define BLOCK_H

#include "constants/constants.h"

#include <SDL2/SDL.h>

//This class is a container for the "virtual" object of a block (I may also refer to it as a tile). 
//Each figure is composed of various blocks that are related to each other by the fact they all 
//pertain to the same figure. There is no specific atribute that selects which figure it is 
//associated to. The way to know where a block belongs to is by searching with the specific coordianates 
//of the block. In each figure you will find a vector of blocks which compose the figure. In reality, 
//any given block is not related to any figure in particular (excepet for the fact that the block 
//can be located in the vector array). Each block has coordinates that act as a unique key, as 
//there is no superposition and each block is placed uniquely in the gameboard. the block works 
//as an independent object with respect to the figure.
//
//Another thing to mention is that the blocks have a "special" coordinate (blockX, blockY) which 
//represent the position inside the gameboard. You should not worry much about this, as you can 
//work with pixels without having to worry about this property. This is better explained in the 
//documentation file if you want to understand how I implemented it. 
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
        SDL_Color inlineColor;

        //An SDL_Color instance representing the outline color of the figure
        SDL_Color outlineColor;


        SDL_Texture * blockTexture = nullptr;

    public:

        //CONSTRUCTORS/DESTRUCTOR

        //Constructor
        Block();

        //Destructor
        ~Block();


        //GETTERS

        //Getter
        //
        //RETURNS:
        //The SDL_Rect instance of the block
        SDL_Rect getBlock() const;

        //Getter
        //
        //RETURNS:
        //An integer representing the position X
        //in pixels of the block
        int getPixelX() const;

        //Getter
        //
        //RETURNS:
        //An integer representing the position Y
        //in pixels of the block
        int getPixelY() const;
        
        //Getter
        //
        //RETURNS:
        //An integer representing the position X
        //in tiles of the block. See doc. 4 + info.
        int getBlockX() const;
        
        //Getter
        //
        //RETURNS:
        //An integer representing the position Y
        //in tiles of the block. See doc. 4 + info.
        int getBlockY() const;
        
        //Getter
        //
        //RETURNS:
        //The SDL_Color instance that references
        //the inside color of the block
        SDL_Color getInlineColor() const;

        //Getter
        //
        //RETURNS:
        //The SDL_Color instance that references
        //the outside color of the block
        SDL_Color getOutlineColor() const;

        //Getter
        //
        //RETURNS:
        //A pointer to the SDL_Texture associated with the block
        SDL_Texture * getBlockTexture();


        //SETTERS
 
        //Setter
        //Also sets de tile X coordinate (both the atribute blockX and the SDL_Rect.x).
        //Calls convertPixelToBlockX()
        //
        //Returns:
        //Void
        void setPixelX(int pixelX);
        
        //Setter
        //Also sets de tile Y coordinate (both the atribute blockY and the SDL_Rect.y)
        //Calls convertPixelToBlockY()
        //
        //Returns:
        //Void
        void setPixelY(int pixelY);

        //Setter
        //Also sets de pixel X coordinate (pixelX). Calls convertBlocktoPixelX()
        //
        //Returns:
        //Void
        void setBlockX(int blockX);
        
        //Setter
        //Also sets de tile Y coordinate (pixelY). Calls convertBlockToPixelY()
        //
        //Returns:
        //Void
        void setBlockY(int blockY);
        
        //Setter
        //
        //Returns:
        //Void
        void setInlineColor(SDL_Color color);

        //Setter
        //
        //Returns:
        //Void
        void setOutlineColor(SDL_Color color);

        //Setter
        //Acts the same as setPixelX but avoids updating blockX. Also avoids calling
        //convertPixelToBlockX()
        //
        //Returns:
        //Void
        void setPixelXDereferenced(int pixelX);
        
        //Setter
        //Acts the same as setPixelY but avoids updating blockY. Also avoids calling
        //convertPixelToBlockY()
        //
        //Returns:
        //Void
        void setPixelYDereferenced(int pixelY);


        void setBlockTexture(SDL_Texture * texture);


        //MISCELANEOUS

        //This method gives the equivalent in pxels of the current tile X position
        //It is a formula to traduce from one coordinate to another. Take into account
        //that the tile coordinate has it's zero on the BSX,BSY points, not on the upper
        //left corner of the screen.
        //
        //RETURNS:
        //An integer repreenting the poisition X in pixels of the X tile coordinate
        int convertBlocktoPixelX();

        //This method gives the equivalent in pxels of the current tile Y position
        //It is a formula to traduce from one coordinate to another. Take into account
        //that the tile coordinate has it's zero on the BSX,BSY points, not on the upper
        //left corner of the screen.
        //
        //RETURNS:
        //An integer representing the poisition Y in pixels of the Y tile coordinate
        int convertBlocktoPixelY();

        //This method gives the equivalent in tiles of the current pixel X position
        //It is a formula to traduce from one coordinate to another. Take into account
        //that the tile coordinate has it's zero on the BSX,BSY points, not on the upper
        //left corner of the screen.
        //
        //RETURNS:
        //An integer repreenting the poisition X in tiles of the pixel X coordinate
        int convertPixeltoBlockX();

        //This method gives the equivalent in tiles of the current pixel Y position
        //It is a formula to traduce from one coordinate to another. Take into account
        //that the tile coordinate has it's zero on the BSX,BSY points, not on the upper
        //left corner of the screen.
        //
        //RETURNS:
        //An integer repreenting the poisition Y in tiles of the pixel Y coordinate
        int convertPixelToBlockY();


        //This method renders the block to the screen. Whenever a figure is rendered, this method
        //will be called consecutively on all the blocks of the figure. This is to say, any method
        //that attempts to render a figure, is internally calling this method for each of it's blocks.
        //Keep in mind this method doesn't show the block directly, it only renders it.
        //
        //RETURNS:
        //Void
        void renderBlock();

};

#endif