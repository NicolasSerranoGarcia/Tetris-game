#ifndef FIGUREL_H
#define FIGUREL_H

#include "src/Figures/FigureF/Figure.h"

#include <SDL2/SDL.h>

class FigL: public Figure{

    public:

        //CONSTRUCTOR

        FigL();

        
        //MISCELLANEOUS

        int updateBlocks() override;

        bool loadInitialBlocks(bool constructor) override;
        
};

#endif