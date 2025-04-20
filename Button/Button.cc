#include "Button.h"

Button::Button(){
    this->color = {0,0,0,0};
    this->container = {0,0,0,0};

    this->screen = &mainScreen;
    this->font =  nullptr;
    this->image = nullptr;
}

Button::Button(SDL_Rect container, SDL_Color color, Screen * screen){
    this->container = container;

    this->color = color;
    this->screen = screen;
}

Button::Button(Coord xy, int w, int h, SDL_Color color, Screen * screen){
    this->container.h = h;
    this->container.w = w;
    this->container.x = xy.x;
    this->container.y = xy.y;

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
    this->container = {0,0,0,0};
    this->color = {0,0,0,0};

    this->screen = nullptr;
    this->font =  nullptr;
    this->image = nullptr;

}


Screen * Button::getScreen() const{
    return this->screen;
}

SDL_Rect Button::getContainer() const{
    return this->container;
}

SDL_Color Button::getColor() const{
    return this->color;
}

Font * Button::getFont() const{
    return this->font;
}


void Button::setFont(Font * newFont){
    this->font = newFont;
}

void Button::setImage(Image * newImage){
    this->image = newImage;
}

void Button::setScreen(Screen * newScreen){
    this->screen = newScreen;
}

void Button::setContainer(SDL_Rect newContainer){
    this->container = newContainer;
}

void Button::setColor(SDL_Color newColor){
    this->color = newColor;
}


bool Button::isClicked(SDL_Event * event){
  
    Coord mouse;

    //loads the two intgers with the position in pixels of the mouse
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

void Button::drawToRender(){
    SDL_SetRenderDrawColor(getScreen()->getRender(), getColor().r, getColor().g, getColor().b, getColor().a);
    SDL_RenderFillRect(getScreen()->getRender(), &this->container);
    
    //If there is an image, load it first so that if there is text, it is shown above it
    if(image != nullptr){
        this->image->CopyToRender();
    }

    //also add the text if there is one
    if(font != nullptr){
        this->font->setCoords(this->container.x, this->container.y);
        this->font->drawTextToRender();
    }
}