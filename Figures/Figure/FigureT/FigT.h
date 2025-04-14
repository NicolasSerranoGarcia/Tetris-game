#ifndef FIGURET_H
#define FIGURET_H

#include <SDL2/SDL.h>
#include "Figures/FigureF/Figure.h"

class FigT: public Figure{
    public:
        FigT(); //load the blocks of the figure in the constuctor
        //inherit an update method that recieves an event and does things with the figure
        int updateBlocks() override;
};

#endif