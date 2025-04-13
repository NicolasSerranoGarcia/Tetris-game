#ifndef FIGURE_H
#define FIGURE_H

#include <SDL2/SDL.h>
#include <vector>
#include "Block/Block.h"
#include "constants/constants.h"

//A father class that generalizes all of the figures. It has a leading block
// that acts as the center of rotation
class Figure{
    private:
        std::vector <Block>blocks;
        SDL_Color figureColor;
        // 0º <= θ <= 360º
        int angle;
        int leadingBlockPos; //gives the position of the leading block insde the blocks array
    public:
        Figure();
        virtual ~Figure();
        virtual int update(SDL_Event event);
        virtual int updateBlocks();
        virtual int getAngle();
        virtual SDL_Color getFigureColor();
        virtual std::vector <Block> &getBlocks();
        virtual int getLeadingBlockPos();

        virtual void setColor(SDL_Color color);
        virtual void setLeadingBlockPos(int pos);
        virtual void setAngle(int angle);
        virtual void deleteBlock(int pos);
        virtual void addBlock(Block block);

        virtual void renderFigure();
};

#endif