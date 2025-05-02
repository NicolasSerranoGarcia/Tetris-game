#ifndef FIGURES_H
#define FIGURES_H

#include "Figures/FigureF/Figure.h"

#include <SDL2/SDL.h>

class FigS: public Figure{

    public:

        //CONSTRUCTOR
        
        FigS();


        //MISCELANEOUS

        int updateBlocks() override;

        bool loadInitialBlocks(bool constructor) override;

};

#endif