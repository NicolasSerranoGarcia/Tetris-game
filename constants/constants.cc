#include "constants.h"

const int SCREENWIDTH = 760;
const int SCREENHEIGHT = 900;

Screen mainScreen(SCREENWIDTH, SCREENHEIGHT, "Tetris");


int py(AbsPosition position, int objH){

    int relativeCenterY = objH/2;

    switch(position) {
        case AbsPosition::POS_CENTER:          return SCREENHEIGHT/2 - relativeCenterY;
        case AbsPosition::POS_UP:              return 0;
        case AbsPosition::POS_DOWN:            return SCREENHEIGHT - relativeCenterY*2;
        case AbsPosition::POS_LEFT:            return SCREENHEIGHT/2 - relativeCenterY;
        case AbsPosition::POS_RIGHT:           return SCREENHEIGHT/2 - relativeCenterY;
        case AbsPosition::POS_CENTER_DOWN:     return SCREENHEIGHT/2 - relativeCenterY + SCREENHEIGHT/6;
        case AbsPosition::POS_CENTER_UP:       return SCREENHEIGHT/2 - relativeCenterY - SCREENHEIGHT/6;
        case AbsPosition::POS_CENTER_LEFT:     return SCREENHEIGHT/2 - relativeCenterY;
        case AbsPosition::POS_CENTER_RIGHT:    return SCREENHEIGHT/2 - relativeCenterY;
        case AbsPosition::POS_UP_LEFT:         return 0;
        case AbsPosition::POS_UP_RIGHT:        return 0;
        case AbsPosition::POS_DOWN_LEFT:       return SCREENHEIGHT - relativeCenterY*2;
        case AbsPosition::POS_DOWN_RIGHT:      return SCREENHEIGHT - relativeCenterY*2;
        default:                             return 0;
    }
};


int px(AbsPosition position, int objW){

    int relativeCenterX = objW/2;

    switch(position) {
        case AbsPosition::POS_CENTER:          return SCREENWIDTH/2 - relativeCenterX;
        case AbsPosition::POS_UP:              return SCREENWIDTH/2 - relativeCenterX;
        case AbsPosition::POS_DOWN:            return SCREENWIDTH/2 - relativeCenterX;
        case AbsPosition::POS_LEFT:            return 0;
        case AbsPosition::POS_RIGHT:           return SCREENWIDTH - relativeCenterX*2;
        case AbsPosition::POS_CENTER_DOWN:     return SCREENWIDTH/2 - relativeCenterX;
        case AbsPosition::POS_CENTER_UP:       return SCREENWIDTH/2 - relativeCenterX;
        case AbsPosition::POS_CENTER_LEFT:     return SCREENWIDTH/2 - 2*relativeCenterX;
        case AbsPosition::POS_CENTER_RIGHT:    return SCREENWIDTH/2;
        case AbsPosition::POS_UP_LEFT:         return 0;
        case AbsPosition::POS_UP_RIGHT:        return SCREENWIDTH - relativeCenterX*2;
        case AbsPosition::POS_DOWN_LEFT:       return 0;
        case AbsPosition::POS_DOWN_RIGHT:      return SCREENWIDTH - relativeCenterX*2;
        default:                             return 0;
    }
};