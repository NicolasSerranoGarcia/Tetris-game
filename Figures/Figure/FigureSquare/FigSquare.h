#ifndef FIGURESQUARE_H
#define FIGURESQUARE_H

#include "Figures/FigureF/Figure.h"

#include <SDL2/SDL.h>

class FigSquare: public Figure{

    public:

        //CONSTRUCTOR

        FigSquare();


        //MISCELANEOUS

        int updateBlocks() override;
        
        bool loadInitialBlocks(bool constructor) override;

};

#endif