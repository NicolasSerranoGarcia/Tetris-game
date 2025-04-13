#ifndef FIGURE_H
#define FIGURE_H

#include <SDL2/SDL.h>
#include <vector>
#include "Block/Block.h"

class Figure{
    private:
        std::vector <Block> blocks;
        SDL_Color figureColor;
        //some type of coordinates tht mach the format of the update function
    public:
        virtual void update(/*pass some form of coordinates maybe?*/);
        virtual void render();
};

#endif