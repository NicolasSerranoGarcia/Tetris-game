#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdexcept>
#include "Screen/Screen.h"


class Font{
    private:
        static Screen * screen; //asociate a screen to the instance of the text
        static TTF_Font * font;
        SDL_Surface* textSurface;
        SDL_Texture* textTexture;
        std::string fontName;
        int fontSize;
        std::string text;
        SDL_Color textColor;
    public:
        enum Font_p{
            FONT_CENTER,
            FONT_UP,
            FONT_DOWN,
            FONT_LEFT,
            FONT_RIGHT,
            FONT_UP_LEFT,
            FONT_UP_RIGHT,
            FONT_DOWN_LEFT,
            FONT_DOWN_RIGHT,
            FONT_CENTER_UP,
            FONT_CENTER_DOWN,
            FONT_CENTER_LEFT,
            FONT_CENTER_RIGHT
        };

        Font(Screen * screen, const char * name, int size, const char * text, SDL_Color color);
        ~Font();
        Screen * getScreen() const;
        std::string getFontName() const;
        int getfontSize() const;
        std::string getText() const;
        SDL_Color getColor() const;
        SDL_Surface * getTextSurface() const;
        SDL_Texture * getTextTexture() const;
        void addColor(SDL_Color newColor);
        void addText(const char * newText);
        int drawTextToRender(int x, int y);
        int drawTextToRender(Font_p position);
        void reset();
};