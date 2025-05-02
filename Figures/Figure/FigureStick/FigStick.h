#ifndef FIGURESTICK_H
#define FIGURESTICK_H

#include <SDL2/SDL.h>
#include "Figures/FigureF/Figure.h"

class FigStick: public Figure{
    public:
        FigStick(); //load the blocks of the figure in the constuctor
        //inherit an update method that recieves an event and does things with the figure
        int updateBlocks() override;
        bool loadInitialBlocks(bool constructor) override;

};

#endif