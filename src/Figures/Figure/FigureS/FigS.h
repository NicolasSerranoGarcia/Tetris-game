#ifndef FIGURES_H
#define FIGURES_H

#include "src/Figures/FigureF/Figure.h"

#include <SDL2/SDL.h>

class FigS: public Figure{

    public:

        //CONSTRUCTOR
        
        FigS();


        //MISCELLANEOUS

        int updateBlocks() override;

        bool loadInitialBlocks(bool constructor) override;

};

#endif