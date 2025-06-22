#ifndef FIGUREI_H
#define FIGUREI_H

#include "Figures/FigureF/Figure.h"

#include <SDL2/SDL.h>

class FigI: public Figure{

    public:

        //CONSTRUCTOR

        FigI();


        //MISCELLANEOUS

        int updateBlocks() override;
        
        bool loadInitialBlocks(bool constructor) override;

};

#endif