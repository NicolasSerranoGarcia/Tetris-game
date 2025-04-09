#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>
#include "Screen/Screen.h"


extern const int SCREENWIDTH;
extern const int SCREENHEIGHT;

extern Screen mainScreen;

constexpr SDL_Color RED = {255, 0, 0, 255};
constexpr SDL_Color GREEN = {0, 255, 0, 255};
constexpr SDL_Color BLUE = {0, 0, 255, 255};
constexpr SDL_Color BLACK = {0, 0, 0, 255};
constexpr SDL_Color WHITE = {255, 255, 255, 255};

enum class Rposition{
    POS_CENTER,
    POS_UP,
    POS_DOWN,
    POS_LEFT,
    POS_RIGHT,
    POS_UP_LEFT,
    POS_UP_RIGHT,
    POS_DOWN_LEFT,
    POS_DOWN_RIGHT,
    POS_CENTER_UP,
    POS_CENTER_DOWN,
    POS_CENTER_LEFT,
    POS_CENTER_RIGHT
};

int px(Rposition position, int objW);

int py(Rposition position, int objH);

#endif