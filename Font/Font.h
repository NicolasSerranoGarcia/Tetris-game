#ifndef FONT_H
#define FONT_H

#include "Screen/Screen.h"
#include "constants/constants.h"

#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdexcept>


class Font{
    private:
        Screen * screen; //asociate a screen to the instance of the text
        TTF_Font * font;
        SDL_Surface* textSurface;
        SDL_Texture* textTexture;
        std::string fontName;
        int fontSize;
        std::string text;
        SDL_Color textColor;
        int x;
        int y;
    public:

        Font();
        Font(Screen * screen, const char * name, int size, const char * text, SDL_Color color);
        ~Font();

        Screen * getScreen() const;
        std::string getFontName() const;
        int getfontSize() const;
        std::string getText() const;
        SDL_Color getColor() const;
        SDL_Surface * getTextSurface() const;
        SDL_Texture * getTextTexture() const;
        TTF_Font * getFont() const;
        int getY() const;
        int getX() const;


        void setFont(TTF_Font * font);
        void setColor(SDL_Color newColor);
        void setText(const char * newText);
        void setCoords(AbsPosition position);
        void setCoords(int x, int y);

        int drawTextToRender();
};

#endif