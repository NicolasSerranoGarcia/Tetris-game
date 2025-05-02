#ifndef FIGURELRIGHT_H
#define FIGURELRIGHT_H

#include <SDL2/SDL.h>
#include "Figures/FigureF/Figure.h"

class FigLRight: public Figure{
    public:
        FigLRight(); //load the blocks of the figure in the constuctor
        //inherit an update method that recieves an event and does things with the figure
        int updateBlocks() override;
        bool loadInitialBlocks(bool constructor) override;

};

#endif