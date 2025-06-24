#include "Font.h"

Font::Font(){
    x = 0;
    y = 0;
    textColor = {0, 0, 0, 0};
    fontSize = 0;
    font = nullptr;
    fontName = "";
    text = "";
}

Font::Font(Screen * screen, const char * name, int size, const char * text, SDL_Color color){
    
    this->screen = screen;
    fontName = name;
    fontSize = size;
    this->text = text;
    this->textColor = color;
    
    std::string path = "src/fonts/" + fontName + ".ttf";
    font = TTF_OpenFont(path.c_str(), getfontSize()); //load the font
    
    
    if (!font) {
        throw std::invalid_argument("The font could not be loaded up");
    }


    textSurface = TTF_RenderText_Solid(font, text, color);
    textTexture = SDL_CreateTextureFromSurface(screen->getRender(), textSurface);
}

Font::~Font() {
    if (textSurface != nullptr){
        SDL_FreeSurface(textSurface);
    }
    if (textTexture != nullptr){
        SDL_DestroyTexture(textTexture);
    }
    if (font != nullptr){
        TTF_CloseFont(font);
    }
}


int Font::getX() const{
    return x;
}

int Font::getY() const{
    return y;
}

SDL_Color Font::getColor() const{
    return textColor;
}

int Font::getfontSize() const{
    return fontSize;
}

TTF_Font * Font::getFont() const{
    return font;
}

std::string Font::getFontName() const{
    return fontName;
}

std::string Font::getText() const{
    return text;
}

Screen * Font::getScreen() const {
    return screen;
}

SDL_Surface * Font::getTextSurface() const{
    return textSurface;
}

SDL_Texture * Font::getTextTexture() const{
    return textTexture;
}


void Font::setCoords(int x, int y){
    this->x = x;
    this->y = y;
}

void Font::setCoords(AbsPosition position){

    int relativeCenterX = textSurface->w/2;
    int relativeCenterY = textSurface->h/2;

    switch(position){
        case AbsPosition::POS_CENTER:
            Font::setCoords(screen->getWidth()/2 - relativeCenterX,  screen->getHeight()/2 - relativeCenterY); break;

        case AbsPosition::POS_UP:
            Font::setCoords(screen->getWidth()/2 - relativeCenterX, 0); break;

        case AbsPosition::POS_DOWN:
            Font::setCoords(screen->getWidth()/2 - relativeCenterX,  screen->getHeight() - relativeCenterY*2); break;

        case AbsPosition::POS_LEFT:
            Font::setCoords(0 ,  screen->getHeight()/2 - relativeCenterY); break;

        case AbsPosition::POS_RIGHT:
            Font::setCoords(screen->getWidth() - relativeCenterX*2,  screen->getHeight()/2 - relativeCenterY); break;

        case AbsPosition::POS_CENTER_DOWN:
            Font::setCoords(screen->getWidth()/2 - relativeCenterX,  screen->getHeight()/2 - relativeCenterY + screen->getHeight()/6); break;

        case AbsPosition::POS_CENTER_UP:
            Font::setCoords(screen->getWidth()/2 - relativeCenterX,  screen->getHeight()/2 - relativeCenterY - screen->getHeight()/6); break;

        case AbsPosition::POS_CENTER_LEFT:
            Font::setCoords(screen->getWidth()/2 - 2*relativeCenterX,  screen->getHeight()/2 - relativeCenterY); break;

        case AbsPosition::POS_CENTER_RIGHT:
            Font::setCoords(screen->getWidth()/2,  screen->getHeight()/2 - relativeCenterY); break;

        case AbsPosition::POS_UP_LEFT:
            Font::setCoords(0 ,  0); break;

        case AbsPosition::POS_UP_RIGHT:
            Font::setCoords(screen->getWidth() - relativeCenterX*2 ,  0); break;

        case AbsPosition::POS_DOWN_LEFT:
            Font::setCoords(0 ,  screen->getHeight() - relativeCenterY*2); break;

        case AbsPosition::POS_DOWN_RIGHT:
            Font::setCoords(screen->getWidth() - relativeCenterX*2 ,  screen->getHeight() - relativeCenterY*2); break;

    }
}

void Font::setColor(SDL_Color newColor){
    
    //Free the previous parameters
    SDL_FreeSurface(getTextSurface());
    SDL_DestroyTexture(getTextTexture());

    textColor = newColor;
    textSurface = TTF_RenderText_Solid(font, getText().c_str(), newColor);
    textTexture = SDL_CreateTextureFromSurface(screen->getRender(), textSurface);
}

void Font::setFont(TTF_Font * font){

    std::string path = "fonts/" + getFontName() + ".ttf";
    font = TTF_OpenFont(path.c_str(), getfontSize()); //load the font
    
    //Free the previous parameters
    SDL_FreeSurface(getTextSurface());
    SDL_DestroyTexture(getTextTexture());

    textSurface = TTF_RenderText_Solid(font, getText().c_str(), getColor());
    textTexture = SDL_CreateTextureFromSurface(screen->getRender(), textSurface);
}

void Font::setText(const char * newText){

    //Free the previous parameters
    SDL_FreeSurface(getTextSurface());
    SDL_DestroyTexture(getTextTexture());

    text = newText;
    textSurface = TTF_RenderText_Solid(font, newText, getColor());
    textTexture = SDL_CreateTextureFromSurface(screen->getRender(), textSurface);
}


int Font::drawTextToRender(){

    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(screen->getRender(), getTextTexture(), NULL, &textRect);
    return 0;
}