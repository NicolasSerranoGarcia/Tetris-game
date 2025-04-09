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


bool Button::isClicked(SDL_Event * event){
  
    Coord mouse;

    SDL_GetMouseState(&mouse.x, &mouse.y);

    //check if the cursor is inside
    if(!((mouse.x <= (getContainer().x + getContainer().w)) && (mouse.x >= getContainer().x) && 
         (mouse.y <= (getContainer().y + getContainer().h)) && (mouse.y >= getContainer().y)))
    {
        return false;
    }


    //check if the user clicked
    while(SDL_PollEvent(event)){
        if(event->type == SDL_MOUSEBUTTONDOWN){
            return true;
        }
    }

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

//This function is overloaded. There will be a way to place the object you're trying to place relative to any other object. 
void Button::setRelativeTo(Button refButton, RPosition position){

    int selfHeight = this->container.h;
    int selfWidth = this->container.w;

    //refers to the object we want to place in reference to. So if we want to place a rectangle to the left of a button, the button is the ref in this case.
    int refX = refButton.container.x;
    int refY = refButton.container.y;
    int refW = refButton.container.w;
    int refH = refButton.container.h;

    //Let some air between the objects
    const int margin = 10; 

    switch(position){
        case RPosition::POS_REL_DOWN:
            this->container.x = refX + refW/2 - selfWidth/2;
            this->container.y = refY + refH + margin;
            break;

        case RPosition::POS_REL_DOWN_LEFT:
            this->container.x = refX;
            this->container.y = refY + refH + margin;
            break;

        case RPosition::POS_REL_DOWN_RIGHT:
            this->container.x = refX + refW - selfWidth;
            this->container.y = refY + refH + margin;
            break;

        case RPosition::POS_REL_UP:
            this->container.x = refX + refW/2 - selfWidth/2;
            this->container.y = refY - selfHeight - margin;
            break;

        case RPosition::POS_REL_UP_LEFT:
            this->container.x = refX;
            this->container.y = refY - selfHeight - margin;
            break;

        case RPosition::POS_REL_UP_RIGHT:
            this->container.x = refX + refW - selfWidth;
            this->container.y = refY - selfHeight - margin;
            break;

        case RPosition::POS_REL_RIGHT:
            this->container.x = refX + refW + margin;
            this->container.y = refY + refH/2 - selfHeight/2;
            break;

        case RPosition::POS_REL_LEFT:
            this->container.x = refX - selfWidth - margin;
            this->container.y = refY + refH/2 - selfHeight/2;
            break;

        default:
            this->container.x = 0;
            this->container.y = 0;
            break;
    }
}


void Button::setRelativeTo(Font * refFont, RPosition position){

    int selfHeight = this->container.h;
    int selfWidth = this->container.w;


    //refers to the object we want to place in reference to. So if we want to place a rectangle to the left of a button, the button is the ref in this case.
    int refX = refFont->getX();
    int refY = refFont->getY();
    int refW = refFont->getTextSurface()->w;
    int refH = refFont->getTextSurface()->h;

    //Let some air between the objects
    const int margin = 10; 

    switch(position){
        case RPosition::POS_REL_DOWN:
            this->container.x = refX + refW/2 - selfWidth/2;
            this->container.y = refY + refH + margin;
            break;

        case RPosition::POS_REL_DOWN_LEFT:
            this->container.x = refX;
            this->container.y = refY + refH + margin;
            break;

        case RPosition::POS_REL_DOWN_RIGHT:
            this->container.x = refX + refW - selfWidth;
            this->container.y = refY + refH + margin;
            break;

        case RPosition::POS_REL_UP:
            this->container.x = refX + refW/2 - selfWidth/2;
            this->container.y = refY - selfHeight - margin;
            break;

        case RPosition::POS_REL_UP_LEFT:
            this->container.x = refX;
            this->container.y = refY - selfHeight - margin;
            break;

        case RPosition::POS_REL_UP_RIGHT:
            this->container.x = refX + refW - selfWidth;
            this->container.y = refY - selfHeight - margin;
            break;

        case RPosition::POS_REL_RIGHT:
            this->container.x = refX + refW + margin;
            this->container.y = refY + refH/2 - selfHeight/2;
            break;

        case RPosition::POS_REL_LEFT:
            this->container.x = refX - selfWidth - margin;
            this->container.y = refY + refH/2 - selfHeight/2;
            break;

        default:
            this->container.x = 0;
            this->container.y = 0;
            break;
    }
}

#endif