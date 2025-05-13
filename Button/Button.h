#ifndef BUTTON_H
#define BUTTON_H

#include "Screen/Screen.h"
#include "Font/Font.h"
#include "Image/Image.h"
#include "constants/constants.h"

#include <SDL2/SDL.h>


//2D vector used inside the button class
//to minimize variable declarations
struct Coord{
    int x;
    int y;
};


//This class implements a way to interact with the user.
//Allows to change screens, alter settings, stop the game...
//It can also hold text an images to ease the interaction 
//with the user. It is important to note that this class
//doesn't need any of the previous two to be rendered and
//shown to the screen.
//This class is an automated way to do all this, as 
//an instance can be set up with all this info
class Button{

    private:

        //This variable is used to check if the button is visible in the screen.
        //Partially visible buttons (for example in settings when you scroll) are considered visible
        bool isVisible = true;
        
        //This is the rectangle that determines the surface
        //of the button
        SDL_Rect container;

        //The plain color of the button. If there is a loaded image,
        //two things can happen: 
        //1. The image does not completely fill the rectangle, 
        //making this color visible on the empty parts.
        //
        //2. The image completely fills the rect., so the color
        //won't be seen
        //
        //When text is loaded the background color will be seen 
        SDL_Color color;

        //The associated screen where the button is shown. Defaults
        //to the mainScreen
        Screen * screen = &mainScreen;

        //An instance of my class Font, that automatically implements 
        //all the handling of the shown text. It is important to note 
        //that the text is not a requirement to show the button.
        //Defaults to nullptr
        Font * font = nullptr;

        //An instance of my class Image, that automatically implements
        //all the handling of the shown image. It is important to note 
        //that the image is not a requirement to show the button.
        //Defaults to nullptr
        Image * image = nullptr;

    public:

        //CONSTRUCTORS/DESTRUCTOR

        //Constructor
        Button();

        //Constructor
        Button(SDL_Rect container, SDL_Color color,  Screen * screen);

        //Constructor
        Button(const Coord xy, const int w, const int h, SDL_Color color, Screen * screen);

        //Constructor
        Button(const int x, const int y, const int w, const int h, SDL_Color color, Screen * screen);

        //Destructor
        ~Button();


        //GETTERS

        //Getter
        //
        //RETURNS:
        //A boolean that represents the visibility of the button 
        bool getVisibility() const;

        //Getter
        //
        //RETURNS:
        //A pointer to the screen that the button is using
        Screen * getScreen() const;

        //Getter
        //
        //RETURNS:
        //The SDL_Rect that delimits the button 
        SDL_Rect getContainer() const;

        //Getter
        //
        //RETURNS:
        //The SDL_Color instance of the button
        SDL_Color getColor() const;

        //Getter
        //
        //Returns:
        //A pointer to the Font instance of the button
        Font * getFont() const;


        //SETTERS

        //Setter
        //
        //RETURNS:
        //void
        void setVisibility(bool newVisibility);

        //Setter
        //
        //RETURNS:
        //void
        void setFont(Font * newFont);

        //Setter
        //
        //RETURNS:
        //void
        void setScreen(Screen * newScreen);

        //Setter
        //
        //RETURNS:
        //void
        void setContainer(SDL_Rect newContainer);

        //Setter
        //
        //RETURNS:
        //void
        void setColor(SDL_Color newColor);

        //Setter
        //
        //RETURNS:
        //void
        void setImage(Image * newImage);

        
        //MISCELANEOUS

        //This method checks if the user clicked the button.
        //Clicking means the cursor is ON the surface AND
        //the user presses the right or left mouse button
        //
        //RETURNS:
        //-true if the user clikced the button
        //-false otherwise
        bool isClicked(SDL_Event * event);

        //This method checks if the user clicked the button.
        //Clicking means the cursor is ON the surface AND
        //the user presses the right or left mouse button
        //
        //NOTE: This method checks if the user clicked in a
        //specific region of the button. The second parameter
        //rect represents the region that it is intended
        //to click. If a default rect (all 0) is passed, the 
        //function will do the same as Button::isClicked()
        //
        //NOTE 2: Keep in mind that the rectangle that is passed
        //is assumed to have it's (0,0) on the upper left corner
        //of our original button. E.g. if we want the parameter
        //rect to cover the right half part of our button, we would
        //pass {Button.w/2, 0, Button.w - Button.w/2, Button.h}.
        //
        //RETURNS:
        //-true if the user clikced the button
        //-false otherwise
        bool isClickedSubdivision(SDL_Event * event, SDL_Rect rect);
        
        //This method automatically sets the button relative to 
        //another button. For that, it uses the enum class
        //RPosition. It works in exactly the same way that
        //ABSPosition works. This method, in conjunction with
        //the other overload, calculates the position in pixels 
        //that the button has to have to be placed in the position
        //that the enum specifies
        //
        //RETURNS:
        //void
        void setRelativeTo(Button refButton, RPosition position);

        //This method automatically sets the button relative to 
        //an instance of class Font. For that, it uses the enum 
        //class RPosition. It works in exactly the same way that
        //ABSPosition works. This method, in conjunction with
        //the other overload, calculates the position in pixels 
        //that the button has to have to be placed in the position
        //that the enum specifies
        //
        //RETURNS:
        //void
        void setRelativeTo(Font * refFont, RPosition position);

        //This method renders the button to the screen. 
        //NOTE: this method does not update the screen 
        //(call Screen::Update() for that). The button 
        //text is not necessary. You can draw a button 
        //to the screen without a text (the method 
        //automatically handles that). If the instance 
        //has an associated Font but you want to draw 
        //the button without a text, make sure you first 
        //delete the associated font by calling Button::setFont(nullptr). 
        //The same goes for the image. If you want to 
        //load an image, first call Button::setImage()
        //
        //RETURNS:
        //void
        void drawToRender();

};

#endif