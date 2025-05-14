#ifndef SLIDER_H
#define SLIDER_H

#include <SDL2/SDL.h>
#include "Button/Button.h"

//This class implements an auxiliary object to work with slidable scenes
class Slider{

    private:
        //The rect that corresponds to the rectangle that the 
        //slider is inside of
        SDL_Rect rectContainer;

        //The actual visual object
        Button slider;

        //THe limit to where the button y pos can go up
        int minY;

        //THe limit to where the button y pos can go down
        int maxY;

        //The inline color the button takes when the button is pressed
        SDL_Color pressedColor;

        SDL_Color defColor;

        bool isClickedNow = false;
        
    public:
        Slider();
        Slider(SDL_Rect rect, SDL_Color pressedColor, SDL_Color defaultColor);
        Slider(Button button, int minY, int maxY, SDL_Color pressedColor);

        Button getSliderButton();
        int getMinY();
        int getMaxY();
        SDL_Color getPressedColor();
        bool getClickedNow();

        void setClickedNow(bool state);
        void setSliderButton(Button newSlider);
        void setSliderY(int y);
        void setMinY(int y);
        void setMaxY(int y);
        void setPressedColor(SDL_Color color);


        void render();
        bool isClicked(SDL_Event *event);

};

#endif