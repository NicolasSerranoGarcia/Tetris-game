#ifndef FIGUREJ_H
#define FIGUREJ_H

#include "Figures/FigureF/Figure.h"

#include <SDL2/SDL.h>

class FigJ: public Figure{

    public:

        //CONSTRUCTOR

        FigJ();


        //MISCELANEOUS  

        int updateBlocks() override;

        bool loadInitialBlocks(bool constructor) override;

};

#endif