#ifndef SLIDER_H
#define SLIDER_H

#include <SDL2/SDL.h>
#include "src/Button/Button.h"

//This class implements an auxiliary object to work with slidable scenes
class Slider{

    private:
        //The rect that corresponds to the rectangle that the 
        //slider is inside of
        SDL_Rect rectContainer;

        //The actual visual object
        Button slider;

        //THe limit to where the button y (or x) pos can go up
        int minPos;

        //THe limit to where the button y (or x) pos can go down
        int maxPos;

        //The inline color the button takes when the button is pressed
        SDL_Color pressedColor;

        //The default color the slider takes when not pressed
        SDL_Color defColor;

        //This variable saves the state of the slider. Whenever the user
        //presses the slider, this variable gets set to true. When the user stops
        //pressing the slider this variable will change it's value to false. 
        bool isClickedNow = false;
        
        //This variable saves the state of the slider. Whenever the slider goes 
        //invisible because the user is sliding another slider or the button 
        //is behind something, this variable will be set to false. In the other 
        //case the variable will be set to true. 
        //Note: In the case the slider is partially visible (e.g. half of it is
        //visible and the other half is not) this variable will be true.
        //This means that the slider must be completely invisible for this
        //variable to be false.
        bool isVisible;

    public:

        //CONSTRUCTORS/DESTRUCTOR

        Slider();

        // Slider(SDL_Rect rect, SDL_Color pressedColor, SDL_Color defaultColor);

        Slider(Button button, int minPos, int maxPos, SDL_Color pressedColor);


        //GETTERS

        //Getter
        //
        //RETURNS:
        //The button associated with the slider
        Button getSliderButton();

        //Getter
        //
        //RETURNS:
        //An integer representing the minimum position
        //to where the slider can go
        int getMin();

        //Getter
        //
        //RETURNS:
        //An integer representing the maximum position
        //to where the slider can go
        int getMax();

        //Getter
        //
        //RETURNS:
        //An SDL_Color instance representing the color
        //that the slider takes when the user clicks on it
        SDL_Color getPressedColor();

        //Getter
        //
        //RETURNS:
        //A boolean that represents wether the slider is 
        //being clicked now
        bool getClickedNow();

        //Getter
        //
        //RETURNS:
        //a boolean representing wether the slider is visible
        //or not. Note that if the slider is partially visible
        //this method will still return true
        bool getVisibility();

        //SETTERS

        //Setter
        //
        //RETURNS:
        //void
        void setClickedNow(bool state);

        //Setter
        //
        //RETURNS:
        //void
        void setSliderButton(Button newSlider);

        //Setter
        //
        //RETURNS:
        //void
        void setSliderY(int y);

        //Setter
        //
        //RETURNS:
        //void
        void setMin(int y);

        //Setter
        //
        //RETURNS:
        //void
        void setMax(int y);

        //Setter
        //
        //RETURNS:
        //void
        void setPressedColor(SDL_Color color);

        //Setter
        //
        //RETURNS:
        //void
        void setVisibility(bool v);


        //MISCELLANEOUS

        //This method renders the slider to the screen. Note that
        //it will only render the clickble part.
        //
        //RETURNS:
        //void
        void render();

        //This method renders the slider button as a circle.
        //This method won't work unless the button of the slider is a square
        //
        //RETURNS:
        //void
        void RenderAsCircle();

        //This method is a wrapper for the Button::isClicked() method.
        //
        //RETURNS:
        //true if the user is clicking the slider button
        //false otherwise
        bool isClicked(SDL_Event *event);

};

#endif