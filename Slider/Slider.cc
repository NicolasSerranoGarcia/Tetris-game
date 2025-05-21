#include "Slider.h"

#include <iostream>

Slider::Slider(){
}

Slider::Slider(Button button, int minY, int maxY, SDL_Color pressedColor){
    slider = button;
    this->minY = minY;
    this->maxY = maxY;
    this->pressedColor = pressedColor;
}

// Slider::Slider(SDL_Rect rect, SDL_Color pressedColor, SDL_Color defaultColor){}

Button Slider::getSliderButton() {
    return slider;
}

int Slider::getMinY() {
    return minY;
}

int Slider::getMaxY() {
    return maxY;
}

bool Slider::getClickedNow(){
    return isClickedNow;
}

SDL_Color Slider::getPressedColor() {
    return pressedColor;
}

bool Slider::getVisibility(){
    return isVisible;
}


void Slider::setClickedNow(bool state){
    isClickedNow = state;
}

void Slider::setSliderButton(Button newSlider) {
    slider = newSlider;
}

void Slider::setSliderY(int y){

    SDL_Rect rect = slider.getContainer();
    rect.y = y;
    slider.setContainer(rect);
}

void Slider::setMinY(int y) {
    minY = y;
}

void Slider::setMaxY(int y) {
    maxY = y;
}

void Slider::setPressedColor(SDL_Color color) {
    pressedColor = color;
}

void Slider::setVisibility(bool v){
    isVisible = v;
}


void Slider::render(){
    if(isClickedNow){
        slider.setColor(pressedColor);
        slider.drawToRender();
    } else{
        SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);
        SDL_Color color = slider.getColor();
        color.a = 50;
        slider.setColor(color);
        slider.drawToRender();
        SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);
    }
}

bool Slider::isClicked(SDL_Event *event){
    return slider.isClicked(&*event);
}

void Slider::RenderAsCircle(){
    if(slider.getContainer().h != slider.getContainer().w){
        std::cout << "Not possible" << std::endl;
        return;
    }

    if(isClickedNow){
        SDL_SetRenderDrawColor(mainScreen.getRender(), pressedColor.r, pressedColor.g, pressedColor.b, pressedColor.a);
        SDL_RenderFillCircle(mainScreen.getRender(), slider.getContainer().x + slider.getContainer().w/2, slider.getContainer().y + slider.getContainer().h/2, slider.getContainer().w/2);
    
        SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        SDL_RenderDrawCircle(mainScreen.getRender(), slider.getContainer().x + slider.getContainer().w/2, slider.getContainer().y + slider.getContainer().h/2, slider.getContainer().w/2);
    } else{
        SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);
        SDL_Color color = slider.getColor();
        color.a = 255;

        SDL_SetRenderDrawColor(mainScreen.getRender(), color.r, color.g, color.b, color.a);
        SDL_RenderFillCircle(mainScreen.getRender(), slider.getContainer().x + slider.getContainer().w/2, slider.getContainer().y + slider.getContainer().h/2, slider.getContainer().w/2);
        
        SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        SDL_RenderDrawCircle(mainScreen.getRender(), slider.getContainer().x + slider.getContainer().w/2, slider.getContainer().y + slider.getContainer().h/2, slider.getContainer().w/2);


        SDL_SetRenderDrawBlendMode(mainScreen.getRender(), SDL_BLENDMODE_BLEND);
    }
}