#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>
#include "Screen/Screen.h"


extern const int SCREENWIDTH;
extern const int SCREENHEIGHT;
extern const int BLOCKLENGTH;    
extern const int BSX;
extern const int BSY;
extern const int BSW;
extern const int BSH;

extern Screen mainScreen;

extern SDL_KeyCode CONTROLLEFT;
extern SDL_KeyCode CONTROLRIGHT;
extern SDL_KeyCode CONTROLDOWN;
extern SDL_KeyCode CONTROLROTATE;

constexpr SDL_Color RED        = {255,   0,   0, 255};
constexpr SDL_Color GREEN      = {  0, 255,   0, 255};
constexpr SDL_Color BLUE       = {  0,   0, 255, 255};
constexpr SDL_Color BLACK      = {  0,   0,   0, 255};
constexpr SDL_Color WHITE      = {255, 255, 255, 255};
constexpr SDL_Color YELLOW     = {255, 255,   0, 255};
constexpr SDL_Color MAGENTA    = {255,   0, 255, 255};
constexpr SDL_Color CYAN       = {  0, 255, 255, 255};
constexpr SDL_Color ORANGE     = {255, 165,   0, 255};
constexpr SDL_Color PURPLE     = {128,   0, 128, 255};
constexpr SDL_Color BROWN      = {165,  42,  42, 255};
constexpr SDL_Color PINK       = {255, 192, 203, 255};
constexpr SDL_Color LIGHT_GREEN= {144, 238, 144, 255};
constexpr SDL_Color LIGHT_BLUE = {173, 216, 230, 255};
constexpr SDL_Color GOLD       = {255, 215,   0, 255};
constexpr SDL_Color SILVER     = {192, 192, 192, 255};
constexpr SDL_Color TEAL       = {  0, 128, 128, 255};
constexpr SDL_Color NAVY       = {  0,   0, 128, 255};
constexpr SDL_Color MAROON     = {128,   0,   0, 255};
constexpr SDL_Color OLIVE      = {128, 128,   0, 255};
constexpr SDL_Color GREY       = {128, 128, 128, 255};
constexpr SDL_Color LIGHT_GREY = {238, 238, 238, 255};
constexpr SDL_Color LIGHT_ORANGE = {255, 200, 120, 255};





enum class AbsPosition{
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
    POS_CENTER_RIGHT,
};

enum class RPosition{
    POS_REL_UP,
    POS_REL_DOWN,
    POS_REL_LEFT,
    POS_REL_RIGHT,
    POS_REL_UP_LEFT,
    POS_REL_UP_RIGHT,
    POS_REL_DOWN_LEFT,
    POS_REL_DOWN_RIGHT,
};


//Returns the x coordinate of the object if it where to be centered in the ABSOLUTE position that the first parameter specifies. To use relative position to place an
//object, use the method of the target object (ej. for buttons, .setRelativeTo())
int px(AbsPosition position, int objW);

//Returns the y coordinate of the object if it where to be centered in the ABSOLUTE position that the first parameter specifies. To use relative position to place an
//object, use the method of the object you want to place (ej. for buttons, .setRelativeTo())
int py(AbsPosition position, int objH);

#endif