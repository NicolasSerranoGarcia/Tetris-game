#ifndef BUTTON_CC
#define BUTTON_CC

#include "Button.h"
#include <iostream>

Button::Button(SDL_Rect container, SDL_Color color, Screen * screen){
    this->container = container;
    this->color = color;
    this->screen = screen;
}

Button::Button(Coord xy, int w, int h, SDL_Color color, Screen * screen){
    this->screen = screen;
    this->color = color;
    this->container.h = h;
    this->container.w = w;
    this->container.x = xy.x;
    this->container.y = xy.y;
}

Button::Button(const int x, const int y, const int w, const int h, SDL_Color color, Screen * screen){
    this->screen = screen;
    this->color = color;
    this->container.h = h;
    this->container.w = w;
    this->container.x = x;
    this->container.y = y;
}

Button::~Button(){
    
}

Screen * Button::getScreen(){
    return this->screen;
}

SDL_Rect Button::getContainer(){
    return this->container;
}

SDL_Event Button::getEvent(){
    return this->ButtonEvent;
}

SDL_Color Button::getColor(){
    return this->color;
}

Font * Button::getText(){
    return this->text;
}

void Button::setText(Font * text){
    this->text = text;
    this->setTextCalled = true;
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

void Button::drawToRender(){
    //also add the text if exists
    
    SDL_SetRenderDrawColor(getScreen()->getRender(), getColor().r, getColor().g, getColor().b, getColor().a);
    SDL_RenderFillRect(getScreen()->getRender(), &this->container);
 
    if(this->setTextCalled){
        //load also the text
        this->text->drawTextToRender(this->container.x, this->container.y);
    }
}

#endif