#ifndef FIGUREO_H
#define FIGUREO_H

#include "Figures/FigureF/Figure.h"

#include <SDL2/SDL.h>

class FigO: public Figure{

    public:

        //CONSTRUCTOR

        FigO();


        //MISCELLANEOUS

        int updateBlocks() override;

        bool loadInitialBlocks(bool constructor) override;

};

#endif