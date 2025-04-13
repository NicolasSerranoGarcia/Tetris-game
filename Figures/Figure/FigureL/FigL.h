#ifndef FIGUREL_H
#define FIGUREL_H

#include <SDL2/SDL.h>
#include "Figures/Figure.h"

class FigL: public Figure{
    public:
        ~FigL() override;
        FigL(); //load the blocks of the figure in the constuctor
};

#endif