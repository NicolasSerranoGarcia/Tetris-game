#ifndef BUTTON_CC
#define BUTTON_CC

#include "Button.h"

#include <iostream>

//Constructor
Button::Button(SDL_Rect container, SDL_Color color, Screen * screen){
    this->container = container;
    this->color = color;
    this->screen = screen;
}

//Constructor
Button::Button(Coord xy, int w, int h, SDL_Color color, Screen * screen){
    this->screen = screen;
    this->color = color;
    this->container.h = h;
    this->container.w = w;
    this->container.x = xy.x;
    this->container.y = xy.y;
}

//Constructor
Button::Button(const int x, const int y, const int w, const int h, SDL_Color color, Screen * screen){
    this->screen = screen;
    this->color = color;
    this->container.h = h;
    this->container.w = w;
    this->container.x = x;
    this->container.y = y;
}

//Destructor
Button::~Button(){
    this->color = {0,0,0,0};
    this->container = {0,0,0,0};
    this->ButtonEvent = {0};
    this->screen = nullptr;
    this->setTextCalled = false;
    this->font =  nullptr;
}

//Getter
Screen * Button::getScreen() const{
    return this->screen;
}

//Getter
SDL_Rect Button::getContainer() const{
    return this->container;
}

//Getter
SDL_Event Button::getEvent() const{
    return this->ButtonEvent;
}

//Getter
SDL_Color Button::getColor() const{
    return this->color;
}

//Getter
Font * Button::getFont() const{
    return this->font;
}

//Setter
void Button::setFont(Font * newFont){
    if(newFont == nullptr){
        this->setTextCalled = false;
        this->font = newFont;
    }
    this->font = newFont;
    this->setTextCalled = true;
}

//Setter
void Button::setScreen(Screen * newScreen){
    this->screen = newScreen;
}

//Setter
void Button::setContainer(SDL_Rect newContainer){
    this->container = newContainer;
}

//Setter
void Button::setColor(SDL_Color newColor){
    this->color = newColor;
}


bool Button::isClicked(){
  
    Coord mouse;

    SDL_GetMouseState(&mouse.x, &mouse.y);

    //check if the cursor is inside
    if(!((mouse.x <= (getContainer().x + getContainer().w)) && (mouse.x >= getContainer().x) && 
         (mouse.y <= (getContainer().y + getContainer().h)) && (mouse.y >= getContainer().y)))
    {
        return false;
    }


    //check if the user clicked
    while(SDL_PollEvent(&this->ButtonEvent)){
        if(getEvent().type == SDL_MOUSEBUTTONDOWN){
            return true;
        }
    }

    SDL_PushEvent(&this->ButtonEvent);

    return false;
}

//This method draws the button to the screen curently selected on the instance. 
//NOTE: this method does not update the screen (call Screen::Update() for that). 
//The button text is not necessary. You can draw a button to the screen without
//a text (the method automatically handles that). If the instance has an associated Font
//but you want to draw the button without a text, make sure you first delete the associated 
//font by calling Button::setFont(nullptr). 
void Button::drawToRender(){
    
    SDL_SetRenderDrawColor(getScreen()->getRender(), getColor().r, getColor().g, getColor().b, getColor().a);
    SDL_RenderFillRect(getScreen()->getRender(), &this->container);
    
    //also add the text if there is one
    if(this->setTextCalled){
        this->font->drawTextToRender(this->container.x, this->container.y);
    }
}

#endif