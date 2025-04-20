#ifndef FONT_H
#define FONT_H

#include "Screen/Screen.h"
#include "constants/constants.h"

#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdexcept>

//This class implements an easy-fast way to use text in my project. 
//You can load fonts inside buttons or directly in the screen. It is necessary
//to initialize the fonts library to use this class. You can do that by calling
//TTF_Init(). Unlike images an buttons in this project, the dimensions of the font
//are determined by the font size (the same as in Microsoft Word). Fonts are,
//essentially, files that carry all the information of a specific type (f.e. Arial).
//This information can be loaded up in execution time to "draw" text given these instructions.
//These instructons are .ttf files
class Font{

    private:
        
        //The X position in pixels where the text is placed
        int x;

        //The Y position in pixels where the text is placed
        int y;
        
        //The foreground color of the text
        SDL_Color textColor;

        //The size in pixels of the font. In Microsoft Word you
        //use the same to scale the text
        int fontSize;
        
        //The TTF_Font instance associated with the text.
        TTF_Font * font;
        
        //What comes before .ttf
        std::string fontName;

        //The actual text to be shown
        std::string text;

        //The associated screen where the text is shown
        //defaults to mainScreen
        Screen * screen = &mainScreen;

        //The surface associaated with the bitmap of the text
        SDL_Surface* textSurface = nullptr;

        //The texture of the text. THe same as in the image class
        SDL_Texture* textTexture = nullptr;

    public:

        //CONSTRUCTORS/DESTRUCTOR

        //Constructor
        Font();

        //Cnstructor
        Font(Screen * screen, const char * name, int size, const char * text, SDL_Color color);

        //Destructor
        ~Font();


        //GETTERS

        //Getter
        //
        //RETURNS:
        //An integer representing the X position in pixels of the text
        int getX() const;

        //Getter
        //
        //RETURNS:
        //An integer representing the Y position in pixels of the text
        int getY() const;

        //Getter
        //
        //RETURNS:
        //The SDL_Color instance that gives the foreground color to the text
        SDL_Color getColor() const;

        //Getter
        //
        //RETURNS:
        //An integer representing the font size in pixels
        int getfontSize() const;
        
        //Getter
        //
        //RETURNS:
        //A pointer to the TTF_Font (SDL) instance that handles the library
        TTF_Font * getFont() const;
        
        //Getter
        //
        //RETURNS:
        //The string representing the name of the file
        std::string getFontName() const;

        //Getter
        //
        //RETURNS:
        //A string representing tht text that is shown in the screen
        std::string getText() const;

        //Getter
        //
        //RETURNS:
        //The screen asociated to the font. By default is mainScreen
        Screen * getScreen() const;

        //Getter
        //
        //RETURNS:
        //A pointer to the SDL_Surface associated with the font
        SDL_Surface * getTextSurface() const;

        //Getter
        //
        //RETURNS:
        //A pointer to the SDL_Texture associated with the font
        SDL_Texture * getTextTexture() const;


        //SETTERS
        
        //Setter
        //
        //RETURNS:
        //void
        void setCoords(int x, int y);

        //Setter
        //Loads the coords in the same way as the button. The enum class
        //AbsPosition translates into pixel coordinates inside this method
        //without having the need to worry about calculating the coordinates
        //each time
        //
        //RETURNS:
        //void
        void setCoords(AbsPosition position);

        //Setter
        //NOTE: This method will free the texture and the surface and then create new ones
        //
        //RETURNS:
        //void
        void setColor(SDL_Color newColor);

        //Setter
        //NOTE: you need to call this method at least once if you didn't construct the 
        //instance directly (you called the constructor with no parameters). It will also 
        //free the previous surface and texture
        //
        //RETURNS:
        //void
        void setFont(TTF_Font * font);


        //Setter
        //NOTE: This method will free the texture and the surface and then create new ones
        //
        //RETURNS:
        //void
        void setText(const char * newText);


        //MISCELANEOUS

        //This method renders text with the dimensions of the surface
        //NOte that it doesn't show it directly, you'lll have to call Screen::Update()
        //
        //RETURNS:
        //0 
        int drawTextToRender();

};

#endif