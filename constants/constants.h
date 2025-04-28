#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Screen/Screen.h"
// #include "Scene/Scene.h"
// #include "Scene/Scenes.h"

#include <SDL2/SDL.h>


//The width in pixels of the screen. Currently static
extern const int SCREENWIDTH;

//The height in pixels of the screen. Curently static
extern const int SCREENHEIGHT;


//The side length of 1 block in the game board. The blocks are squares, so this the
//width and also the length of 1 block.
extern const int BLOCKLENGTH;


//Instance of the class Screen. This is a global var. To access atributes and methods refer to the class Screen.
//This instance is read-only and access-only throught the program.
extern Screen mainScreen;


// //
// extern Scene * currentScene;

// //
// extern Scene * mainScene;


//The position X in pixels of the game board. The game board is the rectangle where the figures fall
extern const int BSX;

//The position Y in pixels of the game board. The game board is the rectangle where the figures fall
extern const int BSY;

//The Width in pixels of the game board. The game board is the rectangle where the figures fall
extern const int BSW;

//The Height in pixels of the game board. The game board is the rectangle where the figures fall
extern const int BSH;


//The position X in pixels of the background rectangle that shows the next figures.
extern const int FSX;

//The position Y in pixels of the background rectangle that shows the next figures.
extern const int FSY;

//The Width in pixels of the background rectangle that shows the next figures.
extern const int FSW;

//The Height in pixels of the background rectangle that shows the next figures.
extern const int FSH;


//The position X in pixels of the background rectangle that shows the info about points, level...
extern const int ISX;

//The position Y in pixels of the background rectangle that shows the info about points, level...
//The Y position varies depending of which stat we are showing
extern const int ISY;

//The Width in pixels of the background rectangle that shows the info about points, level...
extern const int ISW;

//The Height in pixels of the background rectangle that shows the info about points, level...
extern const int ISH;


//An SDL_KeyCode instance that saves the key that the player uses to move the figures to the left
extern SDL_KeyCode CONTROLLEFT;

//An SDL_KeyCode instance that saves the key that the player uses to move the figures to the right
extern SDL_KeyCode CONTROLRIGHT;

//An SDL_KeyCode instance that saves the key that the player uses to move the figures down
extern SDL_KeyCode CONTROLDOWN;

//An SDL_KeyCode instance that saves the key that the player uses to rotate the figures
extern SDL_KeyCode CONTROLROTATE;

//An SDL_KeyCode instance that saves the key that the player uses to instantly place a figure by fast drop
extern SDL_KeyCode CONTROLFASTDOWN;


//An unsigned integer of 32 bits representing the time (ms) that a figure takes to drop one tile
extern Uint32 FALLSPEED;


//The points that the player has
extern unsigned int POINTS;

//The level of the current game
extern unsigned int LEVEL;

//The lines cleared on the current level
extern unsigned int LINES;


//A function that calculates the points won from clearing a certain number of lines (max. 4)
int calculatePoints(int linesCleared);

//A function that returns the current level. It depends on the total lines cleared
int getLevel();

//A function that returns the current speed. It depends on the level
Uint32 getFallSpeed();

//Color palette used in the rest of the project
//                                   R    G    B    A

constexpr SDL_Color RED          = {255,   0,   0, 255};
constexpr SDL_Color GREEN        = {  0, 255,   0, 255};
constexpr SDL_Color BLUE         = {  0,   0, 255, 255};
constexpr SDL_Color BLACK        = {  0,   0,   0, 255};
constexpr SDL_Color WHITE        = {255, 255, 255, 255};
constexpr SDL_Color YELLOW       = {255, 255,   0, 255};
constexpr SDL_Color MAGENTA      = {255,   0, 255, 255};
constexpr SDL_Color CYAN         = {  0, 255, 255, 255};
constexpr SDL_Color ORANGE       = {255, 165,   0, 255};
constexpr SDL_Color PURPLE       = {128,   0, 128, 255};
constexpr SDL_Color BROWN        = {165,  42,  42, 255};
constexpr SDL_Color PINK         = {255, 192, 203, 255};
constexpr SDL_Color LIGHT_GREEN  = {144, 238, 144, 255};
constexpr SDL_Color LIGHT_BLUE   = {173, 216, 230, 255};
constexpr SDL_Color GOLD         = {255, 215,   0, 255};
constexpr SDL_Color SILVER       = {192, 192, 192, 255};
constexpr SDL_Color TEAL         = {  0, 128, 128, 255};
constexpr SDL_Color NAVY         = {  0,   0, 128, 255};
constexpr SDL_Color MAROON       = {128,   0,   0, 255};
constexpr SDL_Color OLIVE        = {128, 128,   0, 255};
constexpr SDL_Color GREY         = {128, 128, 128, 255};
constexpr SDL_Color LIGHT_GREY   = {238, 238, 238, 255};
constexpr SDL_Color LIGHT_ORANGE = {255, 200, 120, 255};
constexpr SDL_Color LIGHT_YELLOW = {255, 255, 153, 255};
constexpr SDL_Color LIGHT_RED    = {255, 102, 102, 255};
constexpr SDL_Color LIGHT_PURPLE = {216, 191, 216, 255};
constexpr SDL_Color LIGHT_CYAN   = {224, 255, 255, 255};


//Enum class that holds all the absolute positions. It is an easy, fast-access way to 
//position something in the screen without having to worry about the dimensions of the
//screen. This can be used in combination with the functions px() and py() to calculate
//directly the XY pixels of an object if it where to be placed in the position that the 
//name specifies
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
    POS_CENTER_RIGHT
};

//Enum class that holds all the relative positions. It is an easy, fast-access way to 
//position something relative to another object without having to worry about the 
//struggle of calculating the XY pixels. It acts in a similar way as AbsPosition but
//this one has as a reference another object, so the positions specified in the class
//are relative to another object
enum class RPosition{
    POS_REL_UP,
    POS_REL_DOWN,
    POS_REL_LEFT,
    POS_REL_RIGHT,
    POS_REL_UP_LEFT,
    POS_REL_UP_RIGHT,
    POS_REL_DOWN_LEFT,
    POS_REL_DOWN_RIGHT
};


//Global function that calculates the Y pixels of each constant in the enum AbsPosition. 
//It recieves ONE constant of type AbsPosition (see the enum AbsPosition to see all the
//posible positions in the screen) and the Height of the object that you want to position,
//and returns the desired Y position in pixels.
//To calculate the X position use px().
//
//RETURNS:
//An integer representing the pixels of the Y position specified by the enum
int py(AbsPosition position, int objH);

//Global function that calculates the X pixels of each constant in the enum AbsPosition. 
//It recieves ONE constant of type AbsPosition (see the enum AbsPosition to see all the
//posible positions in the screen) and the Width of the object that you want to position,
//and returns the desired X position in pixels.
//To calculate the Y position use py().
//
//RETURNS:
//An integer representing the pixels of the X position specified by the enum
int px(AbsPosition position, int objW);

#endif