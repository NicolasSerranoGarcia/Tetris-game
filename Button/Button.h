#ifndef BUTTON_H
#define BUTTON_H

#include "Screen/Screen.h"
#include "Font/Font.h"

#include <SDL2/SDL.h>

//just a 2D vector
struct Coord{
    int x;
    int y;
};


//Implement a dynamic and visual way to change between screens (ej main screen and settings). It just consists of an SDL_rectangle with 
//an associated color and a text of type Font.
class Button{
    private:
        SDL_Rect container;
        SDL_Color color;
        SDL_Event ButtonEvent;
        Screen * screen;
        Font * font = nullptr; //refers to the text that appears inside the button
        bool setTextCalled = false;


    public:
        Button(SDL_Rect container, SDL_Color color,  Screen * screen);
        Button(const Coord xy, const int w, const int h, SDL_Color color, Screen * screen);
        Button(const int x, const int y, const int w, const int h, SDL_Color color, Screen * screen);
        ~Button();

        Screen * getScreen() const;
        SDL_Rect getContainer() const;
        SDL_Event getEvent() const;
        SDL_Color getColor() const;
        Font * getFont() const;

        void setFont(Font * newFont);
        void setScreen(Screen * newScreen);
        void setContainer(SDL_Rect newContainer);
        void setColor(SDL_Color newColor);
        
        bool isClicked();
        void drawToRender();
};

#endif