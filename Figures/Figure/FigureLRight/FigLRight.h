#ifndef FIGURELRIGHT_H
#define FIGURELRIGHT_H

#include "Figures/FigureF/Figure.h"

#include <SDL2/SDL.h>

class FigLRight: public Figure{

    public:

        //CONSTRUCTOR

        FigLRight();


        //MISCELANEOUS  

        int updateBlocks() override;

        bool loadInitialBlocks(bool constructor) override;

};

#endif