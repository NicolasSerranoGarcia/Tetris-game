#include "Button.h"

Button::Button(){
    color = {0,0,0,0};
    container = {0,0,0,0};

    screen = &mainScreen;
    font =  nullptr;
    image = nullptr;
}

Button::Button(SDL_Rect container, SDL_Color color, Screen * screen){
    this->container = container;

    this->color = color;
    this->screen = screen;
}

Button::Button(Coord xy, int w, int h, SDL_Color color, Screen * screen){
    this->container.h = h;
    this->container.w = w;
    container.x = xy.x;
    container.y = xy.y;

    this->screen = screen;
    this->color = color;
}

Button::Button(const int x, const int y, const int w, const int h, SDL_Color color, Screen * screen){
    this->container.h = h;
    this->container.w = w;
    this->container.x = x;
    this->container.y = y;

    this->screen = screen;
    this->color = color;
}

Button::~Button(){
    container = {0,0,0,0};
    color = {0,0,0,0};

    screen = nullptr;
    font =  nullptr;
    image = nullptr;

}

bool Button::getVisibility() const{
    return isVisible;
}

Screen * Button::getScreen() const{
    return screen;
}

SDL_Rect Button::getContainer() const{
    return container;
}

SDL_Color Button::getColor() const{
    return color;
}

Font * Button::getFont() const{
    return font;
}


void Button::setVisibility(bool newVisibility){
    isVisible = newVisibility;
}

void Button::setFont(Font * newFont){
    font = newFont;
}

void Button::setImage(Image * newImage){
    image = newImage;
}

void Button::setScreen(Screen * newScreen){
    screen = newScreen;
}

void Button::setContainer(SDL_Rect newContainer){
    container = newContainer;
}

void Button::setColor(SDL_Color newColor){
    color = newColor;
}


bool Button::isClicked(SDL_Event * event){

    Coord mouse;

    //loads the two integers with the position in pixels of the mouse
    SDL_GetMouseState(&mouse.x, &mouse.y);

    //check if the cursor is inside
    if(!((mouse.x <= (getContainer().x + getContainer().w)) && (mouse.x >= getContainer().x) && 
         (mouse.y <= (getContainer().y + getContainer().h)) && (mouse.y >= getContainer().y)))
    {
        return false;
    }


    //check if the user clicked
    if(event->type == SDL_MOUSEBUTTONDOWN){
        return true;
    }

    return false;
}

bool Button::isClickedSubdivision(SDL_Event * event, SDL_Rect rect){

    if((rect.x == 0) && (rect.y == 0) && (rect.w == 0) && (rect.h == 0)){    
        return isClicked(event);
    }

    Coord mouse;

    //loads the two integers with the position in pixels of the mouse
    SDL_GetMouseState(&mouse.x, &mouse.y);

    //Normalize the coords of the rectangle to have (0,0) at the upper left point of our button
    int x = rect.x + container.x;
    int y = rect.y + container.y;
    int w = rect.w;
    int h = rect.h;

    //check if the cursor is inside the whole button and then if the cursor is inside of the desired rectangle
    if((!((mouse.x <= (getContainer().x + getContainer().w)) && (mouse.x >= getContainer().x) && 
          (mouse.y <= (getContainer().y + getContainer().h)) && (mouse.y >= getContainer().y))) 
         ||
         (!((mouse.x <= (x + w)) && (mouse.x >= x) && 
            (mouse.y <= (y + h)) && (mouse.y >= y)))){

            return false;
    }


    //check if the user clicked
    if(event->type == SDL_MOUSEBUTTONDOWN){
        return true;
    }

    return false;
}

void Button::setRelativeTo(Button refButton, RPosition position){

    int selfHeight = container.h;
    int selfWidth = container.w;

    //refers to the object we want to place in reference to. So if we want to place a rectangle to the left of a button, the button is the ref in this case.
    int refX = refButton.container.x;
    int refY = refButton.container.y;
    int refW = refButton.container.w;
    int refH = refButton.container.h;
    
    //Let some air between the objects
    const int margin = 10; 
    
    switch(position){
        case RPosition::POS_REL_DOWN:
            container.x = refX + refW/2 - selfWidth/2;
            container.y = refY + refH + margin;
            break;
        
        case RPosition::POS_REL_DOWN_LEFT:
            container.x = refX;
            container.y = refY + refH + margin;
            break;
        
        case RPosition::POS_REL_DOWN_RIGHT:
            container.x = refX + refW - selfWidth;
            container.y = refY + refH + margin;
            break;
            
        case RPosition::POS_REL_UP:
            container.x = refX + refW/2 - selfWidth/2;
            container.y = refY - selfHeight - margin;
            break;
            
        case RPosition::POS_REL_UP_LEFT:
            container.x = refX;
            container.y = refY - selfHeight - margin;
            break;
            
        case RPosition::POS_REL_UP_RIGHT:
            container.x = refX + refW - selfWidth;
            container.y = refY - selfHeight - margin;
            break;

        case RPosition::POS_REL_RIGHT:
            container.x = refX + refW + margin;
            container.y = refY + refH/2 - selfHeight/2;
            break;
            
        case RPosition::POS_REL_LEFT:
            container.x = refX - selfWidth - margin;
            container.y = refY + refH/2 - selfHeight/2;
            break;

        default:
            container.x = 0;
            container.y = 0;
            break;
    }
}

void Button::setRelativeTo(Font * refFont, RPosition position){

    int selfHeight = container.h;
    int selfWidth = container.w;

    
    //refers to the object we want to place in reference to. So if we want to place a rectangle to the left of a button, the button is the ref in this case.
    int refX = refFont->getX();
    int refY = refFont->getY();
    int refW = refFont->getTextSurface()->w;
    int refH = refFont->getTextSurface()->h;

    //Let some air between the objects
    const int margin = 10; 

    switch(position){
        case RPosition::POS_REL_DOWN:
            container.x = refX + refW/2 - selfWidth/2;
            container.y = refY + refH + margin;
            break;

        case RPosition::POS_REL_DOWN_LEFT:
            container.x = refX;
            container.y = refY + refH + margin;
            break;
            
        case RPosition::POS_REL_DOWN_RIGHT:
            container.x = refX + refW - selfWidth;
            container.y = refY + refH + margin;
            break;

        case RPosition::POS_REL_UP:
            container.x = refX + refW/2 - selfWidth/2;
            container.y = refY - selfHeight - margin;
            break;

        case RPosition::POS_REL_UP_LEFT:
            container.x = refX;
            container.y = refY - selfHeight - margin;
            break;
            
        case RPosition::POS_REL_UP_RIGHT:
            container.x = refX + refW - selfWidth;
            container.y = refY - selfHeight - margin;
            break;
            
        case RPosition::POS_REL_RIGHT:
            container.x = refX + refW + margin;
            container.y = refY + refH/2 - selfHeight/2;
            break;

        case RPosition::POS_REL_LEFT:
            container.x = refX - selfWidth - margin;
            container.y = refY + refH/2 - selfHeight/2;
            break;

        default:
            container.x = 0;
            container.y = 0;
            break;
    }
}

void Button::drawToRender(){
    SDL_SetRenderDrawColor(getScreen()->getRender(), getColor().r, getColor().g, getColor().b, getColor().a);
    SDL_RenderFillRect(getScreen()->getRender(), &this->container);
    
    //If there is an image, load it first so that if there is text, it is shown above it
    if(image != nullptr){
        image->CopyToRender();
    }

    //also add the text if there is one
    if(font != nullptr){
        font->setCoords(container.x + container.w/2 - font->getTextSurface()->w/2, container.y + container.h/2 - font->getTextSurface()->h/2);
        font->drawTextToRender();
    }
}