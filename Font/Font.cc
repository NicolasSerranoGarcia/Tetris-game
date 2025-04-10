#include "Font.h"

#include <string>

//Constructor
Font::Font(){
    this->x = 0;
    this->y = 0;
    this->screen = nullptr;
    fontName = "";
    fontSize = 0;
    this->text = "";
    this->textColor = {0, 0, 0, 0};
    screen = nullptr;
    font = nullptr;
}

//Constructor
Font::Font(Screen * screen, const char * name, int size, const char * text, SDL_Color color){
    
    this->screen = screen;
    fontName = name;
    fontSize = size;
    this->text = text;
    this->textColor = color;
    
    std::string path = "fonts/" + fontName + ".ttf";
    font = TTF_OpenFont(path.c_str(), getfontSize()); //load the font
    
    
    if (!font) {
        throw std::invalid_argument("The font could not be loaded up");
    }


    textSurface = TTF_RenderText_Solid(font, text, color);
    textTexture = SDL_CreateTextureFromSurface(screen->getRender(), textSurface);
}

//Destructor
Font::~Font() {
    if (textSurface) SDL_FreeSurface(textSurface);
    if (textTexture) SDL_DestroyTexture(textTexture);
    if (font) TTF_CloseFont(font);
}

//Getter
Screen * Font::getScreen() const {
    return screen;
}

//Getter
std::string Font::getFontName() const{
    return fontName;
}

//Getter
int Font::getfontSize() const{
    return fontSize;
}

//Getter
std::string Font::getText() const{
    return text;
}

//Getter
SDL_Color Font::getColor() const{
    return textColor;
}

//Getter
SDL_Surface * Font::getTextSurface() const{
    return textSurface;
}

//Getter
SDL_Texture * Font::getTextTexture() const{
    return textTexture;
}

//Getter
TTF_Font * Font::getFont() const{
    return this->font;
}

int Font::getX() const{
    return this->x;
}

int Font::getY() const{
    return this->y;
}

//changes font main color
//something strange happends and the function resets the screen when called
void Font::setColor(SDL_Color newColor){
    SDL_FreeSurface(getTextSurface());
    SDL_DestroyTexture(getTextTexture());
    this->textColor = newColor;
    this->textSurface = TTF_RenderText_Solid(font, getText().c_str(), newColor);
    this->textTexture = SDL_CreateTextureFromSurface(screen->getRender(), textSurface);
}

//changes displayed text
void Font::setText(const char * newText){
    SDL_FreeSurface(getTextSurface());
    SDL_DestroyTexture(getTextTexture());
    this->text = newText;
    this->textSurface = TTF_RenderText_Solid(font, newText, getColor());
    this->textTexture = SDL_CreateTextureFromSurface(screen->getRender(), textSurface);
}

//reset the font used (or set it if there was no previous set) 
//NOTE: you need to call this method at least once if you didn't construct the instance directly (you called the constructor with no parameters)
void Font::setFont(TTF_Font * font){

    std::string path = "fonts/" + getFontName() + ".ttf";
    font = TTF_OpenFont(path.c_str(), getfontSize()); //load the font

    SDL_FreeSurface(getTextSurface());
    SDL_DestroyTexture(getTextTexture());
    this->font = font;
    this->textSurface = TTF_RenderText_Solid(font, getText().c_str(), getColor());
    this->textTexture = SDL_CreateTextureFromSurface(screen->getRender(), textSurface);
}

void Font::setCoords(int x, int y){
    //also save the posiiton where it is printed
    this->x = x;
    this->y = y;
}

//load teh coords via absolute position see AbsPosition enum for options
void Font::setCoords(AbsPosition position){

    
    int relativeCenterX = this->textSurface->w/2;
    int relativeCenterY = this->textSurface->h/2;

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


//only loads the text to the selected render previously in class calls. To show de text use Screen::Update()
int Font::drawTextToRender(){
    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(screen->getRender(), getTextTexture(), NULL, &textRect);
    return 0;
}