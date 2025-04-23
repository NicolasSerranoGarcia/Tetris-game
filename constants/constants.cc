#include "constants.h"


const int SCREENWIDTH = 960;

const int SCREENHEIGHT = 1000;


const int BLOCKLENGTH = 46;


Screen mainScreen(SCREENWIDTH, SCREENHEIGHT, "Tetris");


const int BSX = SCREENWIDTH/2 - (SCREENWIDTH - (int) (((5.0/16) / 1.5) * SCREENWIDTH))/2;

const int BSY = (int) ((1.0/25) * SCREENHEIGHT);

const int BSW = SCREENWIDTH - (int) ((50.0/96) * SCREENWIDTH);

const int BSH = SCREENHEIGHT - BSY*2;


const int FSY = BSY;

const int FSW = SCREENWIDTH - (FSY*4 + BSW + BSX);

const int FSX = BSX + BSW + (SCREENWIDTH - (BSX + BSW + FSW))/2;

const int FSH = BLOCKLENGTH * 9;


SDL_KeyCode CONTROLLEFT = SDLK_LEFT;

SDL_KeyCode CONTROLRIGHT = SDLK_RIGHT;

SDL_KeyCode CONTROLDOWN = SDLK_DOWN;

SDL_KeyCode CONTROLROTATE = SDLK_UP;

const Uint32 FALLDELAY = 1000;


int py(AbsPosition position, int objH){

    //refers to the Y center of the object you want to position
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
        default:                               return 0;
    }
};

int px(AbsPosition position, int objW){

    //refers to the X center of the object you want to position
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
        default:                               return 0;
    }
};