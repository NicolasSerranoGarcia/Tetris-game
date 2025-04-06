#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include "Screen/Screen.h"
#include "Font/Font.h"

//add so that text can be added inside the button

struct Coord{
    int x;
    int y;
};

class Button{
    private:
        SDL_Rect container;
        SDL_Color color;
        SDL_Event ButtonEvent;
        Screen * screen;
        Font * text = nullptr;
        bool setTextCalled = false;


    public:
        Button(SDL_Rect container, SDL_Color color,  Screen * screen);
        Button(const Coord xy, const int w, const int h, SDL_Color color, Screen * screen);
        Button(const int x, const int y, const int w, const int h, SDL_Color color, Screen * screen);
        ~Button();
        Screen * getScreen();
        SDL_Rect getContainer();
        SDL_Event getEvent();
        SDL_Color getColor();
        void setText(Font * Text);
        Font * getText();
        bool isClicked();
        void drawToRender();
        //add setters to all fields

};

#endif