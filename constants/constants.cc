#include "constants.h"


const int SCREENWIDTH = 960;

const int SCREENHEIGHT = 1000;


const int BLOCKLENGTH = 46;


Screen mainScreen(SCREENWIDTH, SCREENHEIGHT, "Tetris");


// extern Scene * currentScene = new OpScene;

// extern Scene * mainScene = nullptr;


const int BSX = SCREENWIDTH/2 - (SCREENWIDTH - (int) (((5.0/16) / 1.5) * SCREENWIDTH))/2;

const int BSY = (int) ((1.0/25) * SCREENHEIGHT);

const int BSW = SCREENWIDTH - (int) ((50.0/96) * SCREENWIDTH);

const int BSH = SCREENHEIGHT - BSY*2;


const int FSY = BSY;

const int FSW = SCREENWIDTH - (FSY*4 + BSW + BSX);

const int FSX = BSX + BSW + (SCREENWIDTH - (BSX + BSW + FSW))/2;

const int FSH = BLOCKLENGTH * 9;


const int ISX = FSX;

const int ISY = FSY + FSH + (SCREENWIDTH - (BSX + BSW) - FSW)/4;

const int ISW = FSW;

const int ISH = BLOCKLENGTH*2;


SDL_KeyCode CONTROLLEFT = SDLK_LEFT;

SDL_KeyCode CONTROLRIGHT = SDLK_RIGHT;

SDL_KeyCode CONTROLDOWN = SDLK_DOWN;

SDL_KeyCode CONTROLROTATE = SDLK_UP;

Uint32 FALLSPEED = 1250;


unsigned int POINTS = 0;

unsigned int LEVEL = 1;

unsigned int LINES = 0;


int calculatePoints(int linesCleared){
    switch(linesCleared){
        case 1: 
            return 40*(LEVEL + 1);
        case 2: 
            return 100*(LEVEL + 1);
        case 3:
            return 300*(LEVEL + 1);
        case 4:
            return 1200*(LEVEL + 1);
        default:
            return 0;
    }
}

int getLevel(){
    if (LINES < 10) return 0;
    else if (LINES < 30) return 1;
    else if (LINES < 60) return 2;
    else if (LINES < 100) return 3;
    else if (LINES < 150) return 4;
    else if (LINES < 210) return 5;
    else if (LINES < 280) return 6;
    else if (LINES < 360) return 7;
    else if (LINES < 450) return 8;
    else if (LINES < 550) return 9;
    else if (LINES < 650) return 10;
    else if (LINES < 750) return 11;
    else if (LINES < 850) return 12;
    else if (LINES < 950) return 13;
    else if (LINES < 1050) return 14;
    else if (LINES < 1150) return 15;
    else if (LINES < 1250) return 16;
    else if (LINES < 1350) return 17;
    else if (LINES < 1450) return 18;
    else if (LINES < 1550) return 19;
    else if (LINES < 1650) return 20;
    else if (LINES < 1750) return 21;
    else if (LINES < 1850) return 22;
    else if (LINES < 1950) return 23;
    else if (LINES < 2050) return 24;
    else if (LINES < 2150) return 25;
    else if (LINES < 2250) return 26;
    else if (LINES < 2350) return 27;
    else if (LINES < 2450) return 28;
    else return 29;
}

Uint32 getFallSpeed(){
    if (LEVEL == 0){
        return 799;
    } else if (LEVEL == 1){
        return 715;        
    } else if (LEVEL == 2){
        return 632;        
    } else if (LEVEL == 3){
        return 549;        
    } else if (LEVEL == 4){
        return 466;        
    } else if (LEVEL == 5){
        return 383;        
    } else if (LEVEL == 6){
        return 300;        
    } else if (LEVEL == 7){ //if someone manages to get past this...
        return 216;        
    } else if (LEVEL == 8){
        return 133;        
    } else if (LEVEL == 9){
        return 100;        
    } else if ((LEVEL >= 10) && (LEVEL <= 12)){
        return 83;        
    } else if ((LEVEL >= 13) && (LEVEL <= 15)){
        return 67;        
    } else if ((LEVEL >= 16) && (LEVEL <= 18)){
        return 50;        
    } else if ((LEVEL >= 19) && (LEVEL <= 28)){
        return 33;        
    } else{
        return 17;
    }
}


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