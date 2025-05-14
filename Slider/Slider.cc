#include "Slider.h"

Slider::Slider(){
}

Slider::Slider(Button button, int minY, int maxY, SDL_Color pressedColor){
    slider = button;
    this->minY = minY;
    this->maxY = maxY;
    this->pressedColor = pressedColor;
}

Slider::Slider(SDL_Rect rect, SDL_Color pressedColor, SDL_Color defaultColor){
}

Button Slider::getSliderButton() {
    return slider;
}

int Slider::getMinY() {
    return minY;
}

int Slider::getMaxY() {
    return maxY;
}

SDL_Color Slider::getPressedColor() {
    return pressedColor;
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