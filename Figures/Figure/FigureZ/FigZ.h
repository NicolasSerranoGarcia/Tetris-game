#ifndef FIGUREZ_H
#define FIGUREZ_H

#include "Figures/FigureF/Figure.h"

#include <SDL2/SDL.h>

class FigZ: public Figure{

    public:

        //CONSTRUCTOR

        FigZ();


        //MISCELLANEOUS

        int updateBlocks() override;

        bool loadInitialBlocks(bool constructor) override;

};

#endif