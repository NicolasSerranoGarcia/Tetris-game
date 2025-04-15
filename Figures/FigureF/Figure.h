#ifndef FIGURE_H
#define FIGURE_H

#include <SDL2/SDL.h>
#include <vector>
#include "Figures/Block/Block.h"
#include "constants/constants.h"
#include <string>

//A father class that generalizes all of the figures. It has a leading block
// that acts as the center of rotation
class Figure{
    private:
        std::vector <Block>blocks;
        SDL_Color figureColor;
        // 0º <= θ <= 360º
        int angle;
        int leadingBlockPos; //gives the position of the leading block insde the blocks array
        std::string type = "";
    public:
        Figure();
        virtual ~Figure();
        virtual int update(SDL_Event event);
        virtual int updateBlocks();
        virtual int getAngle();
        virtual SDL_Color getFigureColor();
        virtual std::vector <Block> &getBlocks();
        virtual int getLeadingBlockPos();
        virtual std::string getType();


        virtual void setColor(SDL_Color color);
        virtual void setLeadingBlockPos(int pos);
        virtual void setAngle(int angle);
        virtual void setType(std::string type);


        virtual void deleteBlock(int pos);
        virtual void addBlock(Block block);
        virtual void deleteAllBlocks();

        virtual void renderFigure();
};

#endif