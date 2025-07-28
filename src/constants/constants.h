#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "src/Screen/Screen.h"
#include "src/Sound/Sound.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <iostream>


//The width in pixels of the screen. Currently static
extern const int SCREENWIDTH;

//The height in pixels of the screen. Currently static
extern const int SCREENHEIGHT;


//
extern const char * BESTPLAYSFILEPATH;

//
extern const char * KEYBINDSFILEPATH;

//
extern const char * SONGSFILEPATH;


//This variable saves the current line of the song that is playing 
//inside the file "songs.txt". It is indexed at 1, so when 
//there is one song played this variable will save 1. If there are
//no songs this will be 0
extern int CURSONG;

//This variable saves the latest song that has been played. It doesn't
//change if the user rewinds songs. Only when the song ends and a new is
//played or the user skips the song this variable is changed. If the 
//user goes back to previous songs, this variable will be fixed. It is 
//indexed at 1, so when there is one song played this variable will save 1.
//If there are no songs this will be 0
extern int MAXSONG;


//The side length of 1 block in the game board. The blocks are squares, so this the
//width and also the length of 1 block.
extern const int BLOCKLENGTH;


//Instance of the class Screen. This is a global var. To access atributes and methods refer to the class Screen.
//This instance is read-only and access-only throughout the program.
extern Screen mainScreen;


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


//The position X in pixels of the background rectangle in the settings
extern const int SETTINGSBACKGROUNDX;

//The position Y in pixels of the background rectangle in the settings
extern const int SETTINGSBACKGROUNDY;

//The Width in pixels of the background rectangle in the settings
extern const int SETTINGSBACKGROUNDW;

//The Height in pixels of the background rectangle in the settings
extern const int SETTINGSBACKGROUNDH;

//The Height in pixels of the background texture in the settings.
//The rest (x,y,w) is the same as SETTINGSBACKGROUND
extern const int SETTINGSTEXTUREH;


//Refers to the x position where the sound settings start in the texture. This should be used solely for the
//rendering. It is calculated when the buttons in the settings are setted
extern const int TEXTURESOUNDX;

//Refers to the y position where the sound settings start in the texture. This should be used solely for the
//rendering 
extern int TEXTURESOUNDY;

//Refers to the width where the sound settings start in the texture. This should be used solely for the
//rendering . It is calculated when the buttons in the settings are setted
extern const int TEXTURESOUNDW;

//Refers to the height where the sound settings start in the texture. This should be used solely for the
//rendering 
extern int TEXTURESOUNDH;


//The position X in pixels of the hold figure background rectangle
extern const int HFX;

//The position Y in pixels of the hold figure background rectangle
extern const int HFY;

//The Width in pixels of the hold figure background rectangle
extern const int HFW;

//The Height in pixels of the hold figure background rectangle
extern const int HFH;


//An SDL_Keycode instance that saves the key that the player uses to move the figures to the left
extern SDL_Keycode CONTROLLEFT;

//An SDL_KeyCode instance that saves the key that the player uses to move the figures to the right
extern SDL_Keycode CONTROLRIGHT;

//An SDL_Keycode instance that saves the key that the player uses to move the figures down
extern SDL_Keycode CONTROLDOWN;

//An SDL_Keycode instance that saves the key that the player uses to rotate the figures right
extern SDL_Keycode CONTROLROTATERIGHT;

//An SDL_Keycode instance that saves the key that the player uses to instantly place a figure by fast drop
extern SDL_Keycode CONTROLFASTDOWN;

//An SDL_Keycode instance that saves the key that the player uses to swap a figure with the held one
extern SDL_Keycode CONTROLSWAP;

//An SDL_Keycode instance that saves the key that the player uses to rotate the figures left
extern SDL_Keycode CONTROLROTATELEFT;


//An unsigned integer of 32 bits representing the time (ms) that a figure takes to drop one tile
extern Uint32 FALLSPEED;

//AN integer representing the number of times the scroll input is multiplied 
extern int SCROLLFACTOR;


//The points that the player has
extern unsigned int POINTS;

//The current level of the game
extern unsigned int LEVEL;

//The lines cleared on the current level
extern unsigned int LINES;

//0 <= sound <= 100
extern int GENERALSOUNDLVL;

//0 <= sound <= 100
extern int EFFECTSSOUNDLVL;


//Saves wether if the user is dead or not
extern bool dead;


//A function that calculates the points won from clearing a certain number of lines (max. 4)
int calculatePoints(int linesCleared);

//A function that returns the current level. It depends on the total lines cleared
int getLevel();

//A function that returns the current speed. It depends on the level
Uint32 getFallSpeed();

//Color palette used in the rest of the project
//                                   R    G    B    A

constexpr SDL_Color CIANSH       = {155, 177, 222, 255};
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
constexpr SDL_Color LIGHT_CREAM  = {245, 229, 192, 255};


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

//This struct saves three integers corresponding to the level, the points and the lines
//cleared in a game. It is used to extract and handle the best plays from the user from
//a local file and write plays to it
struct Score{
    int points;
    int level;
    int lines;
};


//Global function that calculates the Y pixels of each constant in the enum AbsPosition. 
//It receives ONE constant of type AbsPosition (see the enum AbsPosition to see all the
//possible positions in the screen) and the Height of the object that you want to position,
//and returns the desired Y position in pixels.
//To calculate the X position use px().
//
//RETURNS:
//An integer representing the pixels of the Y position specified by the enum
int py(AbsPosition position, int objH);

//Global function that calculates the X pixels of each constant in the enum AbsPosition. 
//It receives ONE constant of type AbsPosition (see the enum AbsPosition to see all the
//possible positions in the screen) and the Width of the object that you want to position,
//and returns the desired X position in pixels.
//To calculate the Y position use py().
//
//RETURNS:
//An integer representing the pixels of the X position specified by the enum
int px(AbsPosition position, int objW);


//This method takes an SDL_Keycode instance and returns a string referencing the key. 
//
//RETURNS:
//The string associated with the SDL_Keycode instance
std::string convertKeyToLetter(SDL_Keycode key);

//This method takes a character and returns it's associated SDL_Keycode instance
//
//RETURNS:
//An SDL_Keycode instance associated with the character
SDL_Keycode convertLetterToKeycode(char c);


//This method returns a vector of type Score with the best plays of the user. It returns max. 5 plays.
//Score struct contains 3 integers that identify the level, the points and the lines cleared
//RETURNS:
//An std::vector of type Score
std::vector <Score> getBestPlays();

//This method takes a new score and updates the file containing all the best plays. It does so maintaining
//the sorting. Note that it doesn't sort the plays, but it only inserts the new score in it's correct 
//position. See sortBestPlays() for sorting
//RETURNS:
//-true if there were less than 5 plays
//-false if it couldn't open the file 
bool updateBestPlays(Score newScore);

//This method sorts the best plays inside the file, following the order level->points->lines
//Scores with the highest level will go first and in case two scores have the same level,
//the function will check for the points and so. This function calls getBestPlays()
//
//RETURNS:
//- true if the file could be opened, regardless if the function sorted or not.
//- false otherwise
bool sortBestPlays();


std::vector <SDL_Keycode> getFileKeybinds();

bool updateKeybindsFile();

//This method returns the path of a random music track in the Sounds/Music directory
//
//RETURNS:
//The relative path to the random song selected
std::string getRandomMusic();

//This function handles the change in the songs when the user clicks the radio buttons in the settings
//Can take two distinct param. values: "next", "previous"
//
//RETURNS:
//The relative path to the song according to the action
std::string getSong(std::string action);

//This method clears the songs file 
//
//RETURNS:
//void
void clearSongsFile();


//This function attempts to render the perimeter of a circle. This is not implemented by me, see main.cc for acknowledgements
//
//RETURNS:
//0 if the rendering was done successfully
//-1 if there was a problem rendering a point
int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius);

//This function attempts to render the perimeter of a semicircle. Either the left semicircle or the right semicircle can be 
//rendered by passing the lst parameter. This is an overload of SDL_RenderDrawCircle()
//
//RETURNS:
//0 if the rendering was done successfully
//-1 if there was a problem rendering a point
int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius, bool onlyRightQuadrant);

//This function attempts to render the perimeter of a circle. This is not implemented by me, see main.cc for acknowledgements
//
//RETURNS:
//0 if the rendering was done successfully
//-1 if there was a problem rendering a point
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

#endif